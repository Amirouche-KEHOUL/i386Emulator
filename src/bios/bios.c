#include "bios.h"

unsigned int bios_is_bootable (FILE* device_name,_status* status)
{
    if (device_name == NULL)
    {
        *status = _ERR_BIOS_NULL_POINTER;
        err_handler(status,"");
    }
    
    // Look for boot signature in sector 0 (0x55 0xAA at addr 510 and 511 respectively)
    unsigned int byte_stream = 0;
    unsigned int boot_sig[2];
    for (int i = 0 ; i < 512;i++ )
    {
        byte_stream = getc(device_name);
        if (i == 510) boot_sig[0] = byte_stream;
        if (i == 511) boot_sig[1] = byte_stream;
    }
    rewind(device_name);
    if ((boot_sig[0] == 0x55) & (boot_sig[1] == 0xAA)) return _DEVICE_IS_BOOTABLE ; 

    // If signature not found
    *status = _STATUS_DEVICE_BOOT_SIG_NOT_FOUND;
    err_handler(status,"");
}