#ifndef _SYS_H_
#define _SYS_H_

#include <stddef.h>
#include <stdio.h>
#include "../typedefs.h"
#include "../pins/pins.h"
#include "../status/status.h"
#include "../memory/ram.h"
#include "../memory/registers.h"

extern _sys_cond_st sys_cond_st;
extern int status;

extern _pins pins;
extern _ram_ptr ram_ptr;
extern _general_regs_st gen_regs_st;
extern _segment_regs_st seg_regs_st;
extern _eflag_reg_st eflag_reg_st;
extern _eip_st eip_st;
extern _idtr_st idtr_st;
extern _cr0_reg_st cr0_reg_st;

#define _SYS_FAULTY 1
#define _SYS_NOT_FAULTY 0
#define _SYS_SELF_TEST_REQUEST 1
#define _SYS_SELF_TEST_NOT_REQUEST 0

int sys_is_selftest_req(void);
int sys_isfaulty(const _sys_cond_st *sys_cond_st);
void sys_init(void);
void sys_shutdown(void);

#endif // _SYS_H_