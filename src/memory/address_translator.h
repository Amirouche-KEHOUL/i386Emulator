#ifndef _ADDRESS_TRANSLATOR_H_
#define _ADDRESS_TRANSLATOR_H_

// logical address consisting of a segment selector and segment offset

#include <stdio.h>
#include "../typedefs.h"
#include "physical_memory.h"

extern _segment_regs_st segment_regs_st;
extern _physical_memory_ptr physical_memory_ptr;
extern _dtr_reg_st gdtr_reg_st;

// This function assumes that entries does not generate errors or exceptions (check done by the caller)
_32_linear_addr
translate_segment(_32_logical_addr offset, void *segment_decriptor, int segment_descriptor_type);

void load_seg_regs(_selector_st selector_st, int segment_reg);

// performs type checking and loads segment registers given a selector and a segment register destination.
void load_selector_into_seg_reg(_selector_st selector_st, int segment_reg);

#endif //_ADDRESS_TRANSLATOR_H_
