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
void MOV_ALIb(void);
void MOV_CLIb(void);
void MOV_DLIb(void);
void MOV_BLIb(void);
void MOV_AHIb(void);
void MOV_CHIb(void);
void MOV_DHIb(void);
void MOV_BHIb(void);
void MOV_eAXIv(void);
void MOV_eCXIv(void);
void MOV_eDXIv(void);
void MOV_eBXIv(void);
void MOV_eSPIv(void);
void MOV_eBPIv(void);
void MOV_eSIIv(void);
void MOV_eDIIv(void);
void MOV_EbIb(void);
void MOV_EvIv(void);

// Mapped to two-byte opcode map
void MOV_CdRd(void);
void MOV_DdRd(void);
void MOV_RdCd(void);
void MOV_RdDd(void);
void MOV_TdRd(void);
void MOV_RdTd(void);

#endif // _MOV_H_