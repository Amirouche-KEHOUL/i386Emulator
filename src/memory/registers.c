#include "registers.h"

void reg_init_seg (_segment_regs_st* segment_registers_st, _status* status)
{
    if(segment_registers_st == 0 )
    {
        *status = ERR_REG_NULL_POINTER;
        return;
    }
    segment_registers_st->CS = (segment_registers_st->CS) & CONF_RESET_DEFAULT_CS; // init to 0x000
    segment_registers_st->DS = CONF_RESET_DEFAULT_DS;
    segment_registers_st->ES = CONF_RESET_DEFAULT_ES;
    segment_registers_st->SS = CONF_RESET_DEFAULT_SS;
    segment_registers_st->FS = CONF_RESET_DEFAULT_FS;
    segment_registers_st->GS = CONF_RESET_DEFAULT_GS;
}
void reg_init_eip (_eip_st* eip_st, _status* status)
{
    if (eip_st == 0)
    {
        *status = ERR_REG_NULL_POINTER;
        return;
    }
    eip_st->IP = 0xFFF0;
    eip_st->msb = 0x0000;
}

void reg_init_gen (_general_regs_st* general_registers_st, _pins_st* pins_st, _status* status)
{ 

    // EAX: result of power-up self test: 0 if OK  , !0 if NOK (some unit is faulty)
    int ret = 0;
    ret = sys_selftest_resq(pins_st,status);
    if (ret == -1) 
    {
        *status = ERR_REG_INIT;
        return ;
    }
        
    if (ret == 0) // Self test not requested 
    {
        general_registers_st->EAX.AH = CONF_RESET_DEFAULT_EAX_AH;
        general_registers_st->EAX.AL = CONF_RESET_DEFAULT_EAX_AL;
        general_registers_st->EAX.msb = CONF_RESET_DEFAULT_EAX_MSB;         
    }

    if (ret == 1) // Self test requested
    {
        general_registers_st->EAX.AH = 0xAB;
        general_registers_st->EAX.AL = 0xCD;
        general_registers_st->EAX.msb = 0xEF;  
    }
    
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