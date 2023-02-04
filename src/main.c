#include <stdio.h>
#include "status/status.h"
#include "memory/registers.h"
#include "memory/ram.h"
#include "pins/pins.h"

_status status = STATUS_OK ; //status = 0 : not error, > 0: warnig, < 0: error.

int main ()
{
    printf("Start Emulator\n");
    // Create and init pins 
    _pins pins ;
    pins_pow_up (&pins,&status);   
    pins = 0xFFFFFFFF;
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


    reg_init_gen(&gen_regs_st,&pins,&status);

    printf("AH value  = 0x%X\n",gen_regs_st.EAX.AH);
    printf("AH value  = 0x%X\n",gen_regs_st.EAX.AH);
    printf("msb value  = 0x%X\n",gen_regs_st.EAX.msb);

    free(ram_ptr);
    printf("Close Emulator\n");
    
    printf("read busy %d\n", pins_read(&pins,pin_busy,&status));
    printf("read reset %d\n", pins_read(&pins,pin_reset,&status));

    pins_wrtie(&pins,pin_busy,OFF,&status);
    
    printf("read after write busy %d\n", pins_read(&pins,pin_busy,&status));
    printf("read after write reset %d\n", pins_read(&pins,pin_reset,&status));
    
    return 0;

}