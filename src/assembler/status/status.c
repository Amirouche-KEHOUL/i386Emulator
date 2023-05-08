#include "status.h"
#include <stdlib.h>

void err_print (_status* status)
{
    if (*status < 0 ) printf("Following error occurred : ");
    if (*status >= 0 ) printf("Following exception occurred : ");
    
    switch (*status)
    {
        case 2:
            printf("_STATUS_PARSER_EOF_REACHED (code %d)\n", *status);
            break;
        case 1:
            printf("_STATUS_NO_FILE (code %d)\n", *status);
            break;
        case -1 :
            printf("_ERR_OPEN_ASM_FILE_NOK (code %d)\n" , *status);
            break;
        case -2 :
            printf("_ERR_PARSER_NULL_POINTER_ARG (code %d)\n" , *status);
            break;
        case -3 :
            printf("_ERR_PARSER_UNKNOWN_ARGS (code %d)\n" , *status);
            break;
        case -4 :
            printf("_ERR_PARSER_UNKNOWN_MNEMONIC (code %d)\n" , *status);
            break;
        default: 
            printf("Unknown error code! (code %d)\n" , *status );
    }
}

void err_handler(_status* status,char* message)
{   
    err_print(status);

    /* Errors are handled here */
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
        case _ERR_PARSER_NULL_POINTER_ARG: 
            printf("Occurred in %s\n", message );
            printf("----------| Exit i386asm |---------\n"); 
            exit(*status);
        case _ERR_PARSER_UNKNOWN_ARGS: 
            printf("While parsing, could not lookup arguments \"%s\"\n", message );
            // return control to the caller to printout the corresponding error line.
            exit(1);
            break;
        case _ERR_PARSER_UNKNOWN_MNEMONIC: 
            printf("While parsing, could not lookup mnemonic \"%s\"\n", message );
            // return control to the caller to printout the corresponding error line.
           exit(1);
            break;
        default: // Handle case error code is not known
            printf("----------| Exit i386asm |---------\n"); 
            exit(*status);
    }
    free(message);
}