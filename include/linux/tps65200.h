/*
 * Copyright (C) 2007 HTC Incorporated
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#ifndef _TPS65200_H_
#define _TPS65200_H_
#include <linux/notifier.h>
//#include <mach/htc_battery.h>

#define ENABLE_LIMITED_CHG      0x10
#define CLEAR_LIMITED_CHG       0x11
#define CHECK_CHG		0X64
#define SET_ICL500		0X65
#define SET_ICL100		0X66
#define CHECK_INT2		0X67
#define OVERTEMP_VREG		0XC8
#define NORMALTEMP_VREG		0XC9
#define CHECK_INT1		0XCA
#define CHECK_CONTROL		0xCB
#define NORMALTEMP_VREG_HV	0xCC

enum wled_ctl_t {
	WLED_DISABLE = 0,
	WLED_ENABLE,
	WLED_STATUS
};

struct tps65200_chg_int_data {
	int gpio_chg_int;
	int tps65200_reg;
	struct delayed_work int_work;
};

struct tps65200_platform_data {
	int charger_check;
	int gpio_chg_stat;
	int gpio_chg_int;
};

struct tps65200_chg_int_notifier {
	struct list_head notifier_link;
	const char *name;
	void (*func)(int int_reg, int value);
};

#ifdef CONFIG_TPS65200
extern int tps_set_charger_ctrl(u32 ctl);
extern int tps_register_notifier(struct tps65200_chg_int_notifier *notifier);
#else
static int tps_set_charger_ctrl(u32 ctl) { return 0 ; }
#endif
#endif
