#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0xb3753869, "module_layout" },
	{ 0xdfd74b90, "iwl_phy_db_init" },
	{ 0x609f1c7e, "synchronize_net" },
	{ 0x72d02976, "ieee80211_rx_napi" },
	{ 0x2f2c95c4, "flush_work" },
	{ 0xce2398b8, "alloc_pages_current" },
	{ 0x2d3385d3, "system_wq" },
	{ 0xa4b2b77e, "ieee80211_key_replay" },
	{ 0x2b6d15e5, "ieee80211_csa_finish" },
	{ 0x7bd010e, "__iwl_err" },
	{ 0xf2bd333e, "ieee80211_iterate_active_interfaces_mtx" },
	{ 0x35216b26, "kmalloc_caches" },
	{ 0xeb233a45, "__kmalloc" },
	{ 0xc9178b46, "ieee80211_disconnect" },
	{ 0xc4f0da12, "ktime_get_with_offset" },
	{ 0xf9a482f9, "msleep" },
	{ 0x4bfaa4c0, "iwl_acpi_get_lari_config_bitmap" },
	{ 0x1ed8b599, "__x86_indirect_thunk_r8" },
	{ 0x4e3d06ab, "_dmi_get_system_info" },
	{ 0xdae599ff, "iwl_parse_nvm_data" },
	{ 0x6c9a2650, "__skb_gso_segment" },
	{ 0x619cb7dd, "simple_read_from_buffer" },
	{ 0x5c9f73e3, "generic_file_llseek" },
	{ 0x33504981, "iwl_sar_select_profile" },
	{ 0xb43a926b, "backport_dependency_symbol" },
	{ 0x275269b3, "ieee80211_ie_split_ric" },
	{ 0x40e30d71, "debugfs_create_dir" },
	{ 0x4e06e19d, "iwl_acpi_get_pwr_limit" },
	{ 0x41005272, "debugfs_create_u8" },
	{ 0xf88964e4, "iwl_remove_notification" },
	{ 0x5ab5b891, "param_ops_int" },
	{ 0xd1aebb74, "regulatory_set_wiphy_regd" },
	{ 0x91eb9b4, "round_jiffies" },
	{ 0x984ce9bd, "__nla_parse" },
	{ 0x5d4e8097, "ieee80211_sta_ps_transition" },
	{ 0x2b68bd2f, "del_timer" },
	{ 0x8846e228, "iwl_acpi_get_eckv" },
	{ 0x60a13e90, "rcu_barrier" },
	{ 0x779a18af, "kstrtoll" },
	{ 0x8fd54861, "iwl_fw_runtime_resume" },
	{ 0x81188c30, "match_string" },
	{ 0xfce95896, "iwl_acpi_get_ppag_table" },
	{ 0x21cdb86, "iwl_fw_start_dbg_conf" },
	{ 0xfa599bb2, "netlink_register_notifier" },
	{ 0x75160fcb, "iwl_cmd_groups_verify_sorted" },
	{ 0x2710c362, "iwl_dump_desc_assert" },
	{ 0x19f462ab, "kfree_call_rcu" },
	{ 0xcaf9f6d, "thermal_cooling_device_unregister" },
	{ 0x8149917f, "ieee80211_request_smps" },
	{ 0xb1921ae0, "iwl_force_nmi" },
	{ 0x79aa04a2, "get_random_bytes" },
	{ 0xc03c97a8, "iwl_acpi_get_dsm_u32" },
	{ 0x3c262547, "iwl_fw_dbg_stop_sync" },
	{ 0x14ea7346, "iwl_fw_dbg_read_d3_debug_data" },
	{ 0x4c1c952e, "iwl_dnt_start" },
	{ 0xad4fd80d, "ieee80211_cqm_rssi_notify" },
	{ 0xc7a4fbed, "rtnl_lock" },
	{ 0x7879fb05, "ieee80211_tdls_oper_request" },
	{ 0x6ca71fd, "cfg80211_chandef_create" },
	{ 0x70f6ceb2, "no_llseek" },
	{ 0xce0c6460, "iwl_phy_db_set_section" },
	{ 0xb3635b01, "_raw_spin_lock_bh" },
	{ 0xfc1e6f41, "iwl_guid" },
	{ 0xcb46555e, "iwl_set_bits_mask_prph" },
	{ 0x7ef39823, "ieee80211_hdrlen" },
	{ 0xa937826c, "skb_copy" },
	{ 0xc0a3d105, "find_next_bit" },
	{ 0xffeedf6a, "delayed_work_timer_fn" },
	{ 0x5584448a, "ieee80211_channel_to_freq_khz" },
	{ 0x2124474, "ip_send_check" },
	{ 0x4708dc6e, "iwl_opmode_register" },
	{ 0x1c5756e4, "iwl_acpi_is_ppag_approved" },
	{ 0x56470118, "__warn_printk" },
	{ 0x874c77de, "iwl_fw_rate_idx_to_plcp" },
	{ 0x3c12dfe, "cancel_work_sync" },
	{ 0x6b63201a, "ieee80211_resume_disconnect" },
	{ 0xb7d5ffb1, "iwl_rate_mcs" },
	{ 0x66b4cc41, "kmemdup" },
	{ 0x182aaad9, "ieee80211_unregister_hw" },
	{ 0x37956b72, "rs_pretty_print_rate" },
	{ 0x5250cf98, "ieee80211_tkip_add_iv" },
	{ 0x7c3ac925, "ieee80211_get_vht_max_nss" },
	{ 0xdf54a8f7, "netlink_unregister_notifier" },
	{ 0x1c7de9a7, "iwl_sar_get_ewrd_table" },
	{ 0xededc3c3, "param_ops_bool" },
	{ 0xc6f46339, "init_timer_key" },
	{ 0x9fa7184a, "cancel_delayed_work_sync" },
	{ 0x409bcb62, "mutex_unlock" },
	{ 0x85df9b6c, "strsep" },
	{ 0x575d6c56, "ieee80211_iterate_active_interfaces_atomic" },
	{ 0xcb6f0b93, "ieee80211_scan_completed" },
	{ 0xfa759f6d, "ieee80211_sched_scan_results" },
	{ 0x921ec64f, "debugfs_create_file" },
	{ 0x354c7372, "iwl_fw_dbg_stop_restart_recording" },
	{ 0x4629334c, "__preempt_count" },
	{ 0x7f9f2942, "ieee80211_mark_rx_ba_filtered_frames" },
	{ 0xb16ec879, "ieee80211_vif_to_wdev" },
	{ 0x97651e6c, "vmemmap_base" },
	{ 0x22453c63, "iwl_wait_notification" },
	{ 0x8b9dcc6e, "wiphy_rfkill_set_hw_state_reason" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0x638c6409, "debugfs_remove_recursive" },
	{ 0xbc128cf0, "iwl_sar_get_wgds_table" },
	{ 0x36e58bcd, "pv_ops" },
	{ 0x1234131f, "cfg80211_reg_can_beacon" },
	{ 0x15ba50a6, "jiffies" },
	{ 0x1a66fc17, "ieee80211_get_tkip_rx_p1k" },
	{ 0x9d82590c, "iwl_trans_send_cmd" },
	{ 0x9c5b3840, "ieee80211_stop_queues" },
	{ 0xd5c6aca9, "ieee80211_nan_func_terminated" },
	{ 0xf91d85da, "wdev_to_ieee80211_vif" },
	{ 0xbc41f18f, "ieee80211_send_eosp_nullfunc" },
	{ 0xfb384d37, "kasprintf" },
	{ 0x6383c1a4, "ieee80211_ready_on_channel" },
	{ 0xa47175e7, "iwl_read_prph" },
	{ 0xda4da779, "ieee80211_tx_status" },
	{ 0x8a99cef5, "iwl_get_shared_mem_conf" },
	{ 0x157c56dc, "ptp_clock_unregister" },
	{ 0xd9a5ea54, "__init_waitqueue_head" },
	{ 0xb44ad4b3, "_copy_to_user" },
	{ 0x83bb51e5, "debugfs_create_u32" },
	{ 0xd977aa99, "__iwl_dbg" },
	{ 0x69b18f43, "rfc1042_header" },
	{ 0x97934ecf, "del_timer_sync" },
	{ 0xcac89ebf, "cfg80211_chandef_usable" },
	{ 0x3c80c06c, "kstrtoull" },
	{ 0xc5d1476, "cfg80211_vendor_cmd_reply" },
	{ 0x7e526bfa, "__x86_indirect_thunk_r10" },
	{ 0x4e6a1b14, "iwl_tm_init" },
	{ 0xfb578fc5, "memset" },
	{ 0x6bedf402, "ieee80211_freq_khz_to_channel" },
	{ 0x3dad9978, "cancel_delayed_work" },
	{ 0x877e9c1b, "ieee80211_tx_dequeue" },
	{ 0xcb341b18, "cfg80211_bss_flush" },
	{ 0x1d12716e, "iwl_sar_geo_support" },
	{ 0x6e991f60, "default_llseek" },
	{ 0xe0875eb1, "kstrtobool" },
	{ 0x46045dd7, "kstrtou8" },
	{ 0xe0eb5838, "iwl_init_notification_wait" },
	{ 0x37befc70, "jiffies_to_msecs" },
	{ 0x647ef8c7, "iwl_free_fw_paging" },
	{ 0xb37b318c, "iwl_rs_pretty_bw" },
	{ 0xac7dc375, "ieee80211_alloc_hw_nm" },
	{ 0x3a9c3a45, "ieee80211_channel_switch_disconnect" },
	{ 0x977f511b, "__mutex_init" },
	{ 0xc5850110, "printk" },
	{ 0x55f79b6b, "iwl_dnt_dispatch_handle_nic_err" },
	{ 0xbfc777d5, "led_classdev_register_ext" },
	{ 0xbcab6ee6, "sscanf" },
	{ 0xf878c587, "ieee80211_free_txskb" },
	{ 0x8c3253ec, "_raw_spin_trylock" },
	{ 0x59c13bed, "ieee80211_key_mic_failure" },
	{ 0x3c3fce39, "__local_bh_enable_ip" },
	{ 0x1cdfc6bb, "ieee80211_data_to_8023_exthdr" },
	{ 0xa85f7152, "ieee80211_iter_keys_rcu" },
	{ 0x449ad0a7, "memcmp" },
	{ 0x408dd7c5, "iwl_parse_nvm_mcc_info" },
	{ 0x452ba683, "ipv6_ext_hdr" },
	{ 0x46f9f6e6, "ieee80211_rate_control_register" },
	{ 0xdca61efa, "ieee80211_beacon_get_template" },
	{ 0x5d26bbbc, "iwl_fwrt_dump_error_logs" },
	{ 0xf74bb274, "mod_delayed_work_on" },
	{ 0x49e0135d, "iwl_new_rate_from_v1" },
	{ 0xf49fcf35, "ieee80211_wake_queues" },
	{ 0xa5458fe5, "ieee80211_sta_pspoll" },
	{ 0x77c39b5f, "thermal_zone_device_register" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0xef819769, "ieee80211_beacon_set_cntdwn" },
	{ 0x949fadc7, "iwl_tm_set_fw_ver" },
	{ 0x839e2ef7, "nla_put" },
	{ 0x27e5a3f6, "iwl_write32" },
	{ 0xe151f242, "ieee80211_beacon_cntdwn_is_complete" },
	{ 0x2600773, "debugfs_remove" },
	{ 0x45854ccc, "kmem_cache_free" },
	{ 0x2ab7989d, "mutex_lock" },
	{ 0x69dd3b5b, "crc32_le" },
	{ 0xa291547, "ieee80211_remain_on_channel_expired" },
	{ 0x652032cb, "mac_pton" },
	{ 0xea1b26fc, "iwl_nvm_fixups" },
	{ 0xf1969a8e, "__usecs_to_jiffies" },
	{ 0xf435a7e0, "ieee80211_sta_block_awake" },
	{ 0xfdb12285, "ieee80211_find_sta_by_ifaddr" },
	{ 0xc38c83b8, "mod_timer" },
	{ 0xfda9581f, "prandom_u32" },
	{ 0xb6a68816, "find_last_bit" },
	{ 0xd635ff26, "ptp_clock_register" },
	{ 0xf4dc2fe, "ieee80211_reserve_tid" },
	{ 0x2276db98, "kstrtoint" },
	{ 0xb432b981, "iwl_fw_dbg_collect" },
	{ 0xc2905e02, "simple_open" },
	{ 0xf55ea024, "debugfs_create_bool" },
	{ 0xe3a53f4c, "sort" },
	{ 0xe6257e29, "_dev_err" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0xf99aba57, "ieee80211_gtk_rekey_add" },
	{ 0x4ea5d10, "ksize" },
	{ 0x9f46ced8, "__sw_hweight64" },
	{ 0xda91af63, "ieee80211_rx_ba_timer_expired" },
	{ 0x9c1af708, "iwl_acpi_get_dsm_u8" },
	{ 0xc4f0d223, "iwl_write_prph_delay" },
	{ 0x843aa85e, "wiphy_to_ieee80211_hw" },
	{ 0x447339c5, "__cfg80211_send_event_skb" },
	{ 0x9d6cba30, "cfg80211_find_elem_match" },
	{ 0xa1247034, "ieee80211_remove_key" },
	{ 0x7cd8d75e, "page_offset_base" },
	{ 0x1c4a0f62, "ieee80211_stop_tx_ba_cb_irqsafe" },
	{ 0x9de6b93a, "ieee80211_get_channel_khz" },
	{ 0x3ba859c1, "module_put" },
	{ 0x7c979d70, "_iwl_dbg_tlv_time_point" },
	{ 0xdd1289b6, "iwl_sar_get_wrds_table" },
	{ 0x7c888837, "cfg80211_pmsr_complete" },
	{ 0xbbfaa9e3, "iwl_read_external_nvm" },
	{ 0xc0a840a1, "iwl_tm_gnl_send_rx" },
	{ 0xb1de7ccc, "iwlwifi_mod_params" },
	{ 0x10c4a582, "kmem_cache_alloc" },
	{ 0xceeb51d6, "__free_pages" },
	{ 0xb601be4c, "__x86_indirect_thunk_rdx" },
	{ 0xe58888b5, "iwl_dnt_init" },
	{ 0x85945ee2, "iwl_fw_dbg_error_collect" },
	{ 0xc9ac790b, "__alloc_skb" },
	{ 0xf70d7c93, "iwl_pnvm_load" },
	{ 0x87927054, "iwl_fw_lookup_cmd_ver" },
	{ 0xd8e09da4, "ieee80211_set_key_rx_seq" },
	{ 0xb3d18d49, "__cfg80211_alloc_event_skb" },
	{ 0x8ef19fcd, "__cfg80211_alloc_reply_skb" },
	{ 0xa27cbeb6, "put_device" },
	{ 0x49c41a57, "_raw_spin_unlock_bh" },
	{ 0xb2fcb56d, "queue_delayed_work_on" },
	{ 0x81bc92f0, "__iwl_info" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0xbb43816d, "skb_checksum_help" },
	{ 0xd1ce8a4b, "ieee80211_sta_uapsd_trigger" },
	{ 0x27c6254, "ieee80211_sta_set_buffered" },
	{ 0x8ddd8aad, "schedule_timeout" },
	{ 0xb8b9f817, "kmalloc_order_trace" },
	{ 0x47e0ff82, "kfree_skb" },
	{ 0x6a3b11ef, "device_reprobe" },
	{ 0x183dcd3b, "ieee80211_get_key_rx_seq" },
	{ 0x440e702e, "pm_wakeup_dev_event" },
	{ 0x7b0192da, "kstrtou16" },
	{ 0xb5e73116, "flush_delayed_work" },
	{ 0x21dc5982, "ieee80211_iter_keys" },
	{ 0x6644dca6, "ieee80211_find_sta" },
	{ 0x2ea2c95c, "__x86_indirect_thunk_rax" },
	{ 0x9038811a, "iwl_rfi_guid" },
	{ 0x4fc2c3fd, "cfg80211_pmsr_report" },
	{ 0xa596903e, "__iwl_warn" },
	{ 0xbcd041ad, "iwl_init_paging" },
	{ 0x7f24de73, "jiffies_to_usecs" },
	{ 0x2edbeaf7, "hex2bin" },
	{ 0x84bb50e1, "iwl_rs_pretty_ant" },
	{ 0xbe935540, "pskb_expand_head" },
	{ 0xed9beb1b, "iwl_acpi_get_tas" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x467df16d, "netdev_rss_key_fill" },
	{ 0xcbd4898c, "fortify_panic" },
	{ 0xcc5005fe, "msleep_interruptible" },
	{ 0x35033c81, "iwl_phy_db_free" },
	{ 0xf5cb25c8, "kmem_cache_alloc_trace" },
	{ 0xdbf17652, "_raw_spin_lock" },
	{ 0x470ea651, "iwl_get_nvm" },
	{ 0x1332e4de, "iwl_abort_notification_waits" },
	{ 0xd1bab5e3, "ieee80211_stop_rx_ba_session" },
	{ 0x4e9c3473, "get_device" },
	{ 0x4302d0eb, "free_pages" },
	{ 0x3eeb2322, "__wake_up" },
	{ 0x5c52e109, "iwl_opmode_deregister" },
	{ 0x78971d7e, "iwl_he_is_sgi" },
	{ 0xc67dd6b1, "__ieee80211_get_radio_led_name" },
	{ 0x98ea53b9, "ieee80211_rate_control_unregister" },
	{ 0xf6ebc03b, "net_ratelimit" },
	{ 0xf822b42f, "ieee80211_sta_eosp" },
	{ 0x2d4d5f99, "iwl_sar_geo_init" },
	{ 0x8c26d495, "prepare_to_wait_event" },
	{ 0x6514dea8, "ieee80211_restart_hw" },
	{ 0x79c3304f, "_dmi_match" },
	{ 0xf278378d, "ieee80211_register_hw" },
	{ 0xc47f03fe, "led_classdev_unregister" },
	{ 0x336b727c, "thermal_cooling_device_register" },
	{ 0x150e3657, "_raw_read_lock_bh" },
	{ 0xad10eb8, "_raw_read_unlock_bh" },
	{ 0x1d13e5ed, "iwl_fw_dbg_collect_desc" },
	{ 0x1eb9516e, "round_jiffies_relative" },
	{ 0x37a0cba, "kfree" },
	{ 0x69ad2f20, "kstrtouint" },
	{ 0x6f4684d8, "ieee80211_beacon_loss" },
	{ 0x69acdf38, "memcpy" },
	{ 0xc19a3100, "ieee80211_start_tx_ba_session" },
	{ 0xa20ea83b, "iwl_fw_dbg_collect_trig" },
	{ 0xf3188e6a, "iwl_fw_runtime_init" },
	{ 0x1c8a906, "debugfs_create_blob" },
	{ 0x27c3c7a0, "ptp_clock_index" },
	{ 0x1c9158d3, "thermal_zone_device_update" },
	{ 0x3643b80f, "ieee80211_chandef_to_operating_class" },
	{ 0x88b59648, "skb_add_rx_frag" },
	{ 0xbd94d0ca, "ieee80211_iterate_stations_atomic" },
	{ 0xbcb234a3, "ieee80211_get_tkip_p2k" },
	{ 0xc0763484, "rfkill_blocked" },
	{ 0x96848186, "scnprintf" },
	{ 0x9252b3da, "ieee80211_nan_func_match" },
	{ 0x3fa5cb6b, "iwl_fw_lookup_notif_ver" },
	{ 0x78e15e79, "iwl_fw_runtime_suspend" },
	{ 0x74c134b9, "__sw_hweight32" },
	{ 0xe75b7e77, "iwl_notification_wait" },
	{ 0x26aca994, "ieee80211_free_hw" },
	{ 0xb352177e, "find_first_bit" },
	{ 0x92540fbf, "finish_wait" },
	{ 0xd9c7b7ab, "iwl_read_ppag_table" },
	{ 0xab6ad90d, "iwl_acpi_get_mcc" },
	{ 0xa8a37459, "debugfs_create_symlink" },
	{ 0xc4f21948, "ieee80211_update_mu_groups" },
	{ 0x776221bf, "iwl_send_phy_db_data" },
	{ 0x2eeedb47, "_dmi_check_system" },
	{ 0x6f18b0e3, "nla_put_64bit" },
	{ 0xf1d2845e, "iwl_dbg_tlv_del_timers" },
	{ 0xc5b6f236, "queue_work_on" },
	{ 0x8e281574, "nla_reserve" },
	{ 0x656e4a6e, "snprintf" },
	{ 0xe113bbbc, "csum_partial" },
	{ 0x966c2150, "consume_skb" },
	{ 0x61808282, "ieee80211_unreserve_tid" },
	{ 0x7f02188f, "__msecs_to_jiffies" },
	{ 0x5988395c, "iwl_notification_wait_init" },
	{ 0x21e6d010, "iwl_dnt_free" },
	{ 0x3c802b64, "skb_put" },
	{ 0x1bb01d41, "iwl_dnt_dispatch_collect_ucode_message" },
	{ 0x1910f14b, "cfg80211_bss_iter" },
	{ 0x831127f4, "ieee80211_chswitch_done" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0xd63eeb64, "iwl_configure_rxq" },
	{ 0xfc12af91, "ieee80211_sched_scan_stopped" },
	{ 0xafa3dde5, "cfg80211_vendor_cmd_get_sender" },
	{ 0xed905130, "ieee80211_iterate_interfaces" },
	{ 0xb2626a5a, "iwl_set_soc_latency" },
	{ 0xa7f8210b, "iwl_uefi_get_sgom_table" },
	{ 0xb35d64d2, "ieee80211_report_wowlan_wakeup" },
	{ 0x78576c78, "ieee80211_connection_loss" },
	{ 0x6e720ff2, "rtnl_unlock" },
	{ 0x11dfd603, "ieee80211_start_tx_ba_cb_irqsafe" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x1937241e, "try_module_get" },
	{ 0x63f5308, "ieee80211_get_tkip_p1k_iv" },
	{ 0x41cb987c, "regulatory_set_wiphy_regd_sync" },
	{ 0xec0542d, "device_set_wakeup_enable" },
	{ 0x78ba69e8, "ieee80211_gtk_rekey_notify" },
	{ 0xbf1c5ffb, "ieee80211_stop_tx_ba_session" },
	{ 0x70fbbb41, "thermal_zone_device_unregister" },
	{ 0xfe2dbd0, "ieee80211_beacon_update_cntdwn" },
};

MODULE_INFO(depends, "iwlwifi,mac80211,compat,cfg80211");


MODULE_INFO(srcversion, "2625C1E1D6DB965F0D9C833");
