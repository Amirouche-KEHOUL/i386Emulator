#ifndef _PARSER_H_
#define _PARSER_H_

/* 
Temporary assembption :
    - No label support
    - No space in the beggening
    - No comments
*/

typedef struct instr_st
{
    // Prefixe : one or more bytes. Segment override, Address size, Operand size, Repeat
    
    struct 
    {
        unsigned int bits_4_0:4;
        unsigned int bits_4_1:4;
        unsigned int bits_4_2:4;
        unsigned int bits_4_3:4;
    }OPCODE;

    // Register specifier : 
    // Addressing-mode specifier : 
    // SIB byte (Scale, Index, Base):
    // Displacement : 8 , 16, 32 bits
    // Emmediate operand : 8, 16, 32 bits
}_instr_st;

#endif // _PARSER_H_