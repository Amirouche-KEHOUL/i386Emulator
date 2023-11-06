#ifndef _POP_H_
#define _POP_H_
#include <stdio.h>

// Mapped to one-byte opcode map
void POP_ES(void);
void POP_SS(void);
void POP_DS(void);
void POP_Ev(void);

// POP general register)
void POP_eAX(void);
void POP_eCX(void);
void POP_eDX(void);
void POP_eBX(void);
void POP_eSP(void);
void POP_eBP(void);
void POP_eSI(void);
void POP_eDI(void);

// Mapped to two-byte opcode map
void POP_FS(void);
void POP_GS(void);

#endif // _POP_H_