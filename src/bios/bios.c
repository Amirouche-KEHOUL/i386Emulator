#include <stddef.h>
#include <stdio.h>

#include "bios.h"

extern int status;

unsigned int bios_is_bootable(FILE *device_name)
{
    // Arguments check
    if (device_name == NULL)
    {
        status = _ERR_BIOS_NULL_POINTER_ARG;
        err_handler("");
    }

    // Look for boot signature in sector 0 (0x55 0xAA at addr 510 and 511 respectively)
    unsigned int byte_stream = 0;
    unsigned int boot_sig[2];
    for (int i = 0; i < 512; i++)
    {
        byte_stream = getc(device_name);
        if (i == 510)
            boot_sig[0] = byte_stream;
        if (i == 511)
            boot_sig[1] = byte_stream;
    }
    rewind(device_name);
    if ((boot_sig[0] == 0x55) & (boot_sig[1] == 0xAA))
    {
#ifdef DBG
        printf("== Disk is bootable\n");
#endif
        return _DEVICE_IS_BOOTABLE;
    }

    // If signature not found
    status = _STATUS_DEVICE_BOOT_SIG_NOT_FOUND;
    err_handler("");
    return _STATUS_DEVICE_BOOT_SIG_NOT_FOUND;
}

unsigned int bios_load_MBR_TO_RAM(FILE *device)
{
    // copy MBR to RAM
    _byte byte_stream = 0;
    for (int i = 0; i < 512; i++)
    {
        byte_stream = getc(device);
        physical_memory_write(byte_stream, physical_memory_ptr, (_MBR_LOAD_RAM_ADDR + i));
    }
    // Force CS:IP to 0x 0000:_MBR_LOAD_RAM_ADDR
    segment_regs_st.CS = 0x0000;
    eip_st.IP = _MBR_LOAD_RAM_ADDR;
    return 1;
}
