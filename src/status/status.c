#include <stdlib.h>
#include <stdio.h>

#include "status.h"

extern int status;

void err_print()
{
    if (status < 0)
        printf("Followning error occured : ");
    if (status >= 0)
        printf("Followning exception occured : ");

    switch (status)
    {
    case 3:
        printf("_STATUS_DEVICE_BOOT_SIG_NOT_FOUND (code %d)\n", status);
        break;
    case 2:
        printf("_STATUS_NO_DEVICE (code %d)\n", status);
        break;
    case -1:
        printf("_ERR_RAM_ADDR_OUTRANGE (code %d)\n", status);
        break;
    case -2:
        printf("_ERR_RAM_MALLOC (code %d)\n", status);
        break;
    case -3:
        printf("_ERR_RAM_NULL_POINTER_ARG (code %d)\n", status);
        break;
    case -4:
        printf("_ERR_REG_NULL_POINTER_ARG (code %d)\n", status);
        break;
    case -5:
        printf("_ERR_PIN_NULL_POINTER_ARG (code %d)\n", status);
        break;
    case -6:
        printf("_ERR_SYS_NULL_POINTER_ARG (code %d)\n", status);
        break;
    case -7:
        printf("_ERR_REG_INIT (code %d)\n", status);
        break;
    case -8:
        printf("_ERR_BIOS_NULL_POINTER_ARG (code %d)\n", status);
        break;
    case -9:
        printf("_ERR_OPEN_DEVICE_NOK (code %d)\n", status);
        break;
    default:
        printf("Unknown error code! (code %d)\n", status);
    }
}

void err_handler(char *message)
{
    err_print();

    // Error are handeled here
    switch (status)
    {
    case _ERR_RAM_ADDR_OUTRANGE:
        printf("----------| Exit Emulator |---------\n");
        exit(status);
        break;
    case _ERR_RAM_MALLOC:
        printf("----------| Exit Emulator |---------\n");
        exit(status);
        break;
    case _ERR_RAM_NULL_POINTER_ARG:
        printf("----------| Exit Emulator |---------\n");
        exit(status);
        break;
    case _ERR_REG_NULL_POINTER_ARG:
        printf("----------| Exit Emulator |---------\n");
        exit(status);
        break;
    case _ERR_PIN_NULL_POINTER_ARG:
        printf("----------| Exit Emulator |---------\n");
        exit(status);
        break;
    case _ERR_SYS_NULL_POINTER_ARG:
        printf("----------| Exit Emulator |---------\n");
        exit(status);
        break;
    case _ERR_REG_INIT:
        printf("----------| Exit Emulator |---------\n");
        exit(status);
        break;
    case _ERR_OPEN_DEVICE_NOK:
        printf("Could not open file \"%s\"(exists? permissions?). Please use relative path to current working directory.\n", message);
        printf("----------| Exit Emulator |---------\n");
        exit(status);
        break;
    case _STATUS_NO_DEVICE:
        printf("Please provide a device path (relative to the current working directory)\n");
        printf("----------| Exit Emulator |---------\n");
        exit(status);
        break;
    case _ERR_BIOS_NULL_POINTER_ARG:
        printf("----------| Exit Emulator |---------\n");
        exit(status);
        break;
    case _STATUS_DEVICE_BOOT_SIG_NOT_FOUND: // Return before exiting emulator
        printf("\nThe device does not contains the required boot signature (0xAA55 at addr 510)\n");
        break;

    default: // Handle case error code is not known
        printf("----------| Exit Emulator |---------\n");
        exit(status);
    }
}