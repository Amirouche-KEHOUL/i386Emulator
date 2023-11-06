#include "CMP.h"
// Mapped to one-byte opcode map
void CMP_EbGb(void)
{
    printf("CMP operation called correctly \n");
}

void CMP_EvGv(void)
{
    printf("CMP operation called correctly \n");
}

void CMP_GbEb(void)
{
    printf("CMP operation called correctly \n");
}

void CMP_GvEv(void)
{
    printf("CMP operation called correctly \n");
}

void CMP_ALIb(void)
{
    printf("CMP operation called correctly \n");
}

void CMP_eAXIv(void)
{
    printf("CMP operation called correctly \n");
}

// Mapped to ModRM opcode  map

void CMP_EbIb(void)
{
    printf("CMP operation called correctly \n");
}

void CMP_EvIv(void)
{
    printf("CMP operation called correctly \n");
}

void ModRM_CMP(void)
{
    // TODO: confirm which function to be called (2 functions above) based on the previous byte (opcode byte #0)
    printf("CMP operation called correctly \n");
}