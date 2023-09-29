#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#include "../memory/registers.h"
#include "../pins/pins.h"

/*Interrupt and Exception ID Assignments*/
/* 9,15,17-31  are reserved IDs 
32-255      Available for external interrupts via INTR pin (soft interrupts)*/
#define DEVIDE_ERROR_ID 0
#define DEBUG_ECCEPTIONS_ID 1
#define NON_MASKABLE_INTERRUPT_ID 2
#define BREAKPOINT_ID 3
#define OVERFLOW_ID 4
#define BONDS_CHECK_ID 5
#define INVALID_OPCODE_ID 6
#define COPROCESSOR_NOT_AVAILABLE_ID 7
#define DOUBLE_FAULT_ID 8
#define INVALID_TSS_ID 10
#define SEGMENT_NOT_PRESENT_ID 11
#define STACK_EXCEPTION_ID 12
#define GENERAL_PROTECTION_ID 13
#define PAGE_FAULT_ID 14
#define COPROCESSOR_ERROR_ID 16

#define ACCEPT_EXTERNAL_INTERRUPT_VIA_INTR_PIN 1

extern _eflag_reg_st eflag_reg_st; // global main.c
extern _pins pins;                 //global main.c

void check_and_service_interrupts(void);

#endif //_INTERRUPT_H_a