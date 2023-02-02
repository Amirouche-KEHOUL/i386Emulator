#ifndef _CONFIG_H_
#define _CONFIG_H_

/* predefined values for registers at reset and power-up */

#define CONF_RESET_DEFAULT_CS 0xF000 
#define CONF_RESET_DEFAULT_DS 0x0000
#define CONF_RESET_DEFAULT_ES 0x0000
#define CONF_RESET_DEFAULT_SS 0x0000
#define CONF_RESET_DEFAULT_FS 0x0000
#define CONF_RESET_DEFAULT_GS 0x0000

#define CONF_RESET_DEFAULT_EAX_AL 0x00
#define CONF_RESET_DEFAULT_EAX_AH 0x00
#define CONF_RESET_DEFAULT_EAX_MSB 0x0000


/* Pins power up  values */

#define CONF_PIN_BUSY_POW_UP 0
#define CONF_PIN_RESET_POW_UP 0


#endif // _CONFIG_H_