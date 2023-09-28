#ifndef _CONFIG_H_
#define _CONFIG_H_

/* predefined values for registers at reset and power-up */

#define _CONF_RESET_DEFAULT_CS 0xF000
#define _CONF_RESET_DEFAULT_DS 0x0000
#define _CONF_RESET_DEFAULT_ES 0x0000
#define _CONF_RESET_DEFAULT_SS 0x0000
#define _CONF_RESET_DEFAULT_FS 0x0000
#define _CONF_RESET_DEFAULT_GS 0x0000

#define _CONF_RESET_DEFAULT_EAX_AL 0x00
#define _CONF_RESET_DEFAULT_EAX_AH 0x00
#define _CONF_RESET_DEFAULT_EAX_MSB 0x0000

#define _CONF_RESET_DEFAULT_EDX_DH 0x3 // Device ID : 3 indicates i80386 component
#define _CONF_RESET_DEFAULT_EDX_DL 0x3 // Revision Level ID

#define _CONF_RESET_DEFAULT_EIP_IP 0xFFF0
#define _CONF_RESET_DEFAULT_EIP_msb 0x0000

#define _CONF_RESET_DEFAULT_EFLAG_CARRY 0UL
#define _CONF_RESET_DEFAULT_EFLAG_RES1 1UL
#define _CONF_RESET_DEFAULT_EFLAG_PARITY 0UL
#define _CONF_RESET_DEFAULT_EFLAG_RES3 0UL
#define _CONF_RESET_DEFAULT_EFLAG_AUX_CARRY 0UL
#define _CONF_RESET_DEFAULT_EFLAG_RES5 0UL
#define _CONF_RESET_DEFAULT_EFLAG_ZERO 0UL
#define _CONF_RESET_DEFAULT_EFLAG_SIGN 0UL
#define _CONF_RESET_DEFAULT_EFLAG_TRAP 0UL
#define _CONF_RESET_DEFAULT_EFLAG_INTR_ENABLE 0UL
#define _CONF_RESET_DEFAULT_EFLAG_DIREC 0UL
#define _CONF_RESET_DEFAULT_EFLAG_OVERF 0UL
#define _CONF_RESET_DEFAULT_EFLAG_IO_PREV_LEV 0UL
#define _CONF_RESET_DEFAULT_EFLAG_NESTED_TASK 0UL
#define _CONF_RESET_DEFAULT_EFLAG_RES15 0UL
#define _CONF_RESET_DEFAULT_EFLAG_RESUME 0UL
#define _CONF_RESET_DEFAULT_EFLAG_VIRT_8086_MODE 0UL
#define _CONF_RESET_DEFAULT_EFLAG_RES18_31 0UL

#define _CONF_RESET_DEFAULT_CR0_PE 0UL // if 0: protection not enabled (real address mode)
#define _CONF_RESET_DEFAULT_CR0_MP 0UL // if 0: coprocessor not present
#define _CONF_RESET_DEFAULT_CR0_EM 0UL // if 0: do not monitor coprocessor
#define _CONF_RESET_DEFAULT_CR0_TS 0UL // if 0: no task switch
#define _CONF_RESET_DEFAULT_CR0_ET 0UL // indicates presense of 80387
#define _CONF_RESET_DEFAULT_CR0_PG 0UL // if 0: paging disabled

#define _CONF_RESET_DEFAULT_IDTR 0x0000fff0

/* Pins power up  values */
#define _CONF_PIN_BUSY_POW_UP 0UL
#define _CONF_PIN_RESET_POW_UP 0UL

/* Others */
#define _CONF_MAX_LEN_DEVICE_NAME 200UL

#endif // _CONFIG_H_