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
	{ 0x7bd010e, "__iwl_err" },
	{ 0x35216b26, "kmalloc_caches" },
	{ 0xeb233a45, "__kmalloc" },
	{ 0x8133c67d, "complete_and_exit" },
	{ 0x1ed8b599, "__x86_indirect_thunk_r8" },
	{ 0xdae599ff, "iwl_parse_nvm_data" },
	{ 0x5c9f73e3, "generic_file_llseek" },
	{ 0x33504981, "iwl_sar_select_profile" },
	{ 0xb43a926b, "backport_dependency_symbol" },
	{ 0xf88964e4, "iwl_remove_notification" },
	{ 0x754d539c, "strlen" },
	{ 0x60a13e90, "rcu_barrier" },
	{ 0xfce95896, "iwl_acpi_get_ppag_table" },
	{ 0x21cdb86, "iwl_fw_start_dbg_conf" },
	{ 0x75160fcb, "iwl_cmd_groups_verify_sorted" },
	{ 0x2710c362, "iwl_dump_desc_assert" },
	{ 0xb1921ae0, "iwl_force_nmi" },
	{ 0x3c262547, "iwl_fw_dbg_stop_sync" },
	{ 0x4c1c952e, "iwl_dnt_start" },
	{ 0xce0c6460, "iwl_phy_db_set_section" },
	{ 0xb3635b01, "_raw_spin_lock_bh" },
	{ 0xcb46555e, "iwl_set_bits_mask_prph" },
	{ 0x7ef39823, "ieee80211_hdrlen" },
	{ 0x4708dc6e, "iwl_opmode_register" },
	{ 0x1c5756e4, "iwl_acpi_is_ppag_approved" },
	{ 0x56470118, "__warn_printk" },
	{ 0x66b4cc41, "kmemdup" },
	{ 0x1c7de9a7, "iwl_sar_get_ewrd_table" },
	{ 0x9fa7184a, "cancel_delayed_work_sync" },
	{ 0x409bcb62, "mutex_unlock" },
	{ 0x2b54d1d5, "dma_free_attrs" },
	{ 0x921ec64f, "debugfs_create_file" },
	{ 0x4629334c, "__preempt_count" },
	{ 0x97651e6c, "vmemmap_base" },
	{ 0x22453c63, "iwl_wait_notification" },
	{ 0xbc128cf0, "iwl_sar_get_wgds_table" },
	{ 0x36e58bcd, "pv_ops" },
	{ 0xe8bc695c, "kthread_create_on_node" },
	{ 0x9d82590c, "iwl_trans_send_cmd" },
	{ 0x8a99cef5, "iwl_get_shared_mem_conf" },
	{ 0xd9a5ea54, "__init_waitqueue_head" },
	{ 0x6de13801, "wait_for_completion" },
	{ 0xd977aa99, "__iwl_dbg" },
	{ 0x4e6a1b14, "iwl_tm_init" },
	{ 0x1d12716e, "iwl_sar_geo_support" },
	{ 0x961af15b, "iwl_tm_gnl_send_msg" },
	{ 0xe0eb5838, "iwl_init_notification_wait" },
	{ 0x647ef8c7, "iwl_free_fw_paging" },
	{ 0x977f511b, "__mutex_init" },
	{ 0xc5850110, "printk" },
	{ 0xbcab6ee6, "sscanf" },
	{ 0xa5cc5d9f, "kthread_stop" },
	{ 0x3c3fce39, "__local_bh_enable_ip" },
	{ 0x4c9d28b0, "phys_base" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0x949fadc7, "iwl_tm_set_fw_ver" },
	{ 0x27e5a3f6, "iwl_write32" },
	{ 0xfda0bdf3, "dma_alloc_attrs" },
	{ 0x45854ccc, "kmem_cache_free" },
	{ 0x2ab7989d, "mutex_lock" },
	{ 0xb432b981, "iwl_fw_dbg_collect" },
	{ 0xc2905e02, "simple_open" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0x5987fe45, "iwl_fw_lookup_assert_desc" },
	{ 0x7cd8d75e, "page_offset_base" },
	{ 0x7c979d70, "_iwl_dbg_tlv_time_point" },
	{ 0xdd1289b6, "iwl_sar_get_wrds_table" },
	{ 0xb1de7ccc, "iwlwifi_mod_params" },
	{ 0x10c4a582, "kmem_cache_alloc" },
	{ 0xb601be4c, "__x86_indirect_thunk_rdx" },
	{ 0xe58888b5, "iwl_dnt_init" },
	{ 0xc9ac790b, "__alloc_skb" },
	{ 0xf70d7c93, "iwl_pnvm_load" },
	{ 0x87927054, "iwl_fw_lookup_cmd_ver" },
	{ 0xa916b694, "strnlen" },
	{ 0x49c41a57, "_raw_spin_unlock_bh" },
	{ 0x81bc92f0, "__iwl_info" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0x8ddd8aad, "schedule_timeout" },
	{ 0xb8b9f817, "kmalloc_order_trace" },
	{ 0x47e0ff82, "kfree_skb" },
	{ 0xb5e73116, "flush_delayed_work" },
	{ 0x815f2897, "empty_zero_page" },
	{ 0x2ea2c95c, "__x86_indirect_thunk_rax" },
	{ 0xa596903e, "__iwl_warn" },
	{ 0xbcd041ad, "iwl_init_paging" },
	{ 0x76d31a6d, "wake_up_process" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0xcbd4898c, "fortify_panic" },
	{ 0x35033c81, "iwl_phy_db_free" },
	{ 0xf5cb25c8, "kmem_cache_alloc_trace" },
	{ 0xdbf17652, "_raw_spin_lock" },
	{ 0x4302d0eb, "free_pages" },
	{ 0x3eeb2322, "__wake_up" },
	{ 0x5c52e109, "iwl_opmode_deregister" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0x2d4d5f99, "iwl_sar_geo_init" },
	{ 0x8c26d495, "prepare_to_wait_event" },
	{ 0x1d13e5ed, "iwl_fw_dbg_collect_desc" },
	{ 0x37a0cba, "kfree" },
	{ 0xa35f2861, "iwl_phy_db_get_section_data" },
	{ 0x69acdf38, "memcpy" },
	{ 0xf3188e6a, "iwl_fw_runtime_init" },
	{ 0x3fa5cb6b, "iwl_fw_lookup_notif_ver" },
	{ 0xae384beb, "request_firmware" },
	{ 0xe75b7e77, "iwl_notification_wait" },
	{ 0x92540fbf, "finish_wait" },
	{ 0xd9c7b7ab, "iwl_read_ppag_table" },
	{ 0x776221bf, "iwl_send_phy_db_data" },
	{ 0xf1d2845e, "iwl_dbg_tlv_del_timers" },
	{ 0x656e4a6e, "snprintf" },
	{ 0x5988395c, "iwl_notification_wait_init" },
	{ 0x21e6d010, "iwl_dnt_free" },
	{ 0x3c802b64, "skb_put" },
	{ 0x1bb01d41, "iwl_dnt_dispatch_collect_ucode_message" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0x77106d4c, "release_firmware" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0xe484e35f, "ioread32" },
};

MODULE_INFO(depends, "iwlwifi,compat,cfg80211");


MODULE_INFO(srcversion, "1C2032949BA8F98BE4CC152");
