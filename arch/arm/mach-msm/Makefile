obj-y += proc_comm.o
obj-y += io.o irq.o timer.o dma.o memory.o
obj-y += vreg.o
obj-y += dex_comm.o
obj-y += devices.o
obj-y += amss_para.o
obj-y += pmic.o
obj-$(CONFIG_ARCH_MSM_ARM11) += acpuclock-arm11.o idle.o
obj-$(CONFIG_ARCH_MSM_SCORPION) += idle-v7.o
obj-$(CONFIG_ARCH_MSM_SCORPION) += arch-init-scorpion.o
obj-$(CONFIG_ARCH_QSD8X50) += acpuclock-qsd8x50.o
obj-$(CONFIG_ARCH_MSM7X30) += acpuclock-7x30.o
obj-y += gpio.o generic_gpio.o
obj-y += nand_partitions.o

obj-$(CONFIG_ARCH_QSD8X50) += sirc.o
obj-$(CONFIG_MSM_FIQ_SUPPORT) += fiq_glue.o
obj-$(CONFIG_MSM_SMD) += smd.o smd_debug.o
obj-$(CONFIG_MSM_SMD) += smd_tty.o
ifdef CONFIG_MACH_HTCLEO
obj-$(CONFIG_MSM_SMD) +=  smd_qmi_wince.o
obj-y += clock-wince.o 
else
obj-$(CONFIG_MSM_SMD) +=  smd_qmi.o
obj-y += clock-pcom.o
obj-y += clock.o 
endif
obj-$(CONFIG_MSM_SMD) += last_radio_log.o
obj-$(CONFIG_MSM_DAL) += dal.o
obj-$(CONFIG_MSM_ONCRPCROUTER) += smd_rpcrouter.o
obj-$(CONFIG_MSM_ONCRPCROUTER) += smd_rpcrouter_device.o
obj-$(CONFIG_MSM_ONCRPCROUTER) += smd_rpcrouter_servers.o
obj-$(CONFIG_MSM_RPCSERVERS) += rpc_server_dog_keepalive.o
obj-$(CONFIG_MSM_RPCSERVERS) += rpc_server_time_remote.o
obj-$(CONFIG_MSM_ADSP) += qdsp5/
obj-$(CONFIG_MSM_QDSP5V2) += qdsp5v2/
ifdef CONFIG_MACH_HTCLEO
obj-$(CONFIG_MSM_QDSP6) += qdsp6_1550/
else
obj-$(CONFIG_MSM_QDSP6) += qdsp6/
endif
obj-$(CONFIG_MSM_HW3D) += hw3d.o
obj-$(CONFIG_PM) += pm.o
obj-$(CONFIG_CPU_FREQ) += cpufreq.o
obj-$(CONFIG_MSM_REMOTE_SPINLOCK) += remote_spinlock.o
obj-$(CONFIG_MSM_SSBI) += ssbi.o

obj-$(CONFIG_MACH_TROUT) += board-trout.o devices-msm7x00.o
obj-$(CONFIG_MACH_TROUT) += board-trout-gpio.o
obj-$(CONFIG_MACH_TROUT) += board-trout-keypad.o board-trout-panel.o
obj-$(CONFIG_MACH_TROUT) += htc_akm_cal.o htc_wifi_nvs.o htc_acoustic.o
obj-$(CONFIG_MACH_TROUT) += board-trout-mmc.o
obj-$(CONFIG_MACH_TROUT) += board-trout-rfkill.o
obj-$(CONFIG_MACH_TROUT) += board-trout-wifi.o
obj-$(CONFIG_MACH_TROUT) += devices_htc.o
obj-$(CONFIG_TROUT_BATTCHG) += htc_battery.o
obj-$(CONFIG_MACH_SAPPHIRE) += board-sapphire.o board-sapphire-gpio.o
obj-$(CONFIG_MACH_SAPPHIRE) += board-sapphire-keypad.o board-sapphire-panel.o
obj-$(CONFIG_MACH_SAPPHIRE) += board-sapphire-mmc.o board-sapphire-wifi.o
obj-$(CONFIG_MACH_SAPPHIRE) += board-sapphire-rfkill.o msm_vibrator.o
obj-$(CONFIG_MACH_SAPPHIRE) += devices_htc.o
obj-$(CONFIG_MACH_MAHIMAHI) += board-mahimahi.o board-mahimahi-panel.o
obj-$(CONFIG_MACH_MAHIMAHI) += board-mahimahi-keypad.o board-mahimahi-mmc.o
obj-$(CONFIG_MACH_MAHIMAHI) += board-mahimahi-rfkill.o htc_wifi_nvs.o htc_awb_cal.o
obj-$(CONFIG_MACH_MAHIMAHI) += board-mahimahi-wifi.o board-mahimahi-audio.o
obj-$(CONFIG_MACH_MAHIMAHI) += msm_vibrator.o
obj-$(CONFIG_MACH_MAHIMAHI) += board-mahimahi-microp.o
obj-$(CONFIG_MACH_MAHIMAHI) += htc_acoustic_qsd.o
obj-$(CONFIG_MACH_HALIBUT) += board-halibut.o devices-msm7x00.o
obj-$(CONFIG_MACH_HALIBUT) += board-halibut-keypad.o
obj-$(CONFIG_MACH_HALIBUT) += board-halibut-panel.o fish_battery.o
obj-$(CONFIG_MACH_SWORDFISH) += board-swordfish.o
obj-$(CONFIG_MACH_SWORDFISH) += board-swordfish-keypad.o fish_battery.o
obj-$(CONFIG_MACH_SWORDFISH) += board-swordfish-panel.o
obj-$(CONFIG_MACH_SWORDFISH) += board-swordfish-mmc.o
obj-$(CONFIG_MACH_MSM7X30_SURF) += board-surf7x30.o
obj-$(CONFIG_ARCH_MSM7X30) += board-msm7x30.o devices-msm7x30.o
obj-$(CONFIG_ARCH_QSD8X50) += board-qsd8x50.o devices-qsd8x50.o

obj-$(CONFIG_MACH_BRAVO) += board-bravo.o board-bravo-panel.o
obj-$(CONFIG_MACH_BRAVO) += board-bravo-keypad.o board-bravo-mmc.o
obj-$(CONFIG_MACH_BRAVO) += board-bravo-rfkill.o htc_wifi_nvs.o htc_awb_cal.o
obj-$(CONFIG_MACH_BRAVO) += board-bravo-wifi.o board-bravo-audio.o
obj-$(CONFIG_MACH_BRAVO) += msm_vibrator.o
obj-$(CONFIG_MACH_BRAVO) += board-bravo-microp.o
obj-$(CONFIG_MACH_BRAVO) += htc_acoustic_qsd.o
obj-$(CONFIG_MACH_BRAVO) += board-bravo-tpa2018d1.o
obj-$(CONFIG_MACH_BRAVO) += board-bravo-smb329.o

obj-$(CONFIG_MACH_BRAVOC) += board-bravo.o board-bravo-panel.o
obj-$(CONFIG_MACH_BRAVOC) += board-bravo-keypad.o board-bravo-mmc.o
obj-$(CONFIG_MACH_BRAVOC) += board-bravo-rfkill.o htc_wifi_nvs.o htc_awb_cal.o
obj-$(CONFIG_MACH_BRAVOC) += board-bravo-wifi.o board-bravo-audio.o
obj-$(CONFIG_MACH_BRAVOC) += msm_vibrator.o
obj-$(CONFIG_MACH_BRAVOC) += board-bravo-microp.o
obj-$(CONFIG_MACH_BRAVOC) += htc_acoustic_qsd.o
obj-$(CONFIG_MACH_BRAVOC) += board-bravo-tpa2018d1.o
obj-$(CONFIG_MACH_BRAVOC) += board-bravo-smb329.o

obj-$(CONFIG_MACH_HTCLEO) += board-htcleo.o board-htcleo-panel.o board-htcleo-keypad.o
obj-$(CONFIG_MACH_HTCLEO) += board-htcleo-ts.o board-htcleo-mmc.o ieee754-df.o

obj-$(CONFIG_MACH_HTCLEO) += board-htcleo-audio.o 
obj-$(CONFIG_MACH_HTCLEO) += board-htcleo-rfkill.o board-htcleo-wifi.o board-htcleo-wifi-nvs.o board-htcleo-acoustic.o
obj-$(CONFIG_MACH_HTCLEO) += board-htcleo-microp.o board-htcleo-proximity.o board-htcleo-ls.o  board-htcleo-gsensor.o
obj-$(CONFIG_HTCLEO_BACKLIGHT) += board-htcleo-bl.o
obj-$(CONFIG_HTCLEO_BACKLIGHT_LED) += board-htcleo-bl-led.o
obj-$(CONFIG_HTCLEO_BTN_BACKLIGHT_MANAGER) += board-htcleo-btn_backlight-manager.o

obj-$(CONFIG_HTC_HEADSET_MGR) += htc_headset_mgr.o
obj-$(CONFIG_HTC_HEADSET_GPIO) += htc_headset_gpio.o
obj-$(CONFIG_HTC_BATTCHG) += htc_battery.o
obj-$(CONFIG_HTC_PWRSINK) += htc_pwrsink.o
obj-$(CONFIG_HTC_PWRSPLY) += htc_power_supply.o
obj-$(CONFIG_HTC_HEADSET) += htc_headset.o
obj-$(CONFIG_HTC_AUDIO_JACK) += htc_audio_jack.o
obj-$(CONFIG_HTC_35MM_JACK) += htc_35mm_jack.o
obj-$(CONFIG_ARCH_MSM_FLASHLIGHT) += msm_flashlight.o

obj-$(CONFIG_MACH_MAHIMAHI) += board-mahimahi-tpa2018d1.o
obj-$(CONFIG_MACH_MAHIMAHI) += board-mahimahi-smb329.o

obj-$(CONFIG_HTC_FB_CONSOLE) += htc_fb_console.o

