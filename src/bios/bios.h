#ifndef _BIOS_H_
#define _BIOS_H_

#include "../status/status.h"

#define _DEVICE_IS_BOOTABLE 1

/* Checks for BIOS signature. returns 1 if found*/
unsigned int bios_is_bootable (FILE* device_name,_status* status);

#endif // _BIOS_H_