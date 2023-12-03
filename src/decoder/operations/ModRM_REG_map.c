#include "ModRM_REG_map.h"

// Operands
extern _double_word RM_operand;
extern _32_offset RM_operand_addr;
extern _double_word R_operand;
extern _32_offset R_operand_addr;

extern _general_regs_st general_regs_st;

void AL_REG(void)
{
    printf("AL_REG operation called correctly \n");
    R_operand = general_regs_st.EAX.AL;
    R_operand_addr = AL_REG_DEF;
}

void CL_REG(void)
{
    printf("CL_REG operation called correctly \n");
}

void DL_REG(void)
{
    printf("DL_REG operation called correctly \n");
}

void BL_REG(void)
{
    printf("BL_REG operation called correctly \n");
}

void AH_REG(void)
{
    printf("AH_REG operation called correctly \n");
}

void CH_REG(void)
{
    printf("CH_REG operation called correctly \n");
}

void DH_REG(void)
{
    printf("DH_REG operation called correctly \n");
}

void BH_REG(void)
{
    printf("BH_REG operation called correctly \n");
}

void AX_REG(void)
{
    printf("AX_REG operation called correctly \n");
}

void CX_REG(void)
{
    printf("CX_REG operation called correctly \n");
}

void DX_REG(void)
{
    printf("DX_REG operation called correctly \n");
}

void BX_REG(void)
{
    printf("BX_REG operation called correctly \n");
}

void SP_REG(void)
{
    printf("SP_REG operation called correctly \n");
}

void BP_REG(void)
{
    printf("BP_REG operation called correctly \n");
}

void SI_REG(void)
{
    printf("SI_REG operation called correctly \n");
}

void DI_REG(void)
{
    printf("DI_REG operation called correctly \n");
}

void EAX_REG(void)
{
    printf("EAX_REG operation called correctly \n");
}

void ECX_REG(void)
{
    printf("ECX_REG operation called correctly \n");
}

void EDX_REG(void)
{
    printf("EDX_REG operation called correctly \n");
}

void EBX_REG(void)
{
    printf("EBX_REG operation called correctly \n");
}

void ESP_REG(void)
{
    printf("ESP_REG operation called correctly \n");
}

void EBP_REG(void)
{
    printf("EBP_REG operation called correctly \n");
}

void ESI_REG(void)
{
    printf("ESI_REG operation called correctly \n");
}

void EDI_REG(void)
{
    printf("EDI_REG operation called correctly \n");
}
