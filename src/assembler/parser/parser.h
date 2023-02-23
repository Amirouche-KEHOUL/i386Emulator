#ifndef _PARSER_H_
#define _PARSER_H_
#include <string.h>
#include "../status/status.h"

/* 
Temporary assembption :
    - No label support
    - No space in the beggening
    - No comments
*/
typedef  unsigned char _opcode ;

typedef struct instr_st 
{
    char* mnem;
    char* args;
}_instr_st;

/*
typedef struct instr_st
{
    // Prefixe : one or more bytes. Segment override, Address size, Operand size, Repeat
    
    struct 
    {
        unsigned int chunk0 : 4; //Least significant bits
        unsigned int chunk1 : 4; 
        unsigned int chunk2 : 4;
        unsigned int chunk3 : 4; 
    }OPCODE;

    // Register specifier : 
    // Addressing-mode specifier : 
    // SIB byte (Scale, Index, Base):
    // Displacement : 8 , 16, 32 bits
    // Emmediate operand : 8, 16, 32 bits
}_instr_st;
*/
// ## Functions ##

/* Retruns the opcode based on mnemonic and args */
_opcode get_opcode (_instr_st* instr_st,_status* status);



#endif // _PARSER_H_