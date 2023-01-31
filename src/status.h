#ifndef _STATUS_
#define _STATUS_

#include <stdio.h>

/*If err, function must set status variable before exiting*/
typedef int _status; 


#define OK 0
#define ERR_RAM_ADDR_OUTRANGE -1  
#define ERR_RAM_MALLOC -2  
#define ERR_RAM_NULL_POINTER -3 
#define ERR_REG_NULL_POINTER -4


void err_print (_status* status);


#endif //_STATUS__