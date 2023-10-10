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

_byte get_byte_from_linear_addr(_32_linear_addr linear_addr)
{
    _32_physical_addr physical_addr = linear_to_physical_addr(linear_addr);
    _byte byte = physical_memory_read(physical_memory_ptr, physical_addr);
    return byte;
}

// calculate the liear address of byte number "byte_index" of the segment descriptor
_32_linear_addr calc_linear_addr_of_byte_in_seg_desc(_selector_st selector_st, _8bit_index byte_index)
{
    _32_linear_addr dtr = 0;
    if (selector_st.table_indicator == _GDT)
    {
        dtr = gdtr_reg_st.DTR;
    }
    if (selector_st.table_indicator == _LDT)
    {
        dtr = ldtr_reg_st.DTR;
    }

    _32_linear_addr byte_linear_addr = dtr + (selector_st.index * 8U) + byte_index; // size of segment descriptor is 8 bytes
    return byte_linear_addr;
}

int check_segment_type(_selector_st selector_st)
{
    int ret = 0; // TODO: confirm value before return

    if ((selector_st.table_indicator == _GDT) && (selector_st.index == 0U)) // Can not index[0] of a GDT
    {
        // TODO: Implement exception. choose return value
        return ret;
    }

    _32_linear_addr byteN5_linear_addr = calc_linear_addr_of_byte_in_seg_desc(selector_st, 5U); // Byte field holding the type bits
    _byte byte = get_byte_from_linear_addr(byteN5_linear_addr);

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

_32reg return_base(_byte byte_v[8])
{
    // TODO: confirm the shift values below
    _32reg base = 0;

    _32reg byte0 = byte_v[2];
    _32reg byte1 = byte_v[3];
    _32reg byte2 = byte_v[4];
    _32reg byte3 = byte_v[7];

    byte3 = byte3 << 24;
    byte2 = byte2 << 16;
    byte1 = byte1 << 8;

    base = byte0 | byte1 | byte2 | byte3;

    return base;
}

_32reg return_limit(_byte byte_v[8])
{
    // TODO: confirm the shift values below
    _32reg limit = 0; // 20 bits

    _32reg byte0 = byte_v[0];
    _32reg byte1 = byte_v[1];
    _32reg byte2 = byte_v[6];

    byte1 = byte1 << 8;
    byte2 = byte2 << 16; // TODO: Confirm if uper bits (> 19) must be truncated

    limit = byte0 | byte1 | byte2;

    return limit;
}

void flat_bin_to_code_seg_descriptor_st(_byte byte_v[8], _code_segment_descriptor_st *code_segment_descriptor_st_ptr)
{
    code_segment_descriptor_st_ptr->base = return_base(byte_v);
    code_segment_descriptor_st_ptr->limit = return_limit(byte_v);
    code_segment_descriptor_st_ptr->descriptor_privilege_level = byte_v[5] >> 5;
    code_segment_descriptor_st_ptr->segment_present = byte_v[5] >> 7;
    code_segment_descriptor_st_ptr->Code_data_OR_sys_segment = byte_v[5] >> 4;
    code_segment_descriptor_st_ptr->executable = byte_v[5] >> 3;
    code_segment_descriptor_st_ptr->conforming = byte_v[5] >> 2;
    code_segment_descriptor_st_ptr->readable = byte_v[5] >> 1;
    code_segment_descriptor_st_ptr->accessed = byte_v[5];
    code_segment_descriptor_st_ptr->granularity = byte_v[6] >> 7;
    code_segment_descriptor_st_ptr->DEFAULT = byte_v[6] >> 6;
    code_segment_descriptor_st_ptr->available_for_programmer_user = byte_v[6] >> 4;
}

void flat_bin_to_data_seg_descriptor_st(_byte byte_v[8], _data_segment_descriptor_st *data_segment_descriptor_st_ptr)
{
    data_segment_descriptor_st_ptr->base = return_base(byte_v);
    data_segment_descriptor_st_ptr->limit = return_limit(byte_v);
    data_segment_descriptor_st_ptr->descriptor_privilege_level = byte_v[5] >> 5;
    data_segment_descriptor_st_ptr->segment_present = byte_v[5] >> 7;
    data_segment_descriptor_st_ptr->Code_data_OR_sys_segment = byte_v[5] >> 4;
    data_segment_descriptor_st_ptr->executable = byte_v[5] >> 3;
    data_segment_descriptor_st_ptr->expand_down = byte_v[5] >> 2;
    data_segment_descriptor_st_ptr->writable = byte_v[5] >> 1;
    data_segment_descriptor_st_ptr->accessed = byte_v[5];
    data_segment_descriptor_st_ptr->granularity = byte_v[6] >> 7;
    data_segment_descriptor_st_ptr->big = byte_v[6] >> 6;
    data_segment_descriptor_st_ptr->available_for_programmer_user = byte_v[6] >> 4;
}

void init_code_segment_descriptor(_code_segment_descriptor_st *code_segment_descriptor_st_ptr)
{
    code_segment_descriptor_st_ptr->accessed = 0U;
    code_segment_descriptor_st_ptr->available_for_programmer_user = 0U;
    code_segment_descriptor_st_ptr->base = 0U;
    code_segment_descriptor_st_ptr->Code_data_OR_sys_segment = 0U;
    code_segment_descriptor_st_ptr->conforming = 0U;
    code_segment_descriptor_st_ptr->DEFAULT = 0U;
    code_segment_descriptor_st_ptr->descriptor_privilege_level = 0U;
    code_segment_descriptor_st_ptr->executable = 0U;
    code_segment_descriptor_st_ptr->granularity = 0U;
    code_segment_descriptor_st_ptr->limit = 0U;
    code_segment_descriptor_st_ptr->readable = 0U;
    code_segment_descriptor_st_ptr->segment_present = 0U;
}

void init_data_segment_descriptor(_data_segment_descriptor_st *data_segment_descriptor_st_ptr)
{
    data_segment_descriptor_st_ptr->accessed = 0U;
    data_segment_descriptor_st_ptr->available_for_programmer_user = 0U;
    data_segment_descriptor_st_ptr->base = 0U;
    data_segment_descriptor_st_ptr->Code_data_OR_sys_segment = 0U;
    data_segment_descriptor_st_ptr->big = 0U;
    data_segment_descriptor_st_ptr->expand_down = 0U;
    data_segment_descriptor_st_ptr->descriptor_privilege_level = 0U;
    data_segment_descriptor_st_ptr->executable = 0U;
    data_segment_descriptor_st_ptr->granularity = 0U;
    data_segment_descriptor_st_ptr->limit = 0U;
    data_segment_descriptor_st_ptr->writable = 0U;
    data_segment_descriptor_st_ptr->segment_present = 0U;
}

// Returns a code descriptor structure pointer for a given selector.
_code_segment_descriptor_st *get_code_seg_desc(_selector_st selector_st)
{
    if ((selector_st.table_indicator == _GDT) && (selector_st.index == 0U)) // Can not index[0] of a GDT
    {
        // TODO: Implement exception. choose return value
        return NULL;
    }
    if (selector_st.table_indicator != _CODE_DATA_OR_SYSTEM_SEG__BIT_LOCATION)
    {
        // TODO return error ?
        return 0;
    }
    _code_segment_descriptor_st *code_segment_descriptor_st_ptr = (_code_segment_descriptor_st *)malloc(sizeof(_code_segment_descriptor_st));
    if (code_segment_descriptor_st_ptr == NULL)
    {
        // TODO: handle malloc error
    }
    init_code_segment_descriptor(code_segment_descriptor_st_ptr);

    _byte byte_v[8] = {0U};
    _32_linear_addr liear_addr = 0U;

    for (int b_index = 0; b_index < 8; b_index++)
    {
        liear_addr = calc_linear_addr_of_byte_in_seg_desc(selector_st, b_index);
        byte_v[b_index] = get_byte_from_linear_addr(liear_addr);
    }

    flat_bin_to_code_seg_descriptor_st(byte_v, code_segment_descriptor_st_ptr);

    return code_segment_descriptor_st_ptr;
}

// Memory leak risk ! THE CALLER FUNCTION HAVE THE RESPONSIBILITY TO FREE (OR NOT) ALLOCATED MEMORY ! Returns a pointer to a data segment pointed by selector_st.
_data_segment_descriptor_st *get_data_seg_desc(_selector_st selector_st)
{
    if ((selector_st.table_indicator == _GDT) && (selector_st.index == 0U)) // Can not index[0] of a GDT
    {
        // TODO: Implement exception. choose return value
        return NULL;
    }
    if (selector_st.table_indicator != _CODE_DATA_OR_SYSTEM_SEG__BIT_LOCATION)
    {
        // TODO return error ?
        return 0;
    }
    _data_segment_descriptor_st *data_segment_descriptor_st_ptr = (_data_segment_descriptor_st *)malloc(sizeof(_data_segment_descriptor_st));
    if (data_segment_descriptor_st_ptr == NULL)
    {
        // TODO: handle malloc error
    }
    init_data_segment_descriptor(data_segment_descriptor_st_ptr);

    _byte byte_v[8] = {0U};
    _32_linear_addr liear_addr = 0U;

    for (int b_index = 0; b_index < 8; b_index++)
    {
        liear_addr = calc_linear_addr_of_byte_in_seg_desc(selector_st, b_index);
        byte_v[b_index] = get_byte_from_linear_addr(liear_addr);
    }

    flat_bin_to_data_seg_descriptor_st(byte_v, data_segment_descriptor_st_ptr);

    return data_segment_descriptor_st_ptr;
}

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
            _code_segment_descriptor_st *code_segment_descriptor_st_ptr = get_code_seg_desc(selector_st);
            if ((code_segment_descriptor_st_ptr->readable) == _NOT_READABLE_CODE_SEGMENT) // TODO : fix memeory leak
            {
                free(code_segment_descriptor_st_ptr);
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
        _data_segment_descriptor_st *data_segment_descriptor_st_ptr = get_data_seg_desc(selector_st);
        if ((data_segment_descriptor_st_ptr->writable) == _NOT_WRITABLE_CODE_SEGMENT)
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