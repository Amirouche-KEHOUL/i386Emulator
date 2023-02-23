#include <stdio.h>
#include <unistd.h> 
#include <limits.h>
#include "status/status.h"
#include "config.h"
#include "parser/parser.h"

_status status = _STATUS_OK; // status = 0 : OK, > 0: warnig, < 0: error.

int str_length(char str[]) 
{
    int count; 
    for (count = 0; str[count] != '\0'; ++count);
    return count; 
}

int main (int argc, char** argv)
{
    printf("----------| Start i386asm |----------\n");

    // Check args
    if (argv[1] == NULL)
    {
        status = _STATUS_NO_FILE;
        err_handler(&status,"");
    }


    /* Open asm_file file */
    FILE* asm_file; 
    //TODO: check if file is binary, else exit emulator.
    char* asm_file_name = argv[1];
    char device_path[PATH_MAX]; 
        // Construct full path and open the asm_file file
    if (getcwd(device_path, sizeof(device_path)) != NULL) // Current Working Directory
    {
        for (int i = 0 ; i < PATH_MAX - _CONF_MAX_LEN_DEVICE_NAME ; i++)
        {
            if (device_path[i] == 0 )
            {   
                device_path[i] ='/';
                i++;
                int j;
                for(j = 0 ; j < str_length(asm_file_name) ;j++ )
                {
                    device_path[i+j] = asm_file_name[j];
                }
                device_path[i+j]='\0';
                break; 
            }
        }   
        asm_file = fopen(device_path,"r"); 
        if (asm_file == NULL)
        {
            status = _ERR_OPEN_ASM_FILE_NOK;
            err_handler(&status,asm_file_name);
        }
    } else // If getcwd fails
    {
        status = _ERR_OPEN_ASM_FILE_NOK;
        err_handler(&status,asm_file_name);
    }

    _instr_st instruction; 
    
    instruction.mnem = "XOR";
    instruction.args = "Ev_Gv";


    printf("The opcode corresponding to %s %s is 0x%x\n",instruction.mnem,instruction.args,get_opcode(&instruction,&status));

    // Test
    /*
    int ret;
    while (1)
    {   ret = getc(asm_file);
        if (ret == EOF) break;        
        printf("%c",ret);
    }
    */ 
   

    printf("----------| Exit i386asm |----------\n");
    return 0;
}