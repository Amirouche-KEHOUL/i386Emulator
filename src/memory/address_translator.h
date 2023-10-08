#ifndef _ADDRESS_TRANSLATOR_H_
#define _ADDRESS_TRANSLATOR_H_

#include <stdio.h>
#include "../typedefs.h"
#include "physical_memory.h"

#define _CODE_SEGMENT 1
#define _DATA_SEGMENT 2
#define _SYS_SEGMENT 2

// This function assumes that entries does not generate errors or exceptions (check done by the caller)
_32addr translate_segment(_32addr offset, void *segment_decriptor, int segment_descriptor_type);

#endif //_ADDRESS_TRANSLATOR_H_
