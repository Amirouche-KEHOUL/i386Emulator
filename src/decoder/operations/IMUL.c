#include "IMUL.h"

// Mapped to one-byte opcode map
void IMUL_GvEvIv(void)
{
    printf("IMUL operation called correctly \n");
}
// Mapped to two-byte opcode map
void IMUL_GvEv(void)
{
    printf("IMUL operation called correctly \n");
}
// // Mapped to ModRM opcode  map
void ModRM_IMUL_ALeAX(void)
{
    printf("IMUL operation called correctly \n");
}
void IMUL_EbAL (void) {
    printf("IMUL_EbAL operation called correctly \n");
}

void IMUL_EveAL (void) {
    printf("IMUL_EveAL operation called correctly \n");
}
