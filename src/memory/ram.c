#include "ram.h"
#include <stdio.h>

_byte ram_read ( _ram_ptr  ram_ptr, _addr addr, _status *status)
{
    //check if _addr < _RAM_SIZE 
    if (addr >= _RAM_SIZE)
    {
        *status = ERR_RAM_ADDR_OUTRANGE;
        return 0;
    }
    // check if  ram_ptr != NULL
    if (ram_ptr == NULL)
    {
        *status = ERR_RAM_NULL_POINTER;
        return 0;
    } 

    *status = OK;
    return ram_ptr[addr];
} 

void ram_write(_byte byte, _ram_ptr  ram_ptr, _addr addr,  _status* status)
{   
    //check if _addr < _RAM_SIZE 
    if (addr >= _RAM_SIZE)
    {
        *status = ERR_RAM_ADDR_OUTRANGE;
        return;
    }
    // check if  ram_ptr != NULL
    if (ram_ptr == NULL)
    {
        *status = ERR_RAM_NULL_POINTER;
        return;
    }

    // if all OK 
    ram_ptr[addr] = byte;
    *status = OK;
}


_ram_ptr ram_start( _status* status)
{
    _ram_ptr ram_ptr = (_ram_ptr) malloc(sizeof(char)*_RAM_SIZE);
    if (ram_ptr == NULL)
    {
        *status = ERR_RAM_MALLOC;
        return 0;
    }
    
    // set init values

    *status = OK;
    return ram_ptr;
}