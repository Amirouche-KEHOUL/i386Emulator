#include <stdio.h>
#include "status/status.h"
#include "memory/registers.h"
#include "memory/ram.h"
#include "pins/pins.h"



_status status = STATUS_OK ; //status = 0 : not error,status>0: warnig,status<0: error;



int main ()
{
    printf("\nStart Emulator\n");
    // Create and init pins 
    _pins_st pins_st ;
    pins_pow_up (&pins_st,&status);    
    if(status < 0) goto EXIT;  // if err, terminate

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
    status = STATUS_END_OF_RESET;
    pins_st.BUSY = 1;
    reg_init_gen(&gen_regs_st,&pins_st,&status);

    printf("AH value  = 0x%X\n",gen_regs_st.EAX.AH);
    printf("AH value  = 0x%X\n",gen_regs_st.EAX.AH);
    printf("msb value  = 0x%X\n",gen_regs_st.EAX.msb);


    free(ram_ptr);
    printf("Close Emulator\n");
    return 0;

EXIT: 
    printf("Failed to start Emulator : ");
    err_print(&status);
    printf("Exit\n");
    return status; 
}