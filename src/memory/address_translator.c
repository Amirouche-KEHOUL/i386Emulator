#include "address_translator.h"

extern _segment_regs_st segment_regs_st;
extern _physical_memory_ptr physical_memory_ptr;
extern _dtr_reg_st gdtr_reg_st;
extern _dtr_reg_st ldtr_reg_st;
extern _cr0_reg_st cr0_reg_st;
extern _cr3_reg_pdbr cr3_reg_pdbr;
extern int status;

// ############################## Segment Translation #################################//

_code_segment_descriptor_st temp_code_segment_descriptor_st_ptr = {0}; // temporary structure
_data_segment_descriptor_st temp_data_segment_descriptor_st_ptr = {0}; // temporary structure

// Interpret limit based on the granularity bit
_32_linear_addr interpret_limit(const void *segment_decriptor, int segment_descriptor_type)
{
    if (segment_descriptor_type > _SYS_SEGMENT_DESCRIPTOR)
    {
        status = _ERR_ADDR_STRANS_ARG;
        err_handler("");
    }
    _32_linear_addr ret = 0U;

    if (segment_descriptor_type == _DATA_SEGMENT_DESCRIPTOR)
    {
        _data_segment_descriptor_st *data_segment_descriptor_st = (_data_segment_descriptor_st *)segment_decriptor;
        ret = (_32_linear_addr)(data_segment_descriptor_st->limit);
        if (data_segment_descriptor_st->granularity == 1U) // 4K pages
        {
            ret = (ret << 12U) | 0xFFF;
            return ret;
        }
        return ret;
    }
    if (segment_descriptor_type == _CODE_SEGMENT_DESCRIPTOR)
    {
        _code_segment_descriptor_st *code_segment_descriptor_st = (_code_segment_descriptor_st *)segment_decriptor;
    }
    if (segment_descriptor_type == _SYS_SEGMENT_DESCRIPTOR)
    {
        _system_segment_descriptor_st *system_segment_descriptor_st = (_system_segment_descriptor_st *)segment_decriptor;
    }
    return ret;
}

_32_linear_addr translate_segment(_32_offset offset, const void *segment_decriptor, int segment_descriptor_type)
{
    if (segment_descriptor_type > _SYS_SEGMENT_DESCRIPTOR)
    {
        status = _ERR_ADDR_STRANS_ARG;
        err_handler("");
    }
    _32_linear_addr ret = 0U;

    if (segment_descriptor_type == _DATA_SEGMENT_DESCRIPTOR)
    {
        ret = ((_data_segment_descriptor_st *)segment_decriptor)->base + offset;
        return ret;
    }
    if (segment_descriptor_type == _CODE_SEGMENT_DESCRIPTOR)
    {
        ret = (((_code_segment_descriptor_st *)segment_decriptor)->base) + offset;
        return ret;
    }
    if (segment_descriptor_type == _SYS_SEGMENT_DESCRIPTOR)
    {
        ret = ((_system_segment_descriptor_st *)segment_decriptor)->base + offset;
        return ret;
    }
    return ret;
}

// Returns (1) if read value is (1), (0) if read value is (0), (2) if error
int is_bit_set(_byte byte, _8_index index)
{
    if (index > (_8_index)7)
    {
        status = _ERR_ADDR_STRANS_ARG;
        err_handler("");
        return -1;
    }
    _byte SET = 1;

    if (((SET << index) & byte) != 0U)
    {
        return 1;
    }

    return 0U;
}

// Returns a byte located in a given linear address.
_byte get_byte_from_linear_addr(_32_linear_addr linear_addr)
{
    _32_physical_addr physical_addr = linear_to_physical_addr(linear_addr);
    _byte byte = physical_memory_read_byte(physical_memory_ptr, physical_addr);
    return byte;
}

// calculate the liear address of byte number "byte_index" of the segment descriptor
_32_linear_addr calc_linear_addr_of_byte_in_seg_desc(_selector_st selector_st, _8_index byte_index)
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
    int ret = -1; // TODO: confirm value before return

    if ((selector_st.table_indicator == _GDT) && (selector_st.index == 0U)) // Can not index[0] of a GDT
    {
        // TODO: Implement exception. choose return value
#ifdef DBG
        printf("Exception: Can not index[0] of a GDT\n");
#endif
        return ret;
    }

    _32_linear_addr byteN5_linear_addr = calc_linear_addr_of_byte_in_seg_desc(selector_st, 5U); // Byte field holding the type bits
    _byte byte = get_byte_from_linear_addr(byteN5_linear_addr);

    int segment_present_bit = is_bit_set(byte, _SEGMENT_PRESENT__BIT_LOCATION);
    if (segment_present_bit == 0) // If this bit is zero, the descriptor is not valid for use in address transformation; the processor will signal an exception when a selector for the descriptor is loaded into a segment register
    {
        // TODO : implement exception
#ifdef DBG
        printf("Exception: Not-present descriptor\n");
#endif
    }
    int code_data_bit = is_bit_set(byte, _CODE_DATA_OR_SYSTEM_SEG__BIT_LOCATION);
    int executable_bit = is_bit_set(byte, _EXECUTABLE__BIT_LOCATION);

    if ((code_data_bit == 1) && (executable_bit == 0))
    {
        return (int)_DATA_SEGMENT_DESCRIPTOR;
    }
    if ((code_data_bit == 1) && (executable_bit == 1))
    {
        return (int)_CODE_SEGMENT_DESCRIPTOR;
    }
    if (code_data_bit == 0)
    {
        return (int)_SYS_SEGMENT_DESCRIPTOR;
    }

    return ret;
}

// "convert" the strcut into 16bit field reg. TODO:Confirm if still needed
_16_reg concat_selector(_selector_st selector_st)
{
    _16_reg ret = 0U;
    _16_index index = selector_st.index;
    _16_reg table_indicator = selector_st.table_indicator;
    _16_reg requestor_privilege_level = selector_st.requestor_privilege_level;

    ret = requestor_privilege_level | (table_indicator << 2) | (index << 3);

    return ret;
}

_32_reg return_base(_byte byte_v[])
{
    _32_reg base = 0;

    _32_reg byte0 = byte_v[2];
    _32_reg byte1 = byte_v[3];
    _32_reg byte2 = byte_v[4];
    _32_reg byte3 = byte_v[7];

    byte3 = byte3 << 24;
    byte2 = byte2 << 16;
    byte1 = byte1 << 8;

    base = byte0 | byte1 | byte2 | byte3;

    return base;
}

_32_reg return_limit(_byte byte_v[])
{
    _32_reg limit = 0; // 20 bits

    _32_reg byte0 = byte_v[0];
    _32_reg byte1 = byte_v[1];
    _32_reg byte2 = byte_v[6];

    byte1 = byte1 << 8;
    byte2 = byte2 << 16;

    limit = (byte0 | byte1 | byte2) & 0xFFFFF;

    return limit;
}

void flat_bin_to_code_seg_descriptor_st(_byte byte_v[], _code_segment_descriptor_st *code_segment_descriptor_st_ptr)
{
    // Used & to surpress -Wconversion warning (Need to secure the possible conversion Warninig)
    code_segment_descriptor_st_ptr->base = (_32_reg)return_base(byte_v);
    code_segment_descriptor_st_ptr->limit = (_32_reg)return_limit(byte_v) & 0xFFFFF;
    code_segment_descriptor_st_ptr->descriptor_privilege_level = (_32_reg)(byte_v[5] >> 5) & 0b11;
    code_segment_descriptor_st_ptr->segment_present = (_32_reg)(byte_v[5] >> 7) & 0b1;
    code_segment_descriptor_st_ptr->Code_data_OR_sys_segment = (_32_reg)(byte_v[5] >> 4) & 0b1;
    code_segment_descriptor_st_ptr->executable = (_32_reg)(byte_v[5] >> 3) & 0b1;
    code_segment_descriptor_st_ptr->conforming = (_32_reg)(byte_v[5] >> 2) & 0b1;
    code_segment_descriptor_st_ptr->readable = (_32_reg)(byte_v[5] >> 1) & 0b1;
    code_segment_descriptor_st_ptr->accessed = (_32_reg)(byte_v[5]) & 0b1;
    code_segment_descriptor_st_ptr->granularity = (_32_reg)(byte_v[6] >> 7) & 0b1;
    code_segment_descriptor_st_ptr->DEFAULT = (_32_reg)(byte_v[6] >> 6) & 0b1;
    code_segment_descriptor_st_ptr->available_for_programmer_user = (_32_reg)(byte_v[6] >> 4) & 0b1;
}

void flat_bin_to_data_seg_descriptor_st(_byte byte_v[], _data_segment_descriptor_st *data_segment_descriptor_st_ptr)
{

    data_segment_descriptor_st_ptr->base = (_32_reg)return_base(byte_v);
    data_segment_descriptor_st_ptr->limit = (_32_reg)return_limit(byte_v) & 0xFFFFF;
    data_segment_descriptor_st_ptr->descriptor_privilege_level = (_32_reg)(byte_v[5] >> 5) & 0b11;
    data_segment_descriptor_st_ptr->segment_present = (_32_reg)(byte_v[5] >> 7) & 0b1;
    data_segment_descriptor_st_ptr->Code_data_OR_sys_segment = (_32_reg)(byte_v[5] >> 4) & 0b1;
    data_segment_descriptor_st_ptr->executable = (_32_reg)(byte_v[5] >> 3) & 0b1;
    data_segment_descriptor_st_ptr->expand_down = (_32_reg)(byte_v[5] >> 2) & 0b1;
    data_segment_descriptor_st_ptr->writable = (_32_reg)(byte_v[5] >> 1) & 0b1;
    data_segment_descriptor_st_ptr->accessed = (_32_reg)(byte_v[5]) & 0b1;
    data_segment_descriptor_st_ptr->granularity = (_32_reg)(byte_v[6] >> 7) & 0b1;
    data_segment_descriptor_st_ptr->big = (_32_reg)(byte_v[6] >> 6) & 0b1;
    data_segment_descriptor_st_ptr->available_for_programmer_user = (_32_reg)(byte_v[6] >> 4) & 0b1;
}

// Returns a code descriptor structure pointer for a given selector. Caller function must pass a code segment selector.
void get_code_seg_desc(_selector_st selector_st, int segment_reg)
{
    if ((selector_st.table_indicator == _GDT) && (selector_st.index == 0U)) // Can not index[0] of a GDT
    {
        // TODO: Implement exception. choose return value
#ifdef DBG
        printf("Exception: Can not index[0] of a GDT\n");
#endif
        return;
    }

    _byte byte_v[8] = {0U};
    _32_linear_addr liear_addr = 0U;

    for (_8_index b_index = 0; b_index < 8; b_index++)
    {
        liear_addr = calc_linear_addr_of_byte_in_seg_desc(selector_st, b_index);
        byte_v[b_index] = get_byte_from_linear_addr(liear_addr);
    }

    if (segment_reg == _TEMP_DATA_SEG)
    {
        flat_bin_to_code_seg_descriptor_st(byte_v, &temp_code_segment_descriptor_st_ptr);
    }
    if (segment_reg == _CS_REG)
    {
        flat_bin_to_code_seg_descriptor_st(byte_v, segment_regs_st.CS_hidden_code_segment_descriptor);
    }
}

// Returns a pointer to a data segment pointed by selector_st. Caller function must pass a data segment selector.
void get_data_seg_desc(_selector_st selector_st, int segment_reg)
{
    if ((selector_st.table_indicator == _GDT) && (selector_st.index == 0U)) // Can not index[0] of a GDT
    {
        // TODO: Implement exception. choose return value
#ifdef DBG
        printf("Exception: Can not index[0] of a GDT\n");
#endif
        return;
    }

    _byte byte_v[8] = {0U};
    _32_linear_addr liear_addr = 0U;

    for (_8_index b_index = 0; b_index < 8; b_index++)
    {
        liear_addr = calc_linear_addr_of_byte_in_seg_desc(selector_st, b_index);
        byte_v[b_index] = get_byte_from_linear_addr(liear_addr);
    }

    if (segment_reg == _SS_REG)
    {
        flat_bin_to_data_seg_descriptor_st(byte_v, segment_regs_st.SS_hidden_stack_segment_descriptor);
    }
    if (segment_reg == _DS_REG)
    {
        flat_bin_to_data_seg_descriptor_st(byte_v, segment_regs_st.DS_hidden_data_segment_descriptor);
    }
    if (segment_reg == _ES_REG)
    {
        flat_bin_to_data_seg_descriptor_st(byte_v, segment_regs_st.ES_hidden_data_segment_descriptor);
    }
    if (segment_reg == _FS_REG)
    {
        flat_bin_to_data_seg_descriptor_st(byte_v, segment_regs_st.FS_hidden_data_segment_descriptor);
    }
    if (segment_reg == _GS_REG)
    {
        flat_bin_to_data_seg_descriptor_st(byte_v, segment_regs_st.GS_hidden_data_segment_descriptor);
    }

    if (segment_reg == _TEMP_DATA_SEG)
    {
        flat_bin_to_data_seg_descriptor_st(byte_v, &temp_data_segment_descriptor_st_ptr);
    }
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
        segment_regs_st.CS = selector_st;
        get_code_seg_desc(selector_st, _CS_REG);
    }
    if (segment_reg == _SS_REG)
    {
        segment_regs_st.SS = selector_st;
        get_data_seg_desc(selector_st, _SS_REG);
    }
    if (segment_reg == _DS_REG)
    {
        segment_regs_st.DS = selector_st;
        get_data_seg_desc(selector_st, _DS_REG);
    }
    if (segment_reg == _ES_REG)
    {
        segment_regs_st.ES = selector_st;
        get_data_seg_desc(selector_st, _ES_REG);
    }
    if (segment_reg == _FS_REG)
    {
        segment_regs_st.FS = selector_st;
        get_data_seg_desc(selector_st, _FS_REG);
    }
    if (segment_reg == _GS_REG)
    {
        segment_regs_st.GS = selector_st;
        get_data_seg_desc(selector_st, _GS_REG);
    }
}

void check_then_load_selector_into_seg_reg(_selector_st selector_st, int segment_reg)
{
    if (segment_reg > _GS_REG)
    {
        status = _ERR_ADDR_STRANS_ARG;
        err_handler("Segment_reg param should be 0 < param < 6");
    }

    if ((selector_st.table_indicator == _GDT) && (selector_st.index == 0U)) // Can not index[0] of a GDT
    {
        // TODO: Implement exception. choose return value
#ifdef DBG
        printf("Exception: Can not index[0] of a GDT\n");
#endif
        return;
    }

    int segment_type = check_segment_type(selector_st);

    if (segment_reg == _CS_REG) // CS reg eccept only code segments
    {
        if (segment_type != _CODE_SEGMENT_DESCRIPTOR)
        {
            // TODO: rise exception? => TBC
#ifdef DBG
            printf("Exception: CS reg eccept only code segments\n");
#endif
            return;
        }
        load_seg_regs(selector_st, segment_reg);
        return;
    }

    if ((segment_reg != _CS_REG) && (segment_reg != _SS_REG)) // Selectors of executable segments that are not readable cannot be loaded into data-segment registers
    {
        if (segment_type == _CODE_SEGMENT_DESCRIPTOR)
        {
            get_code_seg_desc(selector_st, _TEMP_CODE_SEG);
            if ((temp_code_segment_descriptor_st_ptr.readable) == _NOT_READABLE_CODE_SEGMENT)
            {
                // TODO: rise exception? => TBC
#ifdef DBG
                printf("Exception: Selectors of executable segments that are not readable cannot be loaded into data-segment registers\n");
#endif
                return;
            }
            // Code segment is readable
            if (segment_reg == _DS_REG)
            {
                load_seg_regs(selector_st, segment_reg);
                return;
            }
        }

        // Data segment
        load_seg_regs(selector_st, segment_reg);
        return;
    }

    if (segment_reg == _SS_REG) // Only selectors of writable data segments can be loaded into SS.
    {
        if (segment_type != _DATA_SEGMENT_DESCRIPTOR)
        {
            // TODO: rise exception ? => TBC
#ifdef DBG
            printf("Exception: Only selectors of writable data segments can be loaded into SS.\n");
#endif
            return;
        }
        get_data_seg_desc(selector_st, _TEMP_DATA_SEG);
        if ((temp_data_segment_descriptor_st_ptr.writable) == _NOT_WRITABLE_CODE_SEGMENT)
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

// ############################## Page Translation #################################//

_32_physical_addr get_page_tabe_base_addr(_16_index DIR_entry_index)
{
    _double_word dir_entry = 0x0;
    _32_physical_addr page_table_base_addr = 0x0;

    dir_entry = physical_memory_read_double_word(physical_memory_ptr, (cr3_reg_pdbr + (_32_reg)DIR_entry_index));

    page_table_base_addr = (dir_entry) & (0xFFFFF000);

    return page_table_base_addr;
}

_32_physical_addr get_page_frame_base_addr(_16_index Page_entry_index, _32_physical_addr page_tabe_base_addr)
{
    _double_word page_entry = 0x0;
    _32_physical_addr page_frame_base_addr = 0x0;

    page_entry = physical_memory_read_double_word(physical_memory_ptr, (page_tabe_base_addr + (_32_reg)Page_entry_index));

    page_frame_base_addr = (page_entry) & (0xFFFFF000);

    return page_frame_base_addr;
}

_32_physical_addr translate_page(_16_index DIR_entry_index, _16_index Page_entry_index, _16_index offset)
{
    _32_physical_addr physical_addr = 0x0;
    _32_physical_addr page_tabe_base_addr = 0x0;
    _32_physical_addr page_frame_base_addr = 0x0;

    page_tabe_base_addr = get_page_tabe_base_addr(DIR_entry_index);
    page_frame_base_addr = get_page_frame_base_addr(Page_entry_index, page_tabe_base_addr);

    physical_addr = page_frame_base_addr + offset;

    return physical_addr;
}

_32_physical_addr linear_to_physical_addr(_32_linear_addr linear_addr)
{
    if (cr0_reg_st.PG == 0x0) // Paging is off
    {
        return linear_addr;
    }

    _16_index DIR_entry_index = (_16_index)(linear_addr >> 22);              // 10 bit MSB field
    _16_index Page_entry_index = (_16_index)((linear_addr >> 12) & (0x3FF)); // 10 bit field
    _16_index offset = (_16_index)((linear_addr) & (0xFFF));                 // 12 bit LSB field

    _32_physical_addr physical_memory_addr = 0x0;

    physical_memory_addr = translate_page(DIR_entry_index, Page_entry_index, offset);

    return physical_memory_addr;
}

// ############################## Logical to physical address #################################//

_32_physical_addr logical_to_physical_addr(_32_offset offset, const void *segment_decriptor, int segment_descriptor_type)
{
    _32_physical_addr physical_addr = 0U;
    _32_linear_addr linear_addr = 0U;
    linear_addr = translate_segment(offset, segment_decriptor, segment_descriptor_type);
    physical_addr = linear_to_physical_addr(linear_addr);
    return physical_addr;
}