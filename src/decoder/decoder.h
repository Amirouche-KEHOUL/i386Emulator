#ifndef _DECODER_H_
#define _DECODER_H_

#include "../typedefs.h"
#include "../memory/registers.h"
#include "./prefetch_queue.h"

unsigned int get_effective_address_size(unsigned int default_seg_size, unsigned int adresse_size_prefix_present);

unsigned int get_effective_operand_size(unsigned int default_seg_size, unsigned int operand_size_prefix_present);

void decode(void);
#endif // _DECODER_H_