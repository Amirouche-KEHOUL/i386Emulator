#ifndef _PREFETCH_H_
#define _PREFETCH_H_

#include "../typedefs.h"
#include "../memory/address_translator.h"
#include "../memory/registers.h"

void read_ModRM_byte_to_st(void);
_byte stream_byte_prefetch_queue(void);

#endif // _PREFETCH_H_