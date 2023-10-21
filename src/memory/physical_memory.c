#include <stdio.h>
#include <stdlib.h>

#include "physical_memory.h"

_byte physical_memory_read_byte(_physical_memory_ptr physical_memory_ptr, _32_physical_addr addr)
{
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

_word physical_memory_read_word(_physical_memory_ptr physical_memory_ptr, _32_physical_addr addr)
{
    // check if  physical_memory_ptr != NULL
    if (physical_memory_ptr == NULL)
    {
        status = _ERR_PHYSICAL_MEMORY_NULL_POINTER_ARG;
        err_handler("");
        return 0;
    }
    _word word = 0x0;
    _byte byte_0 = 0x0;
    _byte byte_1 = 0x0;

    byte_0 = physical_memory_read_byte(physical_memory_ptr, addr);
    byte_1 = physical_memory_read_byte(physical_memory_ptr, addr + 1U);

    word = byte_1;
    word = ((_word)(word << 8)) + ((_word)byte_0);

    return word;
}

_double_word physical_memory_read_double_word(_physical_memory_ptr physical_memory_ptr, _32_physical_addr addr)
{
    // check if  physical_memory_ptr != NULL
    if (physical_memory_ptr == NULL)
    {
        status = _ERR_PHYSICAL_MEMORY_NULL_POINTER_ARG;
        err_handler("");
        return 0;
    }
    _double_word double_word = 0x0;
    _word word_0 = 0x0;
    _word word_1 = 0x0;

    word_0 = physical_memory_read_word(physical_memory_ptr, addr);
    word_1 = physical_memory_read_word(physical_memory_ptr, addr + 2U);

    double_word = word_1;
    double_word = (double_word << 16) + (_double_word)word_0;

    return double_word;
}

void physical_memory_write(_byte byte, _physical_memory_ptr physical_memory_ptr, _32_physical_addr addr)
{
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
