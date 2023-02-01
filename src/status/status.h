#ifndef _STATUS_H
#define _STATUS_H

#include <stdio.h>

/*If err, function must set status variable before exiting*/
typedef int _status; 


#define STATUS_OK 0
#define ERR_RAM_ADDR_OUTRANGE -1  
#define ERR_RAM_MALLOC -2  
#define ERR_RAM_NULL_POINTER -3 
#define ERR_REG_NULL_POINTER -4
#define ERR_PIN_NULL_POINTER -5


void err_print (_status* status);


#endif //_STATUS_H