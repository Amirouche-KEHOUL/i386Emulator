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

int status = _STATUS_OK;        // Errors/warning reported by functions. [status = 0]=>OK, [status > 0 ]=>warnig, [status <0 ]=>error.
_sys_cond_st sys_cond_st = {0}; // Processor system  condition is recorder here.

_16bus A3120 = 0; // Address lines 20->31 (12 bits), asserted at reset
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

    /* Load bootable device file */
    FILE *device = open_file_ro(argv[1]);

    /* Initialize system */
    sys_init();

    /* Check is device is bootable */
    bios_is_bootable(device);

    /* Load MBR Master Boot Record */
    bios_load_MBR_TO_RAM(device);

#ifdef DBG
    printf("== LOAD MSB (Master Boot Record) to physical memory location 0x%X\n", _MBR_LOAD_RAM_ADDR);
#endif

    /*
    gdtr_reg_st.DTR = 20U;
     */

    // Test DATA Segment
    _byte byte_v[8] = {0};
    byte_v[0] = (_byte)0xFF;
    byte_v[1] = (_byte)0xCD;
    byte_v[2] = (_byte)0xEE;
    byte_v[3] = (_byte)0xDD;
    byte_v[4] = (_byte)0xBB;
    byte_v[5] = (_byte)0b10010010;
    byte_v[6] = (_byte)0x34;
    byte_v[7] = (_byte)0xCC;

    for (unsigned int i = 0; i < 8; i++)
    {
        physical_memory_write(byte_v[i], physical_memory_ptr, linear_to_physical_addr((gdtr_reg_st.DTR + 8u) + i));
    }

    _selector_st selector_st;
    selector_st.index = 1U;
    selector_st.requestor_privilege_level = 0U;
    selector_st.table_indicator = _GDT;

    // Expect Code segments only
    load_selector_into_seg_reg(selector_st, _SS_REG);

    // Processor starts in real mode
    while (1)
    {
        // system
        check_and_service_interrupts();
        // instruction execution
        break;
    }

    print_end();

    return 0;
}
