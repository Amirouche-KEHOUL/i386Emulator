#include <stddef.h>

#include "registers.h"

extern int status;
extern _sys_cond_st sys_cond_st;

extern _pins pins;
extern _physical_memory_ptr physical_memory_ptr;
extern _general_regs_st general_regs_st;
extern _segment_regs_st segment_regs_st;
extern _code_segment_descriptor_st CS_hidden_code_segment_descriptor;
extern _data_segment_descriptor_st SS_hidden_stack_segment_descriptor;
extern _data_segment_descriptor_st DS_hidden_data_segment_descriptor;
extern _data_segment_descriptor_st ES_hidden_data_segment_descriptor;
extern _data_segment_descriptor_st FS_hidden_data_segment_descriptor;
extern _data_segment_descriptor_st GS_hidden_data_segment_descriptor;
extern _dtr_reg_st gdtr_reg_st;
extern _dtr_reg_st ldtr_reg_st;
extern _eflag_reg_st eflag_reg_st;
extern _eip_st eip_st;
extern _idtr_st idtr_st;
extern _interrupts_flags_st interrupts_flags_st;
extern _task_reg_st task_reg_st;
extern _cr0_reg_st cr0_reg_st;
extern _cr2_reg cr2_reg;
extern _cr3_reg_pdbr cr3_reg_pdbr;
extern _tlb_reg_st tlb_reg_st;

// Clear all fields of selectors
void init_selector(_selector_st *selector_st)
{
    if (selector_st == NULL)
    {
        status = _ERR_REG_ARG;
        err_handler("");
    }
    selector_st->index = (_16_reg)0x0;
    selector_st->table_indicator = (_16_reg)0x0;
    selector_st->requestor_privilege_level = (_16_reg)0x0;
}

void init_code_segment_selector(_selector_st *selector_st)
{
    if (selector_st == NULL)
    {
        status = _ERR_REG_ARG;
        err_handler("");
    }
    // / TODO: TBC doc typo ? 0xF000 intead of 0x000 ?
}

void init_seg_reg(void)
{

    init_code_segment_selector(&segment_regs_st.CS);
    init_selector(&segment_regs_st.SS);
    init_selector(&segment_regs_st.DS);
    init_selector(&segment_regs_st.ES);
    init_selector(&segment_regs_st.FS);
    init_selector(&segment_regs_st.GS);

    segment_regs_st.CS_hidden_code_segment_descriptor = &CS_hidden_code_segment_descriptor;
    segment_regs_st.DS_hidden_data_segment_descriptor = &DS_hidden_data_segment_descriptor;
    segment_regs_st.ES_hidden_data_segment_descriptor = &ES_hidden_data_segment_descriptor;
    segment_regs_st.SS_hidden_stack_segment_descriptor = &SS_hidden_stack_segment_descriptor;
    segment_regs_st.FS_hidden_data_segment_descriptor = &FS_hidden_data_segment_descriptor;
    segment_regs_st.GS_hidden_data_segment_descriptor = &GS_hidden_data_segment_descriptor;
}

void init_eip_reg(void)
{
    eip_st.IP = _CONF_RESET_DEFAULT_EIP_IP;
    eip_st.msb = _CONF_RESET_DEFAULT_EIP_msb;
}

void init_gen_reg(void)
{

    // EAX: result of power-up self test: 0 if OK  , !0 if NOK (some unit is faulty)
    int ret = 0;
    ret = sys_is_selftest_req();

    if (ret == _SYS_SELF_TEST_REQUEST)
    {
        if (sys_isfaulty() == _SYS_NOT_FAULTY)
        {
            general_regs_st.EAX.AL = 0;
            general_regs_st.EAX.AH = 0;
            general_regs_st.EAX.msb = 0;
        }
        if (sys_isfaulty() == _SYS_FAULTY)
        {
            // TODO: these values are radonm. Correct value to be confirmed later on
            general_regs_st.EAX.AL = 0xFF;
            general_regs_st.EAX.AH = 0xFF;
            general_regs_st.EAX.msb = 0xFFFF;
        }
    }
    // EAX value is undefined otherwise

    // DX: DX holds a component identifier and revision number after RESET
    general_regs_st.EDX.DL = _CONF_RESET_DEFAULT_EDX_DL;
    general_regs_st.EDX.DH = _CONF_RESET_DEFAULT_EDX_DH;
}

void init_eflags_reg(void)
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

void init_cr0_reg(void)
{
    cr0_reg_st.PE = _CONF_RESET_DEFAULT_CR0_PE;
    cr0_reg_st.MP = _CONF_RESET_DEFAULT_CR0_MP;
    cr0_reg_st.EM = _CONF_RESET_DEFAULT_CR0_EM;
    cr0_reg_st.TS = _CONF_RESET_DEFAULT_CR0_TS;
    cr0_reg_st.ET = _CONF_RESET_DEFAULT_CR0_ET; // TODO: this is a tempo solution. refer to Initialization chapter 10.1 paragraph 3 in resources directory
    cr0_reg_st.PG = _CONF_RESET_DEFAULT_CR0_PG;
}

void init_idtr_reg(void)
{
    idtr_st.base = _CONF_RESET_DEFAULT_BASE_IDTR;
    idtr_st.limit = _CONF_RESET_DEFAULT_LIMIT_IDTR;
}

void init_dtr_regs(void)
{
    gdtr_reg_st.type = _GDT;
    ldtr_reg_st.type = _LDT;
}

_16_reg get_BX(void)
{
    _16_reg ret = 0U;
    _16_reg BL = 0U;
    BL = general_regs_st.EBX.BL;
    ret = general_regs_st.EBX.BH;
    ret = ret << 8;
    ret = ret | BL;
    return ret;
}

_32_reg get_EAX(void)
{
    _32_reg ret = 0U;
    _32_reg AH = 0U;
    ret = general_regs_st.EAX.msb;
    ret = ret << 16;
    AH = general_regs_st.EAX.AH;
    ret = ret | (AH << 8) | (general_regs_st.EAX.AL);
    return ret;
}

_32_reg get_ECX(void)
{
    _32_reg ret = 0U;
    _32_reg CH = 0U;
    ret = general_regs_st.ECX.msb;
    ret = ret << 16;
    CH = general_regs_st.ECX.CH;
    ret = ret | (CH << 8) | (general_regs_st.ECX.CL);
    return ret;
}

_32_reg get_EDX(void)
{
    _32_reg ret = 0U;
    _32_reg DH = 0U;
    ret = general_regs_st.EDX.msb;
    ret = ret << 16;
    DH = general_regs_st.EDX.DH;
    ret = ret | (DH << 8) | (general_regs_st.EDX.DL);
    return ret;
}

_32_reg get_EBX(void)
{
    _32_reg ret = 0U;
    _32_reg BH = 0U;
    ret = general_regs_st.EBX.msb;
    ret = ret << 16;
    BH = general_regs_st.EBX.BH;
    ret = ret | (BH << 8) | (general_regs_st.EBX.BL);
    return ret;
}

_32_reg get_ESI(void)
{
    _32_reg ret = 0U;
    ret = general_regs_st.ESI.msb;
    ret = ret << 16;
    ret = ret | (general_regs_st.ESI.SI);
    return ret;
}

_32_reg get_EDI(void)
{
    _32_reg ret = 0U;
    ret = general_regs_st.EDI.msb;
    ret = ret << 16;
    ret = ret | (general_regs_st.EDI.DI);
    return ret;
}

_32_reg get_EBP(void)
{
    _32_reg ret = 0U;
    ret = general_regs_st.EBP.msb;
    ret = ret << 16;
    ret = ret | (general_regs_st.EBP.BP);
    return ret;
}

_32_reg get_EIP(void)
{
    _32_reg ret = 0U;
    ret = eip_st.msb;
    ret = ret << 16;
    ret = ret | (_32_reg)eip_st.IP;

    return ret;
}