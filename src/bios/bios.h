#ifndef _BIOS_H_
#define _BIOS_H_

#include "../pins/pins.h"
#include "../sys/sys.h"
#include "../memory/ram.h"
#include "../memory/registers.h"
#include "../status/status.h"

#define _DEVICE_IS_BOOTABLE 1
#define _MBR_LOAD_RAM_ADDR 0x7c00

/* Checks for BIOS signature. returns 1 if found*/
unsigned int bios_is_bootable (const FILE* device_name,_status* status);

/* 
Loads the MBR Master Block Record to _MBR_LOAD_RAM_ADDR RAM address.
Forces CS:IP to 0x(0000:_MBR_LOAD_RAM_ADDR).
*/
unsigned int bios_load_MBR_TO_RAM (const FILE* device,_ram_ptr ram_ptr0,_segment_regs_st* segment_regs_st ,_eip_st* eip_st ,_status* status);

#endif // _BIOS_H_