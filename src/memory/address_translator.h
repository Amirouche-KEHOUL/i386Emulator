#ifndef _ADDRESS_TRANSLATOR_H_
#define _ADDRESS_TRANSLATOR_H_

#include <stdio.h>
#include "../typedefs.h"
#include "physical_memory.h"

extern _segment_regs_st segment_regs_st;

// This function assumes that entries does not generate errors or exceptions (check done by the caller)
_32addr translate_segment(_32addr offset, void *segment_decriptor, int segment_descriptor_type);

void load_seg_regs(_selector_st selector_st, int segment_reg);

// performs type checking and loads segment registers given a selector and a segment register destination.
void load_selector_into_seg_reg(_selector_st selector_st, int segment_reg);

#endif //_ADDRESS_TRANSLATOR_H_
