#include "ram.h"
#include <stdio.h>
_byte ram_read (_ram ram, _addr addr,_status* status)
{
    //check if _addr < _RAM_SIZE 
    if (addr >= _RAM_SIZE)
    {
        *status = ERR_RAM_ADDR_OUTRANGE;
        return 0;
    }
    // check if  ram != NULL
    if (ram == NULL)
    {
        *status = ERR_RAM_NULL_POINTER;
        return 0;
    } 
    *status = OK;
    return ram[addr];
} 

void ram_write(_byte byte,_ram ram, _addr addr,_status* status)
{
    //check if _addr < _RAM_SIZE 
    if (addr >= _RAM_SIZE)
    {
        *status = ERR_RAM_ADDR_OUTRANGE;
        goto stop;
    }
    // check if  ram != NULL
    if (ram == NULL)
    {
        *status = ERR_RAM_NULL_POINTER;
        goto stop;
    }
    // if all OK 
    ram[addr] = byte;
    *status = OK;

stop:}


_ram  ram_start(_status* status)
{
    _ram ram = (_ram) malloc(sizeof(char)*_RAM_SIZE);
    if (ram == NULL)
    {
        *status = ERR_RAM_MALLOC;
        return 0;
    }
    
    // set init values

    *status = OK;
    return ram;
}