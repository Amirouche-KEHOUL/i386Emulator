#include "map.h"

void (*one_byte_map[16][16])(void) = {

    /*0*/ {ADD_EbGb, ADD_EvGv, ADD_GbEb, ADD_GvEv, ADD_ALIb, ADD_eAXIv, PUSH_ES, POP_ES, OR_EbGb, OR_EvGv, OR_GbEb, OR_GvEv, OR_ALIb, OR_eAXIv, PUSH_CS, _2byte_escape},
    /*1*/ {ADC_EbGb, ADC_EvGv, ADC_GbEb, ADC_GvEv, ADC_ALIb, ADC_eAXIv, PUSH_SS, POP_SS, SBB_EbGb, SBB_EvGv, SBB_GbEb, SBB_GvEv, SBB_ALIb, SBB_eAXIv, PUSH_DS, POP_DS},
    /*2*/ {AND_EbGb, AND_EvGv, AND_GbEb, AND_GvEv, AND_ALIb, AND_eAXIv, SEG_ES, DAA, SUB_EbGb, SUB_EvGv, SUB_GbEb, SUB_GvEv, SUB_ALIb, SUB_eAXIv, SEG_CS, DAS},
    /*3*/ {XOR_EbGb, XOR_EvGv, XOR_GbEb, XOR_GvEv, XOR_ALIb, XOR_eAXIv, SEG_SS, AAA, CMP_EbGb, CMP_EvGv, CMP_GbEb, CMP_GvEv, CMP_ALIb, CMP_eAXIv, SEG_DS, AAS},
    /*4*/ {INC_eAX, INC_eCX, INC_eDX, INC_eBX, INC_eSP, INC_eBP, INC_eSI, INC_eDI, DEC_eAX, DEC_eCX, DEC_eDX, DEC_eBX, DEC_eSP, DEC_eBP, DEC_eSI, DEC_eDI},
    /*5*/ {PUSH_eAX, PUSH_eCX, PUSH_eDX, PUSH_eBX, PUSH_eSP, PUSH_eBP, PUSH_eSI, PUSH_eDI, POP_eAX, POP_eCX, POP_eDX, POP_eBX, POP_eSP, POP_eBP, POP_eSI, POP_eDI},
    /*6*/ {PUSHA, POPA, BOUND_GvMa, ARPL_EwRw, SEG_FS, SEG_GS, Operand_Size, Address_Size, PUSH_Ib, IMUL_GvEvIv, PUSH_Ib, IMUL_GvEvIv, INSB_YbDX, INSWD_YvDX, OUTSB_DxXb, OUTSWD_DxXv},
    /*7*/ {JO_Jb, JNO_Jb, JB_Jb, JNB_Jb, JZ_Jb, JNZ_Jb, JBE_Jb, JNBE_Jb, JS_Jb, JNS_Jb, JP_Jb, JNP_Jb, JL_Jb, JNL_Jb, JLE_Jb, JNLE_Jb},
    /*8*/ {grp1_EbIb_escape, grp1_EvIv_escape, no_opcode, TEST_EbGb, TEST_EvGv, MOV_EbGb, MOV_EvGv, MOV_GbEb, MOV_GvEv, LEA_GvM, MOV_SwEw, POP_Ev},
    /*9*/ {NOP, XCHG_eCXeAX, XCHG_eDXeAX, XCHG_eBXeAX, XCHG_eBXeAX, XCHG_eBPeAX, XCHG_eSIeAX, XCHG_eDIeAX, CBW, CWD, CALL_Ap, WAIT, PUSHF_Fv, POPF_Fv, SAHF, LAHF},
    /*A*/ {MOV_ALOb, MOV_eAXOv, MOV_ObAL, MOV_OveAX, MOVSB_XbYb, MOVSWD_XvYv, CMPSB_XbYb, CMPSWD_XvYv, TEST_ALIb, TEST_eAXIv, STOSB_YbAL, STOSWD_YveAX, LODSB_ALXb, LODSWD_eAXXv, SCASB_ALXb, SCASWD_eAXXv},
    /*B*/ {MOV_ALIb, MOV_CLIb, MOV_DLIb, MOV_BLIb, MOV_AHIb, MOV_CHIb, MOV_DHIb, MOV_BHIb, MOV_eAXIv, MOV_eCXIv, MOV_eDXIv, MOV_eBXIv, MOV_eSPIv, MOV_eBPIv, MOV_eSIIv, MOV_eDIIv},
    /*C*/ {grp2_EbIb_escape, grp2_EvIv_escape, RET_NEAR_Iw, RET_NEAR, LES_GvMp, LDS_GvMp, MOV_EbIb, MOV_EvIv, ENTER_IwIb, LEAVE, RET_FAR_Iw, RET_FAR, INT_3, INT_Ib, INTO, IRET},
    /*D*/ {grp2_Eb1_escape, grp2_Ev1_escape, grp2_EbCL_escape, grp2_EvCL_escape, AAM, AAD, no_opcode, XLAT, ESC_COP, ESC_COP, ESC_COP, ESC_COP, ESC_COP, ESC_COP, ESC_COP, ESC_COP},
    /*E*/ {LOOPNE_Jb, LOOPE_Jb, LOOP_Jb, JCXZ_Jb, IN_ALIb, IN_eAXIb, OUT_IbAL, OUT_IbeAX, CALL_Av, no_opcode, no_opcode, no_opcode, IN_ALDX, IN_eAXDX, OUT_DXAL, OUT_DXeAX}, // TODO: confirm  JNP command (put no_operation temporarely)
    /*F*/ {LOCK, no_opcode, REPNE, REP_REPE, HLT, CMC, grp3_Eb_escape, grp3_Ev_escape, CLC, STC, CLI, STI, CLD, STD, grp4_escape, grp5_escape},
};

void (*two_byte_map[16][16])(void) = {
    /*0*/ {grp6_escape, grp7_escape, LAR_GwEw, LSL_GvEw, no_opcode, no_opcode, CLTS, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode},
    /*1*/ {no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode},
    /*2*/ {MOV_CdRd, MOV_DdRd, MOV_RdCd, MOV_RdDd, MOV_TdRd, no_opcode, MOV_RdTd, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode},
    /*3*/ {no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode},
    /*4*/ {no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode},
    /*5*/ {no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode},
    /*6*/ {no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode},
    /*7*/ {no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode},
    /*8*/ {JO_Jv, JNO_Jv, JB_Jv, JNB_Jv, JZ_Jv, JNZ_Jv, JBE_Jv, JNBE_Jv, JS_Jv, JNS_Jv, JP_Jv, JNP_Jv, JL_Jv, JNL_Jv, JLE_Jv, JNLE_Jv},
    /*9*/ {SETO_Eb, SETNO_Eb, SETB_Eb, SETNB_Eb, SETZ_Eb, SETNZ_Eb, SETBE_Eb, SETNBE_Eb, SETS_Eb, SETNS_Eb, SETP_Eb, SETNP_Eb, SETL_Eb, SETNL_Eb, SETLE_Eb, SETNLE_Eb},
    /*A*/ {PUSH_FS, POP_FS, no_opcode, BT_EvGv, SHLD_EvGvIb, SHLD_EvGvCL, no_opcode, no_opcode, PUSH_GS, POP_GS, no_opcode, BTS_EvGv, SHRD_EvGvIb, SHRD_EvGvCL, no_opcode, IMUL_GvEv},
    /*B*/ {no_opcode, no_opcode, LSS_Mp, BTR_EvGv, LFS_Mp, LGS_Mp, MOVZX_GvEb, MOVZX_GvEw, no_opcode, no_opcode, grp8_EvIb_escape, BTC_EvGv, BSF_GvEv, BSR_GvEv, MOVSX_GvEb, MOVSX_GvEw},
    /*C*/ {no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode},
    /*D*/ {no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode},
    /*E*/ {no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode},
    /*F*/ {no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode},
};

void (*group1[2][8])(void) = {
    /*0*/ {ADD_EbIb, OR_EbIb, ADC_EbIb, SBB_EbIb, AND_EbIb, SUB_EbIb, XOR_EbIb, CMP_EbIb},
    /*1*/ {ADD_EvIv, OR_EvIv, ADC_EvIv, SBB_EvIv, AND_EvIv, SUB_EvIv, XOR_EvIv, CMP_EvIv},
};

void (*group2[6][8])(void) = {
    /*0*/ {ROL_EbIb, ROR_EbIb, RCL_EbIb, RCR_EbIb, SHL_EbIb, SHR_EbIb, no_opcode, SAR_EbIb},
    /*1*/ {ROL_EvIv, ROR_EvIv, RCL_EvIv, RCR_EvIv, SHL_EvIv, SHR_EvIv, no_opcode, SAR_EvIv},
    /*2*/ {ROL_Eb1, ROR_Eb1, RCL_Eb1, RCR_Eb1, SHL_Eb1, SHR_Eb1, no_opcode, SAR_Eb1},
    /*3*/ {ROL_Ev1, ROR_Ev1, RCL_Ev1, RCR_Ev1, SHL_Ev1, SHR_Ev1, no_opcode, SAR_Ev1},
    /*4*/ {ROL_EbCL, ROR_EbCL, RCL_EbCL, RCR_EbCL, SHL_EbCL, SHR_EbCL, no_opcode, SAR_EbCL},
    /*5*/ {ROL_EvCL, ROR_EvCL, RCL_EvCL, RCR_EvCL, SHL_EvCL, SHR_EvCL, no_opcode, SAR_EvCL},
};

void (*group3[2][8])(void) = {
    {TEST_EbIb, no_opcode, NOT_Eb, NEG_Eb, MUL_EbAL, IMUL_EbAL, DIV_EbAL, IDIV_EbAL},
    {TEST_EvIv, no_opcode, NOT_Ev, NEG_Ev, MUL_EveAL, IMUL_EveAL, DIV_EveAL, IDIV_EveAL},
};

void (*group4[8])(void) = {INC_Eb, DEC_Eb, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode, no_opcode};

void (*group5[8])(void) = {INC_Ev, DEC_Ev, CALL_Ev, CALL_eP, JMP_Ev, JMP_Ep, PUSH_Ev, no_opcode};

void (*group6[8])(void) = {SLDT_Ew, STR_Ew, LLDT_Ew, LTR_Ew, VERR_Ew, VERW_Ew, no_opcode, no_opcode};

void (*group7[8])(void) = {SGDT_Ms, SIDT_Ms, LGDT_Ms, LIDT_Ms, SMSW_Ew, no_opcode, LMSW_Ew, no_opcode};

void (*group8[8])(void) = {no_opcode, no_opcode, no_opcode, no_opcode, BT, BTS, BTR, BTC};

// R/M operands
void (*ModRM_map[2][8][4])(void) = {
    /*------------16bit------------*/
    {

        /*0*/ {BXSI, BXSI_disp8, BXSI_disp16, EAX_AX_AL},
        /*1*/ {BXDI, BXDI_disp8, BXDI_disp16, ECX_CX_CL},
        /*2*/ {BXDI, BXDI_disp8, BXDI_disp16, EDX_DX_DL},
        /*3*/ {BPDI, BPDI_disp8, BPDI_disp16, EBX_BX_BL},
        /*4*/ {SI, SI_disp8, SI_disp16, ESP_SP_AH},
        /*5*/ {DI, DI_disp8, DI_disp16, EBP_BP_CH},
        /*6*/ {disp16, BP_disp8, BP_disp816, ESI_SI_DH},
        /*7*/ {BX, BX_disp8, BX_disp16, EDI_DI_BH},

    },
    /*------------32bit------------*/
    {
        /*0*/ {EAX, disp8_EAX, disp32_EAX, EAX_AX_AL},
        /*1*/ {ECX, disp8_ECX, disp32_ECX, ECX_CX_CL},
        /*2*/ {EDX, disp8_EDX, disp32_EDX, EDX_DX_DL},
        /*3*/ {EBX, disp8_EBX, disp32_EBX, EBX_BX_BL},
        /*4*/ {SIB, disp8_SIB, disp32_SIB, ESP_SP_AH},
        /*5*/ {disp32, disp8_EBP, disp32_EBP, EBP_BP_CH},
        /*6*/ {ESI, disp8_ESI, disp32_ESI, ESI_SI_DH},
        /*7*/ {EDI, disp8_EDI, disp32_EDI, EDI_DI_BH},
    },
};

// REG operand

void (*ModRM_REG_map[3][8])(void) = {
    /*0*/ {AL_REG, CL_REG, DL_REG, BL_REG, AH_REG, CH_REG, DH_REG, BH_REG},         // r8
    /*1*/ {AX_REG, CX_REG, DX_REG, BX_REG, SP_REG, BP_REG, SI_REG, DI_REG},         // r16
    /*2*/ {EAX_REG, ECX_REG, EDX_REG, EBX_REG, ESP_REG, EBP_REG, ESI_REG, EDI_REG}, // r32
};

void (*SIB_map[8][4])(void) = {
    /*0*/ {EAX, EAX_2, EAX_4, EAX_8},
    /*1*/ {ECX, ECX_2, ECX_4, ECX_8},
    /*2*/ {EDX, EDX_2, EDX_4, EDX_8},
    /*3*/ {EBX, EBX_2, EBX_4, EBX_8},
    /*4*/ {none, non_2, non_4, non_8},
    /*5*/ {EBP, EBP_2, EBP_4, EBP_8},
    /*6*/ {ESI, ESI_2, ESI_4, ESI_8},
    /*7*/ {EDI, EDI_2, EDI_4, EDI_8},
};

void (*SIB_BASE_map[8])(void) = {EAX_REG, ECX_REG, EDX_REG, EBX_REG, ESP_REG, EBP_REG, ESI_REG, EDI_REG};
