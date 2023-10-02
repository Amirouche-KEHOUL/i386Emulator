#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#include "../memory/registers.h"
#include "../pins/pins.h"

#include <stdio.h> // TODO: to remove if not neccessary

/**
 * @brief Definition of the global variable used to register interrupts
 */
typedef struct interrupts_flags_st
{
    struct
    {
        struct
        {
            _reg16 devide : 1;                    // ID 0
            _reg16 bond_check : 1;                // ID 5
            _reg16 invalid_opcode : 1;            // ID 6
            _reg16 coprocessor_not_available : 1; // ID 7
            _reg16 invalid_tss : 1;               // ID 10
            _reg16 segment_not_present : 1;       // ID 11
            _reg16 stack : 1;                     // ID 12
            _reg16 general_protection : 1;        // ID 13
            _reg16 page : 1;                      // ID 14
            _reg16 coprocessor_error : 1;         // ID 16

        } fault;
        struct
        {
            _reg16 breakpoint : 1; // ID 3
            _reg16 overflow : 1;   // ID 4

        } trap;
        struct
        {
            _reg16 double_fault : 1; // ID 8
        } abort;
    } exceptions;
    struct
    {
        _reg16 NMI : 1;  // Signaled by NMI (Non Maskable Interrpts)pin
        _reg16 maskable; // Signaled by INTR pin
    } interrupts;
    // TODO: add debug and  software interrupts
} _interrupts_flags_st;

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