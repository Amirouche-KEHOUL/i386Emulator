#include "sys.h"

int sys_is_selftest_req (_pins* pins,_status* status)
{
    // ret = 1 : self-test requested 
    if (pins == 0 )
    {
        *status = ERR_SYS_NULL_POINTER; 
        err_handler(status,"");     
        return -1 ;
    }
    // if selftest requested
    if (pin_read(pins,pin_busy,status) && (*status == STATUS_END_OF_RESET)) return 1 ;

    // else 
    return 0;
}

int sys_isfaulty (_sys_cond_st* sys_cond_st, _status* status)
{
    if (sys_cond_st == NULL)
    {
        *status = ERR_SYS_NULL_POINTER;
        err_handler(status,"");
        return -1; 
    }

    if (sys_cond_st->unit_faulty) return SYS_FAULTY ;
    return SYS_NOT_FAULTY ;
}