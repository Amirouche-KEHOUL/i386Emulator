#include "ADD.h"
#include "../../memory/address_translator.h"

/*
ADD performs an integer addition of the two operands (DEST and SRC).
The result of the addition is assigned to the first operand (DEST), and the flags are set accordingly.
When an immediate byte is added to a word or doubleword operand, the immediate value is sign-extended to the size of the word or doubleword operand.
*/

extern void (*ModRM_map[2][8][4])(void);
extern void (*ModRM_REG_map[3][8])(void);

extern _ModRM_st ModRM_st;

// Operands
extern _double_word RM_operand;
extern _32_offset RM_operand_addr;
extern _double_word R_operand;
extern _32_offset R_operand_addr;

extern _data_segment_descriptor_st DS_hidden_data_segment_descriptor; // TODO: include segment_regs_st instead?

extern _physical_memory_ptr physical_memory_ptr;

extern _effec_opr_size effec_opr_size;
extern _effec_opr_addr_size effec_opr_addr_size;

// Mapped to one-byte opcode map

void ADD_EbGb(void)
{
    printf("ADD_EbGb operation called correctly \n");
    read_ModRM_byte_to_st();
    // Eb => ModRM call for first operand. 16bit operand size regardless of operand size attribute.
    // TODO: first index (0 == 16bit map just for a test)
    if (effec_opr_addr_size == _16BIT_EFFECT_OPR_ADDR_SIZE)
    {
        ModRM_map[0][ModRM_st.RM][ModRM_st.MOD](); // This will update RM_operand_addr var.
    }
    if (effec_opr_addr_size == _32BIT_EFFECT_OPR_ADDR_SIZE)
    {
        ModRM_map[1][ModRM_st.RM][ModRM_st.MOD](); // This will update RM_operand_addr var.
    }
    // Read R/M dest operand from memory
    RM_operand = physical_memory_read_byte(physical_memory_ptr, logical_to_physical_addr(RM_operand_addr, &DS_hidden_data_segment_descriptor, _DATA_SEGMENT_DESCRIPTOR));

    // Read register src operand
    ModRM_REG_map[0][ModRM_st.REG_OPCODE]();
    RM_operand = RM_operand + R_operand;

    // TODO: wrtie the result to memory.
}

void ADD_EvGv(void)
{
    printf("ADD_EvGv operation called correctly \n");
    read_ModRM_byte_to_st();
    // Eb => ModRM call for first operand. 16bit operand size regardless of operand size attribute.
    // TODO: first index (0 == 16bit map just for a test)
    if (effec_opr_addr_size == _16BIT_EFFECT_OPR_ADDR_SIZE)
    {
        ModRM_map[0][ModRM_st.RM][ModRM_st.MOD](); // This will update RM_operand_addr var.
    }
    if (effec_opr_addr_size == _32BIT_EFFECT_OPR_ADDR_SIZE)
    {
        ModRM_map[1][ModRM_st.RM][ModRM_st.MOD](); // This will update RM_operand_addr var.
    }
    if (effec_opr_size == _16BIT_EFFECT_OPR_SIZE)
    {
        // Read R/M dest operand from memory
        RM_operand = physical_memory_read_word(physical_memory_ptr, logical_to_physical_addr(RM_operand_addr, &DS_hidden_data_segment_descriptor, _DATA_SEGMENT_DESCRIPTOR));
        // Read register src operand
        ModRM_REG_map[1][ModRM_st.REG_OPCODE]();
    }
    if (effec_opr_size == _32BIT_EFFECT_OPR_SIZE)
    {
        // Read R/M dest operand from memory
        RM_operand = physical_memory_read_double_word(physical_memory_ptr, logical_to_physical_addr(RM_operand_addr, &DS_hidden_data_segment_descriptor, _DATA_SEGMENT_DESCRIPTOR));
        // Read register src operand
        ModRM_REG_map[2][ModRM_st.REG_OPCODE]();
    }

    RM_operand = RM_operand + R_operand;

    // TODO: wrtie the result to memory.
}

void ADD_GbEb(void)
{
    printf("ADD operation called correctly \n");
}

void ADD_GvEv(void)
{
    printf("ADD operation called correctly \n");
}

void ADD_ALIb(void)
{
    printf("ADD operation called correctly \n");
}

void ADD_eAXIv(void)
{
    printf("ADD operation called correctly \n");
}

// Mapped to ModRM opcode  map

void ADD_EbIb(void)
{
    printf("ADD operation called correctly \n");
}

void ADD_EvIv(void)
{
    printf("ADD operation called correctly \n");
}
