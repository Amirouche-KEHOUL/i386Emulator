#include "parser.h"

_opcode get_opcode (_instr_st* instr_st,_status* status)
{   
    // Check arguments
    if (instr_st->mnem == NULL | instr_st->args == NULL)
    {
        *status = _ERR_PARSER_NULL_POINTER_ARG;
        err_handler(status,"");
    }
    // TODO : finish the mapping
    // TODO : confirm the meaning of =CS , =ES ...
    // Check if mnemonic + args exists otherwise call err_handler without exiting the program : we want to give back control in order to printout debug information for example line number ...

    if (!strcmp(instr_st->mnem,"ADD")){if (!strcmp(instr_st->args,"Eb_Gb")) return 0x00; if (!strcmp(instr_st->args,"Ev_Gv")) return 0x01; if (!strcmp(instr_st->args,"Gb_Eb")) return 0x02;if (!strcmp(instr_st->args,"Gv_Ev")) return 0x03;if (!strcmp(instr_st->args,"AL_Ib")) return 0x04;if (!strcmp(instr_st->args, "eAX_Iv")) return 0x05;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args);return 1;}
    if (!strcmp(instr_st->mnem,"PUSH")){if (!strcmp(instr_st->args, "ES")) return 0x06;if (!strcmp(instr_st->args, "CS")) return 0x0E;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args);return 1;}
    if (!strcmp(instr_st->mnem,"POP")){if (!strcmp(instr_st->args, "ES")) return 0x07;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args); return 1;}
    if (!strcmp(instr_st->mnem,"OR")){if (!strcmp(instr_st->args, "Eb_Gb")) return 0x08; if (!strcmp(instr_st->args, "Ev_Gv")) return 0x09; if (!strcmp(instr_st->args, "Gb_Eb")) return 0x0A;if (!strcmp(instr_st->args, "Gv_Ev")) return 0x0B;if (!strcmp(instr_st->args, "AL_Ib")) return 0x0C;if (!strcmp(instr_st->args, "eAX_Iv")) return 0x0D;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args);return 1;}

    if (!strcmp(instr_st->mnem,"ADC")){if (!strcmp(instr_st->args,"Eb_Gb")) return 0x10; if (!strcmp(instr_st->args,"Ev_Gv")) return 0x11; if (!strcmp(instr_st->args,"Gb_Eb")) return 0x12;if (!strcmp(instr_st->args,"Gv_Ev")) return 0x13;if (!strcmp(instr_st->args,"AL_Ib")) return 0x14;if (!strcmp(instr_st->args, "eAX_Iv")) return 0x15;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args);return 1;}
    if (!strcmp(instr_st->mnem,"PUSH")){if (!strcmp(instr_st->args, "SS")) return 0x16;if (!strcmp(instr_st->args, "DS")) return 0x1E;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args);return 1;}
    if (!strcmp(instr_st->mnem,"POP")){if (!strcmp(instr_st->args, "SS")) return 0x17;if (!strcmp(instr_st->args, "DS")) return 0x1F;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args); return 1;}
    if (!strcmp(instr_st->mnem,"SBB")){if (!strcmp(instr_st->args, "Eb_Gb")) return 0x18; if (!strcmp(instr_st->args, "Ev_Gv")) return 0x19; if (!strcmp(instr_st->args, "Gb_Eb")) return 0x1A;if (!strcmp(instr_st->args, "Gv_Ev")) return 0x1B;if (!strcmp(instr_st->args, "AL_Ib")) return 0x1C;if (!strcmp(instr_st->args, "eAX_Iv")) return 0x1D;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args);return 1;}

    if (!strcmp(instr_st->mnem,"AND")){if (!strcmp(instr_st->args,"Eb_Gb")) return 0x20; if (!strcmp(instr_st->args,"Ev_Gv")) return 0x21; if (!strcmp(instr_st->args,"Gb_Eb")) return 0x22;if (!strcmp(instr_st->args,"Gv_Ev")) return 0x23;if (!strcmp(instr_st->args,"AL_Ib")) return 0x24;if (!strcmp(instr_st->args, "eAX_Iv")) return 0x25;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args);return 1;}
    if (!strcmp(instr_st->mnem,"SEG")){if (!strcmp(instr_st->args, "=ES")) return 0x26;if (!strcmp(instr_st->args, "=CS")) return 0x2E;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args);return 1;}
    if (!strcmp(instr_st->mnem,"DAA")){if (!strcmp(instr_st->args, "")) return 0x27;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args); return 1;}
    if (!strcmp(instr_st->mnem,"SUB")){if (!strcmp(instr_st->args, "Eb_Gb")) return 0x28; if (!strcmp(instr_st->args, "Ev_Gv")) return 0x29; if (!strcmp(instr_st->args, "Gb_Eb")) return 0x2A;if (!strcmp(instr_st->args, "Gv_Ev")) return 0x2B;if (!strcmp(instr_st->args, "AL_Ib")) return 0x2C;if (!strcmp(instr_st->args, "eAX_Iv")) return 0x2D;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args);return 1;}
    if (!strcmp(instr_st->mnem,"DAS")){if (!strcmp(instr_st->args, "")) return 0x2F;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args);return 1;}

    if (!strcmp(instr_st->mnem,"XOR")){if (!strcmp(instr_st->args,"Eb_Gb")) return 0x30; if (!strcmp(instr_st->args,"Ev_Gv")) return 0x31; if (!strcmp(instr_st->args,"Gb_Eb")) return 0x32;if (!strcmp(instr_st->args,"Gv_Ev")) return 0x33;if (!strcmp(instr_st->args,"AL_Ib")) return 0x34;if (!strcmp(instr_st->args, "eAX_Iv")) return 0x35;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args);return 1;}
    if (!strcmp(instr_st->mnem,"SEG")){if (!strcmp(instr_st->args, "=SS")) return 0x36;if (!strcmp(instr_st->args, "=CS")) return 0x3E;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args);return 1;}
    if (!strcmp(instr_st->mnem,"AAA")){if (!strcmp(instr_st->args, "")) return 0x37;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args); return 1;}
    if (!strcmp(instr_st->mnem,"CMP")){if (!strcmp(instr_st->args, "Eb_Gb")) return 0x38; if (!strcmp(instr_st->args, "Ev_Gv")) return 0x39; if (!strcmp(instr_st->args, "Gb_Eb")) return 0x3A;if (!strcmp(instr_st->args, "Gv_Ev")) return 0x3B;if (!strcmp(instr_st->args, "AL_Ib")) return 0x3C;if (!strcmp(instr_st->args, "eAX_Iv")) return 0x3D;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args);return 1;}
    if (!strcmp(instr_st->mnem,"AAS")){if (!strcmp(instr_st->args, "")) return 0x3F;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args);return 1;}

    if (!strcmp(instr_st->mnem,"INC")){if (!strcmp(instr_st->args,"eAX")) return 0x40; if (!strcmp(instr_st->args,"eCX")) return 0x41; if (!strcmp(instr_st->args,"eDX")) return 0x42;if (!strcmp(instr_st->args,"eBX")) return 0x43;if (!strcmp(instr_st->args,"eSP")) return 0x44;if (!strcmp(instr_st->args, "eBP")) return 0x45;if (!strcmp(instr_st->args, "eSI")) return 0x46;if (!strcmp(instr_st->args, "eDI")) return 0x47;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args);return 1;}
    if (!strcmp(instr_st->mnem,"DEC")){if (!strcmp(instr_st->args,"eAX")) return 0x40; if (!strcmp(instr_st->args,"eCX")) return 0x41; if (!strcmp(instr_st->args,"eDX")) return 0x42;if (!strcmp(instr_st->args,"eBX")) return 0x43;if (!strcmp(instr_st->args,"eSP")) return 0x44;if (!strcmp(instr_st->args, "eBP")) return 0x45;if (!strcmp(instr_st->args, "eSI")) return 0x46;if (!strcmp(instr_st->args, "eDI")) return 0x47;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args);return 1;}


    if (!strcmp(instr_st->mnem,"PUSH")){if (!strcmp(instr_st->args,"eAX")) return 0x50; if (!strcmp(instr_st->args,"eCX")) return 0x51; if (!strcmp(instr_st->args,"eDX")) return 0x52;if (!strcmp(instr_st->args,"eBX")) return 0x53;if (!strcmp(instr_st->args,"eSP")) return 0x54;if (!strcmp(instr_st->args, "eBP")) return 0x55;if (!strcmp(instr_st->args, "eSI")) return 0x56;if (!strcmp(instr_st->args, "eDI")) return 0x57;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args);return 1;}
    if (!strcmp(instr_st->mnem,"POP")){if (!strcmp(instr_st->args,"eAX")) return 0x50; if (!strcmp(instr_st->args,"eCX")) return 0x51; if (!strcmp(instr_st->args,"eDX")) return 0x52;if (!strcmp(instr_st->args,"eBX")) return 0x53;if (!strcmp(instr_st->args,"eSP")) return 0x54;if (!strcmp(instr_st->args, "eBP")) return 0x55;if (!strcmp(instr_st->args, "eSI")) return 0x56;if (!strcmp(instr_st->args, "eDI")) return 0x57;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args);return 1;}


    if (!strcmp(instr_st->mnem,"PUSHA")){if (!strcmp(instr_st->args, "")) return 0x60;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args); return 1;}
    if (!strcmp(instr_st->mnem,"POPA")){if (!strcmp(instr_st->args, "")) return 0x61;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args); return 1;}
    if (!strcmp(instr_st->mnem,"BOUND")){if (!strcmp(instr_st->args, "Gv_Ma")) return 0x62;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args); return 1;}
    if (!strcmp(instr_st->mnem,"ARPL")){if (!strcmp(instr_st->args, "Ew_Rw")) return 0x63;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args); return 1;}
    if (!strcmp(instr_st->mnem,"SEG")){if (!strcmp(instr_st->args, "=FS")) return 0x64;if (!strcmp(instr_st->args, "=GS")) return 0x65;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args); return 1;}
    if (!strcmp(instr_st->mnem,"Operand")){if (!strcmp(instr_st->args, "size")) return 0x66;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args); return 1;}
    if (!strcmp(instr_st->mnem,"Addresse")){if (!strcmp(instr_st->args, "size")) return 0x67;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args); return 1;}
    if (!strcmp(instr_st->mnem,"PUSH")){if (!strcmp(instr_st->args, "Ib")) return 0x68;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args); return 1;}
    if (!strcmp(instr_st->mnem,"IMUL")){if (!strcmp(instr_st->args, "GvEvIv")) return 0x69;*status =_ERR_PARSER_UNKNOWN_ARGS;err_handler(status,instr_st->args); return 1;}

    // In case mnemonic not found
    *status = _ERR_PARSER_UNKNOWN_MNEMONIC;
    err_handler(status,instr_st->mnem);
    return 1;
}