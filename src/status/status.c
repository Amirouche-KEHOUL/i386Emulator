#include "status.h"
#include <stdlib.h>

void err_print (_status* status)
{
    switch (*status)
    {
        case 3:
            printf("_STATUS_DEVICE_BOOT_SIG_NOT_FOUND (%d)\n", *status);
            break;
        case 2:
            printf("_STATUS_NO_DEVICE (%d)\n", *status);
            break;
        case -1 :
            printf("_ERR_RAM_ADDR_OUTRANGE (%d)\n" , *status);
            break;
        case -2 :
            printf("_ERR_RAM_MALLOC (%d)\n" , *status);
            break;  
        case -3 :
            printf("_ERR_RAM_NULL_POINTER (%d)\n" , *status);
            break; 
        case -4 :
            printf("_ERR_REG_NULL_POINTER (%d)\n" , *status);
            break; 
        case -5 :
            printf("_ERR_PIN_NULL_POINTER (%d)\n" , *status);
            break;
        case -6 :
            printf("_ERR_SYS_NULL_POINTER (%d)\n" , *status);
            break;
        case -7 :
            printf("_ERR_REG_INIT (%d)\n" , *status);
            break;
        case -9 :
            printf("_ERR_OPEN_DEVICE_NOK (%d)\n" , *status);
            break;
        default: 
            printf("Unknown error code! (%d)\n" , *status );

    }

}

void err_handler(_status* status,char* message)
{   
    err_print(status);

    // Error are handeled here
    switch (*status)
    {
        case _ERR_RAM_ADDR_OUTRANGE:
            printf("Emulater exited with error.\n");
            exit(*status);
            break; 
        case _ERR_RAM_MALLOC:
            printf("Emulater exited with error.\n");
            exit(*status);
            break; 
        case _ERR_RAM_NULL_POINTER:
            printf("Emulater exited with error.\n");
            exit(*status);
            break; 
        case _ERR_REG_NULL_POINTER:
            printf("Emulater exited with error.\n");
            exit(*status);
            break; 
        case _ERR_PIN_NULL_POINTER:
            printf("Emulater exited with error.\n");
            exit(*status);
            break; 
        case _ERR_SYS_NULL_POINTER:
            printf("Emulater exited with error.\n");
            exit(*status);
            break; 
        case _ERR_REG_INIT:
            printf("Emulater exited with error.\n");
            exit(*status);
            break; 
        case _ERR_OPEN_DEVICE_NOK:
            printf("Could not open file \"%s\"(file existes? permissions?). please use relative path to current working directory.\n",message);
            printf("Emulater exited with error.\n");
            exit(*status);
            break;
        case _STATUS_NO_DEVICE:
            printf("Please provide a device name (relative to the current working directory)\n");
            printf("Emulator exited.\n");
            exit(*status);
            break;
            printf("Please provide a device name (relative to the current working directory)\n");
        case _STATUS_DEVICE_BOOT_SIG_NOT_FOUND: // return before exiting emulator
            printf("The device does not contains the required boot signature (0xAA55 at addr 510)\n");
            break;

        default: // handle case error code not known
            printf("Emulater exited with error.\n");
            exit(*status);
    }
}