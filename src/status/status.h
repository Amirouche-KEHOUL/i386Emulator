#ifndef _STATUS_H
#define _STATUS_H

/* _STATUS */
#define _STATUS_SYSTEM_SHUTDOWN 4
#define _STATUS_DEVICE_BOOT_SIG_NOT_FOUND 3
#define _STATUS_NO_DEVICE 2
#define _STATUS_END_OF_RESET 1
#define _STATUS_OK 0

/* _ERRORS */
#define _ERR_OPEN_DEVICE_NOK -1
#define _ERR_PYSICAL_MEMORY_ADDR_OUTRANGE -2
#define _ERR_PHYSICAL_MEMORY_MALLOC -3
#define _ERR_PHYSICAL_MEMORY_NULL_POINTER_ARG -4
#define _ERR_IO_MEMORY_ADDR_OUTRANGE -5
#define _ERR_REG_INIT -6
#define _ERR_BIOS_NULL_POINTER_ARG -7

void err_print(void);
void err_handler(char *message);

#endif //_STATUS_H