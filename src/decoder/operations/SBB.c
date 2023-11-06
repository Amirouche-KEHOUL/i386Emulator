#include "SBB.h"
// Mapped to one-byte opcode map
void SBB_EbGb(void)
{
    printf("SBB operation called correctly \n");
}

void SBB_EvGv(void)
{
    printf("SBB operation called correctly \n");
}

void SBB_GbEb(void)
{
    printf("SBB operation called correctly \n");
}

void SBB_GvEv(void)
{
    printf("SBB operation called correctly \n");
}

void SBB_ALIb(void)
{
    printf("SBB operation called correctly \n");
}

void SBB_eAXIv(void)
{
    printf("SBB operation called correctly \n");
}

// Mapped to ModRM opcode  map

void SBB_EbIb(void)
{
    printf("SBB operation called correctly \n");
}

void SBB_EvIv(void)
{
    printf("SBB operation called correctly \n");
}

void ModRM_SBB(void)
{
    // TODO: confirm which function to be called (2 functions above) based on the previous byte (opcode byte #0)
    printf("SBB operation called correctly \n");
}