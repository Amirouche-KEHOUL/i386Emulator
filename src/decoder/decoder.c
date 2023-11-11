#include "decoder.h"

/* ------------- data structures -------------*/

extern _general_regs_st general_regs_st;

_ModRM_st ModRM_st = {0};
_prefetch_queue_st prefetch_queue_st = {0};
void (*one_byte_opcode_map[16][16])(void); // Page 414
void (*two_byte_opcode_map[16][16])(void); // Page 415
void (*ModRM_opcode_map[8][8])(void);      // Page 416

/* ------------- FUNCTIONS -------------*/

unsigned int get_effective_address_size(unsigned int default_seg_size, unsigned int adresse_size_prefix_present)
{
    return (default_seg_size ^ adresse_size_prefix_present); // XOR
}

unsigned int get_effective_operand_size(unsigned int default_seg_size, unsigned int operand_size_prefix_present)
{
    return (default_seg_size ^ operand_size_prefix_present); // XOR
}

int get_16bit_addressing_form(_ModRM_st ModRM_st)
{
    if (ModRM_st.MOD == (_byte)0x00)
    {
        if (ModRM_st.RM == (_byte)0x000)
        {
            return _BX_PLUS_SI_;
        }
        if (ModRM_st.RM == (_byte)0x001)
        {
            return _BP_PLUS_SI_;
        }
        if (ModRM_st.RM == (_byte)0x010)
        {
            return _BX_PLUS_DI_;
        }
        if (ModRM_st.RM == (_byte)0x011)
        {
            return _BP_PLUS_DI_;
        }
        if (ModRM_st.RM == (_byte)(_byte)0x100)
        {
            return _SI_;
        }
        if (ModRM_st.RM == (_byte)0x101)
        {
            return _DI_;
        }
        if (ModRM_st.RM == (_byte)0x110)
        {
            return _DISP16_;
        }
        if (ModRM_st.RM == (_byte)0x111)
        {
            return _BX_;
        }
    }
    if (ModRM_st.MOD == (_byte)0x01)
    {
        if (ModRM_st.RM == (_byte)0x000)
        {
            return _BX_PLUS_SI__PLUS_DISP16;
        }
        if (ModRM_st.RM == (_byte)0x001)
        {
            return _BX_PLUS_DI__PLUS_DISP16;
        }
        if (ModRM_st.RM == (_byte)0x010)
        {
            return _BP_PLUS_SI__PLUS_DISP16;
        }
        if (ModRM_st.RM == (_byte)0x011)
        {
            return _BP_PLUS_DI__PLUS_DISP8;
        }
        if (ModRM_st.RM == (_byte)0x100)
        {
            return _SI__PLUS_DISP8;
        }
        if (ModRM_st.RM == (_byte)0x101)
        {
            return _DI__PLUS_DISP8;
        }
        if (ModRM_st.RM == (_byte)0x110)
        {
            return _BP__PLUS_DISP8;
        }
        if (ModRM_st.RM == (_byte)0x111)
        {
            return _BX__PLUS_DISP8;
        }
    }
    if (ModRM_st.MOD == (_byte)0x10)
    {
        if (ModRM_st.RM == (_byte)0x000)
        {
            return _BX_PLUS_SI__PLUS_DISP16;
        }
        if (ModRM_st.RM == (_byte)0x001)
        {
            return _BX_PLUS_DI__PLUS_DISP16;
        }
        if (ModRM_st.RM == (_byte)0x010)
        {
            return _BP_PLUS_SI__PLUS_DISP16;
        }
        if (ModRM_st.RM == (_byte)0x011)
        {
            return _BP_PLUS_DI__PLUS_DISP16;
        }
        if (ModRM_st.RM == (_byte)0x100)
        {
            return _SI__PLUS_DISP16;
        }
        if (ModRM_st.RM == (_byte)0x101)
        {
            return _DI__PLUS_DISP16;
        }
        if (ModRM_st.RM == (_byte)0x110)
        {
            return _BP__PLUS_DISP16;
        }
        if (ModRM_st.RM == (_byte)0x111)
        {
            return _BX__PLUS_DISP16;
        }
    }
    if (ModRM_st.MOD == (_byte)0x11)
    {
        if (ModRM_st.RM == (_byte)0x000)
        {
            return _EAX_AX_AL;
        }
        if (ModRM_st.RM == (_byte)0x001)
        {
            return _ECX_CX_CL;
        }
        if (ModRM_st.RM == (_byte)0x010)
        {
            return _EDX_DX_DL;
        }
        if (ModRM_st.RM == (_byte)0x011)
        {
            return _EBX_BX_BL;
        }
        if (ModRM_st.RM == (_byte)0x100)
        {
            return _ESP_SP_AH;
        }
        if (ModRM_st.RM == (_byte)0x101)
        {
            return _EBP_BP_CH;
        }
        if (ModRM_st.RM == (_byte)0x110)
        {
            return _ESI_SI_DH;
        }
        if (ModRM_st.RM == (_byte)0x111)
        {
            return _EDI_DI_BH;
        }
    }

    return -1;
}

int get_32bit_addressing_form(_ModRM_st ModRM_st)
{
    if (ModRM_st.MOD == (_byte)0x00)
    {
        if (ModRM_st.RM == (_byte)0x000)
        {
            return _EAX_;
        }
        if (ModRM_st.RM == (_byte)0x001)
        {
            return _ECX_;
        }
        if (ModRM_st.RM == (_byte)0x010)
        {
            return _EDX_;
        }
        if (ModRM_st.RM == (_byte)0x011)
        {
            return _EBX_;
        }
        if (ModRM_st.RM == (_byte)(_byte)0x100)
        {
            return _SIB_FOLLOWS_;
        }
        if (ModRM_st.RM == (_byte)0x101)
        {
            return _DISP32_;
        }
        if (ModRM_st.RM == (_byte)0x110)
        {
            return _ESI_;
        }
        if (ModRM_st.RM == (_byte)0x111)
        {
            return _EDI_;
        }
    }
    if (ModRM_st.MOD == (_byte)0x01)
    {
        if (ModRM_st.RM == (_byte)0x000)
        {
            return _DISP8_EAX_;
        }
        if (ModRM_st.RM == (_byte)0x001)
        {
            return _DISP8_ECX_;
        }
        if (ModRM_st.RM == (_byte)0x010)
        {
            return _DISP8_EDX_;
        }
        if (ModRM_st.RM == (_byte)0x011)
        {
            return _DISP8_EBX_;
        }
        if (ModRM_st.RM == (_byte)0x100)
        {
            return _DISP8_SIB_FOLLOWS_;
        }
        if (ModRM_st.RM == (_byte)0x101)
        {
            return _DISP8_EBP_;
        }
        if (ModRM_st.RM == (_byte)0x110)
        {
            return _DISP8_ESI_;
        }
        if (ModRM_st.RM == (_byte)0x111)
        {
            return _DISP8_EDI_;
        }
    }
    if (ModRM_st.MOD == (_byte)0x10)
    {
        if (ModRM_st.RM == (_byte)0x000)
        {
            return _DISP32_EAX_;
        }
        if (ModRM_st.RM == (_byte)0x001)
        {
            return _DISP32_ECX_;
        }
        if (ModRM_st.RM == (_byte)0x010)
        {
            return _DISP32_EDX_;
        }
        if (ModRM_st.RM == (_byte)0x011)
        {
            return _DISP32_EBX_;
        }
        if (ModRM_st.RM == (_byte)0x100)
        {
            return _DISP32_SIB_FOLLOWS_;
        }
        if (ModRM_st.RM == (_byte)0x101)
        {
            return _DISP32_EBP_;
        }
        if (ModRM_st.RM == (_byte)0x110)
        {
            return _DISP32_ESI_;
        }
        if (ModRM_st.RM == (_byte)0x111)
        {
            return _DISP32_EDI_;
        }
    }
    if (ModRM_st.MOD == (_byte)0x11)
    {
        if (ModRM_st.RM == (_byte)0x000)
        {
            return _EAX_AX_AL;
        }
        if (ModRM_st.RM == (_byte)0x001)
        {
            return _ECX_CX_CL;
        }
        if (ModRM_st.RM == (_byte)0x010)
        {
            return _EDX_DX_DL;
        }
        if (ModRM_st.RM == (_byte)0x011)
        {
            return _EBX_BX_BL;
        }
        if (ModRM_st.RM == (_byte)0x100)
        {
            return _ESP_SP_AH;
        }
        if (ModRM_st.RM == (_byte)0x101)
        {
            return _EBP_BP_CH;
        }
        if (ModRM_st.RM == (_byte)0x110)
        {
            return _ESI_SI_DH;
        }
        if (ModRM_st.RM == (_byte)0x111)
        {
            return _EDI_DI_BH;
        }
    }

    return -1;
}

int get_addressing_form_from_ModRM(_ModRM_st ModRM_st, int size_of_addressing_form)
{
    int ret = -1;

    if (size_of_addressing_form == _16BIT_ADDRESSING_FORM)
    {
        ret = get_16bit_addressing_form(ModRM_st);
    }
    if (size_of_addressing_form == _32BIT_ADDRESSING_FORM)
    {
        ret = get_32bit_addressing_form(ModRM_st);
    }

    return ret;
}

int get_scaled_index_form(_SIB_st SIB_st)
{
    int ret = -1;
    if (SIB_st.SS == (_byte)0x00)
    {
        if (SIB_st.INDEX == (_byte)0x000)
        {
            return _EAX_SIB_;
        }
        if (SIB_st.INDEX == (_byte)0x001)
        {
            return _ECX_SIB_;
        }
        if (SIB_st.INDEX == (_byte)0x010)
        {
            return _EDX_SIB_;
        }
        if (SIB_st.INDEX == (_byte)0x011)
        {
            return _EBX_SIB_;
        }
        if (SIB_st.INDEX == (_byte)0x100)
        {
            return _NONE_SIB;
        }
        if (SIB_st.INDEX == (_byte)0x101)
        {
            return _EBP_SIB;
        }
        if (SIB_st.INDEX == (_byte)0x110)
        {
            return _ESI_SIB;
        }
        if (SIB_st.INDEX == (_byte)0x111)
        {
            return _EDI_SIB;
        }
    }
    if (SIB_st.SS == (_byte)0x01)
    {
        if (SIB_st.INDEX == (_byte)0x000)
        {
            return _EAX_MULT_2_SIB_;
        }
        if (SIB_st.INDEX == (_byte)0x001)
        {
            return _ECX_MULT_2_SIB_;
        }
        if (SIB_st.INDEX == (_byte)0x010)
        {
            return _EDX_MULT_2_SIB_;
        }
        if (SIB_st.INDEX == (_byte)0x011)
        {
            return _EBX_MULT_2_SIB_;
        }
        if (SIB_st.INDEX == (_byte)0x100)
        {
            return _NONE_SIB;
        }
        if (SIB_st.INDEX == (_byte)0x101)
        {
            return _EBP_MULT_2_SIB;
        }
        if (SIB_st.INDEX == (_byte)0x110)
        {
            return _ESI_MULT_2_SIB;
        }
        if (SIB_st.INDEX == (_byte)0x111)
        {
            return _EDI_MULT_2_SIB;
        }
    }
    if (SIB_st.SS == (_byte)0x10)
    {
        if (SIB_st.INDEX == (_byte)0x000)
        {
            return _EAX_MULT_4_SIB_;
        }
        if (SIB_st.INDEX == (_byte)0x001)
        {
            return _ECX_MULT_4_SIB_;
        }
        if (SIB_st.INDEX == (_byte)0x010)
        {
            return _EDX_MULT_4_SIB_;
        }
        if (SIB_st.INDEX == (_byte)0x011)
        {
            return _EBX_MULT_4_SIB_;
        }
        if (SIB_st.INDEX == (_byte)0x100)
        {
            return _NONE_SIB;
        }
        if (SIB_st.INDEX == (_byte)0x101)
        {
            return _EBP_MULT_4_SIB;
        }
        if (SIB_st.INDEX == (_byte)0x110)
        {
            return _ESI_MULT_4_SIB;
        }
        if (SIB_st.INDEX == (_byte)0x111)
        {
            return _EDI_MULT_4_SIB;
        }
    }
    if (SIB_st.SS == (_byte)0x11)
    {
        if (SIB_st.INDEX == (_byte)0x000)
        {
            return _EAX_MULT_8_SIB_;
        }
        if (SIB_st.INDEX == (_byte)0x001)
        {
            return _ECX_MULT_8_SIB_;
        }
        if (SIB_st.INDEX == (_byte)0x010)
        {
            return _EDX_MULT_8_SIB_;
        }
        if (SIB_st.INDEX == (_byte)0x011)
        {
            return _EBX_MULT_8_SIB_;
        }
        if (SIB_st.INDEX == (_byte)0x100)
        {
            return _NONE_SIB;
        }
        if (SIB_st.INDEX == (_byte)0x101)
        {
            return _EBP_MULT_8_SIB;
        }
        if (SIB_st.INDEX == (_byte)0x110)
        {
            return _ESI_MULT_8_SIB;
        }
        if (SIB_st.INDEX == (_byte)0x111)
        {
            return _EDI_MULT_8_SIB;
        }
    }
    return ret;
}

_32_offset get_scaled_index_value(_SIB_st SIB_st)
{
    _32_offset ret = 0U;
    int indexing_form = 0U;
    indexing_form = get_scaled_index_form(SIB_st);

    // SS 00
    if (indexing_form == _EAX_SIB_)
    {
        ret = get_EAX();
        goto RETURN;
    }
    if (indexing_form == _ECX_SIB_)
    {
        ret = get_ECX();
        goto RETURN;
    }
    if (indexing_form == _EDX_SIB_)
    {
        ret = get_EDX();
        goto RETURN;
    }
    if (indexing_form == _EBX_SIB_)
    {
        ret = get_EBX();
        goto RETURN;
    }
    if (indexing_form == _NONE_SIB)
    {
        // TODO : Do somthing in case of none
        goto RETURN;
    }
    if (indexing_form == _EBP_SIB)
    {
        ret = get_EBP();
        goto RETURN;
    }
    if (indexing_form == _ESI_SIB)
    {
        ret = get_ESI();
        goto RETURN;
    }
    if (indexing_form == _EDI_SIB)
    {
        ret = get_EDI();
        goto RETURN;
    }

    // SS 01
    if (indexing_form == _EAX_SIB_)
    {
        ret = get_EAX() * 2;
        goto RETURN;
    }
    if (indexing_form == _ECX_SIB_)
    {
        ret = get_ECX() * 2;
        goto RETURN;
    }
    if (indexing_form == _EDX_SIB_)
    {
        ret = get_EDX() * 2;
        goto RETURN;
    }
    if (indexing_form == _EBX_SIB_)
    {
        ret = get_EBX() * 2;
        goto RETURN;
    }
    if (indexing_form == _NONE_SIB)
    {
        // TODO : Do somthing in case of none
        goto RETURN;
    }
    if (indexing_form == _EBP_SIB)
    {
        ret = get_EBP() * 2;
        goto RETURN;
    }
    if (indexing_form == _ESI_SIB)
    {
        ret = get_ESI() * 2;
        goto RETURN;
    }
    if (indexing_form == _EDI_SIB)
    {
        ret = get_EDI() * 2;
        goto RETURN;
    }

    // SS 10
    if (indexing_form == _EAX_SIB_)
    {
        ret = get_EAX() * 4;
        goto RETURN;
    }
    if (indexing_form == _ECX_SIB_)
    {
        ret = get_ECX() * 4;
        goto RETURN;
    }
    if (indexing_form == _EDX_SIB_)
    {
        ret = get_EDX() * 4;
        goto RETURN;
    }
    if (indexing_form == _EBX_SIB_)
    {
        ret = get_EBX() * 4;
        goto RETURN;
    }
    if (indexing_form == _NONE_SIB)
    {
        // TODO : Do somthing in case of none
        goto RETURN;
    }
    if (indexing_form == _EBP_SIB)
    {
        ret = get_EBP() * 4;
        goto RETURN;
    }
    if (indexing_form == _ESI_SIB)
    {
        ret = get_ESI() * 4;
        goto RETURN;
    }
    if (indexing_form == _EDI_SIB)
    {
        ret = get_EDI() * 4;
        goto RETURN;
    }

    // SS 11
    if (indexing_form == _EAX_SIB_)
    {
        ret = get_EAX() * 8;
        goto RETURN;
    }
    if (indexing_form == _ECX_SIB_)
    {
        ret = get_ECX() * 8;
        goto RETURN;
    }
    if (indexing_form == _EDX_SIB_)
    {
        ret = get_EDX() * 8;
        goto RETURN;
    }
    if (indexing_form == _EBX_SIB_)
    {
        ret = get_EBX() * 8;
        goto RETURN;
    }
    if (indexing_form == _NONE_SIB)
    {
        // TODO : Do somthing in case of none
        goto RETURN;
    }
    if (indexing_form == _EBP_SIB)
    {
        ret = get_EBP() * 8;
        goto RETURN;
    }
    if (indexing_form == _ESI_SIB)
    {
        ret = get_ESI() * 8;
        goto RETURN;
    }
    if (indexing_form == _EDI_SIB)
    {
        ret = get_EDI() * 8;
        goto RETURN;
    }

RETURN:
    return ret;
}

_8_displacement get_disp8_value()
{
    // TODO : Get the disp value from the prefesh value
    return 0;
}

_16_displacement get_disp16_value()
{
    // TODO : Get the disp value from the prefesh value
    return 0;
}

_32_displacement get_disp32_value()
{
    // TODO : Get the disp value from the prefesh value
    return 0;
}

_16_offset calculate_16bit_effective_addr(unsigned int _16b_addressing_form)
{
    _16_offset ret = 0U;

    /* Mod 00 */
    if (_16b_addressing_form == _BX_PLUS_SI_)
    {
        ret = (_16_offset)(get_BX() + general_regs_st.ESI.SI);
        goto RETURN;
    }
    if (_16b_addressing_form == _BX_PLUS_DI_)
    {
        ret = (_16_offset)(get_BX() + general_regs_st.EDI.DI);
        goto RETURN;
    }
    if (_16b_addressing_form == _BP_PLUS_SI_)
    {
        ret = (_16_offset)(general_regs_st.EBP.BP + general_regs_st.ESI.SI);
        goto RETURN;
    }
    if (_16b_addressing_form == _BP_PLUS_DI_)
    {
        ret = (_16_offset)(general_regs_st.EBP.BP + general_regs_st.EDI.DI);
        goto RETURN;
    }
    if (_16b_addressing_form == _SI_)
    {
        ret = (_16_offset)(general_regs_st.ESI.SI);
        goto RETURN;
    }
    if (_16b_addressing_form == _DI_)
    {
        ret = (_16_offset)(general_regs_st.EDI.DI);
        goto RETURN;
    }
    if (_16b_addressing_form == _DISP16_)
    {
        ret = (_16_offset)(get_disp16_value());
        goto RETURN;
    }
    if (_16b_addressing_form == _BX_)
    {
        ret = (_16_offset)(get_BX());
        goto RETURN;
    }

    /* Mod 01 */
    if (_16b_addressing_form == _BX_PLUS_SI__PLUS_DISP8)
    {
        ret = (_16_offset)((get_BX() + general_regs_st.ESI.SI + get_disp8_value()));
        goto RETURN;
    }
    if (_16b_addressing_form == _BX_PLUS_DI__PLUS_DISP8)
    {
        ret = (_16_offset)(get_BX() + general_regs_st.EDI.DI + get_disp8_value());
        goto RETURN;
    }
    if (_16b_addressing_form == _BP_PLUS_SI__PLUS_DISP8)
    {
        ret = (_16_offset)(general_regs_st.EBP.BP + general_regs_st.ESI.SI + get_disp8_value());
        goto RETURN;
    }
    if (_16b_addressing_form == _BP_PLUS_DI__PLUS_DISP8)
    {
        ret = (_16_offset)(general_regs_st.EBP.BP + general_regs_st.EDI.DI + get_disp8_value());
        goto RETURN;
    }
    if (_16b_addressing_form == _SI__PLUS_DISP8)
    {
        ret = (_16_offset)(general_regs_st.ESI.SI + get_disp8_value());
        goto RETURN;
    }
    if (_16b_addressing_form == _DI__PLUS_DISP8)
    {
        ret = (_16_offset)(general_regs_st.EDI.DI + get_disp8_value());
        goto RETURN;
    }
    if (_16b_addressing_form == _BP__PLUS_DISP8)
    {
        ret = (_16_offset)(get_disp16_value() + get_disp8_value());
        goto RETURN;
    }
    if (_16b_addressing_form == _BX__PLUS_DISP8)
    {
        ret = (_16_offset)(get_BX() + get_disp8_value());
        goto RETURN;
    }

    /* Mod 10 */
    if (_16b_addressing_form == _BX_PLUS_SI__PLUS_DISP16)
    {
        ret = (_16_offset)(get_BX() + general_regs_st.ESI.SI + get_disp16_value());
        goto RETURN;
    }
    if (_16b_addressing_form == _BX_PLUS_DI__PLUS_DISP16)
    {
        ret = (_16_offset)(get_BX() + general_regs_st.EDI.DI + get_disp16_value());
        goto RETURN;
    }
    if (_16b_addressing_form == _BP_PLUS_SI__PLUS_DISP16)
    {
        ret = (_16_offset)(general_regs_st.EBP.BP + general_regs_st.ESI.SI + get_disp16_value());
        goto RETURN;
    }
    if (_16b_addressing_form == _BP_PLUS_DI__PLUS_DISP16)
    {
        ret = (_16_offset)(general_regs_st.EBP.BP + general_regs_st.EDI.DI + get_disp16_value());
        goto RETURN;
    }
    if (_16b_addressing_form == _SI__PLUS_DISP16)
    {
        ret = (_16_offset)(general_regs_st.ESI.SI + get_disp16_value());
        goto RETURN;
    }
    if (_16b_addressing_form == _DI__PLUS_DISP16)
    {
        ret = (_16_offset)(general_regs_st.EDI.DI + get_disp16_value());
        goto RETURN;
    }
    if (_16b_addressing_form == _BP__PLUS_DISP16)
    {
        ret = (_16_offset)(get_disp16_value() + get_disp16_value());
        goto RETURN;
    }
    if (_16b_addressing_form == _BX__PLUS_DISP16)
    {
        ret = (_16_offset)(get_BX() + get_disp16_value());
        goto RETURN;
    }

    // Mod 11
    if (_16b_addressing_form == _EAX_AX_AL)
    {
        // TODO : choose which portion to return
        goto RETURN;
    }
    if (_16b_addressing_form == _ECX_CX_CL)
    {
        // TODO : choose which portion to return
        goto RETURN;
    }
    if (_16b_addressing_form == _EDX_DX_DL)
    {
        // TODO : choose which portion to return
        goto RETURN;
    }
    if (_16b_addressing_form == _EBX_BX_BL)
    {
        // TODO : choose which portion to return
        goto RETURN;
    }
    if (_16b_addressing_form == _ESP_SP_AH)
    {
        // TODO : choose which portion to return
        goto RETURN;
    }
    if (_16b_addressing_form == _EBP_BP_CH)
    {
        // TODO : choose which portion to return
        goto RETURN;
    }
    if (_16b_addressing_form == _ESI_SI_DH)
    {
        // TODO : choose which portion to return
        goto RETURN;
    }
    if (_16b_addressing_form == _EDI_DI_BH)
    {
        // TODO : choose which portion to return
        goto RETURN;
    }

RETURN:
    return ret;
}

_32_offset calculate_32bit_effective_addr(unsigned int _32b_addressing_form)
{
    _32_offset ret = 0U;

    /* Mod 00 */
    if (_32b_addressing_form == _EAX_)
    {
        ret = (_32_offset)get_EAX();
        goto RETURN;
    }
    if (_32b_addressing_form == _ECX_)
    {
        ret = (_32_offset)get_ECX();
        goto RETURN;
    }
    if (_32b_addressing_form == _EDX_)
    {
        ret = (_32_offset)get_EDX();
        goto RETURN;
    }
    if (_32b_addressing_form == _EBX_)
    {
        ret = (_32_offset)get_EBX();
        goto RETURN;
    }
    if (_32b_addressing_form == _SIB_FOLLOWS_)
    {
        // TODO : implement SIB function
        goto RETURN;
    }
    if (_32b_addressing_form == _DISP32_)
    {
        ret = (_32_offset)get_disp32_value();
        goto RETURN;
    }
    if (_32b_addressing_form == _ESI_)
    {
        ret = (_32_offset)get_ESI();
        goto RETURN;
    }
    if (_32b_addressing_form == _EDI_)
    {
        ret = (_32_offset)get_EDI();
        goto RETURN;
    }

    /* Mod 01 */
    if (_32b_addressing_form == _DISP8_EAX_)
    {
        ret = (_32_offset)get_disp32_value() + get_EAX();
        goto RETURN;
    }
    if (_32b_addressing_form == _DISP8_ECX_)
    {
        ret = (_32_offset)get_disp8_value() + get_ECX();
        goto RETURN;
    }
    if (_32b_addressing_form == _DISP8_EDX_)
    {
        ret = (_32_offset)get_disp8_value() + get_EDX();
        goto RETURN;
    }
    if (_32b_addressing_form == _DISP8_EBX_)
    {
        ret = (_32_offset)get_disp8_value() + get_EBX();
        goto RETURN;
    }
    if (_32b_addressing_form == _DISP8_SIB_FOLLOWS_)
    {
        // Implement SIB function
        goto RETURN;
    }
    if (_32b_addressing_form == _DISP8_EBP_)
    {
        ret = (_32_offset)get_disp8_value() + get_EBP();
        goto RETURN;
    }
    if (_32b_addressing_form == _DISP8_ESI_)
    {
        ret = (_32_offset)get_disp8_value() + get_ESI();
        goto RETURN;
    }
    if (_32b_addressing_form == _DISP8_EDI_)
    {
        ret = (_32_offset)get_disp8_value() + get_EDI();
        goto RETURN;
    }

    /* Mod 10 */
    if (_32b_addressing_form == _DISP32_EAX_)
    {
        ret = (_32_offset)get_disp32_value() + get_EAX();
        goto RETURN;
    }
    if (_32b_addressing_form == _DISP32_ECX_)
    {
        ret = (_32_offset)get_disp32_value() + get_ECX();
        goto RETURN;
    }
    if (_32b_addressing_form == _DISP32_EDX_)
    {
        ret = (_32_offset)get_disp32_value() + get_EDX();
        goto RETURN;
    }
    if (_32b_addressing_form == _DISP32_EBX_)
    {
        ret = (_32_offset)get_disp32_value() + get_EBX();
        goto RETURN;
    }
    if (_32b_addressing_form == _DISP32_SIB_FOLLOWS_)
    {
        // TODO: Implement SIB function
        goto RETURN;
    }
    if (_32b_addressing_form == _DISP32_EBP_)
    {
        ret = (_32_offset)get_disp32_value() + get_EBP();
        goto RETURN;
    }
    if (_32b_addressing_form == _DISP32_ESI_)
    {
        ret = (_32_offset)get_disp32_value() + get_ESI();
        goto RETURN;
    }
    if (_32b_addressing_form == _DISP32_EDI_)
    {
        ret = (_32_offset)get_disp32_value() + get_EDI();
        goto RETURN;
    }

    // Mod 11
    if (_32b_addressing_form == _EAX_AX_AL)
    {
        // TODO : choose which portion to return
        goto RETURN;
    }
    if (_32b_addressing_form == _ECX_CX_CL)
    {
        // TODO : choose which portion to return
        goto RETURN;
    }
    if (_32b_addressing_form == _EDX_DX_DL)
    {
        // TODO : choose which portion to return
        goto RETURN;
    }
    if (_32b_addressing_form == _EBX_BX_BL)
    {
        // TODO : choose which portion to return
        goto RETURN;
    }
    if (_32b_addressing_form == _ESP_SP_AH)
    {
        // TODO : choose which portion to return
        goto RETURN;
    }
    if (_32b_addressing_form == _EBP_BP_CH)
    {
        // TODO : choose which portion to return
        goto RETURN;
    }
    if (_32b_addressing_form == _ESI_SI_DH)
    {
        // TODO : choose which portion to return
        goto RETURN;
    }
    if (_32b_addressing_form == _EDI_DI_BH)
    {
        // TODO : choose which portion to return
        goto RETURN;
    }

RETURN:
    return ret;
}

void decode(void)
{
    prefetch_queue_st.queue[0] = 0x7F;
    prefetch_queue_st.queue[1] = 0xA9;

    _byte byte = stream_byte_prefetch_queue();

    _byte lsb = byte & 0x0F;        // least 4 significant bits
    _byte msb = (byte & 0xF0) >> 4; // most 4 significant bits

    one_byte_opcode_map[msb][lsb]();
}
