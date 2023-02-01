#include <stdio.h>
#include "status/status.h"
#include "memory/registers.h"
#include "memory/ram.h"
#include "pins/pins.h"



_status status = STATUS_OK ; //status = 0 : not error,status>0: warnig,status<0: error;



int main ()
{
    printf("\nStart Emulator\n");
    // Create pins 
    _pins_st pins_st ;
    pins_init(0,&status);    
    if(status < 0) goto EXIT;  // if err, terminate

    // Create RAM 
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



    free(ram_ptr);
    printf("Close Emulator\n");
    return 0;

EXIT: 
    printf("Failed to start Emulator : ");
    err_print(&status);
    printf("Exit\n");
    return status; 
}