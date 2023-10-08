#include <stdio.h>
#include <stdlib.h>

#include "IO.h"

_byte IO_read(_IO_ptr IO_ptr, _32addr addr)
{
    // check if _32addr < _IO_ADDRESS_SPACE
    if (addr >= _IO_ADDRESS_SPACE)
    {
        status = _ERR_IO_MEMORY_ADDR_OUTRANGE;
        err_handler("");
        return 0;
    }
    // check if  IO_ptr != NULL
    if (IO_ptr == NULL)
    {
        status = _ERR_PHYSICAL_MEMORY_NULL_POINTER_ARG;
        err_handler("");
        return 0;
    }

    status = _STATUS_OK;
    return IO_ptr[addr];
}

void IO_write(_byte byte, _IO_ptr IO_ptr, _32addr addr)
{
    // check if _32addr < _IO_ADDRESS_SPACE
    if (addr >= _IO_ADDRESS_SPACE)
    {
        status = _ERR_IO_MEMORY_ADDR_OUTRANGE;
        err_handler("");
        return;
    }
    // check if  IO_ptr != NULL
    if (IO_ptr == NULL)
    {
        status = _ERR_PHYSICAL_MEMORY_NULL_POINTER_ARG;
        err_handler("");
        return;
    }

    // if all _STATUS_OK
    IO_ptr[addr] = byte;
    status = _STATUS_OK;
}

_IO_ptr IO_start(void)
{
    _IO_ptr IO_ptr = (_IO_ptr)malloc(_IO_ADDRESS_SPACE);
    if (IO_ptr == NULL)
    {
        status = _ERR_PHYSICAL_MEMORY_MALLOC;
        err_handler("");
        return 0;
    }

    // set init values

    status = _STATUS_OK;
    return IO_ptr;
}
