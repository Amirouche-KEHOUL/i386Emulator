#ifndef _REGISTERS_H_
#define _REGISTERS_H_

#include "../typedefs.h"
#include "../pins/pins.h"
#include "../status/status.h"
#include "../config.h"
#include "../sys/sys.h"

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

void init_idtr_reg(void);
void init_seg_reg(void);
void init_eip_reg(void);
void init_gen_reg(void);
void init_eflags_reg(void);
void init_cr0_reg(void);
void init_dtr_regs(void);

_16_reg get_BX(void);
_32_reg get_EAX(void);
_32_reg get_ECX(void);
_32_reg get_EDX(void);
_32_reg get_EBX(void);
_32_reg get_ESI(void);
_32_reg get_EDI(void);
_32_reg get_EBP(void);
_32_reg get_EIP(void);

#endif //_REGISTERS_H_