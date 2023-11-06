#include "PUSH.h"

// Mapped to one-byte opcode map
void PUSH_ES(void)
{
    printf("PUSH operation called correclty \n");
}
void PUSH_CS(void)
{
    printf("PUSH operation called correclty \n");
}
void PUSH_SS(void)
{
    printf("PUSH operation called correclty \n");
}
void PUSH_DS(void)
{
    printf("PUSH operation called correclty \n");
}
void PUSH_Ib(void)
{
    printf("PUSH operation called correclty \n");
}

// Mapped to one-byte opcode map (PUSH general register)
void PUSH_eAX(void)
{
    printf("PUSH operation called correclty \n");
}

void PUSH_eCX(void)
{
    printf("PUSH operation called correclty \n");
}

void PUSH_eDX(void)
{
    printf("PUSH operation called correclty \n");
}

void PUSH_eBX(void)
{
    printf("PUSH operation called correclty \n");
}

void PUSH_eSP(void)
{
    printf("PUSH operation called correclty \n");
}

void PUSH_eBP(void)
{
    printf("PUSH operation called correclty \n");
}

void PUSH_eSI(void)
{
    printf("PUSH operation called correclty \n");
}

void PUSH_eDI(void)
{
    printf("PUSH operation called correclty \n");
}

// Mapped to two-byte opcode map
void PUSH_FS(void)
{
    printf("PUSH operation called correctly \n");
}
void PUSH_GS(void)
{
    printf("PUSH operation called correctly \n");
}

// Mapped to ModRM opcode  map
void PUSH_Ev(void)
{
    printf("PUSH operation called correctly \n");
}