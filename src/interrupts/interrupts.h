#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_
#include "../typedefs.h"
#include "../memory/registers.h"
#include "../pins/pins.h"

#include <stdio.h> // TODO: to remove if not neccessary

extern _eflag_reg_st eflag_reg_st;               // Global main.c
extern _pins pins;                               // Global main.c
extern _interrupts_flags_st interrupts_flags_st; // Global main.c

/**Interrupt and Exception ID Assignments
9,15,17-31  are reserved IDs
32-255      Available for external trap trap exception interrupts via INTR pin (soft interrupts: two-byte )*/
#define DEVIDE_ERROR_FAULT_EXECPTION_ID 0
#define DEBUG_ECCEPTIONS_ID 1 // Some debug exceptions are traps and some are faults. The exception handler can determine which has occurred by examining DR6.(Refer to Chapter 12.)
#define NON_MASKABLE_INTERRUPT_ID 2
#define BREAKPOINT_TRAP_EXCEPTION_ID 3
#define OVERFLOW_TRAP_EXCPETION_ID 4
#define BONDS_CHECK_FAULT_EXCEPTION_ID 5
#define INVALID_OPCODE_FAULT_EXCEPTION_ID 6
#define COPROCESSOR_NOT_AVAILABLE_FAULT_EXCEPTION_ID 7
#define DOUBLE_FAULT_ABORT_EXCEPTION_ID 8
// #define OVERRUN_ABORT_EXCEPTION_ID 9 // TODO: TBC
#define INVALID_TSS_FAULT_EXCEPTION_ID 10
#define SEGMENT_NOT_PRESENT_FAULT_EXCEPTION_ID 11
#define STACK_FAULT_EXCEPTION_ID 12
#define GENERAL_PROTECTION_FAULT_EXCEPTION_ID 13
#define PAGE_FAULT_EXCEPTION_ID 14
#define COPROCESSOR_ERROR_FAULT_EXCEPTION_ID 16

#define ACCEPT_EXTERNAL_INTERRUPT_VIA_INTR_PIN 1

/**
 * @brief Reads interrupt flags from the global var interrupts_flags_st and services the interrupts based on
 * the priority policy.
 */
void check_and_service_interrupts(void);

#endif //_INTERRUPT_H_a