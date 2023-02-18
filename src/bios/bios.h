#ifndef _BIOS_H_
#define _BIOS_H_

#include "../status/status.h"
#include "../memory/ram.h"

#define _DEVICE_IS_BOOTABLE 1
#define _MBR_LOAD_RAM_ADDR 0x7c00

/* Checks for BIOS signature. returns 1 if found*/
unsigned int bios_is_bootable (FILE* device_name,_status* status);
/* Loads the MBR Master Block Record to _MBR_LOAD_RAM_ADDR RAM address */
unsigned int bios_load_MBR_TO_RAM (FILE* device,_ram_ptr ram_ptr,_status* status);

#endif // _BIOS_H_