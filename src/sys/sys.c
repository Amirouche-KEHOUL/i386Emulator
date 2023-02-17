#include "sys.h"

int sys_is_selftest_req (_pins* pins,_status* status)
{    
    if (pins == 0 )
    {
        *status = _ERR_SYS_NULL_POINTER; 
        err_handler(status,"");     
    }
    // if selftest requested
    if (pin_read(pins,pin_busy,status) && (*status == _STATUS_END_OF_RESET)) return _SYS_SELF_TEST_REQUEST ;

    // else 
    return _SYS_SELF_TEST_NOT_REQUEST;
}

int sys_isfaulty (_sys_cond_st* sys_cond_st, _status* status)
{
    if (sys_cond_st == NULL)
    {
        *status = _ERR_SYS_NULL_POINTER;
        err_handler(status,"");
        return -1; 
    }

    if (sys_cond_st->unit_faulty) return _SYS_FAULTY ;
    return _SYS_NOT_FAULTY ;
}