#ifndef _DEC_H_
#define _DEC_H_

#include <stdio.h>

// Mapped to one-byte opcode map (DEC general register)
void DEC_eAX(void);
void DEC_eCX(void);
void DEC_eDX(void);
void DEC_eBX(void);
void DEC_eSP(void);
void DEC_eBP(void);
void DEC_eSI(void);
void DEC_eDI(void);
// Mapped to ModRM opcode  map
void ModRM_DEC_Eb(void);
void DEC_Eb (void);
void DEC_Ev (void);
#endif // _DEC_H_