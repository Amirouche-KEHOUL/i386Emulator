#include "address_translator.h"

_32_linear_addr translate_segment(_32_logical_addr offset, void *segment_decriptor, int segment_descriptor_type)
{
    _32_linear_addr ret = 0UL;

    if (segment_descriptor_type == _DATA_SEGMENT_DESCRIPTOR)
    {
        ret = ((_data_segment_descriptor_st *)segment_decriptor)->base + offset;
        return ret;
    }
    if (segment_descriptor_type == _CODE_SEGMENT_DESCRIPTOR)
    {
        ret = ((_code_segment_descriptor_st *)segment_decriptor)->base + offset;
        return ret;
    }
    if (segment_descriptor_type == _SYS_SEGMENT_DESCRIPTOR)
    {
        ret = ((_system_segment_descriptor_st *)segment_decriptor)->base + offset;
        return ret;
    }
    return ret;
}

/*
TODO: Implement Type checking function
When a selector of a descriptor is loaded into a segment register.
Certain segment registers can contain only certain descriptor types. For example:
 - CS reg eccept only code segments
 - Selectors of executable segments that are not readable cannot be loaded into data-segment registers.
 - Only selectors of writable data segments can be loaded into SS.
*/

typedef unsigned char _8bit_index;
typedef unsigned int _16bit_index;

#define _CODE_DATA_OR_SYSTEM_SEG__BIT_LOCATION 4U
#define _EXECUTABLE__BIT_LOCATION 3U

_32_physical_addr linear_to_physical_addr(_32_linear_addr linear_addr)
{
    return linear_addr; // TODO: this is a tomporary solution
}

// Returns (1) if read value is (1), (0) if read value is (0), (2) if error
_byte is_bit_set(_byte byte, _8bit_index index)
{
    if (index > 7)
    {
        // TODO : add error handling ?
        return 2U;
    }
    _byte SET = 1;

    if (((SET << _CODE_DATA_OR_SYSTEM_SEG__BIT_LOCATION) & byte) != 0U)
    {
        return 1U;
    }

    return 0U;
}

int check_segment_type(_selector_st selector_st)
{
    int ret = 0; // TODO: confirm value before return

    if ((selector_st.table_indicator == _GDT) && (selector_st.index == 0U)) // Can not index[0] of a GDT
    {
        // TODO: Implement exception. choose return value
        return ret;
    }
    _byte byte = 0U;
    _32_linear_addr byteN5_linear_addr = (gdtr_reg_st.DTR + (selector_st.index * 8U)) + 5U; // calculate the liear address of byte number 5 (0..5) of the segment descriptor (looking for Type field)
    _32_physical_addr physical_addr = linear_to_physical_addr(byteN5_linear_addr);
    byte = physical_memory_read(physical_memory_ptr, physical_addr);

    if ((is_bit_set(byte, _CODE_DATA_OR_SYSTEM_SEG__BIT_LOCATION) == 1U) && !(is_bit_set(byte, _EXECUTABLE__BIT_LOCATION) == 0U))
    {
        return _DATA_SEGMENT_DESCRIPTOR;
    }
    if ((is_bit_set(byte, _CODE_DATA_OR_SYSTEM_SEG__BIT_LOCATION) == 1U) && (is_bit_set(byte, _EXECUTABLE__BIT_LOCATION) == 1U))
    {
        return _CODE_SEGMENT_DESCRIPTOR;
    }
    if (!(is_bit_set(byte, _CODE_DATA_OR_SYSTEM_SEG__BIT_LOCATION) == 0U))
    {
        return _SYS_SEGMENT_DESCRIPTOR;
    }

    // TODO: if no condition entred there is a problem
    return 4U;
}

// "convert" the strcut into 16bit field reg.
_16reg concat_selector(_selector_st selector_st)
{
    _16reg ret = 0U;
    _16bit_index index = selector_st.index;
    _16reg table_indicator = selector_st.table_indicator;
    _16reg requestor_privilege_level = selector_st.requestor_privilege_level;

    ret = requestor_privilege_level | (table_indicator << 2) | (index << 3);

    return ret;
}

_code_segment_descriptor_st *get_code_seg_desc(_selector_st);
_data_segment_descriptor_st *get_data_seg_desc(_selector_st);

void load_seg_regs(_selector_st selector_st, int segment_reg)
{
    if ((selector_st.table_indicator == _GDT) && (selector_st.index == 0U)) // Can not index[0] of a GDT
    {
        // TODO: Implement exception. choose return value
        return;
    }
    if (segment_reg == _CS_REG)
    {
        segment_regs_st.CS = concat_selector(selector_st);
        segment_regs_st.CS_hidden_code_segment_descriptor = get_code_seg_desc(selector_st);
    }
    if (segment_reg == _SS_REG)
    {
        segment_regs_st.SS = concat_selector(selector_st);
        segment_regs_st.SS_hidden_stack_segment_descriptor = get_data_seg_desc(selector_st);
    }
    if (segment_reg == _DS_REG)
    {
        segment_regs_st.DS = concat_selector(selector_st);
        segment_regs_st.DS_hidden_data_segment_descriptor = get_data_seg_desc(selector_st);
    }
    if (segment_reg == _ES_REG)
    {
        segment_regs_st.ES = concat_selector(selector_st);
        segment_regs_st.ES_hidden_data_segment_descriptor = get_data_seg_desc(selector_st);
    }
    if (segment_reg == _FS_REG)
    {
        segment_regs_st.FS = concat_selector(selector_st);
        segment_regs_st.FS_hidden_data_segment_descriptor = get_data_seg_desc(selector_st);
    }
    if (segment_reg == _GS_REG)
    {
        segment_regs_st.GS = concat_selector(selector_st);
        segment_regs_st.GS_hidden_data_segment_descriptor = get_data_seg_desc(selector_st);
    }
}

void load_selector_into_seg_reg(_selector_st selector_st, int segment_reg)
{
    if ((selector_st.table_indicator == _GDT) && (selector_st.index == 0U)) // Can not index[0] of a GDT
    {
        // TODO: Implement exception. choose return value
        return;
    }

    if (segment_reg == _CS_REG) // CS reg eccept only code segments
    {
        if (check_segment_type(selector_st) != _CODE_SEGMENT_DESCRIPTOR)
        {
#ifdef DBG
            printf("Exception: CS reg eccept only code segments\n");
#endif
            // TODO: rise exception?
            return;
        }
        load_seg_regs(selector_st, segment_reg);
        return;
    }

    if ((segment_reg != _CS_REG) && (segment_reg != _SS_REG)) // Selectors of executable segments that are not readable cannot be loaded into data-segment registers
    {
        if (check_segment_type(selector_st) == _CODE_SEGMENT_DESCRIPTOR)
        {
            if ((get_code_seg_desc(selector_st)->readable) == _NOT_READABLE_CODE_SEGMENT)
            {
#ifdef DBG
                printf("Exception: Selectors of executable segments that are not readable cannot be loaded into data-segment registers\n");
#endif
                // TODO: rise exception?
                return;
            }
            // segment is readable
            if (segment_reg == _DS_REG)
            {
                load_seg_regs(selector_st, segment_reg);
                return;
            }
        }
    }

    if (segment_reg == _SS_REG) // Only selectors of writable data segments can be loaded into SS.
    {
        if (check_segment_type(selector_st) != _DATA_SEGMENT_DESCRIPTOR)
        {
#ifdef DBG
            printf("Exception: Only selectors of writable data segments can be loaded into SS.\n");
#endif
            // TODO: rise exception ?
            return;
        }
        if ((get_data_seg_desc(selector_st)->writable) == _NOT_WRITABLE_CODE_SEGMENT)
        {
#ifdef DBG
            printf("Exception: Only selectors of writable data segments can be loaded into SS.\n");
#endif
            // TODO: rise exception?
            return;
        }
        load_seg_regs(selector_st, segment_reg);
        return;
    }
}

/*
TODO: Implement limit checking
*/