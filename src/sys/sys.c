#include "sys.h"

int sys_is_selftest_req(void)
{
    // if selftest requested
    if (pin_read(pin_busy) && (status == _STATUS_END_OF_RESET))
    {
        return _SYS_SELF_TEST_REQUEST;
    }

    // else
    return _SYS_SELF_TEST_NOT_REQUEST;
}

int sys_isfaulty(void)
{
    if (sys_cond_st.unit_faulty)
        return _SYS_FAULTY;
    return _SYS_NOT_FAULTY;
}

void sys_init(void)
{
    /* Initialize pins */
    pin_pow_up();

    /* Start physical memory */
#ifdef DBG
    printf("== Start physical memory\n");
#endif
    physical_memory_ptr = physical_memory_start();

    /* Initilize registers */
#ifdef DBG
    printf("== Initialize registers\n");
#endif
    reg_init_eflags();
    reg_init_eip();
    reg_init_seg();
    reg_init_gen();
    reg_init_cr0();
    reg_init_idtr();

/* Assert A{31-20} address lines (Chapter 10.2.3)*/
#ifdef DBG
    printf("== Assert A {31-20} address lines \n");
#endif
    A3120 = 0x0FFF;
}

void sys_shutdown(void)
{
    // TODO: compelete the shutdown process
    status = _STATUS_SYSTEM_SHUTDOWN;
    err_handler("");
}
