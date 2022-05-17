/* SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 * Copyright (C) 2018-2022 Intel Corporation
 */
#ifndef __iwl_fw_api_dhc_h__
#define __iwl_fw_api_dhc_h__

#ifdef CPTCFG_IWLWIFI_DHC_PRIVATE
#include "scan.h"
#include "mac.h"
#endif /* CPTCFG_IWLWIFI_DHC_PRIVATE */

#define DHC_TABLE_MASK_POS (28)

/**
 * enum iwl_dhc_table_id - DHC table operations index
 */
enum iwl_dhc_table_id {
	/**
	 * @DHC_TABLE_INTEGRATION: select the integration table
	 */
	DHC_TABLE_INTEGRATION	= 2 << DHC_TABLE_MASK_POS,
#ifdef CPTCFG_IWLWIFI_DHC_PRIVATE
	/**
	 * @DHC_TABLE_TOOLS: select the tools table
	 */
	DHC_TABLE_TOOLS		= 0,
	/**
	 * @DHC_TABLE_AUTOMATION: select the automation table
	 */
	DHC_TABLE_AUTOMATION	= 1 << DHC_TABLE_MASK_POS,
	/**
	 * @DHC_TABLE_DEVELOPMENT: select the development table
	 */
	DHC_TABLE_DEVELOPMENT	= 3 << DHC_TABLE_MASK_POS,
	/**
	 * @DHC_TABLE_UT: select the UT table
	 */
	DHC_TABLE_UT		= 4 << DHC_TABLE_MASK_POS,
	/**
	 * @DHC_TABLE_MAX: maximal id value
	 */
	DHC_TABLE_MAX		= DHC_TABLE_UT,
#endif /* CPTCFG_IWLWIFI_DHC_PRIVATE */
};

#ifdef CPTCFG_IWLWIFI_DHC_PRIVATE
/**
 * enum iwl_dhc_lmac_tools_table - tools operations
 * @DHC_TOOLS_LMAC_TXF_FIFO_DISABLE: disable tx fifo interrupts
 *	1 DW param - bitmask of tx fifos to disable interrupts for
 */
enum iwl_dhc_lmac_tools_table {
	DHC_TOOLS_LMAC_TXF_FIFO_DISABLE = 6,
};

/**
 * enum iwl_dhc_lmac_automation_table - automation operations
 * @DHC_AUTO_LMAC_PHY_GET_STAT: get rx/tx statistics
 * @DHC_AUTO_LMAC_CONFIG_DEBUG_EBS: configure debug data on/off for EBS
 * @DHC_AUTO_LMAC_PHY_ENABLE_CRC_CHECK: enable CRC check
 * @DHC_AUTO_LMAC_SAD_RETURN_PREF_ANTS: get preferred antenna for each
 *	context where SAD is enabled
 * @DHC_AUTO_LMAC_PYFI_TIMING: override PyFi timing
 * @DHC_MAX_AUTO_LMAC_REQUEST: the size of the Automation table in lmac
 */
enum iwl_dhc_lmac_automation_table {
	DHC_AUTO_LMAC_PHY_GET_STAT               = 0,
	DHC_AUTO_LMAC_CONFIG_DEBUG_EBS           = 1,
	DHC_AUTO_LMAC_PHY_ENABLE_CRC_CHECK       = 2,
	DHC_AUTO_LMAC_SAD_RETURN_PREF_ANTS       = 3,
	DHC_AUTO_LMAC_PYFI_TIMING                = 4,
	DHC_MAX_AUTO_LMAC_REQUEST                = 6,
};

/**
 * enum iwl_dhc_umac_automation_table - automation operations
 * @DHC_AUTO_UMAC_SET_PROFILING_REPORT_CONF: configure the profiling
 *	metrics collection
 * @DHC_AUTO_UMAC_REPORT_PROFILING: get profiling report
 * @DHC_AUTO_UMAC_SCAN_CHANNEL_DWELL_ENABLE_REPORT: enable scan channel dwell
 *	reports (received as payload in DHN)
 * @DHC_AUTO_UMAC_ADAPTIVE_DWELL_SCAN_FINE_TUNE_ENABLE_REPORT: enable adaptive
 *	dwell scan fine tune report (received as payload in DHN)
 * @DHC_AUTO_UMAC_CONFIGURE_POWER_FLAGS: configure power flags DW
 * @DHC_AUTO_UMAC_REPORT_POWER_STATISTICS: get power statistics report
 * @DHC_AUTO_UMAC_POWER_SAVE_TESTS_REQ: run ps test
 * @DHC_AUTO_UMAC_POWER_SAVE_TESTS_RES: ask for the ps test response
 * @DHC_MAX_AUTO_UMAC_REQUEST: the size of the Automation table in umac
 */
enum iwl_dhc_umac_automation_table {
	DHC_AUTO_UMAC_SET_PROFILING_REPORT_CONF = 0,
	DHC_AUTO_UMAC_REPORT_PROFILING = 1,
	DHC_AUTO_UMAC_SCAN_CHANNEL_DWELL_ENABLE_REPORT = 2,
	DHC_AUTO_UMAC_ADAPTIVE_DWELL_SCAN_FINE_TUNE_ENABLE_REPORT = 3,
	DHC_AUTO_UMAC_CONFIGURE_POWER_FLAGS  = 4,
	DHC_AUTO_UMAC_REPORT_POWER_STATISTICS  = 5,
	DHC_AUTO_UMAC_POWER_SAVE_TESTS_REQ = 16,
	DHC_AUTO_UMAC_POWER_SAVE_TESTS_RES = 18,
	DHC_MAX_AUTO_UMAC_REQUEST = 19,
};
#endif

/**
 * enum iwl_dhc_umac_integration_table - integration operations
 */
enum iwl_dhc_umac_integration_table {
	/**
	 * @DHC_INT_UMAC_TWT_OPERATION: trigger a TWT operation
	 */
	DHC_INT_UMAC_TWT_OPERATION = 4,
	/**
	 * @DHC_INTEGRATION_TLC_DEBUG_CONFIG: TLC debug
	 */
	DHC_INTEGRATION_TLC_DEBUG_CONFIG = 1,
#ifdef CPTCFG_IWLWIFI_DHC_PRIVATE
	/**
	 * @DHC_INTEGRATION_POWER_FLAGS: Power flags
	 */
	DHC_INTEGRATION_POWER_FLAGS = 0,
	/**
	 * @DHC_INTEGRATION_QUOTA_ENFORCE: Enforce maximum quota
	 */
	DHC_INTEGRATION_QUOTA_ENFORCE = 2,
	/**
	 * @DHC_INT_UMAC_BT_COEX_USER_OVERRIDES: Override BT Coex user
	 */
	DHC_INT_UMAC_BT_COEX_USER_OVERRIDES = 3,
	/**
	 * @DHC_COEX_ATS_USER_OVERRIDES_SET: (not implemented in the driver)
	 */
	DHC_COEX_ATS_USER_OVERRIDES_SET = 5,
	/**
	 * @DHC_COEX_ATS_LOW_LATENCY_SET: (not implemented in the driver)
	 */
	DHC_COEX_ATS_LOW_LATENCY_SET = 6,
	/**
	 * @DHC_INT_UMAC_OMI_OPERATION: send a one-time QoS NULL with HTC-OM control
	 */
	DHC_INT_UMAC_OMI_OPERATION = 7,
	/**
	 * @DHC_INT_BT_COEX_FEATURE_ENABLEMENT_OVERRIDES: BT coex hooks
	 */
	DHC_INT_BT_COEX_FEATURE_ENABLEMENT_OVERRIDES = 8,
	/**
	 * @DHC_INT_TX_ANT_CONFIG: Get valid Tx antennas
	 */
	DHC_INT_TX_ANT_CONFIG = 9,
#endif /* CPTCFG_IWLWIFI_DHC_PRIVATE */
	/**
	 * @DHC_INT_UMAC_TWT_CONTROL: TWT hooks (like disable internal TWT triggers)
	 */
	DHC_INT_UMAC_TWT_CONTROL = 10,
#ifdef CPTCFG_IWLWIFI_DHC_PRIVATE
	/**
	 * @DHC_DP_TAS_CONFIG: config TAS
	 */
	DHC_DP_TAS_CONFIG = 11,
	/**
	 * @DHC_INT_UMAC_TWT_AP_DEBUG_CONFIG: config TWT soft AP test mode
	 */
	DHC_INT_UMAC_TWT_AP_DEBUG_CONFIG = 12,
	/**
	 * @DHC_INT_UMAC_WMAL_READ_PARAMS: read WMAL params
	 */
	DHC_INT_UMAC_WMAL_READ_PARAMS = 13,
	/**
	 * @DHC_INT_UMAC_RFI_CONFIG: RFI config
	 */
	DHC_INT_UMAC_RFI_CONFIG = 14,
	/**
	 * @DHC_INT_UMAC_SEND_TWT_INFO: send a TWT info
	 */
	DHC_INT_UMAC_SEND_TWT_INFO = 15,
#endif /* CPTCFG_IWLWIFI_DHC_PRIVATE */
	/**
	 * @DHC_INTEGRATION_MAX: Maximum UMAC integration table entries
	 */
	DHC_INTEGRATION_MAX
};

#define DHC_TARGET_UMAC BIT(27)
#define DHC_ADWELL_SCAN_CHANNEL_DWELL_INDEX 2
#define DHC_ADWELL_SCAN_FINE_TUNE_INDEX 3

/**
 * struct iwl_dhc_cmd - debug host command
 * @length: length in DWs of the data structure that is concatenated to the end
 *	of this struct
 * @index_and_mask: bit 31 is 1 for data set operation else it's 0
 *	bits 28-30 is the index of the table of the operation -
 *	&enum iwl_dhc_table_id *
 *	bit 27 is 0 if the cmd targeted to LMAC and 1 if targeted to UMAC,
 *	(LMAC is 0 for backward compatibility)
 *	bit 26 is 0 if the cmd targeted to LMAC0 and 1 if targeted to LMAC1,
 *	relevant only if bit 27 set to 0
 *	bits 0-25 is a specific entry index in the table specified in bits 28-30
 *
 * @data: the concatenated data.
 */
struct iwl_dhc_cmd {
	__le32 length;
	__le32 index_and_mask;
	__le32 data[0];
} __packed; /* DHC_CMD_API_S */

#ifdef CPTCFG_IWLWIFI_DHC_PRIVATE
/**
 * struct iwl_dhc_cmd_resp_v1 - debug host command response
 * @status: status of the command
 * @data: the response data
 */
struct iwl_dhc_cmd_resp_v1 {
	__le32 status;
	__le32 data[0];
} __packed; /* DHC_RESP_API_S_VER_1 */

/**
 * struct iwl_dhc_cmd_resp - debug host command response
 * @status: status of the command
 * @descriptor: command descriptor (index_and_mask) returned
 * @data: the response data
 */
struct iwl_dhc_cmd_resp {
	__le32 status;
	__le32 descriptor;
	__le32 data[0];
} __packed; /* DHC_RESP_API_S_VER_2 and DHC_RESP_API_S_VER_3 */

/**
 * struct iwl_dhc_profile_cmd - profiling command.
 * should be concatenated to &struct iwl_dhc_cmd
 * @period: the time period, in seconds, of the report.
 *	if it's set to 0 then report will be sent only when requested
 * @reset: set to 1 for resetting the metrics data
 *	set to 0 for not restting.
 * @enabled_metrics: bitmask of the metrics to enable
 *	bit 0 - cpu_usage_metric
 *	bit 1 - paging_metric
 *	bit 2 - flow_timing_metric
 *	bit 3 - critical_section_metric
 *	bit 4 - memory_pool_metric
 *	bit 5 - fifos_metric
 */
struct iwl_dhc_profile_cmd {
	__le32 period;
	__le32 reset;
	__le32 enabled_metrics;
} __packed;

enum iwl_profiling_context_id {
	PROFILING_CONTEXT_PS_THREAD,
	PROFILING_CONTEXT_RESERVED_1,
	PROFILING_CONTEXT_MAIN_THREAD,
	PROFILING_CONTEXT_AIRTIME_THREAD,
	PROFILING_CONTEXT_MPAPD_THREAD,
	PROFILING_CONTEXT_TIMER_IRQ,
	PROFILING_CONTEXT_RXF2_IRQ,
	PROFILING_CONTEXT_CMD_IRQ,
	PROFILING_CONTEXT_MAX_NUM
}; /* PROFILING_CONTEXT_ID_API_E */

enum iwl_profiling_tasks_id {
	PROFILING_MAIN_INIT_TASK,
	PROFILING_RESERVED_1,
	PROFILING_ELOOP_TASK,
	PROFILING_RESERVED_3,
	PROFILING_LMAC_RXF_TASK,
	PROFILING_MPAPD_TASK,
	PROFILING_TASKS_MAX_NUM
}; /* PROFILING_TASKS_ID_API_E */

enum iwl_profiling_flow_id {
	PROFILING_HANDLING_PRB_RQST_UMAC_FLOW,
	PROFILING_UMAC_BCN_HANDLING_FLOW,
	PROFILING_UMAC_NON_TKIP_HANDLING_FLOW,
	PROFILING_UMAC_TKIP_HANDLING_FLOW,
	PROFILING_UMAC_LMAC_NOTIFICATION_THREAD_HANDLING,
	PROFILING_UMAC_RXF2_DROPPABLE_FRAME_ISR_HANDLING,
	PROFILING_UMAC_OTHER_FRAMES_HANDLING_FLOW,
	PROFILING_AIRTIME_CONTEXT_GET_FLOW,
	PROFILING_AIRTIME_CONTEXT_LOSE_FLOW,
	PROFILING_MAC_CONTEXT_LOSE_FLOW,
	PROFILING_AUX_CONTEXT_GET_FLOW,
	PROFILING_AUX_CONTEXT_CLEAR_FLOW,
	PROFILING_AUX_CONTEXT_SET_FLOW,
	PROFILING_AIRTIME_SCHEDULER_SESSION_CALC_FLOW,
	PROFILING_TLC_STATISTICS_HANDLING_FLOW,
	PROFILING_CHANNEL_SWITCH_FLOW,
	PROFILING_THREAD_CONTEXT_SWITCH_FLOW,
	PROFILING_SYSTEM_POWER_DOWN_FLOW,
	PROFILING_FLOW_MAX_NUM
}; /* PROFILING_FLOW_ID_API_E */

enum iwl_profiling_fifo_id {
	PROFILING_FIFO_UMAC_TO_LMAC1,
	PROFILING_FIFO_UMAC_TO_LMAC2,
	PROFILING_FIFO_LMAC1_TO_UMAC,
	PROFILING_FIFO_LMAC2_TO_UMAC,
	PROFILING_FIFO_RXF2,
	PROFILING_FIFO_MAX_NUM
}; /* PROFILING_FIFO_ID_API_E */

enum iwl_profiling_pool_id {
	PROFILING_POOL_MGMT_FRAME,
	PROFILING_POOL_MPDU_FRWK_1,
	PROFILING_POOL_MPDU_FRWK_2,
	PROFILING_POOL_MSG_QUEUE_AIRTIME,
	PROFILING_POOL_MSG_QUEUE_MAIN,
	PROFILING_POOL_MSG_QUEUE_BACKGROUND,
	PROFILING_POOL_MSG_QUEUE_MPAPD,
	PROFILING_POOL_RESERVED_7,
	PROFILING_POOL_BLOCK_MSG_QUEUE_AIRTIME_BIG,
	PROFILING_POOL_BLOCK_MSG_QUEUE_AIRTIME_SMALL,
	PROFILING_POOL_BLOCK_MSG_QUEUE_MAIN_BIG,
	PROFILING_POOL_BLOCK_MSG_QUEUE_MAIN_SMALL,
	PROFILING_POOL_RESERVED_12,
	PROFILING_POOL_RESERVED_13,
	PROFILING_POOL_INTERNAL_TX,
	PROFILING_POOL_CYCLIC_LMAC_RX,
	PROFILING_POOL_RESERVED_16,
	PROFILING_POOL_BYTE_UMAC_TX,
	PROFILING_POOL_BYTE_UMAC_OS,
	PROFILING_POOL_MAX_NUM
}; /* PROFILING_POOL_ID_API_E */

/**
 * struct iwl_profiling_configuration - profiling collection configuration
 * @time_since_last_metrics_reset: Time elapsed since last FW metrics reset in
 *	usec
 * @current_system_time: Time at which this report was generated
 * @enabled_metrics: Enabled metrics bitmap
 */
struct iwl_profiling_configuration {
	__le32 time_since_last_metrics_reset;
	__le32 current_system_time;
	__le32 enabled_metrics;
} __packed; /* PROFILING_CONFIGURATION_API_S */

/**
 * struct iwl_profiling_umac_cpu_usage - profiling data on CPU usage
 * @context_id: ID of the execution context for which the following information
 *	is provided
 * @run_time: Total run time (since last metrics reset) for this context in
 *	usec
 * @enabled_metrics: enabled metrics bitmap
 * @max_processing_time: Maximal amount of time (since last metrics reset) that
 *	the context ran to completion
 * @num_of_page_faults_dl: Number of Page Fault downloads only for this context
 *	since last metrics reset. Not relevant for IRQ contexts
 * @num_of_page_faults_dl_up: Number of Page Fault uploads and downloads for
 *	this context since last metrics reset. Not relevant for IRQ contexts
 * @max_processing_time_task: ID of task which caused the longest processing
 *	time for this context
 * @max_block_time: Maximal amount of time (since last metrics reset)
 *	thread was blocked due to higher priority context
 * @max_pf_handle_time_dl: Maximal Time between PF exception to return from
 *	completion handling ISR  Download only
 * @max_pf_handle_time_dl_up: Upload + Download - Including cache write back
 *	and invalidation
 * @min_pf_handle_time_dl: Minimal Time between PF exception to return from
 *	completion handling ISR Download only
 * @min_pf_handle_time_dl_up: Upload + Download - Including cache write back
 *	and invalidation
 * @sum_pf_handle_time_dl: Accumulated Time between PF exception to return from
 *	completion handling ISR
 * @sum_pf_handle_time_dl_up: Upload + Download - Including cache write back
 *	and invalidation
 * @p_fHandle_time_bucket1:  Time for Handling Page Faults Histogram
 *	(any PF - DL or UL+DL) Number of page faults that were handled within
 *	31 microseconds. Buckets are emptied every metrics reset
 * @p_fHandle_time_bucket2:  Time for Handling Page Faults Histogram
 *	(any PF - DL or UL+DL) Number of page faults that were handled within
 *	32-63us. Buckets are emptied every metrics reset
 * @p_fHandle_time_bucket3:  Time for Handling Page Faults Histogram
 *	(any PF - DL or UL+DL) Number of page faults that were handled within
 *	64-127us. Buckets are emptied every metrics reset
 * @p_fHandle_time_bucket4:  Time for Handling Page Faults Histogram
 *	(any PF - DL or UL+DL) Number of page faults that were handled within
 *	128-255us. Buckets are emptied every metrics reset
 * @p_fHandle_time_bucket5:  Time for Handling Page Faults Histogram
 *	(any PF - DL or UL+DL) Number of page faults that were handled within
 *	256+us. Buckets are emptied every metrics reset
 * @stack_size:  Total stack size for this context
 * @stack_max_usage:  Max used stack since last reset (stack is repainted on
 *	each metrics reset)
 * @stack_max_usage_task: Task ID that used the max stack space
 */
struct iwl_profiling_umac_cpu_usage {
	__le32 context_id;
	__le32 run_time;
	__le32 enabled_metrics;
	__le32 max_processing_time;
	__le32 num_of_page_faults_dl;
	__le32 num_of_page_faults_dl_up;
	__le32 max_processing_time_task;
	__le32 max_block_time;
	__le16 max_pf_handle_time_dl;
	__le16 max_pf_handle_time_dl_up;
	__le16 min_pf_handle_time_dl;
	__le16 min_pf_handle_time_dl_up;
	__le32 sum_pf_handle_time_dl;
	__le32 sum_pf_handle_time_dl_up;
	__le16 p_fHandle_time_bucket1;
	__le16 p_fHandle_time_bucket2;
	__le16 p_fHandle_time_bucket3;
	__le16 p_fHandle_time_bucket4;
	__le16 p_fHandle_time_bucket5;
	__le16 stack_size;
	__le16 stack_max_usage;
	__le32 stack_max_usage_task;

} __packed; /* PROFILING_UMAC_CPU_USAGE_API_S */

/**
 * struct iwl_profiling_umac_general_paging
 * @num_of_page_faults:  Total number of PF since last metrics reset
 * @inter_page_fault_time_bucket1:  Time Between Page Faults Histogram Number of
 *	page faults that occurred 0-5 microseconds from the end of the previous
 *	page fault. Buckets are emptied every metrics reset
 * @inter_page_fault_time_bucket2:  Time Between Page Faults Histogram Number of
 *	page faults that occurred 6-10us from the end of the previous page
 *	fault. Buckets are emptied every metrics reset
 * @inter_page_fault_time_bucket3:  Time Between Page Faults Histogram Number of
 *	page faults that occurred 11-1000us from the end of the previous page
 *	fault. Buckets are emptied every metrics reset
 * @inter_page_fault_time_bucket4: Time Between Page Faults Histogram Number of
 *	page faults that occurred 1ms-100ms from the end of the previous page
 *	fault. Buckets are emptied every metrics reset
 * @inter_page_fault_time_bucket5: Time Between Page Faults Histogram Number of
 *	page faults that occurred 100ms+ from the end of the previous page
 *	fault. Buckets are emptied every metrics reset
 * @max_page_fault_wait_time: The maximal number of microseconds that a PF was
 *	waiting in line to be handled (due to other PFs that were handled
 *	previously)
 * @max_num_of_pending_pfs: The maximal number of pending page faults that was
 *	encountered (measured each time a PF is queued to be handled).
 */
struct iwl_profiling_umac_general_paging {
	__le32 num_of_page_faults;
	__le32 inter_page_fault_time_bucket1;
	__le32 inter_page_fault_time_bucket2;
	__le32 inter_page_fault_time_bucket3;
	__le32 inter_page_fault_time_bucket4;
	__le32 inter_page_fault_time_bucket5;
	__le16 max_page_fault_wait_time;
	__le16 max_num_of_pending_pfs;
} __packed; /* PROFILING_UMAC_GENERAL_PAGING_API_S */

/**
 * struct iwl_profiling_umac_flow_timing
 * @flow_id: Identifier of the flow for which the following information is
 *	provided should be in &enum iwl_profiling_flow_id
 * @num_of_runs: Number of times this flow occurred
 * @total_run_time: Total time this flow ran
 * @max_run_time: Maximal time this flow was timed running
 * @min_run_time: Minimal time this flow was timed running
 */
struct iwl_profiling_umac_flow_timing {
	__le32 flow_id;
	__le32 num_of_runs;
	__le32 total_run_time;
	__le32 max_run_time;
	__le32 min_run_time;
} __packed; /* PROFILING_UMAC_FLOW_TIMING_API_S */

/**
 * struct iwl_profiling_umac_critical_section
 * @max_critical_section_time: Maximal length of time of all critical sections
 */
struct iwl_profiling_umac_critical_section {
	__le32 max_critical_section_time;
} __packed; /* PROFILING_UMAC_CRITICAL_SECTION_API_S */

/**
 * struct iwl_profiling_umac_memory_pools {
 * @pool_id: Identifier of the memory pool for which the following information
 *	is provided should be in &enum iwl_profiling_pool_id
 * @min_free_space: Minimum number of blocks or bytes (depending on the pool
 *	type) that were available since last metrics reset
 * @largest_allocated_size: For byte pools, gives an indication of level of
 *	fragmentation
 */
struct iwl_profiling_umac_memory_pools {
	__le32 pool_id;
	__le32 min_free_space;
	__le32 largest_allocated_size;
} __packed; /* PROFILING_UMAC_MEMORY_POOLS_API_S */

/**
 * struct iwl_profiling_umac_fifos
 * @fifo_id: Identifier of the FIFO for which the following information is
 *	provided should be in &enum iwl_profiling_fifo_id
 * @min_free_bytes: Min number of bytes that were available since last metrics
 *	reset
 */
struct iwl_profiling_umac_fifos {
	__le32 fifo_id;
	__le32 min_free_bytes;
} __packed; /* PROFILING_UMAC_FIFOS_API_S */

/**
 * struct iwl_profiling_umac_metrics_report
 * @configuration: configuration of the following
 *	metric report
 * @umac_cpu_usage_ctx: UMAC CPU Usage per context
 * @umac_general_paging: UMAC General Paging  (not context specific)
 * @umac_flows_timing: Flows Timing (provided for each enumerated flow)
 * @umac_critical_section: UMAC critical sections
 * @umac_memory_pools: UMAC Memory Pools (provided for each enumerated
 *	memory pool)
 * @umac_fifos_arr: UMAC FIFOs (provided for each enumerated FIFO)
 */
struct iwl_profiling_umac_metrics_report {
	struct iwl_profiling_configuration configuration;
	struct iwl_profiling_umac_cpu_usage umac_cpu_usage_ctx[PROFILING_CONTEXT_MAX_NUM];
	struct iwl_profiling_umac_general_paging umac_general_paging;
	struct iwl_profiling_umac_flow_timing umac_flows_timing[PROFILING_FLOW_MAX_NUM];
	struct iwl_profiling_umac_critical_section umac_critical_section;
	struct iwl_profiling_umac_memory_pools umac_memory_pools[PROFILING_POOL_MAX_NUM];
	struct iwl_profiling_umac_fifos umac_fifos_arr[PROFILING_FIFO_MAX_NUM];
} __packed; /* PROFILING_UMAC_METRICS_REPORT_API_S */

/**
 * struct iwl_ltr_statistic_report
 * @tx_active_time: time during which ltr was in tx active state
 * @rx_active_time: time during which ltr was in rx active state
 * @rx_listen_time: time during which ltr was in rx listen state
 * @power_save_time: time during which ltr was in power save state
 * @total_time: total time of statistic collection
 */
struct iwl_ltr_statistics_report {
	__le32 tx_active_time;
	__le32 rx_active_time;
	__le32 rx_listen_time;
	__le32 power_save_time;
	__le32 total_time;
} __packed; /* LTR_STATISTICS_REPORT_API_S */

/**
 * struct iwl_ps_report {
 * @total_sleep_counter: number of times NIC actually go to PD [cnt]
 * @total_sleep_duration: total sleep duration of sleep-master CPU [usec]
 * @report_duration: time since current statistics collection began [usec]
 * @total_missed_beacon_counter: number of missed-beacons [cnt]
 * @missed_3_consecutive_beacon_count: number of missed-3-consecutive-beacons
 *	events [cnt]
 * @ps_flags: 4 bytes of flag bits, 1 for each MAC (4 MACs max)
 * @phy_inactive_duration: total time PHY is powered down [usec]
 * @mac_ctdp_sum: UMAC CTDP power consumption sum [uJouls]
 * @ppm_offset_vs_ap_sum: drift offset from AP clock sum [secs]
 * @deep_sleep_duration: UMAC time in deep sleep during the report interval
 *	[usecs]
 * @received_beacon_counter: number of received beacons [cnt]
 * @bcon_in_lprx_counter: number of beacons in LPRX [cnt]
 * @bcon_abort_counter: number of beacon aborts [cnt]
 * @multicast_indication_tim_counter: number of multicast indications in TIM
 *	information element from AP [cnt]
 * @missed_multicast_counter: number of missed multicasts [cnt]
 * @misbehave_counter: number of instances of misbehave AP, which forces
 *	PM to change mode [cnt]
 * @max_sleep_duration: maximum sleep time in usecs
 * @total_page_faults: total page faults counter, include both code page
 *	fault and data page fault
 * @sleep_abort_count: total sleep abort counter
 * @max_active_duration: maximum active timer in usecs
 * @max_pu_duration: maximum UMAC power up duration
 * @max_pd_duration: maximum UMAC power down duration
 * @max_phy_pu_duration: maximum power up duration per LMAC
 * @max_phy_pd_duration: maximum power down duration per LMAC
 * @ltr: ltr statistics report collection
 * @ps_duration: powersave duration (per index)
 */
struct iwl_ps_report {
	__le32 total_sleep_counter;
	__le32 total_sleep_duration;
	__le32 report_duration;
	__le32 total_missed_beacon_counter;
	__le32 missed_3_consecutive_beacon_count;
	__le32 ps_flags;
	__le32 phy_inactive_duration;
	__le32 mac_ctdp_sum;
	__le32 ppm_offset_vs_ap_sum;
	__le32 deep_sleep_duration;
	__le32 received_beacon_counter;
	__le16 bcon_in_lprx_counter;
	__le16 bcon_abort_counter;
	__le16 multicast_indication_tim_counter;
	__le16 missed_multicast_counter;
	__le32 misbehave_counter;
	__le32 max_sleep_duration;
	__le32 total_page_faults;
	__le32 sleep_abort_count;
	__le32 max_active_duration;
	__le16 max_pu_duration;
	__le16 max_pd_duration;
	__le16 max_phy_pu_duration[2];
	__le16 max_phy_pd_duration[2];
	struct iwl_ltr_statistics_report ltr;
	__le32 ps_duration[3];
} __packed; /* PS_REPORT_API_S_VER_7 */

/**
 * struct iwl_ps_config {
 * @pwr_flags: power flags - description @ POWER_TABLE_CMD_FLAG in FW / pwr.h
 * @pwr_flags_msk: power flag masks - description @ POWER_TABLE_CMD_FLAG in
 *                 FW / pwr.h. in case mask bit is 1 - the flag should be
 *                 processed.
 * @param1: generic param1 - usage according to flags
 */
struct iwl_ps_config {
	__le32 pwr_flags;
	__le32 pwr_flags_msk;
	__le32 param1;
} __packed; /* DHC_PS_CONFIG_API_S */

/**
 * struct iwl_ps_test_req {
 * @flags:      ps test flags
 * @test_case:   ps test case to run
 * @test_param1: generic test param 1
 * @test_param2: generic test param 2
 * @test_param3: generic test param 3
 * @test_param4: generic test param 4
 */
struct iwl_ps_test_req {
	__le32 flags;
	__le32 test_case;
	__le32 test_param1;
	__le32 test_param2;
	__le32 test_param3;
	__le32 test_param4;
} __packed; /* PS_TEST_REQ_API_S */

/**
 * struct iwl_ps_test_res {
 * @test_res1: generic test result 1
 * @test_res2: generic test result 2
 * @test_res3: generic test result 3
 * @test_res4: generic test result 4
 */
struct iwl_ps_test_res {
	__le32 test_res1;
	__le32 test_res2;
	__le32 test_res3;
	__le32 test_res4;
} __packed; /* PS_TEST_RES_API_S */

/**
 * struct iwl_dhn_hdr - the header of the Debug Host Notification (DHN)
 * @length: length in DWs of the data structure that is concatenated to the end
 *	of this struct
 * @index_and_mask: bit 31 is 1 for data set operation else it's 0
 *	bits 28-30 is the index of the table of the operation -
 *	&enum iwl_dhc_table_id
 *	bit 27 is 0 if the cmd targeted to LMAC and 1 if targeted to UMAC,
 *	(LMAC is 0 for backward compatibility)
 *	bit 26 is 0 if the cmd targeted to LMAC0 and 1 if targeted to LMAC1,
 *	relevant only if bit 27 set to 0
 *	bits 0-25 is a specific entry index in the table specified in bits 28-30
 */
struct iwl_dhn_hdr {
	__le32 length;
	__le32 index_and_mask;
} __packed; /* DHC_NOTIFICATION_API_S */

/**
 * struct iwl_profiling_notification - the notification of the profiling report
 * @header: DHN header
 * @profiling_metrics: the profiling metrics
 */
struct iwl_profiling_notification {
	struct iwl_dhn_hdr header;
	struct iwl_profiling_umac_metrics_report profiling_metrics;
} __packed; /* DHC_NOTIFICATION_API_S */

/**
 * struct iwl_channel_dwell_report - channel dwell time report
 *
 * This DHN (Debug Host Notification) is raised for each channel during
 * the scan, at the beginning of the dwell time,
 * and includes the following data:
 *
 * @header: DHN header
 * @channel_num: the current channel
 * @dwell_tsf: start dwell tsf
 * @dwell_time: requested dwell time
 */
struct iwl_channel_dwell_report {
	struct iwl_dhn_hdr header;
	__le32 channel_num;
	__le32 dwell_tsf;
	__le32 dwell_time;
} __packed; /* SCAN_CHANNEL_DWELL_REPORT_API_S */

/**
 * struct iwl_adwell_fine_tune_metrics_report
 *
 * This DHN (Debug Host Notification) raised at the end of the scan
 * and contains the following table:
 *
 * @header: DHN header
 * @index: indices array of the channels numbers
 * @scan_counter: fine tune scans number
 * @success_counter: fine tune success counter
 */
struct iwl_adwell_fine_tune_metrics_report {
	struct iwl_dhn_hdr header;
	s8 index[IWL_SCAN_MAX_NUM_OF_CHANNELS];
	u8 scan_counter[IWL_SCAN_MAX_NUM_OF_CHANNELS];
	u8 success_counter[IWL_SCAN_MAX_NUM_OF_CHANNELS];
} __packed; /* ADAPTIVE_DWELL_SCAN_FINE_TUNE_METRICS_REPORT_API_S */

/**
 * enum iwl_dhc_quota_enforce_type
 *
 * @QUOTA_ENFORCE_TYPE_RESERVATION: Enforce minimum quota.
 * @QUOTA_ENFORCE_TYPE_LIMITATION: Enforce maximum quota.
 */
enum iwl_dhc_quota_enforce_type {
	QUOTA_ENFORCE_TYPE_RESERVATION,
	QUOTA_ENFORCE_TYPE_LIMITATION,
}; /* DHC_QUOTA_ENFORCE_TYPE_API_E */

/**
 * struct iwl_quota_enforce - Enforce quota percent
 *
 * @macs: bitmask of MAC IDs relevant here
 * @quota_enforce_type: &enum iwl_dhc_quota_enforce_type
 * @reserved: reserved for alignment
 * @quota_percentage: quota to enforce as percentage [0 - 100]
 */
struct iwl_dhc_quota_enforce {
	u8 macs;
	u8 quota_enforce_type;
	__le16 reserved;
	__le32 quota_percentage[MAC_INDEX_AUX];
} __packed; /* DHC_QUOTA_ENFORCE_API_S */
#endif /* CPTCFG_IWLWIFI_DHC_PRIVATE */

/**
 * enum iwl_dhc_twt_operation_type - describes the TWT operation type
 *
 * @DHC_TWT_REQUEST: Send a Request TWT command
 * @DHC_TWT_SUGGEST: Send a Suggest TWT command
 * @DHC_TWT_DEMAND: Send a Demand TWT command
 * @DHC_TWT_GROUPING: Send a Grouping TWT command
 * @DHC_TWT_ACCEPT: Send a Accept TWT command
 * @DHC_TWT_ALTERNATE: Send a Alternate TWT command
 * @DHC_TWT_DICTATE: Send a Dictate TWT command
 * @DHC_TWT_REJECT: Send a Reject TWT command
 * @DHC_TWT_TEARDOWN: Send a TearDown TWT command
 */
enum iwl_dhc_twt_operation_type {
	DHC_TWT_REQUEST,
	DHC_TWT_SUGGEST,
	DHC_TWT_DEMAND,
	DHC_TWT_GROUPING,
	DHC_TWT_ACCEPT,
	DHC_TWT_ALTERNATE,
	DHC_TWT_DICTATE,
	DHC_TWT_REJECT,
	DHC_TWT_TEARDOWN,
}; /* DHC_TWT_OPERATION_TYPE_E */

/**
 * struct iwl_dhc_twt_operation - trigger a TWT operation
 *
 * @mac_id: the mac Id on which to trigger TWT operation
 * @twt_operation: see &enum iwl_dhc_twt_operation_type
 * @target_wake_time: when should we be on channel
 * @interval_exp: the exponent for the interval
 * @interval_mantissa: the mantissa for the interval
 * @min_wake_duration: the minimum duration for the wake period
 * @trigger: is the TWT triggered or not
 * @flow_type: is the TWT announced or not
 * @flow_id: the TWT flow identifier from 0 to 7
 * @protection: is the TWT protected
 * @ndo_paging_indicator: is ndo_paging_indicator set
 * @responder_pm_mode: is responder_pm_mode set
 * @negotiation_type: if the responder wants to doze outside the TWT SP
 * @twt_request: 1 for TWT request, 0 otherwise
 * @implicit: is TWT implicit
 * @twt_group_assignment: the TWT group assignment
 * @twt_channel: the TWT channel
 * @reserved: reserved
 */
struct iwl_dhc_twt_operation {
	__le32 mac_id;
	__le32 twt_operation;
	__le64 target_wake_time;
	__le32 interval_exp;
	__le32 interval_mantissa;
	__le32 min_wake_duration;
	u8 trigger;
	u8 flow_type;
	u8 flow_id;
	u8 protection;
	u8 ndo_paging_indicator;
	u8 responder_pm_mode;
	u8 negotiation_type;
	u8 twt_request;
	u8 implicit;
	u8 twt_group_assignment;
	u8 twt_channel;
	u8 reserved;
}; /* DHC_TWT_OPERATION_API_S */

#ifdef CPTCFG_IWLWIFI_DHC_PRIVATE
/**
 * struct iwl_dhc_htc_omi - send QoS NULL with HE HTC OM Control
 *
 * @operating_mode: the OM control as defined in 11ax D3.0 9.2.4.6a.2
 * @mac_id: the mac ID on which to send the frame
 * @reserved: reserved
 */
struct iwl_dhc_htc_omi {
	__le32 operating_mode;
	u8 mac_id;
	u8 reserved[3];
}; /* DHC_OMI_OPERATION_API_S */
#endif /* CPTCFG_IWLWIFI_DHC_PRIVATE */

/**
 * struct iwl_dhc_twt_control - control TWT behavior
 *
 * @twt_test_mode: if 1 TWT internal triggers (e.g. PM) will be disabled
 * @reserved: reserved
 */
struct iwl_dhc_twt_control {
	u8 twt_test_mode;
	u8 reserved[3];
}; /* DHC_TWT_CONTROL_API_S_VER_1 */

#endif /* __iwl_fw_api_dhc_h__ */
