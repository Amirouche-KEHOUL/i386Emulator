#ifndef _CALL_H_
#define _CALL_H_

#include <stdio.h>

// Mapped to one-byte opcode map
void CALL_Ap(void);
void CALL_Av(void);

// Mapped to ModRM opcode map
void ModRM_CALL_Ev(void);
void ModRM_CALL_Ep(void);

void CALL_Ev (void);
void CALL_eP (void);
#endif // _CALL_H_