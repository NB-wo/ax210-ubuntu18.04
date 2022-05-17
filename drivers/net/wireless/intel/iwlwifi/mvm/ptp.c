// SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2021 - 2022 Intel Corporation
 */

#include "mvm.h"
#include "iwl-debug.h"
#include <linux/timekeeping.h>

static int
iwl_mvm_get_crosstimestamp_fw(struct iwl_mvm *mvm, u32 *gp2, u64 *sys_time)
{
	struct iwl_synced_time_cmd synced_time_cmd = {
		.operation = cpu_to_le32(IWL_SYNCED_TIME_OPERATION_READ_BOTH)
	};
	struct iwl_host_cmd cmd = {
		.id = WNM_PLATFORM_PTM_REQUEST_CMD,
		.flags = CMD_WANT_SKB,
		.data[0] = &synced_time_cmd,
		.len[0] = sizeof(synced_time_cmd),
	};
	struct iwl_synced_time_rsp *resp;
	struct iwl_rx_packet *pkt;
	int ret;
	u64 gp2_10ns;

	mutex_lock(&mvm->mutex);
	ret = iwl_mvm_send_cmd(mvm, &cmd);
	if (ret)
		goto out;

	pkt = cmd.resp_pkt;

	if (iwl_rx_packet_payload_len(pkt) != sizeof(*resp)) {
		IWL_ERR(mvm, "PTP: Invalid command response\n");
		ret = -EIO;
		iwl_free_resp(&cmd);
		goto out;
	}

	resp = (void *)pkt->data;

	gp2_10ns = (u64)le32_to_cpu(resp->gp2_timestamp_hi) << 32 |
		le32_to_cpu(resp->gp2_timestamp_lo);
	*gp2 = gp2_10ns / 100;

	*sys_time = (u64)le32_to_cpu(resp->platform_timestamp_hi) << 32 |
		le32_to_cpu(resp->platform_timestamp_lo);
 out:
	mutex_unlock(&mvm->mutex);
	return ret;
}

static int
iwl_mvm_phc_get_crosstimestamp(struct ptp_clock_info *ptp,
			       struct system_device_crosststamp *xtstamp)
{
	struct iwl_mvm *mvm = container_of(ptp, struct iwl_mvm,
					   ptp_data.ptp_clock_info);
	/* Raw value read from GP2 register in usec */
	u32 gp2;
	/* GP2 value in ns*/
	s64 gp2_ns;
	/* System (wall) time */
	ktime_t sys_time;

	memset(xtstamp, 0, sizeof(struct system_device_crosststamp));

	if (!mvm->ptp_data.ptp_clock) {
		IWL_ERR(mvm, "No PHC clock registered\n");
		return -ENODEV;
	}

	if (fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_SYNCED_TIME)) {
		int ret = iwl_mvm_get_crosstimestamp_fw(mvm, &gp2, &sys_time);

		if (ret)
			return ret;
	} else {
		iwl_mvm_get_sync_time(mvm, CLOCK_REALTIME, &gp2, NULL,
				      &sys_time);
	}

	/* Check if GP2 has wrapped */
	if (mvm->ptp_data.last_gp2 > gp2)
		gp2_ns = (gp2 + 0x100000000L) * 1000L;
	else
		gp2_ns = gp2 * 1000L;

	IWL_INFO(mvm, "Got Sync Time: GP2:%u, last_GP2: %u, GP2_ns: %lld, sys_time: %lld\n",
		 gp2, mvm->ptp_data.last_gp2, gp2_ns, (s64)sys_time);

	/* System monotonic raw time is not used */
	xtstamp->device = (ktime_t)gp2_ns;
	xtstamp->sys_realtime = sys_time;
	mvm->ptp_data.last_gp2 = gp2;

	return 0;
}

/*
 * iwl_mvm_ptp_init - initialize PTP for devices which support it.
 * @mvm: internal mvm structure, see &struct iwl_mvm.
 *
 * Performs the required steps for enabling PTP support.
 */
void iwl_mvm_ptp_init(struct iwl_mvm *mvm)
{
	/* Warn if the interface already has a ptp_clock defined */
	if (WARN_ON(mvm->ptp_data.ptp_clock))
		return;

	mvm->ptp_data.ptp_clock_info.owner = THIS_MODULE;
	mvm->ptp_data.ptp_clock_info.max_adj = 0;
	mvm->ptp_data.ptp_clock_info.n_alarm = 0;
	mvm->ptp_data.ptp_clock_info.n_ext_ts = 0;
	mvm->ptp_data.ptp_clock_info.n_per_out = 0;
	mvm->ptp_data.ptp_clock_info.n_pins = 0;
	mvm->ptp_data.ptp_clock_info.pps = 0;
	mvm->ptp_data.ptp_clock_info.adjfreq = NULL;
	mvm->ptp_data.ptp_clock_info.adjtime = NULL;
	mvm->ptp_data.ptp_clock_info.getcrosststamp =
					iwl_mvm_phc_get_crosstimestamp;
	mvm->ptp_data.ptp_clock_info.enable = NULL;
	mvm->ptp_data.ptp_clock_info.verify = NULL;
	mvm->ptp_data.last_gp2 = 0;

	/* Give a short 'friendly name' to identify the PHC clock */
	snprintf(mvm->ptp_data.ptp_clock_info.name,
		 sizeof(mvm->ptp_data.ptp_clock_info.name),
		 "%s", "iwlwifi-PTP");

	mvm->ptp_data.ptp_clock =
		ptp_clock_register(&mvm->ptp_data.ptp_clock_info, mvm->dev);

	if (IS_ERR(mvm->ptp_data.ptp_clock)) {
		IWL_ERR(mvm, "Failed to register PHC clock (%ld)\n",
			PTR_ERR(mvm->ptp_data.ptp_clock));
		mvm->ptp_data.ptp_clock = NULL;
	} else if (mvm->ptp_data.ptp_clock) {
		IWL_INFO(mvm, "Registered PHC clock: %s, with index: %d\n",
			 mvm->ptp_data.ptp_clock_info.name,
			 ptp_clock_index(mvm->ptp_data.ptp_clock));
	}
}

/*
 * iwl_mvm_ptp_remove - disable PTP device.
 * @mvm: internal mvm structure, see &struct iwl_mvm.
 *
 * Disable PTP support.
 */
void iwl_mvm_ptp_remove(struct iwl_mvm *mvm)
{
	if (mvm->ptp_data.ptp_clock) {
		IWL_INFO(mvm, "Unregistering PHC clock: %s, with index: %d\n",
			 mvm->ptp_data.ptp_clock_info.name,
			 ptp_clock_index(mvm->ptp_data.ptp_clock));

		ptp_clock_unregister(mvm->ptp_data.ptp_clock);
		mvm->ptp_data.ptp_clock = NULL;
		memset(&mvm->ptp_data.ptp_clock_info, 0,
		       sizeof(mvm->ptp_data.ptp_clock_info));
		mvm->ptp_data.last_gp2 = 0;
	}
}
