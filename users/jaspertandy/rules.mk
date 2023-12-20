# Drashna's OLED driver for SH1107.
ifeq ($(strip $(OLED_DRIVER)), custom)
ifeq ($(strip $(OLED_ENABLE)), yes)
	OPT_DEFS += -DOLED_ENABLE -DOLED_DRIVER_SH1107
	SRC += $(USER_PATH)/oled/sh110x.c
	QUANTUM_LIB_SRC += i2c_master.c
	DEFERRED_EXEC_ENABLE = yes
endif
endif
