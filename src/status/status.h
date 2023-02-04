#ifndef _STATUS_H
#define _STATUS_H

#include <stdio.h>

typedef int _status; 

/* STATUS */
#define STATUS_END_OF_RESET 1
#define STATUS_OK 0

/* ERRORS */
#define ERR_RAM_ADDR_OUTRANGE -1  
#define ERR_RAM_MALLOC -2  
#define ERR_RAM_NULL_POINTER -3 
#define ERR_REG_NULL_POINTER -4
#define ERR_PIN_NULL_POINTER -5
#define ERR_SYS_NULL_POINTER -6
#define ERR_REG_INIT -7


void err_print (_status* status);
void err_handler(_status* status);

#endif //_STATUS_H