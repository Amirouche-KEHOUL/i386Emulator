#ifndef _ESCAPE_H_
#define _ESCAPE_H_

#include <stdio.h>
#include "../../typedefs.h"
#include "../prefetch_queue.h"

void no_opcode(void);
void _2byte_escape(void);
void grp1_EbIb_escape(void);
void grp1_EvIv_escape(void);
void grp2_EbIb_escape(void);
void grp2_EvIv_escape(void);
void grp2_Eb1_escape(void);
void grp2_Ev1_escape(void);
void grp2_EbCL_escape(void);
void grp2_EvCL_escape(void);
void grp3_Eb_escape(void);
void grp3_Ev_escape(void);
void grp4_escape(void);
void grp5_escape(void);
void grp6_escape(void);
void grp7_escape(void);
void grp8_EvIb_escape(void);
#endif // _ESCAPE_H_