#include "registers.h"

void reg_init_seg (_segment_regs_st* segment_registers_st, _status* status)
{
    if(segment_registers_st == 0 )
    {
        *status = ERR_REG_NULL_POINTER;
        err_handler(status);        
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
        err_handler(status);        
        return;
    }
    eip_st->IP = CONF_RESET_DEFAULT_EIP_IP ;
    eip_st->msb = CONF_RESET_DEFAULT_EIP_msb ;
}

void reg_init_gen (_general_regs_st* general_registers_st, _pins* pins,_sys_cond_st* sys_cond_st, _status* status)
{ 

    // EAX: result of power-up self test: 0 if OK  , !0 if NOK (some unit is faulty)
    int ret = 0;
    ret = sys_is_selftest_req(pins,status);
    if (ret == -1 || general_registers_st == NULL || pins == NULL || sys_cond_st == NULL) 
    {
        *status = ERR_REG_INIT;
        err_handler(status);        
        return ;
    }       

    if (ret == 1) // Self test requested
    {
        if (sys_isfaulty(sys_cond_st,status) == SYS_NOT_FAULTY)
        {
            general_registers_st->EAX.AL = 0;
            general_registers_st->EAX.AH = 0;
            general_registers_st->EAX.msb = 0;
        }
        if (sys_isfaulty(sys_cond_st, status) == SYS_FAULTY)
        {
            // TODO: these values are radonm. Correct value to be confirmed later on
            general_registers_st->EAX.AL = 0xFF;
            general_registers_st->EAX.AH = 0xFF;
            general_registers_st->EAX.msb = 0xFFFF;
        }
    }
    // EAX value is undefined otherwise
    
    // DX: DX holds a component identifier and revision number after RESET
    general_registers_st->EDX.DL = CONF_RESET_DEFAULT_EDX_DL;
    general_registers_st->EDX.DH = CONF_RESET_DEFAULT_EDX_DH;
}

void reg_init_eflags(_eflag_reg_st* eflag_register_st , _status* status)
{   
    if (eflag_register_st == 0 ) 
    {
        *status = ERR_REG_NULL_POINTER;
        err_handler(status);        
        return;        
    }

    // eflag_register_st = 0x00000002;
    eflag_register_st->carry_s = CONF_RESET_DEFAULT_EFLAG_CARRY;
    eflag_register_st->RES1 = CONF_RESET_DEFAULT_EFLAG_RES1 ; 
    eflag_register_st->parity_s = CONF_RESET_DEFAULT_EFLAG_PARITY;
    eflag_register_st->RES3 = CONF_RESET_DEFAULT_EFLAG_RES3;
    eflag_register_st->auxilary_carry_s = CONF_RESET_DEFAULT_EFLAG_AUX_CARRY;
    eflag_register_st->RES5 = CONF_RESET_DEFAULT_EFLAG_RES5;
    eflag_register_st->zero_s = CONF_RESET_DEFAULT_EFLAG_ZERO ;
    eflag_register_st->sign_s = CONF_RESET_DEFAULT_EFLAG_SIGN ;
    eflag_register_st->trap_s = CONF_RESET_DEFAULT_EFLAG_TRAP;
    eflag_register_st->interrupt_enable_x = CONF_RESET_DEFAULT_EFLAG_INTR_ENABLE;
    eflag_register_st->direction_c = CONF_RESET_DEFAULT_EFLAG_DIREC;
    eflag_register_st->overflow_s = CONF_RESET_DEFAULT_EFLAG_OVERF;
    eflag_register_st->io_previlege_level_x = CONF_RESET_DEFAULT_EFLAG_IO_PREV_LEV;
    eflag_register_st->nested_task_s = CONF_RESET_DEFAULT_EFLAG_NESTED_TASK;
    eflag_register_st->RES15 = CONF_RESET_DEFAULT_EFLAG_RES15 ;
    eflag_register_st->resume_x = CONF_RESET_DEFAULT_EFLAG_RESUME;
    eflag_register_st->virtual_8086_mode_x = CONF_RESET_DEFAULT_EFLAG_VIRT_8086_MODE;
    eflag_register_st->RES18_31 = CONF_RESET_DEFAULT_EFLAG_RES18_31;
}

void reg_init_cr0 (_cr0_reg_st* cr0_reg_st,_status* status)
{
    if (cr0_reg_st == NULL)
    {
        *status = ERR_REG_NULL_POINTER;
        err_handler(status);
        return;
    }
    cr0_reg_st->PE = CONF_RESET_DEFAULT_CR0_PE;
    cr0_reg_st->MP = CONF_RESET_DEFAULT_CR0_MP;
    cr0_reg_st->EM = CONF_RESET_DEFAULT_CR0_EM;
    cr0_reg_st->TS = CONF_RESET_DEFAULT_CR0_TS;
    cr0_reg_st->ET = CONF_RESET_DEFAULT_CR0_ET; // TODO: this is a tempo solution. refer to Initialization chapter in resources
    cr0_reg_st->PG = CONF_RESET_DEFAULT_CR0_PG;    
}