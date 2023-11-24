#include "decoder.h"

extern _general_regs_st general_regs_st;
extern void (*one_byte_map[16][16])(void);

_ModRM_st ModRM_st = {0};
_prefetch_queue_st prefetch_queue_st = {0};


unsigned int get_effective_address_size(unsigned int default_seg_size, unsigned int adresse_size_prefix_present)
{
    return (default_seg_size ^ adresse_size_prefix_present); // XOR
}

unsigned int get_effective_operand_size(unsigned int default_seg_size, unsigned int operand_size_prefix_present)
{
    return (default_seg_size ^ operand_size_prefix_present); // XOR
}

void decode(void)
{
    prefetch_queue_st.queue[0] = 0x80;
    prefetch_queue_st.queue[1] = 0xA9;

    _byte byte = stream_byte_prefetch_queue();

    _byte lsb = byte & 0x0F;        // least 4 significant bits
    _byte msb = (byte & 0xF0) >> 4; // most 4 significant bits

    one_byte_map[msb][lsb]();
}

/*
prefetch queueu  = 00

Global one-byte_map[][]
Global two-byte_map[][]
Global Groupe_map[][]

Global 16bit_ModRM_map[][]
Global 32bit_ModRM_map[][]
Global REG_map[][]

Global SIB_map[][]
Global base_map[][]

Global R/M_Operand
Global R/M_Operand_address.
Global R_Operand
Global R_Operand_addresse.

Global effective_operand_size
Global effective_operand_address_size

stream_byte() ==> bL = 0 , bH = 0
one-byte_map[bH][bL] () ==> call Add_Eb,Gb()

Add_Eb,Gb()
{
    // Eb ==> Use modRM_map[]
    // Gb ==> Use of Reg_map[]
    stream_byte()
    update_ModRM_st()

    Xbit_ModRM_map[R/M][Mod]()
    REG_map[r8][REG]()

    Do_operation()

}

Xbit_ModRM_map[R/M][Mod]()
{
    R/M_Operand_addresse = calculate_addr()
    R/M_Operand = read_from_mem(M_Operand_addresse)

}

REG_map[r8][REG]()
{
    R_Operand = read_reg()
    R_operand_address
}

*/
