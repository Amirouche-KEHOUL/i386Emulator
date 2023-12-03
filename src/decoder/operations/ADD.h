#ifndef _ADD_H_
#define _ADD_H_

#include <stdio.h>
#include "../../typedefs.h"
#include "../prefetch_queue.h"

void ADD_EbGb(void);
void ADD_EvGv(void);
void ADD_GbEb(void);
void ADD_GvEv(void);
void ADD_ALIb(void);
void ADD_eAXIv(void);

// groupe1 ModRM opcode
void ADD_EbIb(void);
void ADD_EvIv(void);
#endif // _ADD_H_