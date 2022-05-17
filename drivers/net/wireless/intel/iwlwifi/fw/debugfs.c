// SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2014, 2018-2022 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#include "api/commands.h"
#include "debugfs.h"
#include "dbg.h"
#include <linux/seq_file.h>
#ifdef CPTCFG_IWLWIFI_DHC_PRIVATE
#include "api/dhc.h"
#include "dhc-priv.h"
#endif
#include "api/rs.h"

#define FWRT_DEBUGFS_OPEN_WRAPPER(name, buflen, argtype)		\
struct dbgfs_##name##_data {						\
	argtype *arg;							\
	bool read_done;							\
	ssize_t rlen;							\
	char rbuf[buflen];						\
};									\
static int _iwl_dbgfs_##name##_open(struct inode *inode,		\
				    struct file *file)			\
{									\
	struct dbgfs_##name##_data *data;				\
									\
	data = kzalloc(sizeof(*data), GFP_KERNEL);			\
	if (!data)							\
		return -ENOMEM;						\
									\
	data->read_done = false;					\
	data->arg = inode->i_private;					\
	file->private_data = data;					\
									\
	return 0;							\
}

#define FWRT_DEBUGFS_READ_WRAPPER(name)					\
static ssize_t _iwl_dbgfs_##name##_read(struct file *file,		\
					char __user *user_buf,		\
					size_t count, loff_t *ppos)	\
{									\
	struct dbgfs_##name##_data *data = file->private_data;		\
									\
	if (!data->read_done) {						\
		data->read_done = true;					\
		data->rlen = iwl_dbgfs_##name##_read(data->arg,		\
						     sizeof(data->rbuf),\
						     data->rbuf);	\
	}								\
									\
	if (data->rlen < 0)						\
		return data->rlen;					\
	return simple_read_from_buffer(user_buf, count, ppos,		\
				       data->rbuf, data->rlen);		\
}

static int _iwl_dbgfs_release(struct inode *inode, struct file *file)
{
	kfree(file->private_data);

	return 0;
}

#define _FWRT_DEBUGFS_READ_FILE_OPS(name, buflen, argtype)		\
FWRT_DEBUGFS_OPEN_WRAPPER(name, buflen, argtype)			\
FWRT_DEBUGFS_READ_WRAPPER(name)						\
static const struct file_operations iwl_dbgfs_##name##_ops = {		\
	.read = _iwl_dbgfs_##name##_read,				\
	.open = _iwl_dbgfs_##name##_open,				\
	.llseek = generic_file_llseek,					\
	.release = _iwl_dbgfs_release,					\
}

#define FWRT_DEBUGFS_WRITE_WRAPPER(name, buflen, argtype)		\
static ssize_t _iwl_dbgfs_##name##_write(struct file *file,		\
					 const char __user *user_buf,	\
					 size_t count, loff_t *ppos)	\
{									\
	argtype *arg =							\
		((struct dbgfs_##name##_data *)file->private_data)->arg;\
	char buf[buflen] = {};						\
	size_t buf_size = min(count, sizeof(buf) -  1);			\
									\
	if (copy_from_user(buf, user_buf, buf_size))			\
		return -EFAULT;						\
									\
	return iwl_dbgfs_##name##_write(arg, buf, buf_size);		\
}

#define _FWRT_DEBUGFS_READ_WRITE_FILE_OPS(name, buflen, argtype)	\
FWRT_DEBUGFS_OPEN_WRAPPER(name, buflen, argtype)			\
FWRT_DEBUGFS_WRITE_WRAPPER(name, buflen, argtype)			\
FWRT_DEBUGFS_READ_WRAPPER(name)						\
static const struct file_operations iwl_dbgfs_##name##_ops = {		\
	.write = _iwl_dbgfs_##name##_write,				\
	.read = _iwl_dbgfs_##name##_read,				\
	.open = _iwl_dbgfs_##name##_open,				\
	.llseek = generic_file_llseek,					\
	.release = _iwl_dbgfs_release,					\
}

#define _FWRT_DEBUGFS_WRITE_FILE_OPS(name, buflen, argtype)		\
FWRT_DEBUGFS_OPEN_WRAPPER(name, buflen, argtype)			\
FWRT_DEBUGFS_WRITE_WRAPPER(name, buflen, argtype)			\
static const struct file_operations iwl_dbgfs_##name##_ops = {		\
	.write = _iwl_dbgfs_##name##_write,				\
	.open = _iwl_dbgfs_##name##_open,				\
	.llseek = generic_file_llseek,					\
	.release = _iwl_dbgfs_release,					\
}

#define FWRT_DEBUGFS_READ_FILE_OPS(name, bufsz)				\
	_FWRT_DEBUGFS_READ_FILE_OPS(name, bufsz, struct iwl_fw_runtime)

#define FWRT_DEBUGFS_WRITE_FILE_OPS(name, bufsz)			\
	_FWRT_DEBUGFS_WRITE_FILE_OPS(name, bufsz, struct iwl_fw_runtime)

#define FWRT_DEBUGFS_READ_WRITE_FILE_OPS(name, bufsz)			\
	_FWRT_DEBUGFS_READ_WRITE_FILE_OPS(name, bufsz, struct iwl_fw_runtime)

#define FWRT_DEBUGFS_ADD_FILE_ALIAS(alias, name, parent, mode) do {	\
	debugfs_create_file(alias, mode, parent, fwrt,			\
			    &iwl_dbgfs_##name##_ops);			\
	} while (0)
#define FWRT_DEBUGFS_ADD_FILE(name, parent, mode) \
	FWRT_DEBUGFS_ADD_FILE_ALIAS(#name, name, parent, mode)

static int iwl_fw_send_timestamp_marker_cmd(struct iwl_fw_runtime *fwrt)
{
	struct iwl_mvm_marker marker = {
		.dw_len = sizeof(struct iwl_mvm_marker) / 4,
		.marker_id = MARKER_ID_SYNC_CLOCK,

		/* the real timestamp is taken from the ftrace clock
		 * this is for finding the match between fw and kernel logs
		 */
		.timestamp = cpu_to_le64(fwrt->timestamp.seq++),
	};

	struct iwl_host_cmd hcmd = {
		.id = MARKER_CMD,
		.flags = CMD_ASYNC,
		.data[0] = &marker,
		.len[0] = sizeof(marker),
	};

	return iwl_trans_send_cmd(fwrt->trans, &hcmd);
}

static int iwl_dbgfs_enabled_severities_write(struct iwl_fw_runtime *fwrt,
					      char *buf, size_t count)
{
	struct iwl_dbg_host_event_cfg_cmd event_cfg;
	struct iwl_host_cmd hcmd = {
		.id = WIDE_ID(DEBUG_GROUP, HOST_EVENT_CFG),
		.flags = CMD_ASYNC,
		.data[0] = &event_cfg,
		.len[0] = sizeof(event_cfg),
	};
	u32 enabled_severities;
	int ret = kstrtou32(buf, 10, &enabled_severities);

	if (ret < 0)
		return ret;

	event_cfg.enabled_severities = cpu_to_le32(enabled_severities);

	ret = iwl_trans_send_cmd(fwrt->trans, &hcmd);
	IWL_INFO(fwrt,
		 "sent host event cfg with enabled_severities: %u, ret: %d\n",
		 enabled_severities, ret);

	return ret ?: count;
}

FWRT_DEBUGFS_WRITE_FILE_OPS(enabled_severities, 16);

static void iwl_fw_timestamp_marker_wk(struct work_struct *work)
{
	int ret;
	struct iwl_fw_runtime *fwrt =
		container_of(work, struct iwl_fw_runtime, timestamp.wk.work);
	unsigned long delay = fwrt->timestamp.delay;

	ret = iwl_fw_send_timestamp_marker_cmd(fwrt);
	if (!ret && delay)
		schedule_delayed_work(&fwrt->timestamp.wk,
				      round_jiffies_relative(delay));
	else
		IWL_INFO(fwrt,
			 "stopping timestamp_marker, ret: %d, delay: %u\n",
			 ret, jiffies_to_msecs(delay) / 1000);
}

void iwl_fw_trigger_timestamp(struct iwl_fw_runtime *fwrt, u32 delay)
{
	IWL_INFO(fwrt,
		 "starting timestamp_marker trigger with delay: %us\n",
		 delay);

	iwl_fw_cancel_timestamp(fwrt);

	fwrt->timestamp.delay = msecs_to_jiffies(delay * 1000);

	schedule_delayed_work(&fwrt->timestamp.wk,
			      round_jiffies_relative(fwrt->timestamp.delay));
}

static ssize_t iwl_dbgfs_timestamp_marker_write(struct iwl_fw_runtime *fwrt,
						char *buf, size_t count)
{
	int ret;
	u32 delay;

	ret = kstrtou32(buf, 10, &delay);
	if (ret < 0)
		return ret;

	iwl_fw_trigger_timestamp(fwrt, delay);

	return count;
}

static ssize_t iwl_dbgfs_timestamp_marker_read(struct iwl_fw_runtime *fwrt,
					       size_t size, char *buf)
{
	u32 delay_secs = jiffies_to_msecs(fwrt->timestamp.delay) / 1000;

	return scnprintf(buf, size, "%d\n", delay_secs);
}

FWRT_DEBUGFS_READ_WRITE_FILE_OPS(timestamp_marker, 16);

struct hcmd_write_data {
	__be32 cmd_id;
	__be32 flags;
	__be16 length;
	u8 data[];
} __packed;

static ssize_t iwl_dbgfs_send_hcmd_write(struct iwl_fw_runtime *fwrt, char *buf,
					 size_t count)
{
	size_t header_size = (sizeof(u32) * 2 + sizeof(u16)) * 2;
	size_t data_size = (count - 1) / 2;
	int ret;
	struct hcmd_write_data *data;
	struct iwl_host_cmd hcmd = {
		.len = { 0, },
		.data = { NULL, },
	};

	if (!iwl_trans_fw_running(fwrt->trans))
		return -EIO;

	if (count < header_size + 1 || count > 1024 * 4)
		return -EINVAL;

	data = kmalloc(data_size, GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	ret = hex2bin((u8 *)data, buf, data_size);
	if (ret)
		goto out;

	hcmd.id = be32_to_cpu(data->cmd_id);
	hcmd.flags = be32_to_cpu(data->flags);
	hcmd.len[0] = be16_to_cpu(data->length);
	hcmd.data[0] = data->data;

	if (count != header_size + hcmd.len[0] * 2 + 1) {
		IWL_ERR(fwrt,
			"host command data size does not match header length\n");
		ret = -EINVAL;
		goto out;
	}

	if (fwrt->ops && fwrt->ops->send_hcmd)
		ret = fwrt->ops->send_hcmd(fwrt->ops_ctx, &hcmd);
	else
		ret = -EPERM;

	if (ret < 0)
		goto out;

	if (hcmd.flags & CMD_WANT_SKB)
		iwl_free_resp(&hcmd);
out:
	kfree(data);
	return ret ?: count;
}

FWRT_DEBUGFS_WRITE_FILE_OPS(send_hcmd, 512);

#ifdef CPTCFG_IWLWIFI_DHC_PRIVATE
struct iwl_dhc_write_data {
	__be32 length;
	__be32 index_and_mask;
	__be32 data[0];
} __packed;

static ssize_t iwl_dbgfs_send_dhc_write(struct iwl_fw_runtime *fwrt,
					char *buf, size_t count)
{
	int ret, i;
	struct iwl_dhc_write_data *data;
	u32 length;
	size_t header_size = sizeof(u32) * 2 * 2;
	size_t data_size = (count - 1) / 2, cmd_size;
	struct iwl_dhc_cmd *dhc_cmd = NULL;
	struct iwl_host_cmd hcmd = {
		.id = WIDE_ID(LEGACY_GROUP, DEBUG_HOST_COMMAND),
		.flags = CMD_ASYNC,
		.len = { 0, },
		.data = { NULL, },
	};

	if (!iwl_trans_fw_running(fwrt->trans))
		return -EIO;

	if (count < header_size + 1 || count > 1024 * 4)
		return -EINVAL;

	data = kmalloc(data_size, GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	ret = hex2bin((u8 *)data, buf, data_size);
	if (ret)
		goto out;

	length = be32_to_cpu(data->length);

	if (count != header_size + sizeof(u32) * length * 2 + 1) {
		IWL_ERR(fwrt, "DHC data size does not match length header\n");
		ret = -EINVAL;
		goto out;
	}

	cmd_size = sizeof(*dhc_cmd) + length * sizeof(u32);
	dhc_cmd = kzalloc(cmd_size, GFP_KERNEL);
	if (!dhc_cmd) {
		ret = -ENOMEM;
		goto out;
	}

	dhc_cmd->length = cpu_to_le32(length);
	dhc_cmd->index_and_mask =
		cpu_to_le32(be32_to_cpu(data->index_and_mask));
	for (i = 0; i < length; i++)
		dhc_cmd->data[i] =
			cpu_to_le32(be32_to_cpu(data->data[i]));

	hcmd.len[0] = cmd_size;
	hcmd.data[0] = dhc_cmd;

	if (fwrt->ops && fwrt->ops->send_hcmd)
		ret = fwrt->ops->send_hcmd(fwrt->ops_ctx, &hcmd);
	else
		ret = -EPERM;
out:
	kfree(dhc_cmd);
	kfree(data);
	return ret ?: count;
}

FWRT_DEBUGFS_WRITE_FILE_OPS(send_dhc, 512);

struct iwl_dhc_tlc_whole_cmd {
	struct iwl_dhc_cmd dhc;
	struct iwl_dhc_tlc_cmd tlc_data;
} __packed;

static void iwl_fw_build_dhc_tlc_cmd(struct iwl_dhc_tlc_whole_cmd *cmd,
				     enum iwl_tlc_debug_types type, u32 data)
{
	cmd->dhc.length = cpu_to_le32(sizeof(cmd->tlc_data) >> 2);
	cmd->dhc.index_and_mask = cpu_to_le32(DHC_TABLE_INTEGRATION |
					  DHC_TARGET_UMAC |
					  DHC_INTEGRATION_TLC_DEBUG_CONFIG);

	cmd->tlc_data.type = cpu_to_le32(type);
	cmd->tlc_data.data[0] = cpu_to_le32(data);
}

static ssize_t iwl_dbgfs_tpc_enable_write(struct iwl_fw_runtime *fwrt,
					  char *buf, size_t count)
{
	struct iwl_dhc_tlc_whole_cmd dhc_cmd = {};
	struct iwl_host_cmd hcmd = {
		.id = WIDE_ID(IWL_ALWAYS_LONG_GROUP, DEBUG_HOST_COMMAND),
		.data[0] = &dhc_cmd,
		.len[0] = sizeof(dhc_cmd),
	};
	bool enabled;
	int ret;

	ret = kstrtobool(buf, &enabled);
	iwl_fw_build_dhc_tlc_cmd(&dhc_cmd, IWL_TLC_DEBUG_TPC_ENABLED,
				 enabled);

	ret = iwl_trans_send_cmd(fwrt->trans, &hcmd);
	if (ret) {
		IWL_ERR(fwrt, "Failed to send TLC Debug command: %d\n", ret);
		return ret;
	}

	fwrt->tpc_enabled = enabled;

	return count;
}

static ssize_t iwl_dbgfs_tpc_enable_read(struct iwl_fw_runtime *fwrt,
					 size_t size, char *buf)
{
	return scnprintf(buf, size, "tpc is currently %s\n",
			 fwrt->tpc_enabled ? "enabled" : "disabled");
}

FWRT_DEBUGFS_READ_WRITE_FILE_OPS(tpc_enable, 30);

static ssize_t iwl_dbgfs_tpc_stats_read(struct iwl_fw_runtime *fwrt,
					size_t size, char *buf)
{
	struct iwl_dhc_tlc_whole_cmd dhc_cmd = {};
	struct iwl_host_cmd hcmd = {
		.id = WIDE_ID(IWL_ALWAYS_LONG_GROUP, DEBUG_HOST_COMMAND),
		.flags = CMD_WANT_SKB,
		.data[0] = &dhc_cmd,
		.len[0] = sizeof(dhc_cmd),
	};
	struct iwl_tpc_stats *stats;
	unsigned int resp_len = 0;
	u32 status;
	int ret = 0;

	iwl_fw_build_dhc_tlc_cmd(&dhc_cmd, IWL_TLC_DEBUG_TPC_STATS, 0);

	ret = iwl_trans_send_cmd(fwrt->trans, &hcmd);
	if (ret) {
		IWL_ERR(fwrt, "Failed to send TLC Debug command: %d\n", ret);
		goto err;
	}

	if (!hcmd.resp_pkt) {
		IWL_ERR(fwrt,
			"Response expected\n");
		goto err;
	}

	status = iwl_dhc_resp_status(fwrt->fw, hcmd.resp_pkt);
	if (status != 1) {
		IWL_ERR(fwrt, "response status is not success: %d\n", status);
		ret = -EINVAL;
		goto err;
	}

	stats = iwl_dhc_resp_data(fwrt->fw, hcmd.resp_pkt, &resp_len);
	if (IS_ERR(stats) || resp_len != sizeof(*stats)) {
		IWL_ERR(fwrt,
			"Invalid size for TPC stats request response (%u instead of %zd)\n",
			resp_len, sizeof(*stats));
		ret = -EINVAL;
		goto err;
	}

	return scnprintf(buf, size,
			 "tpc stats: no-tpc %u, step1 %u, step2 %u, step3 %u, step4 %u, step5 %u\n",
			 le32_to_cpu(stats->no_tpc),
			 le32_to_cpu(stats->step[0]),
			 le32_to_cpu(stats->step[1]),
			 le32_to_cpu(stats->step[2]),
			 le32_to_cpu(stats->step[3]),
			 le32_to_cpu(stats->step[4]));

err:
	return ret ?: -EIO;
}

FWRT_DEBUGFS_READ_FILE_OPS(tpc_stats, 150);

#define PS_REPORT_FIELDS \
		PS_FIELD(le32, total_sleep_counter) \
		PS_FIELD(le32, total_sleep_duration) \
		PS_FIELD(le32, report_duration) \
		PS_FIELD(le32, total_missed_beacon_counter) \
		PS_FIELD(le32, missed_3_consecutive_beacon_count) \
		PS_FIELD(le32, ps_flags) \
		PS_FIELD(le32, phy_inactive_duration) \
		PS_FIELD(le32, mac_ctdp_sum) \
		PS_FIELD(le32, ppm_offset_vs_ap_sum) \
		PS_FIELD(le32, deep_sleep_duration) \
		PS_FIELD(le32, received_beacon_counter) \
		PS_FIELD(le16, bcon_in_lprx_counter) \
		PS_FIELD(le16, bcon_abort_counter) \
		PS_FIELD(le16, multicast_indication_tim_counter) \
		PS_FIELD(le16, missed_multicast_counter) \
		PS_FIELD(le32, misbehave_counter) \
		PS_FIELD(le32, max_sleep_duration) \
		PS_FIELD(le32, total_page_faults) \
		PS_FIELD(le32, sleep_abort_count) \
		PS_FIELD(le32, max_active_duration) \
		PS_FIELD(le16, max_pu_duration) \
		PS_FIELD(le16, max_pd_duration) \
		PS_FIELD(le16, max_phy_pu_duration[0]) \
		PS_FIELD(le16, max_phy_pu_duration[1]) \
		PS_FIELD(le16, max_phy_pd_duration[0]) \
		PS_FIELD(le16, max_phy_pd_duration[1]) \
		PS_FIELD(le32, ltr.tx_active_time) \
		PS_FIELD(le32, ltr.rx_active_time) \
		PS_FIELD(le32, ltr.rx_listen_time) \
		PS_FIELD(le32, ltr.power_save_time) \
		PS_FIELD(le32, ltr.total_time) \
		PS_FIELD(le32, ps_duration[0]) \
		PS_FIELD(le32, ps_duration[1]) \
		PS_FIELD(le32, ps_duration[2])

static ssize_t iwl_dbgfs_ps_report_read(struct iwl_fw_runtime *fwrt,
					size_t size, char *buf, int mac_mask)
{
	__le32 cmd_data;

	struct iwl_dhc_cmd cmd = {
		.length = cpu_to_le32(1),
		.index_and_mask = cpu_to_le32(DHC_TABLE_AUTOMATION |
			mac_mask |
			DHC_AUTO_UMAC_REPORT_POWER_STATISTICS),
	};

	struct iwl_host_cmd hcmd = {
		.id = WIDE_ID(LEGACY_GROUP, DEBUG_HOST_COMMAND),
		.flags = CMD_WANT_SKB,
		.data = { &cmd, &cmd_data},
		.len = { sizeof(cmd), sizeof(cmd_data) },
	};
	struct iwl_ps_report *ps_report;
	int ret = 0;
	u32 status;
	unsigned int report_size = 0;

	ret = iwl_trans_send_cmd(fwrt->trans, &hcmd);
	if (ret) {
		IWL_ERR(fwrt,
			"Failed to send power-save report command: %d\n", ret);
		goto err;
	}

	if (!hcmd.resp_pkt) {
		IWL_ERR(fwrt,
			"Response expected\n");
		goto err;
	}

	status = iwl_dhc_resp_status(fwrt->fw, hcmd.resp_pkt);
	if (status != 1) {
		IWL_ERR(fwrt, "response status is not success: %d\n", status);
		ret = -EINVAL;
		goto err;
	}

	ps_report = iwl_dhc_resp_data(fwrt->fw, hcmd.resp_pkt, &report_size);
	if (IS_ERR(ps_report))
		goto err;

	ret = scnprintf(buf, size, "power-save report\n");

#define PS_FIELD(_t, _f)							\
	ret += ({ BUILD_BUG_ON(sizeof(ps_report->_f) != sizeof(__ ##_t ));	\
			offsetofend(typeof(*ps_report), _f) <= report_size ?	\
				scnprintf(buf + ret, size - ret, #_f " %u\n",	\
					  _t## _to_cpu(ps_report->_f)) :	\
				sizeof(__ ##_t );});

	PS_REPORT_FIELDS
#undef PS_FIELD

	return ret;

err:
	return ret ?: -EIO;
}

static ssize_t iwl_dbgfs_ps_report_umac_read
				(struct iwl_fw_runtime *fwrt,
				size_t size,
				char *buf)
{
	return iwl_dbgfs_ps_report_read(fwrt, size, buf, DHC_TARGET_UMAC);
}

#define PS_FIELD(x, y) + 1
/* We set the size of the ps_report_umac file to be according to the ps report size.
 10 -> indicates the maximun char that can be added by 4 byte int converted to string
 20 -> indicates the avarege chars in a field*/
FWRT_DEBUGFS_READ_FILE_OPS(ps_report_umac,
			   (PS_REPORT_FIELDS) * (10 + 20));
#undef PS_FIELD

static ssize_t iwl_dbgfs_send_ps_test_write(struct iwl_fw_runtime *fwrt,
					    struct iwl_ps_test_req *ps_test_req)
{
	int ret_val = 0;

	struct iwl_dhc_cmd *dhc_cmd;
	struct iwl_host_cmd hcmd = {
		.id = WIDE_ID(LEGACY_GROUP, DEBUG_HOST_COMMAND),
		.flags = CMD_WANT_SKB,
	};
	/* allocate the maximal amount of memory that can be sent */
	dhc_cmd = kzalloc(sizeof(*dhc_cmd) + sizeof(*ps_test_req),
			  GFP_KERNEL);
	if (!dhc_cmd)
		return -ENOMEM;

	dhc_cmd->length = cpu_to_le32(sizeof(*ps_test_req) >> 2);
	dhc_cmd->index_and_mask =
			cpu_to_le32(DHC_AUTO_UMAC_POWER_SAVE_TESTS_REQ |
				    DHC_TABLE_AUTOMATION |
				    DHC_TARGET_UMAC);

	memcpy((void *)dhc_cmd->data,
	       (void *)ps_test_req,
	       sizeof(*ps_test_req));

	hcmd.len[0] = sizeof(*ps_test_req) + sizeof(*dhc_cmd);
	hcmd.data[0] = dhc_cmd;

	ret_val = iwl_trans_send_cmd(fwrt->trans, &hcmd);

	if (ret_val) {
		IWL_ERR(fwrt,
			"Failed to send power-save tests request command: %d\n", ret_val);
		goto err;
	}

	return ret_val;

err:
	return ret_val ?: -EIO;
}

static ssize_t iwl_dbgfs_ps_test_req_write(struct iwl_fw_runtime *fwrt,
					   char *buf, size_t count)
{
	int ret;
	struct iwl_ps_test_req cmd_data;

	if (sscanf(buf, "%x %x %x %x %x %x",
		   &cmd_data.flags,
		   &cmd_data.test_case,
		   &cmd_data.test_param1,
		   &cmd_data.test_param2,
		   &cmd_data.test_param3,
		   &cmd_data.test_param4) != 6)
		return -EINVAL;

	ret = iwl_dbgfs_send_ps_test_write(fwrt, &cmd_data);

	return ret ?: count;
}

FWRT_DEBUGFS_WRITE_FILE_OPS(ps_test_req, 44);

static ssize_t iwl_dbgfs_ps_test_response_read
				(struct iwl_fw_runtime *fwrt,
				size_t size, char *buf, int mac_mask)
{
	__le32 cmd_data;

	int ret = 0;
	u32 status;
	struct iwl_ps_test_res *ps_test_res;
	unsigned int rsp_size = 0;

	struct iwl_dhc_cmd cmd = {
		.length = cpu_to_le32(1),
		.index_and_mask = cpu_to_le32(DHC_TABLE_AUTOMATION |
			mac_mask |
			DHC_AUTO_UMAC_POWER_SAVE_TESTS_RES),
	};

	struct iwl_host_cmd hcmd = {
		.id = WIDE_ID(LEGACY_GROUP, DEBUG_HOST_COMMAND),
		.flags = CMD_WANT_SKB,
		.data = { &cmd, &cmd_data},
		.len = { sizeof(cmd), sizeof(cmd_data) },
	};

	ret = iwl_trans_send_cmd(fwrt->trans, &hcmd);
	if (ret) {
		IWL_ERR(fwrt,
			"Failed to send power-save test response command: %d\n", ret);
		goto err;
	}

	if (!hcmd.resp_pkt) {
		IWL_ERR(fwrt,
			"Response expected\n");
		goto err;
	}

	status = iwl_dhc_resp_status(fwrt->fw, hcmd.resp_pkt);
	if (status != 1) {
		IWL_ERR(fwrt, "response status is not success: %d\n", status);
		ret = -EINVAL;
		goto err;
	}

	ps_test_res = iwl_dhc_resp_data(fwrt->fw, hcmd.resp_pkt, &rsp_size);
	if (IS_ERR(ps_test_res) || rsp_size > sizeof(*ps_test_res)) {
		IWL_ERR(fwrt,
			"ps test response size is wrong! expected at most %zd, received %d\n",
			sizeof(*ps_test_res), rsp_size);
		goto err;
	}

	ret = scnprintf(buf, size, "power-save test response\n");

#define PRINT_PS_TEST_RSP_32(_f)						\
	({ BUILD_BUG_ON(sizeof(ps_test_res->_f) != 4);			\
	   offsetofend(typeof(*ps_test_res), _f) <= rsp_size ?	\
			   scnprintf(buf + ret, size - ret, #_f " %u\n",	\
				 le32_to_cpu(ps_test_res->_f)) :		\
			   0; })

	ret += PRINT_PS_TEST_RSP_32(test_res1);
	ret += PRINT_PS_TEST_RSP_32(test_res2);
	ret += PRINT_PS_TEST_RSP_32(test_res3);
	ret += PRINT_PS_TEST_RSP_32(test_res4);

#undef PRINT_PS_TEST_RSP_32

	return ret;

err:
	return ret ?: -EIO;
}

static ssize_t iwl_dbgfs_ps_test_res_read
				(struct iwl_fw_runtime *fwrt,
				size_t size,
				char *buf)
{
	return iwl_dbgfs_ps_test_response_read(fwrt, size, buf, DHC_TARGET_UMAC);
}

FWRT_DEBUGFS_READ_FILE_OPS(ps_test_res, 80);

#endif

static ssize_t iwl_dbgfs_fw_dbg_domain_read(struct iwl_fw_runtime *fwrt,
					    size_t size, char *buf)
{
	return scnprintf(buf, size, "0x%08x\n",
			 fwrt->trans->dbg.domains_bitmap);
}

FWRT_DEBUGFS_READ_FILE_OPS(fw_dbg_domain, 20);

struct iwl_dbgfs_fw_info_priv {
	struct iwl_fw_runtime *fwrt;
};

struct iwl_dbgfs_fw_info_state {
	loff_t pos;
};

static void *iwl_dbgfs_fw_info_seq_next(struct seq_file *seq,
					void *v, loff_t *pos)
{
	struct iwl_dbgfs_fw_info_state *state = v;
	struct iwl_dbgfs_fw_info_priv *priv = seq->private;
	const struct iwl_fw *fw = priv->fwrt->fw;

	*pos = ++state->pos;
	if (*pos >= fw->ucode_capa.n_cmd_versions)
		return NULL;

	return state;
}

static void iwl_dbgfs_fw_info_seq_stop(struct seq_file *seq,
				       void *v)
{
	kfree(v);
}

static void *iwl_dbgfs_fw_info_seq_start(struct seq_file *seq, loff_t *pos)
{
	struct iwl_dbgfs_fw_info_priv *priv = seq->private;
	const struct iwl_fw *fw = priv->fwrt->fw;
	struct iwl_dbgfs_fw_info_state *state;

	if (*pos >= fw->ucode_capa.n_cmd_versions)
		return NULL;

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (!state)
		return NULL;
	state->pos = *pos;
	return state;
};

static int iwl_dbgfs_fw_info_seq_show(struct seq_file *seq, void *v)
{
	struct iwl_dbgfs_fw_info_state *state = v;
	struct iwl_dbgfs_fw_info_priv *priv = seq->private;
	const struct iwl_fw *fw = priv->fwrt->fw;
	const struct iwl_fw_cmd_version *ver;
	u32 cmd_id;

	if (!state->pos)
		seq_puts(seq, "fw_api_ver:\n");

	ver = &fw->ucode_capa.cmd_versions[state->pos];

	cmd_id = WIDE_ID(ver->group, ver->cmd);

	seq_printf(seq, "  0x%04x:\n", cmd_id);
	seq_printf(seq, "    name: %s\n",
		   iwl_get_cmd_string(priv->fwrt->trans, cmd_id));
	seq_printf(seq, "    cmd_ver: %d\n", ver->cmd_ver);
	seq_printf(seq, "    notif_ver: %d\n", ver->notif_ver);
	return 0;
}

static const struct seq_operations iwl_dbgfs_info_seq_ops = {
	.start = iwl_dbgfs_fw_info_seq_start,
	.next = iwl_dbgfs_fw_info_seq_next,
	.stop = iwl_dbgfs_fw_info_seq_stop,
	.show = iwl_dbgfs_fw_info_seq_show,
};

static int iwl_dbgfs_fw_info_open(struct inode *inode, struct file *filp)
{
	struct iwl_dbgfs_fw_info_priv *priv;

	priv = __seq_open_private(filp, &iwl_dbgfs_info_seq_ops,
				  sizeof(*priv));

	if (!priv)
		return -ENOMEM;

	priv->fwrt = inode->i_private;
	return 0;
}

static const struct file_operations iwl_dbgfs_fw_info_ops = {
	.owner = THIS_MODULE,
	.open = iwl_dbgfs_fw_info_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = seq_release_private,
};

void iwl_fwrt_dbgfs_register(struct iwl_fw_runtime *fwrt,
			    struct dentry *dbgfs_dir)
{
	INIT_DELAYED_WORK(&fwrt->timestamp.wk, iwl_fw_timestamp_marker_wk);
	FWRT_DEBUGFS_ADD_FILE(timestamp_marker, dbgfs_dir, 0200);
	FWRT_DEBUGFS_ADD_FILE(fw_info, dbgfs_dir, 0200);
	FWRT_DEBUGFS_ADD_FILE(send_hcmd, dbgfs_dir, 0200);
	FWRT_DEBUGFS_ADD_FILE(enabled_severities, dbgfs_dir, 0200);
	FWRT_DEBUGFS_ADD_FILE(fw_dbg_domain, dbgfs_dir, 0400);
#ifdef CPTCFG_IWLWIFI_DHC_PRIVATE
	if (fw_has_capa(&fwrt->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_TLC_OFFLOAD)) {
		FWRT_DEBUGFS_ADD_FILE(tpc_enable, dbgfs_dir, 0600);
		FWRT_DEBUGFS_ADD_FILE(tpc_stats, dbgfs_dir, 0400);
	}
	FWRT_DEBUGFS_ADD_FILE(ps_report_umac, dbgfs_dir, 0400);
	FWRT_DEBUGFS_ADD_FILE(ps_test_res, dbgfs_dir, 0400);
	FWRT_DEBUGFS_ADD_FILE(ps_test_req, dbgfs_dir, 0600);
	FWRT_DEBUGFS_ADD_FILE(send_dhc, dbgfs_dir, 0200);
#endif
}
