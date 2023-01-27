#include <stdio.h>
#include "statusflags.h"
#include "memory/registers.h"
#include "memory/ram.h"


_status status = OK ; //status = 0 : not error,status>0: warnig,status<0: error;


int main ()
{
    // Create RAM
    _ram ram = ram_start(&status);
    if(status < 0) // if error
    {
        printf("ERROR: %d : RAM could not be started \n",status);
        return status;
    }
    // Create registers
    _general_regs gen_regs;
    _segment_regs seg_regs;
    _eflag_reg flag_reg; 
    _eip eip;

    
    free(ram);
    return  0;
}