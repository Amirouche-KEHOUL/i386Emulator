#ifndef _MOV_H_
#define _MOV_H_

#include <stdio.h>
// Mapped to one-byte opcode map
void MOV_EbGb(void);
void MOV_EvGv(void);
void MOV_GbEb(void);
void MOV_GvEv(void);
void MOV_EwSw(void);
void MOV_SwEw(void);
void MOV_ALOb(void);
void MOV_eAXOv(void);
void MOV_ObAL(void);
void MOV_OveAX(void);
void MOV_AL(void);
void MOV_CL(void);
void MOV_DL(void);
void MOV_BL(void);
void MOV_AH(void);
void MOV_CH(void);
void MOV_DH(void);
void MOV_BH(void);
void MOV_eAX(void);
void MOV_eCX(void);
void MOV_eDX(void);
void MOV_eBX(void);
void MOV_eSP(void);
void MOV_eBP(void);
void MOV_eSI(void);
void MOV_eDI(void);
void MOV_EbIb(void);
void MOV_EvIv(void);

// Mapped to two-byte opcode map
void MOV_CbRb(void);
void MOV_DdRd(void);
void MOV_RdCd(void);
void MOV_RdDd(void);
void MOV_TdRd(void);
void MOV_RdTd(void);

#endif // _MOV_H_