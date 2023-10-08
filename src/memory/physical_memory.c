#include <stdio.h>
#include <stdlib.h>

#include "physical_memory.h"

_byte physical_memory_read(_physical_memory_ptr physical_memory_ptr, _32addr addr)
{
    // check if _32addr < _PHYSICAL_MEMORY_ADDRESS_SPACE
    if (addr >= _PHYSICAL_MEMORY_ADDRESS_SPACE)
    {
        status = _ERR_PYSICAL_MEMORY_ADDR_OUTRANGE;
        err_handler("");
        return 0;
    }
    // check if  physical_memory_ptr != NULL
    if (physical_memory_ptr == NULL)
    {
        status = _ERR_PHYSICAL_MEMORY_NULL_POINTER_ARG;
        err_handler("");
        return 0;
    }

    status = _STATUS_OK;
    return physical_memory_ptr[addr];
}

void physical_memory_write(_byte byte, _physical_memory_ptr physical_memory_ptr, _32addr addr)
{
    // check if _32addr < _PHYSICAL_MEMORY_ADDRESS_SPACE
    if (addr >= _PHYSICAL_MEMORY_ADDRESS_SPACE)
    {
        status = _ERR_PYSICAL_MEMORY_ADDR_OUTRANGE;
        err_handler("");
        return;
    }
    // check if  physical_memory_ptr != NULL
    if (physical_memory_ptr == NULL)
    {
        status = _ERR_PHYSICAL_MEMORY_NULL_POINTER_ARG;
        err_handler("");
        return;
    }

    // if all _STATUS_OK
    physical_memory_ptr[addr] = byte;
    status = _STATUS_OK;
}

_physical_memory_ptr physical_memory_start(void)
{
    _physical_memory_ptr physical_memory_ptr = (_physical_memory_ptr)malloc(_PHYSICAL_MEMORY_ADDRESS_SPACE);
    
    if (physical_memory_ptr == NULL)
    {
        status = _ERR_PHYSICAL_MEMORY_MALLOC;
        err_handler("");
        return 0;
    }

    // set init values

    status = _STATUS_OK;
    return physical_memory_ptr;
}
