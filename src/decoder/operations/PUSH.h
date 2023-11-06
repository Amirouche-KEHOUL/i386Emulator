#ifndef _PUSH_H_
#define _PUSH_H_
#include <stdio.h>

// Mapped to one-byte opcode map
void PUSH_ES(void);
void PUSH_CS(void);
void PUSH_SS(void);
void PUSH_DS(void);
void PUSH_Ib(void); // Mapped 2 times

// PUSH general register)
void PUSH_eAX(void);
void PUSH_eCX(void);
void PUSH_eDX(void);
void PUSH_eBX(void);
void PUSH_eSP(void);
void PUSH_eBP(void);
void PUSH_eSI(void);
void PUSH_eDI(void);

// Mapped to two-byte opcode map
void PUSH_FS(void);
void PUSH_GS(void);

// Mapped to ModRM opcode  map
void PUSH_Ev(void);
#endif // _PUSH_H_