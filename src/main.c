#include </usr/include/linux/limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "typedefs.h"
#include "status/status.h"
#include "bios/bios.h"
#include "config.h"
#include "memory/ram.h"
#include "memory/registers.h"
#include "pins/pins.h"
#include "screen/screen.h"
#include "utils/utils.h"
#include "interrupts/interrupts.h"
#include "sys/sys.h"

int status = _STATUS_OK;        // Errors/warning reported by functions. [status = 0]=>OK, [status > 0 ]=>warnig, [status <0 ]=>error.
_sys_cond_st sys_cond_st = {0}; // Processor system  condition is recorder here.

_pins pins;
_ram_ptr ram_ptr;
_general_regs_st gen_regs_st;
_segment_regs_st seg_regs_st;
_eflag_reg_st eflag_reg_st;
_eip_st eip_st;
_gdtr_reg gdtr_reg = {0};
_ldtr_reg ldtr_reg = {0};
_idtr_st idtr_st;
_interrupts_flags_st interrupts_flags_st = {0};
_task_reg_st task_reg_st = {0};
_cr0_reg_st cr0_reg_st;
_cr2_reg cr2_reg = {0};
_cr3_reg_pdbr cr3_reg_pdbr = {0};
_tlb_reg_st tlb_reg_st = {0};

int main(int argc, char **argv)
{
    print_start();

    if (argv[1] == NULL)
    {
        status = _STATUS_NO_DEVICE;
        err_handler("");
    }

    /* Initialize system */
    sys_init();

    /* Load bootable device file */
    FILE *device = open_file_ro(argv[1]);

    /* Check is device is bootable */
    bios_is_bootable(device);

    /* Load MBR Master Boot Record */
    bios_load_MBR_TO_RAM(device);

#ifdef DBG
    printf("== LOAD MSB (Master Boot Record) to RAM location 0x%X\n", _MBR_LOAD_RAM_ADDR);
#endif

    // Processor starts in real mode
    while (1)
    {
        // system
        // test
        idtr_st.limit = 0UL; // casues shutdown in case of interruption
        interrupts_flags_st.exceptions.trap.overflow = 1;
        check_and_service_interrupts();
        // instruction execution
        break;
    }

    print_end();

    return 0;
}
