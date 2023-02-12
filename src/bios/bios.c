#include "bios.h"

unsigned int bios_is_bootable (char* device_name,_status* status)
{
    if (device_name == NULL)
    {
        *status = ERR_BIOS_NULL_POINTER;
        err_handler(status,"");
    }
    
    // TODO: look for boot signature in sector 0 (0x55 0xAA at addr 510 and 511 respectively)

    return 1;
}