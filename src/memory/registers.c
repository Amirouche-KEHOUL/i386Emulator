#include <stddef.h>

#include "registers.h"

void reg_init_seg(void)
{

    seg_regs_st.CS = (seg_regs_st.CS) & _CONF_RESET_DEFAULT_CS; // init to 0x000
    seg_regs_st.DS = _CONF_RESET_DEFAULT_DS;
    seg_regs_st.ES = _CONF_RESET_DEFAULT_ES;
    seg_regs_st.SS = _CONF_RESET_DEFAULT_SS;
    seg_regs_st.FS = _CONF_RESET_DEFAULT_FS;
    seg_regs_st.GS = _CONF_RESET_DEFAULT_GS;
}

void reg_init_eip(void)
{
    eip_st.IP = _CONF_RESET_DEFAULT_EIP_IP;
    eip_st.msb = _CONF_RESET_DEFAULT_EIP_msb;
}

void reg_init_gen(void)
{

    // EAX: result of power-up self test: 0 if OK  , !0 if NOK (some unit is faulty)
    int ret = 0;
    ret = sys_is_selftest_req();

    if (ret == _SYS_SELF_TEST_REQUEST)
    {
        if (sys_isfaulty() == _SYS_NOT_FAULTY)
        {
            gen_regs_st.EAX.AL = 0;
            gen_regs_st.EAX.AH = 0;
            gen_regs_st.EAX.msb = 0;
        }
        if (sys_isfaulty() == _SYS_FAULTY)
        {
            // TODO: these values are radonm. Correct value to be confirmed later on
            gen_regs_st.EAX.AL = 0xFF;
            gen_regs_st.EAX.AH = 0xFF;
            gen_regs_st.EAX.msb = 0xFFFF;
        }
    }
    // EAX value is undefined otherwise

    // DX: DX holds a component identifier and revision number after RESET
    gen_regs_st.EDX.DL = _CONF_RESET_DEFAULT_EDX_DL;
    gen_regs_st.EDX.DH = _CONF_RESET_DEFAULT_EDX_DH;
}

void reg_init_eflags(void)
{
    // eflag_register_st = 0x00000002;
    eflag_reg_st.carry_s = _CONF_RESET_DEFAULT_EFLAG_CARRY;
    eflag_reg_st.RES1 = _CONF_RESET_DEFAULT_EFLAG_RES1;
    eflag_reg_st.parity_s = _CONF_RESET_DEFAULT_EFLAG_PARITY;
    eflag_reg_st.RES3 = _CONF_RESET_DEFAULT_EFLAG_RES3;
    eflag_reg_st.auxilary_carry_s = _CONF_RESET_DEFAULT_EFLAG_AUX_CARRY;
    eflag_reg_st.RES5 = _CONF_RESET_DEFAULT_EFLAG_RES5;
    eflag_reg_st.zero_s = _CONF_RESET_DEFAULT_EFLAG_ZERO;
    eflag_reg_st.sign_s = _CONF_RESET_DEFAULT_EFLAG_SIGN;
    eflag_reg_st.trap_s = _CONF_RESET_DEFAULT_EFLAG_TRAP;
    eflag_reg_st.interrupt_enable_x = _CONF_RESET_DEFAULT_EFLAG_INTR_ENABLE;
    eflag_reg_st.direction_c = _CONF_RESET_DEFAULT_EFLAG_DIREC;
    eflag_reg_st.overflow_s = _CONF_RESET_DEFAULT_EFLAG_OVERF;
    eflag_reg_st.io_previlege_level_x = _CONF_RESET_DEFAULT_EFLAG_IO_PREV_LEV;
    eflag_reg_st.nested_task_s = _CONF_RESET_DEFAULT_EFLAG_NESTED_TASK;
    eflag_reg_st.RES15 = _CONF_RESET_DEFAULT_EFLAG_RES15;
    eflag_reg_st.resume_x = _CONF_RESET_DEFAULT_EFLAG_RESUME;
    eflag_reg_st.virtual_8086_mode_x = _CONF_RESET_DEFAULT_EFLAG_VIRT_8086_MODE;
    eflag_reg_st.RES18_31 = _CONF_RESET_DEFAULT_EFLAG_RES18_31;
}

void reg_init_cr0(void)
{
    cr0_reg_st.PE = _CONF_RESET_DEFAULT_CR0_PE;
    cr0_reg_st.MP = _CONF_RESET_DEFAULT_CR0_MP;
    cr0_reg_st.EM = _CONF_RESET_DEFAULT_CR0_EM;
    cr0_reg_st.TS = _CONF_RESET_DEFAULT_CR0_TS;
    cr0_reg_st.ET = _CONF_RESET_DEFAULT_CR0_ET; // TODO: this is a tempo solution. refer to Initialization chapter 10.1 paragraph 3 in resources directory
    cr0_reg_st.PG = _CONF_RESET_DEFAULT_CR0_PG;
}

void reg_init_idtr(void)
{
    idtr_st.base = _CONF_RESET_DEFAULT_BASE_IDTR;
    idtr_st.limit = _CONF_RESET_DEFAULT_LIMIT_IDTR;
}
