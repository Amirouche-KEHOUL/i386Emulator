#include "TEST.h"

// Mapped to one-byte opcode map
void TEST_EbGb(void)
{
    printf("TEST operation called correctly \n");
}
void TEST_EvGv(void)
{
    printf("TEST operation called correctly \n");
}
void TEST_ALIb(void)
{
    printf("TEST operation called correctly \n");
}
void TEST_eAXIv(void)
{
    printf("TEST operation called correctly \n");
}

// Mapped to ModRM opcode map
void ModRM_TEST(void)
{
    printf("TEST operation called correctly \n");
}
void TEST_Eb(void)
{
    printf("TEST operation called correctly \n");
}
void TEST_Ev(void)
{
    printf("TEST operation called correctly \n");
}
void TEST_EbIb (void) {
    printf("TEST_EbIb operation called correctly \n");
}

void TEST_EvIv (void) {
    printf("TEST_EvIv operation called correctly \n");
}
