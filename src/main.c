#include <stdio.h>
#include "status.h"
#include "memory/registers.h"
#include "memory/ram.h"



_status status = OK ; //status = 0 : not error,status>0: warnig,status<0: error;



int main ()
{
    printf("\nStart Emulator\n");

    // Create RAM 
    _ram_ptr ram_ptr = ram_start(&status);
    if(status < 0) goto EXIT;  // if err, terminate

    // Create registers
    _general_regs_st gen_regs_st;
    _segment_regs_st seg_regs_st;
    _eflag_reg_st eflag_reg_st; 
    _eip_st eip_st;
    // init regs
    reg_init_eflags(&eflag_reg_st,&status);
    status = - 6;
    if(status < 0) goto EXIT;  // if err, terminate

    printf("value of RES1 = %d\n", eflag_reg_st.RES1);

    free(ram_ptr);
    printf("Program end\n");
    return 0;

EXIT: 
    printf("Failed to start Emulator : ");
    err_print(&status);
    return status; 
}