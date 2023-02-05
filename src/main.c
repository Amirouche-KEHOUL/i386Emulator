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
        // init regs
    reg_init_eflags(&eflag_reg_st,&status);
    reg_init_eip(&eip_st, &status);
    reg_init_seg(&seg_regs_st,&status);
    reg_init_gen(&gen_regs_st,&pins,&sys_cond_st, &status);

    printf("AH value  = 0x%X\n",gen_regs_st.EAX.AH);
    printf("AH value  = 0x%X\n",gen_regs_st.EAX.AH);
    printf("msb value  = 0x%X\n",gen_regs_st.EAX.msb);

    free(ram_ptr);
    printf("Close Emulator\n");  
     
    return 0;
}