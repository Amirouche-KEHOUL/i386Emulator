#ifndef _INC_H_
#define _INC_H_

#include <stdio.h>

// Mapped to one-byte opcode map (INC general register)
void INC_eAX(void);
void INC_eCX(void);
void INC_eDX(void);
void INC_eBX(void);
void INC_eSP(void);
void INC_eBP(void);
void INC_eSI(void);
void INC_eDI(void);
// Mapped to ModRM opcode  map
void ModRM_INC_Eb(void);
#endif // _INC_H_