#include "parser.h"

_line get_line (FILE* asm_file_post_pro, _status* status )
{
    // Check arguments
    if (asm_file_post_pro == NULL )
    {
        *status = _ERR_PARSER_NULL_POINTER_ARG;
        err_handler(status,"");
    }
    
    // Get the raw line 
    _line line = (_line) malloc(_INSTRUCTION_MAX_LENGTH);
        // check if end of file is reached 
    int i = 0;
    while((line[i] = getc(asm_file_post_pro)) != '\n' && line[i] != EOF) i++;
    // Signal to status that EOF is reached
    if (line[i] == EOF)
    {
        *status = _STATUS_PARSER_EOF_REACHED;
    }
    return line;
}

_instr_st get_instruction(_line line , _status* status)
{
    // Check arguments
    if (line == NULL )
    {
        *status = _ERR_PARSER_NULL_POINTER_ARG;
        err_handler(status,"");
    }

    _instr_st instruction;
    instruction.mnem = (char*) malloc(_INSTRUCTION_MNEM_MAX_LENGTH);
    instruction.args = (char*) malloc (_INSTRUCTION_ARGS_MAX_LENGTH);
    instruction.mnem[0] = ' ';
    instruction.args[0] = ' ';

    // If end of file is reached retrun empty instruction (space char).
    if (*status == _STATUS_PARSER_EOF_REACHED) return instruction;

    // First get mnemonic    
    int i_line = 0;
    while ((instruction.mnem[i_line]=line[i_line]) != '\n' && line[i_line] != ' ') i_line++;
   
    if (line[i_line] == '\n') // If only mnem found then return it with empty args (space char)
    {
        instruction.mnem[i_line] = '\0'; // Replace space char in mnem by \n 
        return instruction; 
    }
    
    // In case of existing args 
    instruction.mnem[i_line] = '\0'; // Replace space char in mnem by \n 
    i_line++; // setp up the space btw mnem and args
    int i_args = 0; 
    while (line[i_line]!='\n') 
    {   
        instruction.args[i_args]=line[i_line];
        if (line[i_line] == ',') instruction.args[i_args]='_';
        i_line++;
        i_args++;
    }
    instruction.args[i_args]='\0';
    return instruction;
}

_opcode get_opcode (_instr_st instr_st,_status* status)
{   
    // Check if mnemonic + args exists otherwise call err_handler without exiting the program : we want to give back control in order to printout debug information for example line number ...
    char* mnem = instr_st.mnem;
    char* args = instr_st.args;

    if (!strcmp(mnem,"ADD"))
    {
        if (!strcmp(args,"Eb_Gb")) return _ADD_Eb_Gb_OPCODE;
        if (!strcmp(args,"EV_Gv")) return _ADD_EV_Gv_OPCODE;
        if (!strcmp(args,"Gb_Eb")) return _ADD_Gb_Eb_OPCODE;
        if (!strcmp(args,"Gv_Ev")) return _ADD_Gv_Ev_OPCODE;
        if (!strcmp(args,"AL_Ib")) return _ADD_AL_Ib_OPCODE;
        if (!strcmp(args,"eAX_Iv")) return _ADD_AL_Ib_OPCODE;
        *status = _ERR_PARSER_UNKNOWN_ARGS;
        err_handler(status,args);
        return 1;
    }        
     
    *status = _ERR_PARSER_UNKNOWN_MNEMONIC;
    err_handler(status,mnem);    
    return 1;     
}

void assemble_to_flat_bin(FILE* asm_file_post_pro , char* output_bin_file_path,_status* status )
{
    FILE* output_bin_file;
    output_bin_file = fopen(output_bin_file_path,"w");
    char* opcode;
    while ( *status != _STATUS_PARSER_EOF_REACHED )
    {
        opcode[0] = get_opcode(get_instruction(get_line(asm_file_post_pro,status),status),status);
        fputs(opcode,output_bin_file);
    }
}
