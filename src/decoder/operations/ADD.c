#include "ADD.h"
// Mapped to one-byte opcode map
void ADD_EbGb(void)
{
    printf("ADD operation called correctly \n");
}

void ADD_EvGv(void)
{
    printf("ADD operation called correctly \n");
}

void ADD_GbEb(void)
{
    printf("ADD operation called correctly \n");
}

void ADD_GvEv(void)
{
    printf("ADD operation called correctly \n");
}

void ADD_ALIb(void)
{
    printf("ADD operation called correctly \n");
}

void ADD_eAXIv(void)
{
    printf("ADD operation called correctly \n");
}

// Mapped to ModRM opcode  map

void ADD_EbIb(void)
{
    printf("ADD operation called correctly \n");
}

void ADD_EvIv(void)
{
    printf("ADD operation called correctly \n");
}

void ModRM_ADD(void)
{
    // TODO: confirm which function to be called (2 functions above) based on the previous byte (opcode byte #0)
    printf("ADD operation called correctly \n");
}