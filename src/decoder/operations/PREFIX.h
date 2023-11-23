#ifndef _PREFIX_H_
#define _PREFIX_H_

#include <stdio.h>

void SEG_ES(void);
void SEG_CS(void);
void SEG_DS(void);
void SEG_SS(void);
void SEG_FS(void);
void SEG_GS(void);
void Operand_Size(void);
void Address_Size(void);
void LOCK(void);
void REPNE(void);
void REP_REPE(void);

#endif // _PREFIX_H_