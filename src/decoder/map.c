#include "map.h"

extern _ModRM_st ModRM_st;

extern void (*one_byte_opcode_map[16][16])(void); // Page 414
extern void (*two_byte_opcode_map[16][16])(void); // Page 415
extern void (*ModRM_opcode_map[8][8])(void);      // Page 416

// Used tu fill empty cells in opcode maps at program init
void no_operation_opcode(void)
{
    // TODO: confirm what to do in case of opcode hits an empty cell
    printf("No operation for this opcode\n");
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

void map_ADD_operations(void)
{
    one_byte_opcode_map[0x0][0x0] = &ADD_EbGb;
    one_byte_opcode_map[0x0][0x1] = &ADD_EvGv;
    one_byte_opcode_map[0x0][0x2] = &ADD_GbEb;
    one_byte_opcode_map[0x0][0x3] = &ADD_GvEv;
    one_byte_opcode_map[0x0][0x4] = &ADD_ALIb;
    one_byte_opcode_map[0x0][0x5] = &ADD_eAXIv;

    ModRM_opcode_map[0x0][0x0] = &ModRM_ADD;
}

void map_OR_operations(void)
{
    one_byte_opcode_map[0x0][0x8] = &OR_EbGb;
    one_byte_opcode_map[0x0][0x9] = &OR_EvGv;
    one_byte_opcode_map[0x0][0xA] = &OR_GbEb;
    one_byte_opcode_map[0x0][0xB] = &OR_GvEv;
    one_byte_opcode_map[0x0][0xC] = &OR_ALIb;
    one_byte_opcode_map[0x0][0xD] = &OR_eAXIv;

    ModRM_opcode_map[0x0][0x1] = &ModRM_OR;
}

void map_ADC_operations(void)
{
    one_byte_opcode_map[0x1][0x0] = &ADC_EbGb;
    one_byte_opcode_map[0x1][0x1] = &ADC_EvGv;
    one_byte_opcode_map[0x1][0x2] = &ADC_GbEb;
    one_byte_opcode_map[0x1][0x3] = &ADC_GvEv;
    one_byte_opcode_map[0x1][0x4] = &ADC_ALIb;
    one_byte_opcode_map[0x1][0x5] = &ADC_eAXIv;

    ModRM_opcode_map[0x0][0x2] = &ModRM_ADC;
}

void map_SBB_operations(void)
{
    one_byte_opcode_map[0x1][0x8] = &SBB_EbGb;
    one_byte_opcode_map[0x1][0x9] = &SBB_EvGv;
    one_byte_opcode_map[0x1][0xA] = &SBB_GbEb;
    one_byte_opcode_map[0x1][0xB] = &SBB_GvEv;
    one_byte_opcode_map[0x1][0xC] = &SBB_ALIb;
    one_byte_opcode_map[0x1][0xD] = &SBB_eAXIv;

    ModRM_opcode_map[0x0][0x3] = &ModRM_SBB;
}

void map_AND_operations(void)
{
    one_byte_opcode_map[0x2][0x0] = &AND_EbGb;
    one_byte_opcode_map[0x2][0x1] = &AND_EvGv;
    one_byte_opcode_map[0x2][0x2] = &AND_GbEb;
    one_byte_opcode_map[0x2][0x3] = &AND_GvEv;
    one_byte_opcode_map[0x2][0x4] = &AND_ALIb;
    one_byte_opcode_map[0x2][0x5] = &AND_eAXIv;

    ModRM_opcode_map[0x0][0x4] = &ModRM_AND;
}

void map_SUB_operations(void)
{
    one_byte_opcode_map[0x2][0x8] = &SUB_EbGb;
    one_byte_opcode_map[0x2][0x9] = &SUB_EvGv;
    one_byte_opcode_map[0x2][0xA] = &SUB_GbEb;
    one_byte_opcode_map[0x2][0xB] = &SUB_GvEv;
    one_byte_opcode_map[0x2][0xC] = &SUB_ALIb;
    one_byte_opcode_map[0x2][0xD] = &SUB_eAXIv;

    ModRM_opcode_map[0x0][0x5] = &ModRM_SUB;
}

void map_XOR_operations(void)
{
    one_byte_opcode_map[0x3][0x0] = &XOR_EbGb;
    one_byte_opcode_map[0x3][0x1] = &XOR_EvGv;
    one_byte_opcode_map[0x3][0x2] = &XOR_GbEb;
    one_byte_opcode_map[0x3][0x3] = &XOR_GvEv;
    one_byte_opcode_map[0x3][0x4] = &XOR_ALIb;
    one_byte_opcode_map[0x3][0x5] = &XOR_eAXIv;

    ModRM_opcode_map[0x0][0x6] = &ModRM_XOR;
}

void map_CMP_operations(void)
{
    one_byte_opcode_map[0x3][0x8] = &CMP_EbGb;
    one_byte_opcode_map[0x3][0x9] = &CMP_EvGv;
    one_byte_opcode_map[0x3][0xA] = &CMP_GbEb;
    one_byte_opcode_map[0x3][0xB] = &CMP_GvEv;
    one_byte_opcode_map[0x3][0xC] = &CMP_ALIb;
    one_byte_opcode_map[0x3][0xD] = &CMP_eAXIv;

    ModRM_opcode_map[0x0][0x7] = &ModRM_CMP;
}

void map_INC_operations(void)
{

    one_byte_opcode_map[0x4][0x0] = &INC_eAX;
    one_byte_opcode_map[0x4][0x1] = &INC_eCX;
    one_byte_opcode_map[0x4][0x2] = &INC_eDX;
    one_byte_opcode_map[0x4][0x3] = &INC_eBX;
    one_byte_opcode_map[0x4][0x4] = &INC_eSP;
    one_byte_opcode_map[0x4][0x5] = &INC_eBP;
    one_byte_opcode_map[0x4][0x6] = &INC_eSI;
    one_byte_opcode_map[0x4][0x7] = &INC_eDI;

    ModRM_opcode_map[0x3][0x0] = &ModRM_INC_Eb;
}

void map_DEC_operations(void)
{

    one_byte_opcode_map[0x4][0x8] = &DEC_eAX;
    one_byte_opcode_map[0x4][0x9] = &DEC_eCX;
    one_byte_opcode_map[0x4][0xA] = &DEC_eDX;
    one_byte_opcode_map[0x4][0xB] = &DEC_eBX;
    one_byte_opcode_map[0x4][0xC] = &DEC_eSP;
    one_byte_opcode_map[0x4][0xD] = &DEC_eBP;
    one_byte_opcode_map[0x4][0xE] = &DEC_eSI;
    one_byte_opcode_map[0x4][0xF] = &DEC_eDI;

    ModRM_opcode_map[0x3][0x1] = &ModRM_DEC_Eb;
}

void map_PUSH_operations(void)
{

    one_byte_opcode_map[0x0][0x6] = &PUSH_ES;
    one_byte_opcode_map[0x0][0xE] = &PUSH_CS;
    one_byte_opcode_map[0x1][0x6] = &PUSH_SS;
    one_byte_opcode_map[0x1][0xE] = &PUSH_DS;
    one_byte_opcode_map[0x6][0x8] = &PUSH_Ib;
    one_byte_opcode_map[0x6][0xA] = &PUSH_Ib; // Mapped 2 times

    one_byte_opcode_map[0x5][0x0] = &PUSH_eAX;
    one_byte_opcode_map[0x5][0x1] = &PUSH_eCX;
    one_byte_opcode_map[0x5][0x2] = &PUSH_eDX;
    one_byte_opcode_map[0x5][0x3] = &PUSH_eBX;
    one_byte_opcode_map[0x5][0x4] = &PUSH_eSP;
    one_byte_opcode_map[0x5][0x5] = &PUSH_eBP;
    one_byte_opcode_map[0x5][0x6] = &PUSH_eSI;
    one_byte_opcode_map[0x5][0x7] = &PUSH_eDI;

    two_byte_opcode_map[0xA][0x0] = &PUSH_FS;
    two_byte_opcode_map[0xA][0x8] = &PUSH_GS;

    ModRM_opcode_map[0x4][0x6] = &ModRM_PUSH_Ev;
}

void map_POP_operations(void)
{

    one_byte_opcode_map[0x0][0x7] = &POP_ES;
    one_byte_opcode_map[0x1][0x7] = &POP_SS;
    one_byte_opcode_map[0x1][0xF] = &POP_DS;
    one_byte_opcode_map[0x8][0xF] = &POP_Ev;

    one_byte_opcode_map[0x5][0x8] = &POP_eAX;
    one_byte_opcode_map[0x5][0x9] = &POP_eCX;
    one_byte_opcode_map[0x5][0xA] = &POP_eDX;
    one_byte_opcode_map[0x5][0xB] = &POP_eBX;
    one_byte_opcode_map[0x5][0xC] = &POP_eSP;
    one_byte_opcode_map[0x5][0xD] = &POP_eBP;
    one_byte_opcode_map[0x5][0xE] = &POP_eSI;
    one_byte_opcode_map[0x5][0xF] = &POP_eDI;

    two_byte_opcode_map[0xA][0x1] = &POP_FS;
    two_byte_opcode_map[0xA][0x9] = &POP_GS;
}

void map_DAA_operations(void)
{
    one_byte_opcode_map[0x2][0x7] = &DAA;
}

void map_DAS_operations(void)
{
    one_byte_opcode_map[0x2][0xF] = &DAS;
}

void map_AAA_operations(void)
{
    one_byte_opcode_map[0x3][0x7] = &AAA;
}

void map_AAS_operations(void)
{
    one_byte_opcode_map[0x3][0xF] = &AAS;
}

void map_PUSHA_operations(void)
{
    one_byte_opcode_map[0x6][0x0] = &PUSHA;
}

void map_POPA_operations(void)
{
    one_byte_opcode_map[0x6][0x1] = &POPA;
}

void map_BOUND_operations(void)
{
    one_byte_opcode_map[0x6][0x2] = &BOUND_GvMa;
}

void map_ARPL_operations(void)
{
    one_byte_opcode_map[0x6][0x3] = &ARPL_EwRw;
}

void map_IMUL_operations(void)
{
    one_byte_opcode_map[0x6][0x9] = &IMUL_GvEvIv;
    one_byte_opcode_map[0x6][0xB] = &IMUL_GvEvIv;

    two_byte_opcode_map[0xA][0xF] = &IMUL_GvEv;

    ModRM_opcode_map[0x2][0x5] = &ModRM_IMUL_ALeAX;
}

void map_INSB_operations(void)
{
    one_byte_opcode_map[0x6][0xC] = &INSB_YbDx;
}

void map_INSW_D_operations(void)
{
    one_byte_opcode_map[0x6][0xD] = &INSW_D_YbDx;
}

void map_OUTSB_operations(void)
{
    one_byte_opcode_map[0x6][0xE] = &OUTSB_DxXb;
}

void map_OUTSW_D_operations(void)
{
    one_byte_opcode_map[0x6][0xE] = &OUTSW_D_DxXv;
}

void map_JO_SHORT_operations(void)
{
    one_byte_opcode_map[0x7][0x0] = &JO_SHORT;
}

void map_JNO_SHORT_operations(void)
{
    one_byte_opcode_map[0x7][0x1] = &JNO_SHORT;
}

void map_JB_SHORT_operations(void)
{
    one_byte_opcode_map[0x7][0x2] = &JB_SHORT;
}

void map_JNB_SHORT_operations(void)
{
    one_byte_opcode_map[0x7][0x3] = &JNB_SHORT;
}

void map_JZ_SHORT_operations(void)
{
    one_byte_opcode_map[0x7][0x4] = &JZ_SHORT;
}

void map_JNZ_SHORT_operations(void)
{
    one_byte_opcode_map[0x7][0x5] = &JNZ_SHORT;
}

void map_JBE_SHORT_operations(void)
{
    one_byte_opcode_map[0x7][0x6] = &JBE_SHORT;
}

void map_JNBE_SHORT_operations(void)
{
    one_byte_opcode_map[0x7][0x7] = &JNBE_SHORT;
}

void map_JS_SHORT_operations(void)
{
    one_byte_opcode_map[0x7][0x8] = &JS_SHORT;
}

void map_JNS_SHORT_operations(void)
{
    one_byte_opcode_map[0x7][0x9] = &JNS_SHORT;
}

void map_JP_SHORT_operations(void)
{
    one_byte_opcode_map[0x7][0xA] = &JP_SHORT;
}

void map_JNP_SHORT_operations(void)
{
    one_byte_opcode_map[0x7][0xB] = &JNP_SHORT;
}

void map_JL_SHORT_operations(void)
{
    one_byte_opcode_map[0x7][0xC] = &JL_SHORT;
}

void map_JNL_SHORT_operations(void)
{
    one_byte_opcode_map[0x7][0xD] = &JNL_SHORT;
}

void map_JLE_SHORT_operations(void)
{
    one_byte_opcode_map[0x7][0xE] = &JLE_SHORT;
}

void map_JNLE_SHORT_operations(void)
{
    one_byte_opcode_map[0x7][0xF] = &JNLE_SHORT;
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
    map_ADD_operations();
    map_OR_operations();
    map_ADC_operations();
    map_SBB_operations();
    map_AND_operations();
    map_SUB_operations();
    map_XOR_operations();
    map_CMP_operations();
    map_INC_operations();
    map_DEC_operations();
    map_PUSH_operations();
    map_POP_operations();
    map_DAA_operations();
    map_DAS_operations();
    map_AAA_operations();
    map_AAS_operations();
    map_PUSHA_operations();
    map_POPA_operations();
    map_BOUND_operations();
    map_ARPL_operations();
    map_IMUL_operations();
    map_INSB_operations();
    map_INSW_D_operations();
    map_OUTSB_operations();
    map_OUTSW_D_operations();
    map_JO_SHORT_operations();
    map_JNO_SHORT_operations();
    map_JB_SHORT_operations();
    map_JNB_SHORT_operations();
    map_JZ_SHORT_operations();
    map_JNZ_SHORT_operations();
    map_JBE_SHORT_operations();
    map_JNBE_SHORT_operations();
    map_JS_SHORT_operations();
    map_JNS_SHORT_operations();
    map_JP_SHORT_operations();
    map_JNP_SHORT_operations();
    map_JL_SHORT_operations();
    map_JNL_SHORT_operations();
    map_JLE_SHORT_operations();
    map_JNLE_SHORT_operations();
}