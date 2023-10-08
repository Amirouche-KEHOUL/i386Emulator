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
extern _system_segment_descriptor_st SS_hidden_stack_segment_descriptor;
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

/**
 * @brief Initialize Instruction Descriptor Table Register (IDTR)
 * @par Specifications:
 * [SPEC-10.1.4]
 */
void init_idtr_reg(void);

/**
 * @brief Initialize segment registers
 * @par Specifications:
 * [SPEC-10.1.4]
 */
void init_seg_reg(void);

/**
 * @brief Inilialize Intruction pointer
 * @par Specifications:
 * [SPEC-10.1.4]
 */
void init_eip_reg(void);

/**
 * @brief Inilialize the general purpose registers
 * @param sys_cond_st: global variable storing the system condition values.
 * @par Specifications:
 * [SPEC-10.1.1-2]
 */
void init_gen_reg(void);

/**
 * @brief Initialize EFLAGS
 * @par Specifications:
 * [SPEC-10.1.4]
 */
void init_eflags_reg(void);

/**
 * @brief Initialize the conrtol register 0
 * @par Specification:
 * [SPEC-10.1.3]
 */
void init_cr0_reg(void);

/**
 * @brief Initialize the global and local descriptor tables
 * @par Specification:
 * [SPEC-10.1.3]
 */
void init_dtr_regs(void);

#endif //_REGISTERS_H_