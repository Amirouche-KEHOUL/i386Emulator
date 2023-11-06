#include "decoder.h"

_prefetch_queue_st prefetch_queue_st = {0};

_ModRM_st ModRM_st = {0};
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
    // todo : Get the disp value from the prefesh value
    return 0;
}

_16_displacement get_disp16_value()
{
    // todo : Get the disp value from the prefesh value
    return 0;
}

_32_displacement get_disp32_value()
{
    // todo : Get the disp value from the prefesh value
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
        // todo : choose which portion to return
        goto RETURN;
    }
    if (_16b_addressing_form == _ECX_CX_CL)
    {
        // todo : choose which portion to return
        goto RETURN;
    }
    if (_16b_addressing_form == _EDX_DX_DL)
    {
        // todo : choose which portion to return
        goto RETURN;
    }
    if (_16b_addressing_form == _EBX_BX_BL)
    {
        // todo : choose which portion to return
        goto RETURN;
    }
    if (_16b_addressing_form == _ESP_SP_AH)
    {
        // todo : choose which portion to return
        goto RETURN;
    }
    if (_16b_addressing_form == _EBP_BP_CH)
    {
        // todo : choose which portion to return
        goto RETURN;
    }
    if (_16b_addressing_form == _ESI_SI_DH)
    {
        // todo : choose which portion to return
        goto RETURN;
    }
    if (_16b_addressing_form == _EDI_DI_BH)
    {
        // todo : choose which portion to return
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
        // todo : choose which portion to return
        goto RETURN;
    }
    if (_32b_addressing_form == _ECX_CX_CL)
    {
        // todo : choose which portion to return
        goto RETURN;
    }
    if (_32b_addressing_form == _EDX_DX_DL)
    {
        // todo : choose which portion to return
        goto RETURN;
    }
    if (_32b_addressing_form == _EBX_BX_BL)
    {
        // todo : choose which portion to return
        goto RETURN;
    }
    if (_32b_addressing_form == _ESP_SP_AH)
    {
        // todo : choose which portion to return
        goto RETURN;
    }
    if (_32b_addressing_form == _EBP_BP_CH)
    {
        // todo : choose which portion to return
        goto RETURN;
    }
    if (_32b_addressing_form == _ESI_SI_DH)
    {
        // todo : choose which portion to return
        goto RETURN;
    }
    if (_32b_addressing_form == _EDI_DI_BH)
    {
        // todo : choose which portion to return
        goto RETURN;
    }

RETURN:
    return ret;
}

void fetch_prefetch_queue(void)
{
    unsigned char i = 0;
    _32_physical_addr physical_addr = 0;

    for (i = 0; i < 16; i++)
    {
        physical_addr = logical_to_physical_addr((get_EIP() + i), segment_regs_st.CS_hidden_code_segment_descriptor, _CODE_SEGMENT_DESCRIPTOR);
        prefetch_queue_st.queue[i] = physical_memory_read_byte(physical_memory_ptr, physical_addr);
    }
    prefetch_queue_st.index = 0;
}

// Reads byte from prefetch queue and increments the read index
_byte stream_byte_prefetch_queue(void)
{
    _byte ret = prefetch_queue_st.queue[prefetch_queue_st.index];
    if (prefetch_queue_st.index == 15U) // If end of the queue prefetch the next 16 bytes
    {
        fetch_prefetch_queue();
        return ret;
    }
    prefetch_queue_st.index++;
    return ret;
}

void ADD(void)
{
    printf("ADD Operation called correctly\n");
}

void SUB(void)
{
    printf("SUB Operation called correctly\n");
}

// Used tu fill empty cells in opcode maps at program init
void no_operation_opcode(void)
{
    // TODO: confirm what to do in case of opcode hits an empty cell
    printf("No operation for this opcode\n");
}

void read_ModRM_byte_to_st()
{
    _byte byte = stream_byte_prefetch_queue();
    ModRM_st.RM = (_byte)(byte & 0x07);
    ModRM_st.REG_OPCODE = (_byte)((byte & 0x38) >> 3);
    // TODO: confirm the conversion warning (should be ok )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
    ModRM_st.MOD = (_byte)((byte & 0xC0) >> 6);
#pragma GCC diagnostic pop
}

void _2byte_escape(void)
{
    _byte byte = stream_byte_prefetch_queue();
    // _byte byte = 0x55;
    _byte lsb = byte & 0x0F;        // least 4 significant bits
    _byte msb = (byte & 0xF0) >> 4; // most 4 significant bits

    two_byte_opcode_map[msb][lsb]();
}

void grp1_EbIb_escape(void)
{
    read_ModRM_byte_to_st();
    ModRM_opcode_map[0x0][ModRM_st.REG_OPCODE]();
}

void grp1_EvIv_escape(void)
{
    read_ModRM_byte_to_st();
    ModRM_opcode_map[0x0][ModRM_st.REG_OPCODE]();
}

void grp2_EbIb_escape(void)
{
    read_ModRM_byte_to_st();
    ModRM_opcode_map[0x1][ModRM_st.REG_OPCODE]();
}

void grp2_EvIv_escape(void)
{
    read_ModRM_byte_to_st();
    ModRM_opcode_map[0x1][ModRM_st.REG_OPCODE]();
}

void grp2_Eb1_escape(void)
{
    read_ModRM_byte_to_st();
    ModRM_opcode_map[0x1][ModRM_st.REG_OPCODE]();
}

void grp2_Ev1_escape(void)
{
    read_ModRM_byte_to_st();
    ModRM_opcode_map[0x1][ModRM_st.REG_OPCODE]();
}

void grp2_EbCl_escape(void)
{
    read_ModRM_byte_to_st();
    ModRM_opcode_map[0x1][ModRM_st.REG_OPCODE]();
}

void grp2_EvCl_escape(void)
{
    read_ModRM_byte_to_st();
    ModRM_opcode_map[0x1][ModRM_st.REG_OPCODE]();
}

void grp3_Eb_escape(void)
{
    read_ModRM_byte_to_st();
    ModRM_opcode_map[0x2][ModRM_st.REG_OPCODE]();
}

void grp3_Ev_escape(void)
{
    read_ModRM_byte_to_st();
    ModRM_opcode_map[0x2][ModRM_st.REG_OPCODE]();
}

void grp4_escape(void)
{
    read_ModRM_byte_to_st();
    ModRM_opcode_map[0x3][ModRM_st.REG_OPCODE]();
}

void grp5_escape(void)
{
    read_ModRM_byte_to_st();
    ModRM_opcode_map[0x4][ModRM_st.REG_OPCODE]();
}

void grp6_escape(void)
{
    read_ModRM_byte_to_st();
    ModRM_opcode_map[0x5][ModRM_st.REG_OPCODE]();
}

void grp7_escape(void)
{
    read_ModRM_byte_to_st();
    ModRM_opcode_map[0x6][ModRM_st.REG_OPCODE]();
}

void grp8_EvIb_escape(void)
{
    read_ModRM_byte_to_st();
    ModRM_opcode_map[0x7][ModRM_st.REG_OPCODE]();
}

void map_escape_function(void)
{
    one_byte_opcode_map[0x0][0xF] = &_2byte_escape;
    one_byte_opcode_map[0x8][0x0] = &grp1_EbIb_escape;
    one_byte_opcode_map[0x8][0x1] = &grp1_EvIv_escape;
    one_byte_opcode_map[0x8][0x3] = &grp1_EvIv_escape; // TODO: TBC if not typo in opcode map
    one_byte_opcode_map[0xC][0x0] = &grp2_EbIb_escape;
    one_byte_opcode_map[0xC][0x1] = &grp2_EvIv_escape;
    one_byte_opcode_map[0xD][0x0] = &grp2_Eb1_escape;
    one_byte_opcode_map[0xD][0x1] = &grp2_Ev1_escape;
    one_byte_opcode_map[0xD][0x2] = &grp2_EbCl_escape;
    one_byte_opcode_map[0xD][0x3] = &grp2_EvCl_escape;
    one_byte_opcode_map[0xF][0x6] = &grp3_Eb_escape;
    one_byte_opcode_map[0xF][0x7] = &grp3_Ev_escape;
    one_byte_opcode_map[0xF][0xE] = &grp4_escape;
    one_byte_opcode_map[0xF][0xF] = &grp5_escape;

    two_byte_opcode_map[0x0][0x0] = &grp6_escape;
    two_byte_opcode_map[0x0][0x1] = &grp7_escape;
    two_byte_opcode_map[0xB][0xA] = &grp8_EvIb_escape;
}

// Init opcode maps: set all cells to no operation opcode (empty cells in opcode map)
void init_opcode_maps(void)
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            one_byte_opcode_map[i][j] = &no_operation_opcode;
            two_byte_opcode_map[i][j] = &no_operation_opcode;
            if ((i < 8) && (j < 8))
            {
                ModRM_opcode_map[i][j] = &no_operation_opcode;
            }
        }
    }
}

// Inits opcode maps and maps operations to their corresponding cells.
void map_operations_to_opcode_maps(void)
{
    init_opcode_maps();
    map_escape_function();

    ModRM_opcode_map[0x0][0x7] = &ADD;
    ModRM_opcode_map[0x7][0x0] = &SUB;
}

void decode(void)
{
    prefetch_queue_st.queue[0] = 0x80;
    prefetch_queue_st.queue[1] = 0x38;

    _byte byte = stream_byte_prefetch_queue();
    // _byte byte = 0x80;
    _byte lsb = byte & 0x0F;        // least 4 significant bits
    _byte msb = (byte & 0xF0) >> 4; // most 4 significant bits

    one_byte_opcode_map[msb][lsb]();
}
