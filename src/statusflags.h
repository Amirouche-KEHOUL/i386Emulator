#ifndef _STATUSFLAGS_
#define _STATUSFLAGS_


/*If err, function must set status before exiting*/

typedef int _status; 

#define OK 0
#define ERR_RAM_ADDR_OUTRANGE -1  
#define ERR_RAM_MALLOC -2  
#define ERR_RAM_NULL_POINTER -3




#endif //STATUSFLAGS_