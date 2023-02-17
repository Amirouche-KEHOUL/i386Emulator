#ifndef _SYS_H_
#define _SYS_H_
#include "../status/status.h"
#include "../pins/pins.h"

typedef struct  sys_cond_st
{
    int unit_faulty : 1 ;
} _sys_cond_st;

#define _SYS_FAULTY 1 
#define _SYS_NOT_FAULTY 0 
#define _SYS_SELF_TEST_REQUEST 1 
#define _SYS_SELF_TEST_NOT_REQUEST 0 

int sys_is_selftest_req (_pins* pins,_status* status);
int sys_isfaulty (_sys_cond_st* sys_cond_st, _status* status);

#endif // _SYS_H_