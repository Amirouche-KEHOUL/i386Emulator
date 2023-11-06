#include "sys.h"

extern _sys_cond_st sys_cond_st;
extern int status;
extern _16_bus A3120;
extern _pins pins;
extern _physical_memory_ptr physical_memory_ptr;
extern _IO_ptr IO_ptr;
extern _general_regs_st general_regs_st;
extern _segment_regs_st segment_regs_st;
extern _eflag_reg_st eflag_reg_st;
extern _eip_st eip_st;
extern _idtr_st idtr_st;
extern _cr0_reg_st cr0_reg_st;

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

    /* Start IO memory */
#ifdef DBG
    printf("== Start IO memory\n");
#endif
    IO_ptr = IO_start();

    /* Initilize registers */
#ifdef DBG
    printf("== Initialize registers\n");
#endif
    init_eflags_reg();
    init_eip_reg();
    init_seg_reg();
    init_gen_reg();
    init_cr0_reg();
    init_idtr_reg();
    init_dtr_regs();

/* Assert A{31-20} address lines (Chapter 10.2.3)*/
#ifdef DBG
    printf("== Assert A {31-20} address lines \n");
#endif
    A3120 = 0x0FFF;

    /* Init opcode maps*/
    map_operations_to_opcode_maps();
}

void sys_shutdown(void)
{
    // TODO: compelete the shutdown process
    status = _STATUS_SYSTEM_SHUTDOWN;
    err_handler("");
}
