#include "AND.h"
// Mapped to one-byte opcode map
void AND_EbGb(void)
{
    printf("AND operation called correctly \n");
}

void AND_EvGv(void)
{
    printf("AND operation called correctly \n");
}

void AND_GbEb(void)
{
    printf("AND operation called correctly \n");
}

void AND_GvEv(void)
{
    printf("AND operation called correctly \n");
}

void AND_ALIb(void)
{
    printf("AND operation called correctly \n");
}

void AND_eAXIv(void)
{
    printf("AND operation called correctly \n");
}

// Mapped to ModRM opcode  map

void AND_EbIb(void)
{
    printf("AND operation called correctly \n");
}

void AND_EvIv(void)
{
    printf("AND operation called correctly \n");
}

void ModRM_AND(void)
{
    // TODO: confirm which function to be called (2 functions above) based on the previous byte (opcode byte #0)
    printf("AND operation called correctly \n");
}