#include "ESCAPE.h"
extern _ModRM_st ModRM_st;
extern void (*two_byte_map[16][16])(void);
extern void (*group1[2][8])(void);
extern void (*group2[6][8])(void);
extern void (*group3[2][8])(void);
extern void (*group4[8])(void);
extern void (*group5[8])(void);
extern void (*group6[8])(void);
extern void (*group7[8])(void);
extern void (*group8[8])(void);

void no_opcode(void)
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

    two_byte_map[msb][lsb]();
}

void grp1_EbIb_escape(void)
{
    read_ModRM_byte_to_st();
    group1[0x0][ModRM_st.REG_OPCODE]();
}

void grp1_EvIv_escape(void)
{
    read_ModRM_byte_to_st();
    group1[0x1][ModRM_st.REG_OPCODE]();
}

void grp2_EbIb_escape(void)
{
    read_ModRM_byte_to_st();
    group2[0x0][ModRM_st.REG_OPCODE]();
}

void grp2_EvIv_escape(void)
{
    read_ModRM_byte_to_st();
    group2[0x1][ModRM_st.REG_OPCODE]();
}

void grp2_Eb1_escape(void)
{
    read_ModRM_byte_to_st();
    group2[0x2][ModRM_st.REG_OPCODE]();
}

void grp2_Ev1_escape(void)
{
    read_ModRM_byte_to_st();
    group2[0x3][ModRM_st.REG_OPCODE]();
}

void grp2_EbCL_escape(void)
{
    read_ModRM_byte_to_st();
    group2[0x4][ModRM_st.REG_OPCODE]();
}

void grp2_EvCL_escape(void)
{
    read_ModRM_byte_to_st();
    group2[0x5][ModRM_st.REG_OPCODE]();
}

void grp3_Eb_escape(void)
{
    read_ModRM_byte_to_st();
    group3[0x0][ModRM_st.REG_OPCODE]();
}

void grp3_Ev_escape(void)
{
    read_ModRM_byte_to_st();
    group3[0x1][ModRM_st.REG_OPCODE]();
}

void grp4_escape(void)
{
    read_ModRM_byte_to_st();
    group4[ModRM_st.REG_OPCODE]();
}

void grp5_escape(void)
{
    read_ModRM_byte_to_st();
    group5[ModRM_st.REG_OPCODE]();
}

void grp6_escape(void)
{
    read_ModRM_byte_to_st();
    group6[ModRM_st.REG_OPCODE]();
}

void grp7_escape(void)
{
    read_ModRM_byte_to_st();
    group7[ModRM_st.REG_OPCODE]();
}

void grp8_EvIb_escape(void)
{
    read_ModRM_byte_to_st();
    group8[ModRM_st.REG_OPCODE]();
}
