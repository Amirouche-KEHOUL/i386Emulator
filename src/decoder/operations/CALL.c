#include "CALL.h"

// Mapped to one-byte opcode map
void CALL_Ap(void)
{
    printf("CALL operation called correctly \n");
}
void CALL_Av(void)
{
    printf("CALL operation called correctly \n");
}

// Mapped to ModRM opcode map
void ModRM_CALL_Ev(void)
{
    printf("CALL operation called correctly \n");
}
void ModRM_CALL_Ep(void)
{
    printf("CALL operation called correctly \n");
}
void CALL_Ev (void) {
    printf("CALL_Ev operation called correctly \n");
}

void CALL_eP (void) {
    printf("CALL_eP operation called correctly \n");
}
