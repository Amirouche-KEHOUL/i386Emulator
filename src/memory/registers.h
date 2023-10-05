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
extern _eflag_reg_st eflag_reg_st;
extern _eip_st eip_st;
extern _gdtr_reg gdtr_reg;
extern _ldtr_reg ldtr_reg;
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
void reg_init_idtr(void);

/**
 * @brief Initialize segment registers
 *
 * @param segment_reg_st
 * @par Specifications:
 * [SPEC-10.1.4]
 */
void reg_init_seg(void);

/**
 * @brief Inilialize Intruction pointer
 *
 * @param eip_st
 * @par Specifications:
 * [SPEC-10.1.4]
 */
void reg_init_eip(void);

/**
 * @brief Inilialize the general purpose registers
 *
 * @param _general_regs_st
 * @param pins
 * @param sys_cond_st: global variable storing the system condition values.
 * @par Specifications:
 * [SPEC-10.1.1-2]
 */
void reg_init_gen(void);

/**
 * @brief Initialize EFLAGS
 *
 * @param eflag_register
 * @par Specifications:
 * [SPEC-10.1.4]
 */
void reg_init_eflags(void);

/**
 * @brief Initialize the conrtol register 0
 *
 * @param cr0_reg_st
 * @par Specification:
 * [SPEC-10.1.3]
 */
void reg_init_cr0(void);

#endif //_REGISTERS_H_