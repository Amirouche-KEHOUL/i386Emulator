#include "decoder.h"

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
            return _BX_PLUS_SI__PLUS_DISP8;
        }
        if (ModRM_st.RM == (_byte)0x001)
        {
            return _BX_PLUS_DI__PLUS_DISP8;
        }
        if (ModRM_st.RM == (_byte)0x010)
        {
            return _BP_PLUS_SI__PLUS_DISP8;
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

int get_addressing_form_from_ModRM(_ModRM_st ModRM_st, int addressing_form)
{
    int ret = -1;

    if (addressing_form == _16BIT_ADDRESSING_FORM)
    {
        ret = get_16bit_addressing_form(ModRM_st);
    }
    if (addressing_form == _32BIT_ADDRESSING_FORM)
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

_16_offset calculate_16bit_effective_addr(unsigned int _16b_addressing_form)
{
    _16_offset ret = 0U;

    if (_16b_addressing_form == _BX_PLUS_SI_)
    {
        ret = get_BX(&general_regs_st) + (_16_offset)general_regs_st.ESI.SI;
        goto RETURN;
    }
    if (_16b_addressing_form == _BX_PLUS_DI_)
    {
        ret = get_BX(&general_regs_st) + (_16_offset)general_regs_st.EDI.DI;
        goto RETURN;
    }
    if (_16b_addressing_form == _BP_PLUS_SI_)
    {
        ret = (_16_offset)general_regs_st.EBP.BP + (_16_offset)general_regs_st.ESI.SI;
        goto RETURN;
    }
    if (_16b_addressing_form == _BP_PLUS_DI_)
    {
        ret = (_16_offset)general_regs_st.EBP.BP + (_16_offset)general_regs_st.EDI.DI;
        goto RETURN;
    }
    if (_16b_addressing_form == _SI_)
    {
        ret = (_16_offset)general_regs_st.ESI.SI;
        goto RETURN;
    }
    if (_16b_addressing_form == _DI_)
    {
        ret = (_16_offset)general_regs_st.EDI.DI;
        goto RETURN;
    }
    if (_16b_addressing_form == _DI_)
    {
        ret = (_16_offset)general_regs_st.EDI.DI;
        goto RETURN;
    }

RETURN:
    return ret;
}