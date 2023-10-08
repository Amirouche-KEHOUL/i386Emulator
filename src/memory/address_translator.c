#include "address_translator.h"

_32addr translate_segment(_32addr offset, void *segment_decriptor, int segment_descriptor_type)
{
    _32addr ret = 0UL;

    if (segment_descriptor_type == _DATA_SEGMENT)
    {
        ret = ((_data_segment_descriptor_st *)segment_decriptor)->base + offset;
        return ret;
    }
    if (segment_descriptor_type == _CODE_SEGMENT)
    {
        ret = ((_code_segment_descriptor_st *)segment_decriptor)->base + offset;
        return ret;
    }
    if (segment_descriptor_type == _SYS_SEGMENT)
    {
        ret = ((_system_segment_descriptor_st *)segment_decriptor)->base + offset;
        return ret;
    }
    return ret;
}

/*
TODO: Implement Type checking function
When a selector of a descriptor is loaded into a segment register.
Certain segment registers can contain only certain descriptor types. For example:
 - CS reg eccept only code segments
 - Selectors of executable segments that are not readable cannot be loaded into data-segment registers.
 - Only selectors of writable data segments can be loaded into SS.
*/

/*
TODO: Implement limit checking
*/