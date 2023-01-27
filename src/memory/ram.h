#ifndef _RAM_H_
#define _RAM_H_

#include <stdlib.h>
#include "../statusflags.h"

# define _RAM_SIZE 4294967296 // 4GB. THIS Value should not be changed. 

typedef unsigned long* _ram;
typedef unsigned char _byte;
typedef unsigned long _addr;

/*Reads a byte from the RAM*/
_byte ram_read (_ram ram, _addr addr,_status* status);

/*Writes a byte to the RAM*/
void ram_write(_byte byte,_ram ram, _addr addr,_status* status);

/*Allocate memory and inits the RAM*/
_ram ram_start(_status* status);

#endif //_RAM_H_