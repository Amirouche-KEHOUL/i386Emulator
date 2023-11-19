#ifndef _XCHG_H_
#define _XCHG_H_

#include <stdio.h>

// Mapped to one-byte opcode map
void XCHG_eCXeAX(void);
void XCHG_eDXeAX(void);
void XCHG_eBXeAX(void);
void XCHG_eBXeAX(void);
void XCHG_eBPeAX(void);
void XCHG_eSIeAX(void);
void XCHG_eDIeAX(void);

#endif // _XCHG_H_