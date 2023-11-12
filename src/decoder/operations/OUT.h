#ifndef _OUT_H_
#define _OUT_H_

#include <stdio.h>

// Mapped to one-byte opcode map
void OUT_IbAL(void);
void OUT_IbeAX(void);
void OUT_DXAL(void);
void OUT_DXeAX(void);

#endif // _OUT_H_