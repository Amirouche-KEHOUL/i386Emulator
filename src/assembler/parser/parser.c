#include "parser.h"

#define SPACE_CHAR ' '
#define LINEFEED_CHAR 0x0A

_line_st* get_line (FILE* asm_file_post_pro, _status* status )
{
    /* Check arguments */
    if (asm_file_post_pro == NULL )
    {
        *status = _ERR_PARSER_NULL_POINTER_ARG;
        err_handler(status,"");
    }
    
    static unsigned int line_num_record ; // keep track on the line number for debugging information for example
    _line_st* line_st  = (_line_st*) malloc(sizeof(_line_st));
    line_st->line = (char*) malloc(_INSTRUCTION_MAX_LENGTH);   

    int index = 0;    
    while (1)
    {
        while((line_st->line[index] = getc(asm_file_post_pro)) != '\n' && line_st->line[index] != EOF && line_st->line[index] != ';' ) index++;
        if (line_st->line[index] == '\n') break; //Break while(1);
        if (line_st->line[index] == EOF) 
        {
            *status = _STATUS_PARSER_EOF_REACHED; // Signal to status that EOF is reached
            break; // Break while(1)
        }
        if (line_st->line[index] == ';') 
        {
            while((line_st->line[index] = getc(asm_file_post_pro)) != '\n' && line_st->line[index] != EOF );
            break;
        }
    }    
   
    line_st->line[index+1]='\0';  //terminate the string by (space)+(\0)    
    line_st->line_number=line_num_record;
    line_num_record++; 

    return line_st;
}



_token* line_2_tokens(_line_st* line_st, _status *status)
{
    /* Check arguments */
    if (line_st == NULL )
    {
        *status = _ERR_PARSER_NULL_POINTER_ARG;
        err_handler(status,"\"line_2_tokens()\" function");
    }

    /* Token array structure: used to store found tokens in line_st  
            +------------+
            | token_array|
            +------------+
            |            |
            |  _token    |
            |  +------+  |
            |  |char* |--|----> [0]---->[_][_][_][_][_][_][_][_][_][_]
            |  +------+  |      [1]---->[_][_][_][_][_][_][_][_][_][_]
            |            |       ...
            |  _token    |       [max-1]->[_][_][_][_][_][_][_][_][_][_]
            |  +------+  |
            |  |char* |--|----> [0]---->[_][_][_][_][_][_][_][_][_][_]
            |  +------+  |      [1]---->[_][_][_][_][_][_][_][_][_][_]
            |    ...     |       ...
            |            |
            +------------+
    */
    _token* token_array = (_token*) malloc(_TOKEN_ARRAY_MAX_LENGTH*sizeof(_token));
    for(int i= 0 ; i < _TOKEN_MAX_LENGTH;i++ )
    {
        token_array[i]=(_token)malloc(_TOKEN_MAX_LENGTH*sizeof(char));
    }

    /* Init single_token_array : used to recognize then in line_st */
    char* single_token_array = _SINGLE_CHAR_TOKENS;
   
    int token_flag = 0; // set to 1 to start acquiring token.   
    int line_index = 0;
    int token_index = 0;
    int token_char_index = 0;
     
    char character;    
    while (((character = line_st->line[line_index]) !='\0') && ((character = line_st->line[line_index]) != LINEFEED_CHAR))
    {
        int index = 0;
        for ( index = 0 ;(single_token_array[index]!='\0') && (single_token_array[index]!=character) ;index++ ); // Search for single char tokens : stop the loop if char == single token list or reached it end
        if (single_token_array[index]!= '\0') // If true, it means that a single token correspondence has been found
        {
            if(token_char_index > 0 ) 
            {
                *(token_array[token_index]+token_char_index)='\0';
                token_char_index = 0;
                token_index++;
            }
            *token_array[token_index] = single_token_array[index];
            *token_array[token_index+1] = '\0'; // Terminate the string.
            
            token_index++;
            line_index++;
            continue;
        }
        if(character != SPACE_CHAR)
        {
           *(token_array[token_index]+token_char_index)=character;
            token_char_index++;
            line_index++;
            continue;
        }
        if((character == SPACE_CHAR) &&  (token_char_index > 0) )
        {
            *(token_array[token_index]+token_char_index)='\0';
            token_char_index = 0;
            token_index++;
            line_index++;    
            continue;        
        }   
        if(character == SPACE_CHAR &&  token_char_index == 0 )
        {
            line_index++;
            continue;
        }
    }

    /*terminates the array by a null elements */
    if (token_char_index == 0) token_array[token_index]=NULL;
    if (token_char_index > 0 ) token_array[token_index+1]=NULL;// handle case ABCD\0   

    //free(line_st); //TODO: kept in comment for test purpose. Uncomment to prevent memory leaks
    return token_array;
}