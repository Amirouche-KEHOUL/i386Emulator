#include "OR.h"
// Mapped to one-byte opcode map
void OR_EbGb(void)
{
    printf("OR operation called correctly \n");
}

void OR_EvGv(void)
{
    printf("OR operation called correctly \n");
}

void OR_GbEb(void)
{
    printf("OR operation called correctly \n");
}

void OR_GvEv(void)
{
    printf("OR operation called correctly \n");
}

void OR_ALIb(void)
{
    printf("OR operation called correctly \n");
}

void OR_eAXIv(void)
{
    printf("OR operation called correctly \n");
}

// Mapped to ModRM opcode  map

void OR_EbIb(void)
{
    printf("OR operation called correctly \n");
}

void OR_EvIv(void)
{
    printf("OR operation called correctly \n");
}

void ModRM_OR(void)
{
    // TODO: confirm which function to be called (2 functions above) based on the previous byte (opcode byte #0)
    printf("OR operation called correctly \n");
}