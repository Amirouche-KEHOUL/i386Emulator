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
#include "screen/screen.h"
#include "utils/utils.h"

int status = _STATUS_OK;  // Status = 0 : OK, > 0: warnig, < 0: error.
_sys_cond_st sys_cond_st; // System  condition

_pins pins;
_ram_ptr ram_ptr;
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

int main(int argc, char **argv)
{
    printf("----------| Start Emulator |----------\n");

    if (argv[1] == NULL)
    {
        status = _STATUS_NO_DEVICE;
        err_handler("");
    }

    /* Init pins */
    pin_pow_up(&pins);

    /* Start RAM */
    printf("== Initialize RAM\n");
    ram_ptr = ram_start();

    /* Create registers */
    printf("== Initialize registers\n");
    reg_init_eflags(&eflag_reg_st);
    reg_init_eip(&eip_st);
    reg_init_seg(&seg_regs_st);
    reg_init_gen(&gen_regs_st, &pins, &sys_cond_st);
    reg_init_cr0(&cr0_reg_st);
    reg_init_idtr(&idtr_reg);

    /* Load bootable device file */
    FILE *device = open_file_ro(argv[1]); // Bootable device

    /* Check is device is bootable */ // TODO: optimize the code conditions below
    if (bios_is_bootable(device) == _DEVICE_IS_BOOTABLE)
    {
        printf("(bootable).\n");
    }
    if (status == _STATUS_DEVICE_BOOT_SIG_NOT_FOUND) // in case of device not bootable
    {
        fclose(device);
        printf("----------| Exit Emulator |---------\n");
        exit(status);
    }

    /* Load MBR Master Boot Record */
    bios_load_MBR_TO_RAM(device, ram_ptr, &seg_regs_st, &eip_st);
    printf("== LOAD MSB (Master Boot Record) to RAM location 0x%X\n", _MBR_LOAD_RAM_ADDR);

    while (1)
    {
        // system
        // Interrupts
        // instruction execution
        break;
    }

    printf("----------| Exit Emulator |----------\n");
    return 0;
}
