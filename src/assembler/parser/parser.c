#include "parser.h"

_line_st get_line (FILE* asm_file_post_pro, _status* status )
{
    // Check arguments
    if (asm_file_post_pro == NULL )
    {
        *status = _ERR_PARSER_NULL_POINTER_ARG;
        err_handler(status,"");
    }
    
    static unsigned int line_num_record ; // keep track on the line number for debugging information for example
    
    // Get the raw line 
    _line_st line_st;
    line_st.line=(char*)malloc(_INSTRUCTION_MAX_LENGTH);

        // check if end of file is reached 
    int i = 0;
    while((line_st.line[i] = getc(asm_file_post_pro)) != '\n' && line_st.line[i] != EOF) i++;
    
    // Signal to status that EOF is reached
    if (line_st.line[i] == EOF)
    {
        *status = _STATUS_PARSER_EOF_REACHED;
    }
    line_st.line[i+1]='\0'; //terminate the string
    
    line_num_record++; 
    line_st.line_number=line_num_record;
    return line_st;
}

_instr_st get_instruction(_line_st line_st , _status* status)
{
    _instr_st instruction;
    instruction.mnem = (char*) malloc(_INSTRUCTION_MNEM_MAX_LENGTH);
    instruction.args = (char*) malloc (_INSTRUCTION_ARGS_MAX_LENGTH);
    instruction.mnem[0] = '\0';
    instruction.args[0] = '\0';
    instruction.line_number = line_st.line_number;

    // If end of file is reached retrun empty instruction.
    if (*status == _STATUS_PARSER_EOF_REACHED) return instruction;

    // First get mnemonic    
    int i_line = 0;
    while ((instruction.mnem[i_line]=line_st.line[i_line]) != '\n' && line_st.line[i_line] != ' ') i_line++;
    instruction.mnem[i_line] = '\0'; // Replace \n char in mnem by \0
    if (line_st.line[i_line] == '\n') // If no args 
    {
        free(line_st.line); // free memory allocated in get_line()
        return instruction; // return "MNEM\0" + "\0" for args
    }
    
    // In case args exists
    i_line++; // setp up the space btw mnem and args
    int i_args = 0;
    while (line_st.line[i_line]!='\n')
    {   
        instruction.args[i_args]=line_st.line[i_line];
        if (line_st.line[i_line] == ',') instruction.args[i_args]='_';
        i_line++;
        i_args++;
    }

    instruction.args[i_args]='\0'; 
    free(line_st.line); // free memory allocated in get_line()
    return instruction; // retrun "MMEN\0" + "ARGS\0"
}

_opcode get_opcode (_instr_st instr_st,_status* status)
{   
    // Check if mnemonic + args exists otherwise call err_handler without exiting the program : we want to give back control in order to printout debug information for example line number ...
    char* mnem = instr_st.mnem;
    char* args = instr_st.args;


    if (!strcmp(mnem,"ADD"))
    {
        if (!strcmp(args,"Eb_Gb")) {free(instr_st.mnem);free(instr_st.args);return _ADD_Eb_Gb_OPCODE;}
        if (!strcmp(args,"EV_Gv")) {free(instr_st.mnem);free(instr_st.args);return _ADD_EV_Gv_OPCODE;}
        if (!strcmp(args,"Gb_Eb")) {free(instr_st.mnem);free(instr_st.args);return _ADD_Gb_Eb_OPCODE;}
        if (!strcmp(args,"Gv_Ev")) {free(instr_st.mnem);free(instr_st.args);return _ADD_Gv_Ev_OPCODE;}
        if (!strcmp(args,"AL_Ib")) {free(instr_st.mnem);free(instr_st.args);return _ADD_AL_Ib_OPCODE;}
        if (!strcmp(args,"eAX_Iv")) {free(instr_st.mnem);free(instr_st.args);return _ADD_AL_Ib_OPCODE;}

        *status = _ERR_PARSER_UNKNOWN_ARGS;
        printf("In line number %d\n",instr_st.line_number);
        err_handler(status,args);
        return 1;
    }        
     
    *status = _ERR_PARSER_UNKNOWN_MNEMONIC;
    err_handler(status,mnem);    
    return 1;     
}

void assemble_to_flat_bin(FILE* asm_file_post_pro , char* output_bin_file_path,_status* status )
{
    FILE* output_bin_file = fopen(output_bin_file_path,"wb");
    _opcode opcode; 
    while ( *status != _STATUS_PARSER_EOF_REACHED )
    {
        opcode = get_opcode(get_instruction(get_line(asm_file_post_pro,status),status),status);
        fwrite(&opcode, sizeof(char),1,output_bin_file);
    }    
}
