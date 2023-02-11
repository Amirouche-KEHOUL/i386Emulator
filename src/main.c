#include <stdio.h>
#include "status/status.h"
#include "memory/registers.h"
#include "memory/ram.h"
#include "pins/pins.h"

_status status = STATUS_OK ; //status = 0 : not error, > 0: warnig, < 0: error.
_sys_cond_st sys_cond_st ; 

int main ()
{
    printf("Start Emulator\n");

    // Create and init pins 
    _pins pins ;
    pin_pow_up (&pins,&status);  

    // Create and init RAM 
    _ram_ptr ram_ptr = ram_start(&status);

    // Create registers
    _general_regs_st gen_regs_st;
    _segment_regs_st seg_regs_st;
    _eflag_reg_st eflag_reg_st;
    _eip_st eip_st;
    _gdtr_reg gdtr_reg;
    _ldtr_reg ldtr_reg;
    _idtr_reg idtr_reg;
    _task_reg_st task_reg_st;
    _cr0_reg_st cr0_reg_st;
    _cr2_reg cr2_reg;
    _cr3_reg_pdbr cr3_reg_pdbr;
    _tlb_reg_st tlb_reg_st;

        // init regs
    reg_init_eflags(&eflag_reg_st,&status);
    reg_init_eip(&eip_st, &status);
    reg_init_seg(&seg_regs_st,&status);
    reg_init_gen(&gen_regs_st,&pins,&sys_cond_st, &status);
    reg_init_cr0(&cr0_reg_st,&status);



    free(ram_ptr);

    printf("Close Emulator\n");

    return   0;
}