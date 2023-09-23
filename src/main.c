#include </usr/include/linux/limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 

#include "status/status.h"
#include "bios/bios.h"
#include "config.h"
#include "memory/registers.h"
#include "memory/ram.h"
#include "pins/pins.h"
#include "sys/sys.h"

int status = _STATUS_OK; // status = 0 : OK, > 0: warnig, < 0: error.

_sys_cond_st sys_cond_st ; 

int str_length(char str[]) 
{
    int count; 
    for (count = 0; str[count] != '\0'; ++count);
    return count; 
}

int main (int argc, char **argv)
{
    printf("----------| Start Emulator |----------\n");
    /* If no device quit Emulator */

    /* Create and init pins */
    _pins pins ;
    pin_pow_up (&pins);  

    /* Create and init RAM */
    printf("== Create and initialise RAM\n");
    _ram_ptr ram_ptr = ram_start();

    /* Create registers */
    printf("== Create and initialise registers\n");
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
    reg_init_eflags(&eflag_reg_st);
    reg_init_eip(&eip_st);
    reg_init_seg(&seg_regs_st);
    reg_init_gen(&gen_regs_st,&pins,&sys_cond_st);
    reg_init_cr0(&cr0_reg_st);
        
    if (argv[1] == NULL)
    {
        status = _STATUS_NO_DEVICE;
        err_handler("");
    }
    
    /* Load bootable device file */
    FILE *device; // Bootable device
    //TODO: check if file is binary, else exit emulator.
    char *device_name = argv[1];
    char device_path[PATH_MAX]; 
        // Construct full path and open the device file
    if (getcwd(device_path, sizeof(device_path)) != NULL) // Current Working Directory
    {
        for (int i = 0 ; i < PATH_MAX - _CONF_MAX_LEN_DEVICE_NAME ; i++)
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
            status = _ERR_OPEN_DEVICE_NOK;
            err_handler(device_name);
        }
    } else // If getcwd fails
    {
        status = _ERR_OPEN_DEVICE_NOK;
        err_handler(device_name);
    }
   
    printf("Disk : %s ",device_name);

    /* Check is device is bootable */
    if (bios_is_bootable(device) == _DEVICE_IS_BOOTABLE) printf ("(bootable).\n");
        // in case of device not bootable
    if (status == _STATUS_DEVICE_BOOT_SIG_NOT_FOUND) 
    {
        fclose(device);
        printf("----------| Exit Emulator |---------\n"); 
        exit(status);
    }
    /* Load MBR Master Block Record */
    bios_load_MBR_TO_RAM(device,ram_ptr,&seg_regs_st,&eip_st);
    printf("== LOAD Master Boot Record to RAM location 0x%X\n",_MBR_LOAD_RAM_ADDR);    

    /* 
    printf("value of CS = 0x%X\n",seg_regs_st.CS);
    printf("value of IP = 0x%X\n",eip_st.IP);
    for (int i = 0; i < 512 ; i++)
    {    * 
        printf("0x%X  :  0x%X\n",0x7c00+i,ram_read(ram_ptr,0x7c00+i,) );
    }
    */
   
    printf("----------| Exit Emulator |----------\n");
    return   0;
}