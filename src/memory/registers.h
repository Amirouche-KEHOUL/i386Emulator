#ifndef _REGISTERS_H_
#define _REGISTERS_H_

#include "../typedefs.h"
#include "../pins/pins.h"
#include "../status/status.h"
#include "../config.h"
#include "../sys/sys.h"

extern int status;               // Global main.c
extern _sys_cond_st sys_cond_st; // Global main.c

/**
 * @brief Initialize Instruction Descriptor Table Register (IDTR)
 *
 * @param _idtr_reg
 * @par Specifications:
 * [SPEC-10.1.4]
 */
void reg_init_idtr(_idtr_reg *idtr_reg);

/**
 * @brief Initialize segment registers
 *
 * @param segment_reg_st
 * @par Specifications:
 * [SPEC-10.1.4]
 */
void reg_init_seg(_segment_regs_st *segment_reg_st);

/**
 * @brief Inilialize Intruction pointer
 *
 * @param eip_st
 * @par Specifications:
 * [SPEC-10.1.4]
 */
void reg_init_eip(_eip_st *eip_st);

/**
 * @brief Inilialize the general purpose registers
 *
 * @param _general_regs_st
 * @param pins
 * @param sys_cond_st: global variable storing the system condition values.
 * @par Specifications:
 * [SPEC-10.1.1-2]
 */
void reg_init_gen(_general_regs_st *_general_regs_st, const _pins *pins, const _sys_cond_st *sys_cond_st);

/**
 * @brief Initialize EFLAGS
 *
 * @param eflag_register
 * @par Specifications:
 * [SPEC-10.1.4]
 */
void reg_init_eflags(_eflag_reg_st *eflag_register);

/**
 * @brief Initialize the conrtol register 0
 *
 * @param cr0_reg_st
 * @par Specification:
 * [SPEC-10.1.3]
 */
void reg_init_cr0(_cr0_reg_st *cr0_reg_st);

#endif //_REGISTERS_H_