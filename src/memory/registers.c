#include "registers.h"

void reg_init_gen (_general_regs_st* general_registers_st, int selftest, _status* status)
{ 

    // EAX: result of power-up self test: 0 if OK , !0 if NOK (some unit is faulty)
    
    // DX: DX holds a component identifier and revision number after RESET

    // CR0 ? 

}

void reg_init_eflags(_eflag_reg_st* eflag_register_st , _status* status)
{   
    if (eflag_register_st == 0 ) 
    {
        *status = ERR_REG_NULL_POINTER;
        return;        
    }

    // eflag_register_st = 0x00000002;
    eflag_register_st->carry_s = 0;
    eflag_register_st->RES1 = 1; 
    eflag_register_st->parity_s = 0;
    eflag_register_st->RES3 = 0;
    eflag_register_st->auxilary_carry_s = 0;
    eflag_register_st->RES5 = 0;
    eflag_register_st->zero_s = 0;
    eflag_register_st->sign_s = 0;
    eflag_register_st->trap_s = 0;
    eflag_register_st->interrupt_enable_x = 0;
    eflag_register_st->direction_c = 0;
    eflag_register_st->overflow_s = 0;
    eflag_register_st->io_previlege_level_x = 0;
    eflag_register_st->nested_task_s = 0;
    eflag_register_st->RES15 = 0;
    eflag_register_st->resume_x = 0;
    eflag_register_st->virtual_8086_mode_x = 0;
    eflag_register_st->RES18_31 = 0;
}