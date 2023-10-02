#include <stddef.h>

#include "registers.h"

void reg_init_seg(_segment_regs_st *segment_reg_st)
{
    if (segment_reg_st == 0)
    {
        status = _ERR_REG_NULL_POINTER_ARG;
        err_handler("");
        return;
    }
    segment_reg_st->CS = (segment_reg_st->CS) & _CONF_RESET_DEFAULT_CS; // init to 0x000
    segment_reg_st->DS = _CONF_RESET_DEFAULT_DS;
    segment_reg_st->ES = _CONF_RESET_DEFAULT_ES;
    segment_reg_st->SS = _CONF_RESET_DEFAULT_SS;
    segment_reg_st->FS = _CONF_RESET_DEFAULT_FS;
    segment_reg_st->GS = _CONF_RESET_DEFAULT_GS;
}

void reg_init_eip(_eip_st *eip_st)
{
    if (eip_st == NULL)
    {
        status = _ERR_REG_NULL_POINTER_ARG;
        err_handler("");
        return;
    }
    eip_st->IP = _CONF_RESET_DEFAULT_EIP_IP;
    eip_st->msb = _CONF_RESET_DEFAULT_EIP_msb;
}

void reg_init_gen(_general_regs_st *_general_regs_st, const _pins *pins, const _sys_cond_st *sys_cond_st)
{

    // EAX: result of power-up self test: 0 if OK  , !0 if NOK (some unit is faulty)
    int ret = 0;
    ret = sys_is_selftest_req(pins);
    if (_general_regs_st == NULL || pins == NULL || sys_cond_st == NULL)
    {
        status = _ERR_REG_INIT;
        err_handler("");
        return;
    }

    if (ret == _SYS_SELF_TEST_REQUEST)
    {
        if (sys_isfaulty(sys_cond_st) == _SYS_NOT_FAULTY)
        {
            _general_regs_st->EAX.AL = 0;
            _general_regs_st->EAX.AH = 0;
            _general_regs_st->EAX.msb = 0;
        }
        if (sys_isfaulty(sys_cond_st) == _SYS_FAULTY)
        {
            // TODO: these values are radonm. Correct value to be confirmed later on
            _general_regs_st->EAX.AL = 0xFF;
            _general_regs_st->EAX.AH = 0xFF;
            _general_regs_st->EAX.msb = 0xFFFF;
        }
    }
    // EAX value is undefined otherwise

    // DX: DX holds a component identifier and revision number after RESET
    _general_regs_st->EDX.DL = _CONF_RESET_DEFAULT_EDX_DL;
    _general_regs_st->EDX.DH = _CONF_RESET_DEFAULT_EDX_DH;
}

void reg_init_eflags(_eflag_reg_st *eflag_register_st)
{
    if (eflag_register_st == NULL)
    {
        status = _ERR_REG_NULL_POINTER_ARG;
        err_handler("");
        return;
    }

    // eflag_register_st = 0x00000002;
    eflag_register_st->carry_s = _CONF_RESET_DEFAULT_EFLAG_CARRY;
    eflag_register_st->RES1 = _CONF_RESET_DEFAULT_EFLAG_RES1;
    eflag_register_st->parity_s = _CONF_RESET_DEFAULT_EFLAG_PARITY;
    eflag_register_st->RES3 = _CONF_RESET_DEFAULT_EFLAG_RES3;
    eflag_register_st->auxilary_carry_s = _CONF_RESET_DEFAULT_EFLAG_AUX_CARRY;
    eflag_register_st->RES5 = _CONF_RESET_DEFAULT_EFLAG_RES5;
    eflag_register_st->zero_s = _CONF_RESET_DEFAULT_EFLAG_ZERO;
    eflag_register_st->sign_s = _CONF_RESET_DEFAULT_EFLAG_SIGN;
    eflag_register_st->trap_s = _CONF_RESET_DEFAULT_EFLAG_TRAP;
    eflag_register_st->interrupt_enable_x = _CONF_RESET_DEFAULT_EFLAG_INTR_ENABLE;
    eflag_register_st->direction_c = _CONF_RESET_DEFAULT_EFLAG_DIREC;
    eflag_register_st->overflow_s = _CONF_RESET_DEFAULT_EFLAG_OVERF;
    eflag_register_st->io_previlege_level_x = _CONF_RESET_DEFAULT_EFLAG_IO_PREV_LEV;
    eflag_register_st->nested_task_s = _CONF_RESET_DEFAULT_EFLAG_NESTED_TASK;
    eflag_register_st->RES15 = _CONF_RESET_DEFAULT_EFLAG_RES15;
    eflag_register_st->resume_x = _CONF_RESET_DEFAULT_EFLAG_RESUME;
    eflag_register_st->virtual_8086_mode_x = _CONF_RESET_DEFAULT_EFLAG_VIRT_8086_MODE;
    eflag_register_st->RES18_31 = _CONF_RESET_DEFAULT_EFLAG_RES18_31;
}

void reg_init_cr0(_cr0_reg_st *cr0_reg_st)
{
    if (cr0_reg_st == NULL)
    {
        status = _ERR_REG_NULL_POINTER_ARG;
        err_handler("");
        return;
    }
    cr0_reg_st->PE = _CONF_RESET_DEFAULT_CR0_PE;
    cr0_reg_st->MP = _CONF_RESET_DEFAULT_CR0_MP;
    cr0_reg_st->EM = _CONF_RESET_DEFAULT_CR0_EM;
    cr0_reg_st->TS = _CONF_RESET_DEFAULT_CR0_TS;
    cr0_reg_st->ET = _CONF_RESET_DEFAULT_CR0_ET; // TODO: this is a tempo solution. refer to Initialization chapter 10.1 paragraph 3 in resources directory
    cr0_reg_st->PG = _CONF_RESET_DEFAULT_CR0_PG;
}

void reg_init_idtr(_idtr_reg *idtr_reg)
{
    if (idtr_reg == NULL)
    {
        status = _ERR_REG_NULL_POINTER_ARG;
        err_handler("");
        return;
    }
    *idtr_reg = _CONF_RESET_DEFAULT_IDTR;
}
