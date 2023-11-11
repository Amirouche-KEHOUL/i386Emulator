#ifndef _XCHG_H_
#define _XCHG_H_

#include <stdio.h>

// Mapped to one-byte opcode map
void XCHG_eCX(void);
void XCHG_eDX(void);
void XCHG_eBX(void);
void XCHG_eSP(void);
void XCHG_eBP(void);
void XCHG_eSI(void);
void XCHG_eDI(void);

#endif // _XCHG_H_