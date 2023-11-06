#include "XOR.h"
// Mapped to one-byte opcode map
void XOR_EbGb(void)
{
    printf("XOR operation called correctly \n");
}

void XOR_EvGv(void)
{
    printf("XOR operation called correctly \n");
}

void XOR_GbEb(void)
{
    printf("XOR operation called correctly \n");
}

void XOR_GvEv(void)
{
    printf("XOR operation called correctly \n");
}

void XOR_ALIb(void)
{
    printf("XOR operation called correctly \n");
}

void XOR_eAXIv(void)
{
    printf("XOR operation called correctly \n");
}

// Mapped to ModRM opcode  map

void XOR_EbIb(void)
{
    printf("XOR operation called correctly \n");
}

void XOR_EvIv(void)
{
    printf("XOR operation called correctly \n");
}

void ModRM_XOR(void)
{
    // TODO: confirm which function to be called (2 functions above) based on the previous byte (opcode byte #0)
    printf("XOR operation called correctly \n");
}