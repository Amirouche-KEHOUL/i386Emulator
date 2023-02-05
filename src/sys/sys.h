#ifndef _SYS_H_
#define _SYS_H_
#include "../status/status.h"
#include "../pins/pins.h"

typedef struct  sys_cond_st
{
    int unit_faulty : 1 ;
} _sys_cond_st;

#define SYS_FAULTY 1 
#define SYS_NOT_FAULTY 0 

int sys_is_selftest_req (_pins* pins,_status* status);
int sys_isfaulty (_sys_cond_st* sys_cond_st, _status* status);

#endif // _SYS_H_