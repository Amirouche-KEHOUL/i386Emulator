#include "SUB.h"
// Mapped to one-byte opcode map
void SUB_EbGb(void)
{
    printf("SUB operation called correctly \n");
}

void SUB_EvGv(void)
{
    printf("SUB operation called correctly \n");
}

void SUB_GbEb(void)
{
    printf("SUB operation called correctly \n");
}

void SUB_GvEv(void)
{
    printf("SUB operation called correctly \n");
}

void SUB_ALIb(void)
{
    printf("SUB operation called correctly \n");
}

void SUB_eAXIv(void)
{
    printf("SUB operation called correctly \n");
}

// Mapped to ModRM opcode  map

void SUB_EbIb(void)
{
    printf("SUB operation called correctly \n");
}

void SUB_EvIv(void)
{
    printf("SUB operation called correctly \n");
}

void ModRM_SUB(void)
{
    // TODO: confirm which function to be called (2 functions above) based on the previous byte (opcode byte #0)
    printf("SUB operation called correctly \n");
}