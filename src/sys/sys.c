#include "sys.h"

int sys_selftest_resq (_pins* pins,_status* status)
{
    // ret = 1 : self-test requested 
    if (pins == 0 )
    {
        *status = ERR_SYS_NULL_POINTER; 
        err_handler(status);     
        return -1 ;
    }

    if (0)
    {
        printf("double condition OK\n");
         return 1; 
    }
    if (0) 
    {
        printf("condition OK\n"); 
        return 0;
    }
    printf("no condition\n");
}