#ifndef _BIOS_H_
#define _BIOS_H_

#include "../status/status.h"

unsigned int bios_is_bootable (char* device_name,_status* status);

#endif // _BIOS_H_