/*
 * Copyright (C) 2009 Google, Inc.
 * Copyright (C) 2009 HTC Corporation.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

/* Control bluetooth power for htcleo platform */

#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/rfkill.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <asm/mach-types.h>

#include "gpio_chip.h"
#include "proc_comm.h"
#include "board-htcleo.h"

#define HTC_RFKILL_DBG
#define MAX_BT_SIZE 0x6U

static struct rfkill *bt_rfk;
static const char bt_name[] = "bcm4329";
static int pre_state;


/* Fix BT address for Leo */
static unsigned char bt_bd_ram[MAX_BT_SIZE] = {0x50,0xC3,0x00,0x00,0x00,0x00};
unsigned char *get_bt_bd_ram(void)
{
	return (bt_bd_ram);
}


/* bt initial configuration */
static uint32_t htcleo_bt_init_table[] = {

	PCOM_GPIO_CFG(HTCLEO_GPIO_BT_UART1_RTS, /* BT_RTS */
				2,
				GPIO_OUTPUT,
				GPIO_NO_PULL,
				GPIO_8MA),
	PCOM_GPIO_CFG(HTCLEO_GPIO_BT_UART1_CTS, /* BT_CTS */
				0,
				GPIO_INPUT,
				GPIO_PULL_UP,
				GPIO_8MA),
	PCOM_GPIO_CFG(HTCLEO_GPIO_BT_UART1_RX, /* BT_RX */
				0,
				GPIO_INPUT,
				GPIO_PULL_UP,
				GPIO_8MA),
	PCOM_GPIO_CFG(HTCLEO_GPIO_BT_UART1_TX, /* BT_TX */
				2,
				GPIO_OUTPUT,
				GPIO_NO_PULL,
				GPIO_8MA),

	PCOM_GPIO_CFG(HTCLEO_GPIO_BT_RESET_N, /* BT_RESET_N */
				0,
				GPIO_OUTPUT,
				GPIO_NO_PULL,
				GPIO_4MA),
	PCOM_GPIO_CFG(HTCLEO_GPIO_BT_SHUTDOWN_N, /* BT_SHUTDOWN_N */
				0,
				GPIO_OUTPUT,
				GPIO_NO_PULL,
				GPIO_4MA),

	PCOM_GPIO_CFG(HTCLEO_GPIO_BT_HOST_WAKE, /* BT_HOST_WAKE */
				0,
				GPIO_INPUT,
				GPIO_PULL_UP,
				GPIO_4MA),
	PCOM_GPIO_CFG(HTCLEO_GPIO_BT_CHIP_WAKE, /* BT_CHIP_WAKE */
				0,
				GPIO_OUTPUT,
				GPIO_NO_PULL,
				GPIO_4MA),
};

/* bt on configuration */
static uint32_t htcleo_bt_on_table[] = {

	PCOM_GPIO_CFG(HTCLEO_GPIO_BT_UART1_RTS, /* BT_RTS */
				2,
				GPIO_OUTPUT,
				GPIO_NO_PULL,
				GPIO_8MA),
	PCOM_GPIO_CFG(HTCLEO_GPIO_BT_UART1_CTS, /* BT_CTS */
				2,
				GPIO_INPUT,
				GPIO_PULL_UP,
				GPIO_8MA),
	PCOM_GPIO_CFG(HTCLEO_GPIO_BT_UART1_RX, /* BT_RX */
				2,
				GPIO_INPUT,
				GPIO_PULL_UP,
				GPIO_8MA),
	PCOM_GPIO_CFG(HTCLEO_GPIO_BT_UART1_TX, /* BT_TX */
				2,
				GPIO_OUTPUT,
				GPIO_NO_PULL,
				GPIO_8MA),

	PCOM_GPIO_CFG(HTCLEO_GPIO_BT_HOST_WAKE, /* BT_HOST_WAKE */
				0,
				GPIO_INPUT,
				GPIO_PULL_DOWN,
				GPIO_4MA),
	PCOM_GPIO_CFG(HTCLEO_GPIO_BT_CHIP_WAKE, /* BT_CHIP_WAKE */
				0,
				GPIO_OUTPUT,
				GPIO_PULL_UP,
				GPIO_4MA),

	PCOM_GPIO_CFG(HTCLEO_GPIO_BT_RESET_N, /* BT_RESET_N */
				0,
				GPIO_OUTPUT,
				GPIO_NO_PULL,
				GPIO_4MA),
	PCOM_GPIO_CFG(HTCLEO_GPIO_BT_SHUTDOWN_N, /* BT_SHUTDOWN_N */
				0,
				GPIO_OUTPUT,
				GPIO_NO_PULL,
				GPIO_4MA),
};

/* bt off configuration */
static uint32_t htcleo_bt_off_table[] = {

	PCOM_GPIO_CFG(HTCLEO_GPIO_BT_UART1_RTS, /* BT_RTS */
				0,
				GPIO_OUTPUT,
				GPIO_NO_PULL,
				GPIO_8MA),
	PCOM_GPIO_CFG(HTCLEO_GPIO_BT_UART1_CTS, /* BT_CTS */
				0,
				GPIO_INPUT,
				GPIO_PULL_UP,
				GPIO_8MA),
	PCOM_GPIO_CFG(HTCLEO_GPIO_BT_UART1_RX, /* BT_RX */
				0,
				GPIO_INPUT,
				GPIO_PULL_UP,
				GPIO_8MA),
	PCOM_GPIO_CFG(HTCLEO_GPIO_BT_UART1_TX, /* BT_TX */
				0,
				GPIO_OUTPUT,
				GPIO_NO_PULL,
				GPIO_8MA),

	PCOM_GPIO_CFG(HTCLEO_GPIO_BT_RESET_N, /* BT_RESET_N */
				0,
				GPIO_OUTPUT,
				GPIO_NO_PULL,
				GPIO_4MA),
	PCOM_GPIO_CFG(HTCLEO_GPIO_BT_SHUTDOWN_N, /* BT_SHUTDOWN_N */
				0,
				GPIO_OUTPUT,
				GPIO_NO_PULL,
				GPIO_4MA),

	PCOM_GPIO_CFG(HTCLEO_GPIO_BT_HOST_WAKE, /* BT_HOST_WAKE */
				0,
				GPIO_INPUT,
				GPIO_PULL_UP,
				GPIO_4MA),
	PCOM_GPIO_CFG(HTCLEO_GPIO_BT_CHIP_WAKE, /* BT_CHIP_WAKE */
				0,
				GPIO_OUTPUT,
				GPIO_NO_PULL,
				GPIO_4MA),
};

static void config_bt_table(uint32_t *table, int len)
{
	int n;
	unsigned id;
	for (n = 0; n < len; n++) {
		id = table[n];
		msm_proc_comm(PCOM_RPC_GPIO_TLMM_CONFIG_EX, &id, 0);
	}
}

static void htcleo_config_bt_init(void)
{
	/* set bt initial configuration*/
	config_bt_table(htcleo_bt_init_table,
				ARRAY_SIZE(htcleo_bt_init_table));
	mdelay(5);

	/* BT_RESET_N */
	gpio_configure(HTCLEO_GPIO_BT_RESET_N,
				GPIOF_DRIVE_OUTPUT | GPIOF_OUTPUT_LOW);
	mdelay(2);
	/* BT_SHUTDOWN_N */
	gpio_configure(HTCLEO_GPIO_BT_SHUTDOWN_N,
				GPIOF_DRIVE_OUTPUT | GPIOF_OUTPUT_LOW);
	mdelay(2);

	/* BT_CHIP_WAKE */
	gpio_configure(HTCLEO_GPIO_BT_CHIP_WAKE,
				GPIOF_DRIVE_OUTPUT | GPIOF_OUTPUT_HIGH);

}

static void htcleo_config_bt_on(void)
{

	#ifdef HTC_RFKILL_DBG
	printk(KERN_INFO "-- RK ON --\n");
	#endif

	/* set bt on configuration*/
	config_bt_table(htcleo_bt_on_table,
				ARRAY_SIZE(htcleo_bt_on_table));
	mdelay(5);

	/* BT_RESET_N */
	gpio_configure(HTCLEO_GPIO_BT_RESET_N,
				GPIOF_DRIVE_OUTPUT | GPIOF_OUTPUT_HIGH);
	mdelay(2);
	/* BT_SHUTDOWN_N */
	gpio_configure(HTCLEO_GPIO_BT_SHUTDOWN_N,
				GPIOF_DRIVE_OUTPUT | GPIOF_OUTPUT_HIGH);
	mdelay(2);
}

static void htcleo_config_bt_off(void)
{
	#ifdef HTC_RFKILL_DBG
	printk(KERN_INFO "-- RK OFF --\n");
	#endif

	/* BT_SHUTDOWN_N */
	gpio_configure(HTCLEO_GPIO_BT_SHUTDOWN_N,
				GPIOF_DRIVE_OUTPUT | GPIOF_OUTPUT_LOW);
	mdelay(2);
	/* BT_RESET_N */
	gpio_configure(HTCLEO_GPIO_BT_RESET_N,
				GPIOF_DRIVE_OUTPUT | GPIOF_OUTPUT_LOW);
	mdelay(2);

	/* set bt off configuration*/
	config_bt_table(htcleo_bt_off_table,
				ARRAY_SIZE(htcleo_bt_off_table));
	mdelay(5);

	/* BT_RTS */
	gpio_configure(HTCLEO_GPIO_BT_UART1_RTS,
				GPIOF_DRIVE_OUTPUT | GPIOF_OUTPUT_LOW);
	/* BT_TX */
	gpio_configure(HTCLEO_GPIO_BT_UART1_TX,
				GPIOF_DRIVE_OUTPUT | GPIOF_OUTPUT_LOW);

	/* BT_CHIP_WAKE */
	gpio_configure(HTCLEO_GPIO_BT_CHIP_WAKE,
				GPIOF_DRIVE_OUTPUT | GPIOF_OUTPUT_LOW);
}

static int bluetooth_set_power(void *data, bool blocked)
{
	if (pre_state == blocked) {
		#ifdef HTC_RFKILL_DBG
		printk(KERN_INFO "-- SAME ST --\n");
		#endif
		return 0;
	} else
		pre_state = blocked;

	if (!blocked)
		htcleo_config_bt_on();
	else
		htcleo_config_bt_off();

	return 0;
}

static struct rfkill_ops htcleo_rfkill_ops = {
	.set_block = bluetooth_set_power,
};

static int htcleo_rfkill_probe(struct platform_device *pdev)
{
	int rc = 0;
	bool default_state = true; /* off */

	htcleo_config_bt_init();	/* bt gpio initial config */

	bluetooth_set_power(NULL, default_state);

	bt_rfk = rfkill_alloc(bt_name, &pdev->dev, RFKILL_TYPE_BLUETOOTH,
						 &htcleo_rfkill_ops, NULL);
	if (!bt_rfk) {
		rc = -ENOMEM;
		goto err_rfkill_reset;
	}

	rfkill_set_states(bt_rfk, default_state, false);

	/* userspace cannot take exclusive control */
	rc = rfkill_register(bt_rfk);
	if (rc)
		goto err_rfkill_reg;

	return 0;

err_rfkill_reg:
	rfkill_destroy(bt_rfk);
err_rfkill_reset:
	return rc;
}

static int htcleo_rfkill_remove(struct platform_device *dev)
{
	rfkill_unregister(bt_rfk);
	rfkill_destroy(bt_rfk);
	gpio_free(HTCLEO_GPIO_BT_SHUTDOWN_N);
	gpio_free(HTCLEO_GPIO_BT_RESET_N);

	return 0;
}

static struct platform_driver htcleo_rfkill_driver = {
	.probe = htcleo_rfkill_probe,
	.remove = htcleo_rfkill_remove,
	.driver = {
		.name = "htcleo_rfkill",
		.owner = THIS_MODULE,
	},
};

static int __init htcleo_rfkill_init(void)
{
	pre_state = -1;
	if (!machine_is_htcleo())
		return 0;

	return platform_driver_register(&htcleo_rfkill_driver);
}

static void __exit htcleo_rfkill_exit(void)
{
	platform_driver_unregister(&htcleo_rfkill_driver);
}

module_init(htcleo_rfkill_init);
module_exit(htcleo_rfkill_exit);
MODULE_DESCRIPTION("htcleo rfkill");
MODULE_AUTHOR("Markinus");
MODULE_LICENSE("GPL");
