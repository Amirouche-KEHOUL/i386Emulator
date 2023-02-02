#include "sys.h"

int sys_selftest_resq (_pins_st* pins_st,_status* status)
{
    // ret = 1 : self-test requested 
    if (pins_st == 0 )
    {
        *status = ERR_SYS_NULL_POINTER; 
        return -1 ;
    }
    if ((pins_st->BUSY == 1) && (*status == STATUS_END_OF_RESET) ) return 1; 
    if (pins_st->BUSY == 0 ) return 0;    
}