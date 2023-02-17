#ifndef _STATUS_H
#define _STATUS_H

#include <stdio.h>

typedef int _status ; 

/* _STATUS */
#define _STATUS_OK 0
#define _STATUS_END_OF_RESET 1
#define _STATUS_NO_DEVICE 2 
#define _STATUS_DEVICE_BOOT_SIG_NOT_FOUND 3

/* _ERRORS */
#define _ERR_RAM_ADDR_OUTRANGE -1  
#define _ERR_RAM_MALLOC -2  
#define _ERR_RAM_NULL_POINTER -3 
#define _ERR_REG_NULL_POINTER -4
#define _ERR_PIN_NULL_POINTER -5
#define _ERR_SYS_NULL_POINTER -6
#define _ERR_REG_INIT -7
#define _ERR_BIOS_NULL_POINTER -8
#define _ERR_OPEN_DEVICE_NOK -9


void err_print (_status* status);
void err_handler(_status* status,char* message);

#endif //_STATUS_H