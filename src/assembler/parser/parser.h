#ifndef _PARSER_H_
#define _PARSER_H_
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include "../status/status.h"


/* Configuration */
#define _INSTRUCTION_MAX_LENGTH 255
#define _TOKEN_ARRAY_MAX_LENGTH 50
#define _TOKEN_MAX_LENGTH 50

# define _SINGLE_CHAR_TOKENS "*-+.,;:()[]\"" // Put here the list of single character tokens. 

typedef struct line_st
{
    char *line;
    unsigned int line_number;
    char *file_name;
} _line_st;

typedef char* _token;

typedef struct tokens_st
{    
    _token* tokens;
    unsigned int line_number;
    char *file_name;
}_tokens_st;

/* Returns a stream of line from an input file and ignores comments. */
_line_st* get_line(FILE *asm_file_post_pro, _status *status); // /!\ LINES IN asm_file_post_pro ARG MUST BE TERMINATED WITH A LINE-FEED CHARACTER (0x0A)

/* Returns an array of tokens */
_tokens_st* line_2_tokens(_line_st* line_st, _status *status);
#endif // _PARSER_H_