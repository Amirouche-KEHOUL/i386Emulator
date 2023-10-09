#include "address_translator.h"

_32addr translate_segment(_32addr offset, void *segment_decriptor, int segment_descriptor_type)
{
    _32addr ret = 0UL;

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

int check_segment_type(_selector_st);
_16reg concat_selector(_selector_st); // "convert" the strcut into 16bit field reg.
_code_segment_descriptor_st *get_code_seg_desc(_selector_st);
_data_segment_descriptor_st *get_data_seg_desc(_selector_st);

void load_seg_regs(_selector_st selector_st, int segment_reg)
{
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