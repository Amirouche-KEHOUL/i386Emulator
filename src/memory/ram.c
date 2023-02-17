#include "ram.h"
#include <stdio.h>

_byte ram_read ( _ram_ptr  ram_ptr, _addr addr, _status *status)
{
    //check if _addr < _RAM_SIZE 
    if (addr >= _RAM_SIZE)
    {
        *status = _ERR_RAM_ADDR_OUTRANGE;
        err_handler(status,"");        
        return 0;
    }
    // check if  ram_ptr != NULL
    if (ram_ptr == NULL)
    {
        *status = _ERR_RAM_NULL_POINTER;
        err_handler(status,"");        
        return 0;
    } 

    *status = _STATUS_OK;
    return ram_ptr[addr];
} 

void ram_write(_byte byte, _ram_ptr  ram_ptr, _addr addr,  _status* status)
{   
    //check if _addr < _RAM_SIZE 
    if (addr >= _RAM_SIZE)
    {
        *status = _ERR_RAM_ADDR_OUTRANGE;
        err_handler(status,"");        
        return;
    }
    // check if  ram_ptr != NULL
    if (ram_ptr == NULL)
    {
        *status = _ERR_RAM_NULL_POINTER;
        err_handler(status,"");        
        return;
    }

    // if all _STATUS_OK 
    ram_ptr[addr] = byte;
    *status = _STATUS_OK;
}


_ram_ptr ram_start( _status* status)
{
    _ram_ptr ram_ptr = (_ram_ptr) malloc(sizeof(char)*_RAM_SIZE);
    if (ram_ptr == NULL)
    {
        *status = _ERR_RAM_MALLOC;
        err_handler(status,"");        
        return 0;
    }
    
    // set init values

    *status = _STATUS_OK;
    return ram_ptr;
}