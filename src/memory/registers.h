#ifndef _REGISTERS_H_
#define _REGISTERS_H_

#include "../typedefs.h"
#include "../pins/pins.h"
#include "../status/status.h"
#include "../config.h"
#include "../sys/sys.h"

void init_idtr_reg(void);
void init_seg_reg(void);
void init_eip_reg(void);
void init_gen_reg(void);
void init_eflags_reg(void);
void init_cr0_reg(void);
void init_dtr_regs(void);

_16_reg get_BX(void);
_32_reg get_EAX(void);
_32_reg get_ECX(void);
_32_reg get_EDX(void);
_32_reg get_EBX(void);
_32_reg get_ESI(void);
_32_reg get_EDI(void);
_32_reg get_EBP(void);
_32_reg get_EIP(void);

#endif //_REGISTERS_H_