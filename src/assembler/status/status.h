#ifndef _STATUS_H
#define _STATUS_H

#include <stdio.h>

typedef int _status ; 

/* _STATUS */
#define _STATUS_OK 0

#define _STATUS_NO_FILE 1 
#define _ERR_OPEN_ASM_FILE_NOK -1


void err_print (_status* status);
void err_handler(_status* status,char* message);

#endif //_STATUS_H