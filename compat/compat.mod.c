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
	{ 0xad995dac, "netdev_stats_to_stats64" },
	{ 0x60a13e90, "rcu_barrier" },
	{ 0x56470118, "__warn_printk" },
	{ 0x4629334c, "__preempt_count" },
	{ 0xc5e4a5d1, "cpumask_next" },
	{ 0xbc93792a, "netif_rx" },
	{ 0x17de3d5, "nr_cpu_ids" },
	{ 0xde4c1a24, "param_ops_charp" },
	{ 0x7aaab7d1, "netif_rx_ni" },
	{ 0x9e683f75, "__cpu_possible_mask" },
	{ 0xc5850110, "printk" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0x2ea2c95c, "__x86_indirect_thunk_rax" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0xb19a5453, "__per_cpu_offset" },
	{ 0xd262dfcb, "vscnprintf" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "D35E7EF5F7246968007C742");
