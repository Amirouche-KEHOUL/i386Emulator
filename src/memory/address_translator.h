#ifndef _ADDRESS_TRANSLATOR_H_
#define _ADDRESS_TRANSLATOR_H_

// logical address consisting of a segment selector and segment offset

#include <stdio.h>
#include <stdlib.h>
#include "../typedefs.h"
#include "physical_memory.h"

// Converts a logical address into liear given an offset and a segment descriptor. This function assumes that entries does not generate errors or exceptions (check done by the caller)
_32_linear_addr translate_segment(_32_offset offset, const void *segment_decriptor, int segment_descriptor_type);

// Performs type checking and loads segment registers given a selector and a segment register destination.
void check_then_load_selector_into_seg_reg(_selector_st selector_st, int segment_reg);

_32_physical_addr logical_to_physical_addr(_32_offset offset, const void *segment_decriptor, int segment_descriptor_type);

// ----- TEST INCLUDES ---------//
_32_physical_addr linear_to_physical_addr(_32_linear_addr linear_addr);
// ----- TEST INCLUDES ---------//

#endif //_ADDRESS_TRANSLATOR_H_
