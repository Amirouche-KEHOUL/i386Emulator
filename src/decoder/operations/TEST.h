#ifndef _TEST_H_
#define _TEST_H_

#include <stdio.h>

// Mapped to one-byte opcode map
void TEST_EbGb(void);
void TEST_EvGv(void);
void TEST_ALIb(void);
void TEST_eAXIv(void);

// Mapped to ModRM opcode map
void ModRM_TEST(void);
void TEST_Eb(void);
void TEST_Ev(void);

void TEST_EbIb(void);
void TEST_EvIv(void);
#endif // _TEST_H_