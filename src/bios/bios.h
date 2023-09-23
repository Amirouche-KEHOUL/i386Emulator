/**
 * @file bios.h
 * @author Amirouche KEHOUL (amirouchekehoul7@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-09-23
 *
 */
#ifndef _BIOS_H_
#define _BIOS_H_

#include "../pins/pins.h"
#include "../sys/sys.h"
#include "../memory/ram.h"
#include "../memory/registers.h"
#include "../status/status.h"

#define _DEVICE_IS_BOOTABLE 1
#define _MBR_LOAD_RAM_ADDR 0x7c00

/**
 * @brief Checks if device is bootable MSB (Master Block Record).
 *
 * @param device_name
 * @return _DEVICE_IS_BOOTABLE if MSB found. _STATUS_DEVICE_BOOT_SIG_NOT_FOUND else.
 */
unsigned int bios_is_bootable(FILE *device_name);

/*
Loads the MBR Master Block Record to _MBR_LOAD_RAM_ADDR RAM address.
Forces CS:IP to 0x(0000:_MBR_LOAD_RAM_ADDR).
*/
unsigned int bios_load_MBR_TO_RAM(FILE *device, _ram_ptr ram_ptr0, _segment_regs_st *segment_regs_st, _eip_st *eip_st);

#endif // _BIOS_H_