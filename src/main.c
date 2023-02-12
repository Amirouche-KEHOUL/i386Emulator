#include <stdio.h>
#include <unistd.h> 
#include <limits.h>
#include "status/status.h"
#include "memory/registers.h"
#include "memory/ram.h"
#include "pins/pins.h"

_status status = STATUS_OK ; //status = 0 : not error, > 0: warnig, < 0: error.
_sys_cond_st sys_cond_st ; 

int str_length(char str[]) 
{
    int count; 
    for (count = 0; str[count] != '\0'; ++count);
    return count; 
}

int main (int argc, char** argv)
{
    printf("Start Emulator\n");
    
    /* load bootable device file */
    FILE* device; // bootable device
    char* device_name = argv[1];
    char device_path[PATH_MAX]; 
        // construct full path and open the device file
    if (getcwd(device_path, sizeof(device_path)) != NULL) // Current Working Directory
    {
        for (int i = 0 ; i < PATH_MAX - CONF_MAX_LEN_DEVICE_NAME ; i++)
        {
            if (device_path[i] == 0 )
            {   
                device_path[i] ='/';
                i++;
                int j;
                for(j = 0 ; j < str_length(device_name) ;j++ )
                {
                    device_path[i+j] = device_name[j];
                }
                device_path[i+j]='\0';
                break; 
            }
        }   
        device = fopen(device_path,"r");
        if (device == NULL)
        {
            status = ERR_OPEN_DEVICE_NOK;
            err_handler(&status,device_name);
        }
    } else // if getcwd fails
    {
        status = ERR_OPEN_DEVICE_NOK;
        err_handler(&status,device_name);
    }
   
    printf("Disk : %s\n",device_name);

    /* Create and init pins */
    _pins pins ;
    pin_pow_up (&pins,&status);  

    /* Create and init RAM */
    printf("== Create and initialise RAM ...\n");
    _ram_ptr ram_ptr = ram_start(&status);

    /* Create registers */
    printf("== Create and initialise registers ...\n");
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

    
    /* Start BIOS */
    printf("== Start BIOS...\n");
    
    free(ram_ptr);
    printf("Close Emulator\n");

    return   0;
}