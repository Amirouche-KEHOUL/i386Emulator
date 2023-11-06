#include "ADC.h"
// Mapped to one-byte opcode map
void ADC_EbGb(void)
{
    printf("ADC operation called correctly \n");
}

void ADC_EvGv(void)
{
    printf("ADC operation called correctly \n");
}

void ADC_GbEb(void)
{
    printf("ADC operation called correctly \n");
}

void ADC_GvEv(void)
{
    printf("ADC operation called correctly \n");
}

void ADC_ALIb(void)
{
    printf("ADC operation called correctly \n");
}

void ADC_eAXIv(void)
{
    printf("ADC operation called correctly \n");
}

// Mapped to ModRM opcode  map

void ADC_EbIb(void)
{
    printf("ADC operation called correctly \n");
}

void ADC_EvIv(void)
{
    printf("ADC operation called correctly \n");
}

void ModRM_ADC(void)
{
    // TODO: confirm which function to be called (2 functions above) based on the previous byte (opcode byte #0)
    printf("ADC operation called correctly \n");
}