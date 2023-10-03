#include "sys.h"

int sys_is_selftest_req(void)
{
    // if selftest requested
    if (pin_read(pins, pin_busy) && (status == _STATUS_END_OF_RESET))
    {
        return _SYS_SELF_TEST_REQUEST;
    }

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

void sys_init(void)
{
    /* Initialize pins */
    pin_pow_up(&pins);

    /* Start RAM */
#ifdef VERBOSE
    printf("== Initialize RAM\n");
#endif
    ram_ptr = ram_start();

    /* Initilize registers */
#ifdef VERBOSE
    printf("== Initialize registers\n");
#endif
    reg_init_eflags(&eflag_reg_st);
    reg_init_eip(&eip_st);
    reg_init_seg(&seg_regs_st);
    reg_init_gen(&gen_regs_st, &pins, &sys_cond_st);
    reg_init_cr0(&cr0_reg_st);
    reg_init_idtr();
}

void sys_shutdown(void)
{
    // TODO: compelete the shutdown process
    status = _STATUS_SYSTEM_SHUTDOWN;
    err_handler("");
}