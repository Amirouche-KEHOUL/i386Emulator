#ifndef _SYS_H_
#define _SYS_H_

#include "../pins/pins.h"
#include "../status/status.h"

typedef struct sys_cond_st
{
    int unit_faulty : 1;
} _sys_cond_st;

#define _SYS_FAULTY 1
#define _SYS_NOT_FAULTY 0
#define _SYS_SELF_TEST_REQUEST 1
#define _SYS_SELF_TEST_NOT_REQUEST 0

int sys_is_selftest_req(const _pins *pins);
int sys_isfaulty(const _sys_cond_st *sys_cond_st);

#endif // _SYS_H_