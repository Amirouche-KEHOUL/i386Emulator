#include </usr/include/linux/limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "typedefs.h"
#include "sys/sys.h"
#include "config.h"
#include "status/status.h"
#include "pins/pins.h"
#include "bios/bios.h"
#include "memory/physical_memory.h"
#include "memory/registers.h"
#include "memory/address_translator.h"
#include "interrupts/interrupts.h"
#include "utils/utils.h"
#include "decoder/decoder.h"

int status = _STATUS_OK;        // Errors/warning reported by functions. [status = 0]=>OK, [status > 0 ]=>warnig, [status <0 ]=>error.
_sys_cond_st sys_cond_st = {0}; // Processor system  condition is recorder here.

_16_bus A3120 = 0; // Address lines 20->31 (12 bits), asserted at reset
_pins pins = 0;
_physical_memory_ptr physical_memory_ptr = NULL;
_IO_ptr IO_ptr = NULL;
_general_regs_st general_regs_st = {0};
_segment_regs_st segment_regs_st = {0};
_code_segment_descriptor_st CS_hidden_code_segment_descriptor = {0};
_data_segment_descriptor_st SS_hidden_stack_segment_descriptor = {0};
_data_segment_descriptor_st DS_hidden_data_segment_descriptor = {0};
_data_segment_descriptor_st ES_hidden_data_segment_descriptor = {0};
_data_segment_descriptor_st FS_hidden_data_segment_descriptor = {0};
_data_segment_descriptor_st GS_hidden_data_segment_descriptor = {0};
_eflag_reg_st eflag_reg_st = {0};
_eip_st eip_st = {0};
_dtr_reg_st gdtr_reg_st = {0};
_dtr_reg_st ldtr_reg_st = {0};
_idtr_st idtr_st = {0};
_interrupts_flags_st interrupts_flags_st = {0};
_task_reg_st task_reg_st = {0};
_cr0_reg_st cr0_reg_st = {0};
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

    decode();
    print_end();

    return 0;
}
