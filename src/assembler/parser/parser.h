#ifndef _PARSER_H_
#define _PARSER_H_
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../status/status.h"

/* Configuration */
#define _INSTRUCTION_MAX_LENGTH 10
#define _INSTRUCTION_MNEM_MAX_LENGTH 10
#define _INSTRUCTION_ARGS_MAX_LENGTH 15

/* instruction <-> Opcode pairs*/
#define  _ADD_Eb_Gb_OPCODE   0x00
#define  _ADD_EV_Gv_OPCODE   0x01
#define  _ADD_Gb_Eb_OPCODE   0x02
#define  _ADD_Gv_Ev_OPCODE   0x03
#define  _ADD_AL_Ib_OPCODE   0x04
#define  _ADD_eAX_Iv_OPCODE   0x05


typedef  unsigned char _opcode ;
typedef char* _line;

typedef struct instr_st 
{
    char* mnem;
    char* args;
}_instr_st;

/* ## Functions ## */


/* Return a stream of line from an input file */
_line get_line (FILE* asm_file_post_pro, _status* status );
/* Retruns a stream of instructions from an input file. Retruns space char for both mnem and args if end of file is reached*/
_instr_st get_instruction(_line line , _status* status);
/* Retruns the opcode based on mnemonic and args */
_opcode get_opcode (_instr_st instr_st,_status* status);
/* */ 
void assemble_to_flat_bin(FILE* asm_file_post_pro , char* output_bin_file_path,_status* status );


#endif // _PARSER_H_