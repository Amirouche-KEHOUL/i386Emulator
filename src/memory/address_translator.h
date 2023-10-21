#ifndef _ADDRESS_TRANSLATOR_H_
#define _ADDRESS_TRANSLATOR_H_

// logical address consisting of a segment selector and segment offset

#include <stdio.h>
#include <stdlib.h>
#include "../typedefs.h"
#include "physical_memory.h"

extern _segment_regs_st segment_regs_st;
extern _physical_memory_ptr physical_memory_ptr;
extern _dtr_reg_st gdtr_reg_st;
extern _dtr_reg_st ldtr_reg_st;
extern _cr0_reg_st cr0_reg_st;
extern _cr3_reg_pdbr cr3_reg_pdbr;

// Converts a logical address into liear given an offset and a segment descriptor. This function assumes that entries does not generate errors or exceptions (check done by the caller)
_32_linear_addr translate_segment(_32_logical_addr offset, const void *segment_decriptor, int segment_descriptor_type);

// Performs type checking and loads segment registers given a selector and a segment register destination.
void check_then_load_selector_into_seg_reg(_selector_st selector_st, int segment_reg);

// ----- TEST INCLUDES ---------//
_32_physical_addr linear_to_physical_addr(_32_linear_addr linear_addr);
// ----- TEST INCLUDES ---------//

#endif //_ADDRESS_TRANSLATOR_H_
