#ifndef _IMUL_H_
#define _IMUL_H_

#include <stdio.h>

// Mapped to one-byte opcode map
void IMUL_GvEvIv(void);
// Mapped to two-byte opcode map
void IMUL_GvEv(void);
// // Mapped to ModRM opcode  map
void ModRM_IMUL_ALeAX(void);

#endif // _IMUL_H_