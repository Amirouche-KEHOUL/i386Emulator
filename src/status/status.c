#include <stdlib.h>
#include <stdio.h>

#include "status.h"

extern int status;

void err_print(void)
{
    if (status < 0)
        printf("ERROR : ");
    if (status >= 0)
        printf("Warning : ");

    switch (status)
    {
    case _STATUS_SYSTEM_SHUTDOWN:
        printf("_STATUS_SYSTEM_SHUTDOWN (code %d)\n", status);
        break;
    case _STATUS_DEVICE_BOOT_SIG_NOT_FOUND:
        printf("_STATUS_DEVICE_BOOT_SIG_NOT_FOUND (code %d)\n", status);
        break;
    case _STATUS_NO_DEVICE:
        printf("_STATUS_NO_DEVICE (code %d)\n", status);
        break;
    case _ERR_PYSICAL_MEMORY_ADDR_OUTRANGE:
        printf("_ERR_PYSICAL_MEMORY_ADDR_OUTRANGE (code %d)\n", status);
        break;
    case _ERR_PHYSICAL_MEMORY_MALLOC:
        printf("_ERR_PHYSICAL_MEMORY_MALLOC (code %d)\n", status);
        break;
    case _ERR_PHYSICAL_MEMORY_NULL_POINTER_ARG:
        printf("_ERR_PHYSICAL_MEMORY_NULL_POINTER_ARG (code %d)\n", status);
        break;
    case _ERR_BIOS_NULL_POINTER_ARG:
        printf("_ERR_BIOS_NULL_POINTER_ARG (code %d)\n", status);
        break;
    case _ERR_REG_INIT:
        printf("_ERR_REG_INIT (code %d)\n", status);
        break;
    case _ERR_OPEN_DEVICE_NOK:
        printf("_ERR_OPEN_DEVICE_NOK (code %d)\n", status);
        break;
    case _ERR_IO_MEMORY_ADDR_OUTRANGE:
        printf("_ERR_IO_MEMORY_ADDR_OUTRANGE (code %d)\n", status);
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
    case _ERR_IO_MEMORY_ADDR_OUTRANGE:
        printf("----------| Exit Emulator |---------\n");
        exit(status);
        break;
    case _ERR_PYSICAL_MEMORY_ADDR_OUTRANGE:
        printf("----------| Exit Emulator |---------\n");
        exit(status);
        break;
    case _ERR_PHYSICAL_MEMORY_MALLOC:
        printf("----------| Exit Emulator |---------\n");
        exit(status);
        break;
    case _ERR_PHYSICAL_MEMORY_NULL_POINTER_ARG:
        printf("----------| Exit Emulator |---------\n");
        exit(status);
        break;
    case _ERR_BIOS_NULL_POINTER_ARG:
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
    case _STATUS_SYSTEM_SHUTDOWN:
        printf("----------| Exit Emulator |---------\n");
        exit(status);
        break;
    case _STATUS_DEVICE_BOOT_SIG_NOT_FOUND: // Return before exiting emulator
        printf("\nThe device does not contains the required boot signature (0xAA55 at addr 510)\n");
        printf("----------| Exit Emulator |---------\n");
        exit(status);
        break;

    default: // Handle case error code is not known
        printf("Event not handled\n");
        printf("----------| Exit Emulator |---------\n");
        exit(status);
    }
}