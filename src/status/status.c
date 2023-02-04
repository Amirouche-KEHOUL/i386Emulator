#include "status.h"
#include <stdlib.h>

void err_print (_status* status)
{
    if (*status < 0 )
    {
        switch (*status)
        {
            case -1 :
                printf("ERR_RAM_ADDR_OUTRANGE (%d)\n" , *status);
                break;
            case -2 :
                printf("ERR_RAM_MALLOC (%d)\n" , *status);
                break;  
            case -3 :
                printf("ERR_RAM_NULL_POINTER (%d)\n" , *status);
                break; 
            case -4 :
                printf("ERR_REG_NULL_POINTER (%d)\n" , *status);
                break; 
            case -5 :
                printf("ERR_PIN_NULL_POINTER (%d)\n" , *status);
                break;
            case -6 :
                printf("ERR_SYS_NULL_POINTER (%d)\n" , *status);
                break;
            case -7 :
                printf("ERR_REG_INIT (%d)\n" , *status);
                break;
            default: 
                printf("Unknown error code (%d)\n" , *status );

        }
    }
}

void err_handler(_status* status)
{   
    printf("Following error occured : ");
    err_print(status);
    // error are handeled here
    switch (*status)
    {
        case ERR_RAM_ADDR_OUTRANGE:
            printf("Emulater exited with error.\n");
            exit(*status);
            break; 
        case ERR_RAM_MALLOC:
            printf("Emulater exited with error.\n");
            exit(*status);
            break; 
        case ERR_RAM_NULL_POINTER:
            printf("Emulater exited with error.\n");
            exit(*status);
            break; 
            break; 
        case ERR_REG_NULL_POINTER:
            printf("Emulater exited with error.\n");
            exit(*status);
            break; 
        case ERR_PIN_NULL_POINTER:
            printf("Emulater exited with error.\n");
            exit(*status);
            break; 
        case ERR_SYS_NULL_POINTER:
            printf("Emulater exited with error.\n");
            exit(*status);
            break; 
        case ERR_REG_INIT:
            printf("Emulater exited with error.\n");
            exit(*status);
            break; 
    
        default: // handle case error code not known
            printf("Emulater exited with error.\n");
            exit(*status);
            
    }
    
}