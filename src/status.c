#include "status.h"

void err_print (_status* status)
{
    if (*status == 0 ) return;
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
            default: 
                printf("Unknown error code (%d)\n" , *status );

        }
    }
}