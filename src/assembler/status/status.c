#include "status.h"
#include <stdlib.h>

void err_print (_status* status)
{
    if (*status < 0 ) printf("Followning error occured : ");
    if (*status >= 0 ) printf("Followning exception occured : ");
    
    switch (*status)
    {
        case 1:
            printf("_STATUS_NO_FILE (code %d)\n", *status);
            break;
        case -1 :
            printf("_ERR_OPEN_ASM_FILE_NOK (code %d)\n" , *status);
            break;
        default: 
            printf("Unknown error code! (code %d)\n" , *status );
    }
}

void err_handler(_status* status,char* message)
{   
    err_print(status);

    // Error are handeled here
    switch (*status)
    {
        case _STATUS_NO_FILE: 
            printf("Please provide a file name\n");
            printf("----------| Exit i386asm |---------\n"); 
            exit(*status);
        case _ERR_OPEN_ASM_FILE_NOK:
            printf("Could not open file \"%s\"(exists? permissions?). Please use relative path to current working directory.\n",message);
            printf("----------| Exit i386asm |---------\n"); 
            exit(*status);
        default: // Handle case error code is not known
            printf("----------| Exit i386asm |---------\n"); 
            exit(*status);
    }
}