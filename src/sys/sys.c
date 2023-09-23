#include <stddef.h>

#include "sys.h"

extern int status;

int sys_is_selftest_req(const _pins *pins)
{
    if (pins == 0)
    {
        status = _ERR_SYS_NULL_POINTER_ARG;
        err_handler("");
    }
    // if selftest requested
    if (pin_read(pins, pin_busy) && (status == _STATUS_END_OF_RESET))
        return _SYS_SELF_TEST_REQUEST;

    // else
    return _SYS_SELF_TEST_NOT_REQUEST;
}

int sys_isfaulty(const _sys_cond_st *sys_cond_st)
{
    if (sys_cond_st == NULL)
    {
        status = _ERR_SYS_NULL_POINTER_ARG;
        err_handler("");
        return -1;
    }

    if (sys_cond_st->unit_faulty)
        return _SYS_FAULTY;
    return _SYS_NOT_FAULTY;
}