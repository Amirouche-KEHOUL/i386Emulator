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

void map_TEST_operations(void)
{
    one_byte_opcode_map[0x8][0x4] = &TEST_EbGb;
    one_byte_opcode_map[0x8][0x5] = &TEST_EvGv;
    one_byte_opcode_map[0xA][0x8] = &TEST_ALIb;
    one_byte_opcode_map[0xA][0x9] = &TEST_eAXIv;

    ModRM_opcode_map[0x2][0x0] = &TEST_eAXIv;
}

void map_XCNG_operations(void)
{
    one_byte_opcode_map[0x8][0x6] = &XCNG_EbGb;
    one_byte_opcode_map[0x8][0x7] = &XCNG_EvGv;
}

void map_MOV_operations(void)
{

    one_byte_opcode_map[0x8][0x8] = &MOV_EbGb;
    one_byte_opcode_map[0x8][0x9] = &MOV_EvGv;
    one_byte_opcode_map[0x8][0xA] = &MOV_GbEb;
    one_byte_opcode_map[0x8][0xB] = &MOV_GvEv;
    one_byte_opcode_map[0x8][0xC] = &MOV_EwSw;
    one_byte_opcode_map[0x8][0xE] = &MOV_SwEw;
    one_byte_opcode_map[0xA][0x0] = &MOV_ALOb;
    one_byte_opcode_map[0xA][0x1] = &MOV_eAXOv;
    one_byte_opcode_map[0xA][0x2] = &MOV_ObAL;
    one_byte_opcode_map[0xA][0x3] = &MOV_OveAX;
    one_byte_opcode_map[0xB][0x0] = &MOV_AL;
    one_byte_opcode_map[0xB][0x1] = &MOV_CL;
    one_byte_opcode_map[0xB][0x2] = &MOV_DL;
    one_byte_opcode_map[0xB][0x3] = &MOV_BL;
    one_byte_opcode_map[0xB][0x4] = &MOV_AH;
    one_byte_opcode_map[0xB][0x5] = &MOV_CH;
    one_byte_opcode_map[0xB][0x6] = &MOV_DH;
    one_byte_opcode_map[0xB][0x7] = &MOV_BH;
    one_byte_opcode_map[0xB][0x8] = &MOV_eAX;
    one_byte_opcode_map[0xB][0x9] = &MOV_eCX;
    one_byte_opcode_map[0xB][0xA] = &MOV_eDX;
    one_byte_opcode_map[0xB][0xB] = &MOV_eBX;
    one_byte_opcode_map[0xB][0xC] = &MOV_eSP;
    one_byte_opcode_map[0xB][0xD] = &MOV_eBP;
    one_byte_opcode_map[0xB][0xE] = &MOV_eSI;
    one_byte_opcode_map[0xB][0xF] = &MOV_eDI;
    one_byte_opcode_map[0xC][0x6] = &MOV_EbIb;
    one_byte_opcode_map[0xC][0x7] = &MOV_EvIv;

    two_byte_opcode_map[0x2][0x0] = &MOV_CbRb;
    two_byte_opcode_map[0x2][0x1] = &MOV_DdRd;
    two_byte_opcode_map[0x2][0x2] = &MOV_RdCd;
    two_byte_opcode_map[0x2][0x3] = &MOV_RdDd;
    two_byte_opcode_map[0x2][0x4] = &MOV_TdRd;
    two_byte_opcode_map[0x2][0x6] = &MOV_RdTd;
}

void map_LEA_operations(void)
{
    one_byte_opcode_map[0x8][0x6] = &LEA_GvM;
}

void map_NOP_operations(void)
{
    one_byte_opcode_map[0x9][0x0] = &NOP;
}

void map_XCHG_operations(void)
{

    one_byte_opcode_map[0x9][0x1] = &XCHG_eCX;
    one_byte_opcode_map[0x9][0x2] = &XCHG_eDX;
    one_byte_opcode_map[0x9][0x3] = &XCHG_eBX;
    one_byte_opcode_map[0x9][0x4] = &XCHG_eSP;
    one_byte_opcode_map[0x9][0x5] = &XCHG_eBP;
    one_byte_opcode_map[0x9][0x6] = &XCHG_eSI;
    one_byte_opcode_map[0x9][0x7] = &XCHG_eDI;
}

void map_CBW_operations(void)
{
    one_byte_opcode_map[0x9][0x8] = &CBW;
}

void map_CWD_operations(void)
{
    one_byte_opcode_map[0x9][0x9] = &CWD;
}

void map_CALL_operations(void)
{
    one_byte_opcode_map[0x9][0xA] = &CALL_Ap;
    one_byte_opcode_map[0xE][0x8] = &CALL_Av;

    ModRM_opcode_map[0x4][0x2] = &ModRM_CALL_Ev;
    ModRM_opcode_map[0x4][0x3] = &ModRM_CALL_Ep;
}

void map_WAIT_operations(void)
{
    one_byte_opcode_map[0x9][0xB] = &WAIT;
}

void map_PUSHF_operations(void)
{
    one_byte_opcode_map[0x9][0xC] = &PUSHF_Fv;
}

void map_POPF_operations(void)
{
    one_byte_opcode_map[0x9][0xD] = &POPF_Fv;
}

void map_SAHF_operations(void)
{
    one_byte_opcode_map[0x9][0xE] = &SAHF;
}

void map_LAHF_operations(void)
{
    one_byte_opcode_map[0x9][0xF] = &LAHF;
}

void map_MOVSB_operations(void)
{
    one_byte_opcode_map[0xA][0x4] = &MOVSB_XbYb;
}

void map_MOVSW_operations(void)
{
    one_byte_opcode_map[0xA][0x5] = &MOVSW_XvYv;
}

void map_CMPSB_operations(void)
{
    one_byte_opcode_map[0xA][0x6] = &CMPSB_XbYb;
}

void map_CMPSW_operations(void)
{
    one_byte_opcode_map[0xA][0x7] = &CMPSW_XvYv;
}

void map_STOSB_operations(void)
{
    one_byte_opcode_map[0xA][0xA] = &STOSB_YbAL;
}

void map_STOSW_operations(void)
{
    one_byte_opcode_map[0xA][0xB] = &STOSW_YveAX;
}

void map_LODSB_operations(void)
{
    one_byte_opcode_map[0xA][0xC] = &LODSB_ALXb;
}

void map_LODSW_operations(void)
{
    one_byte_opcode_map[0xA][0xD] = &LODSW_sAXXv;
}

void map_SCASB_operations(void)
{
    one_byte_opcode_map[0xA][0xE] = &SCASB_ALXb;
}

void map_SCASW_operations(void)
{
    one_byte_opcode_map[0xA][0xE] = &SCASW_eAXXv;
}

void map_RET_NEAR_operations(void)
{
    one_byte_opcode_map[0xC][0x2] = &RET_NEAR_Iw;
    one_byte_opcode_map[0xC][0x3] = &RET_NEAR;
}

void map_LES_operations(void)
{
    one_byte_opcode_map[0xC][0x4] = &LES_GvMp;
}

void map_LDS_operations(void)
{
    one_byte_opcode_map[0xC][0x5] = &LDS_GvMp;
}

void map_ENTER_operations(void)
{
    one_byte_opcode_map[0xC][0x8] = &ENTER_IwIb;
}

void map_LEAVE_operations(void)
{
    one_byte_opcode_map[0xC][0x9] = &LEAVE;
}

void map_RET_FAR_operations(void)
{
    one_byte_opcode_map[0xC][0xA] = &RET_FAR_Iw;
    one_byte_opcode_map[0xC][0xB] = &RET_FAR;
}

void map_INT_operations(void)
{
    one_byte_opcode_map[0xC][0xC] = &INT_3;
    one_byte_opcode_map[0xC][0xD] = &INT_Ib;
}

void map_INTO_operations(void)
{
    one_byte_opcode_map[0xC][0xE] = &INTO;
}

void map_IRET_operations(void)
{
    one_byte_opcode_map[0xC][0xF] = &IRET;
}

void map_AAM_operations(void)
{
    one_byte_opcode_map[0xD][0x4] = &AAM;
}

void map_AAD_operations(void)
{
    one_byte_opcode_map[0xD][0x5] = &AAD;
}

void map_XLAT_operations(void)
{
    one_byte_opcode_map[0xD][0x7] = &XLAT;
}

void map_ESC_COP_operations(void)
{
    one_byte_opcode_map[0xD][0x8] = &ESC_COP;
    one_byte_opcode_map[0xD][0x9] = &ESC_COP;
    one_byte_opcode_map[0xD][0xA] = &ESC_COP;
    one_byte_opcode_map[0xD][0xB] = &ESC_COP;
    one_byte_opcode_map[0xD][0xC] = &ESC_COP;
    one_byte_opcode_map[0xD][0xD] = &ESC_COP;
    one_byte_opcode_map[0xD][0xE] = &ESC_COP;
    one_byte_opcode_map[0xD][0xF] = &ESC_COP;
}

void map_LOOPNE_operations(void)
{
    one_byte_opcode_map[0xE][0x0] = &LOOPNE_Jb;
}

void map_LOOPE_operations(void)
{
    one_byte_opcode_map[0xE][0x1] = &LOOPE_Jb;
}

void map_LOOP_operations(void)
{
    one_byte_opcode_map[0xE][0x2] = &LOOP_Jb;
}

void map_JCXZ_operations(void)
{
    one_byte_opcode_map[0xE][0x3] = &LOOP_Jb;
}

void map_IN_operations(void)
{
    one_byte_opcode_map[0xE][0x4] = &IN_ALIb;
    one_byte_opcode_map[0xE][0x5] = &IN_eAXIb;
    one_byte_opcode_map[0xE][0xC] = &IN_ALDX;
    one_byte_opcode_map[0xE][0xD] = &IN_eAXDX;
}

void map_OUT_operations(void)
{
    one_byte_opcode_map[0xE][0x6] = &OUT_IbAL;
    one_byte_opcode_map[0xE][0x7] = &OUT_IbeAX;
    one_byte_opcode_map[0xE][0xE] = &OUT_DXAL;
    one_byte_opcode_map[0xE][0xF] = &OUT_DXeAX;
}

void map_HLT_operations(void)
{
    one_byte_opcode_map[0xF][0x4] = &HLT;
}

void map_CMC_operations(void)
{
    one_byte_opcode_map[0xF][0x5] = &CMC;
}

void map_CLC_operations(void)
{
    one_byte_opcode_map[0xF][0x8] = &CLC;
}

void map_STC_operations(void)
{
    one_byte_opcode_map[0xF][0x9] = &STC;
}

void map_CLI_operations(void)
{
    one_byte_opcode_map[0xF][0xA] = &CLI;
}

void map_STI_operations(void)
{
    one_byte_opcode_map[0xF][0xB] = &STI;
}

void map_CLD_operations(void)
{
    one_byte_opcode_map[0xF][0xC] = &CLD;
}

void map_STD_operations(void)
{
    one_byte_opcode_map[0xF][0xC] = &STD;
}

void map_LAR_operations(void)
{
    two_byte_opcode_map[0x0][0x2] = &LAR_GwEw;
}

void map_LSL_operations(void)
{
    two_byte_opcode_map[0x0][0x3] = &LSL_GwEw;
}

void map_CLTS_operations(void)
{
    two_byte_opcode_map[0x0][0x6] = &CLTS;
}

void map_JO_LONG_operations(void)
{
    two_byte_opcode_map[0x8][0x0] = &JO_LONG;
}

void map_JNO_LONG_operations(void)
{
    two_byte_opcode_map[0x8][0x1] = &JNO_LONG;
}

void map_JB_LONG_operations(void)
{
    two_byte_opcode_map[0x8][0x2] = &JB_LONG;
}

void map_JNB_LONG_operations(void)
{
    two_byte_opcode_map[0x8][0x3] = &JNB_LONG;
}

void map_JZ_LONG_operations(void)
{
    two_byte_opcode_map[0x8][0x4] = &JZ_LONG;
}

void map_JNZ_LONG_operations(void)
{
    two_byte_opcode_map[0x8][0x5] = &JNZ_LONG;
}

void map_JBE_LONG_operations(void)
{
    two_byte_opcode_map[0x8][0x6] = &JBE_LONG;
}

void map_JNBE_LONG_operations(void)
{
    two_byte_opcode_map[0x8][0x7] = &JNBE_LONG;
}

void map_JS_LONG_operations(void)
{
    two_byte_opcode_map[0x8][0x8] = &JS_LONG;
}

void map_JNS_LONG_operations(void)
{
    two_byte_opcode_map[0x8][0x9] = &JNS_LONG;
}

void map_JP_LONG_operations(void)
{
    two_byte_opcode_map[0x8][0xA] = &JP_LONG;
}

void map_JNP_LONG_operations(void)
{
    two_byte_opcode_map[0x8][0xB] = &JNP_LONG;
}

void map_JL_LONG_operations(void)
{
    two_byte_opcode_map[0x8][0xC] = &JL_LONG;
}

void map_JNL_LONG_operations(void)
{
    two_byte_opcode_map[0x8][0xD] = &JNL_LONG;
}

void map_JLE_LONG_operations(void)
{
    two_byte_opcode_map[0x8][0xE] = &JLE_LONG;
}

void map_JNLE_LONG_operations(void)
{
    two_byte_opcode_map[0x8][0xF] = &JNLE_LONG;
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
    map_TEST_operations();
    map_XCNG_operations();
    map_MOV_operations();
    map_LEA_operations();
    map_NOP_operations();
    map_XCHG_operations();
    map_CBW_operations();
    map_CWD_operations();
    map_CALL_operations();
    map_WAIT_operations();
    map_PUSHF_operations();
    map_POPF_operations();
    map_SAHF_operations();
    map_LAHF_operations();
    map_MOVSB_operations();
    map_MOVSW_operations();
    map_CMPSB_operations();
    map_CMPSW_operations();
    map_STOSB_operations();
    map_STOSW_operations();
    map_LODSB_operations();
    map_LODSW_operations();
    map_SCASB_operations();
    map_SCASW_operations();
    map_RET_NEAR_operations();
    map_LES_operations();
    map_LDS_operations();
    map_ENTER_operations();
    map_LEAVE_operations();
    map_RET_FAR_operations();
    map_INT_operations();
    map_INTO_operations();
    map_IRET_operations();
    map_AAM_operations();
    map_AAD_operations();
    map_XLAT_operations();
    map_ESC_COP_operations();
    map_LOOPNE_operations();
    map_LOOPE_operations();
    map_LOOP_operations();
    map_JCXZ_operations();
    map_IN_operations();
    map_OUT_operations();
    map_HLT_operations();
    map_CMC_operations();
    map_CLC_operations();
    map_STC_operations();
    map_CLI_operations();
    map_STI_operations();
    map_CLD_operations();
    map_STD_operations();
    map_LAR_operations();
    map_LSL_operations();
    map_LSL_operations();
    map_CLTS_operations();
    map_JO_LONG_operations();
    map_JNO_LONG_operations();
    map_JB_LONG_operations();
    map_JNB_LONG_operations();
    map_JZ_LONG_operations();
    map_JNZ_LONG_operations();
    map_JBE_LONG_operations();
    map_JNBE_LONG_operations();
    map_JS_LONG_operations();
    map_JNS_LONG_operations();
    map_JP_LONG_operations();
    map_JNP_LONG_operations();
    map_JL_LONG_operations();
    map_JNL_LONG_operations();
    map_JLE_LONG_operations();
    map_JNLE_LONG_operations();
}