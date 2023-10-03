#ifndef _RAM_H_
#define _RAM_H_

#include "../typedefs.h"
#include "../status/status.h"

/*
The physical memory of an 80386 system is organized as a sequence of 8-bit bytes.
Each byte is assigned a unique address that ranges from zero to a maximum of 232-1 (4 gigabytes).

i3086 implements two memory models:
- Flat: applications programmer sees a single array of up to 232 bytes.
- Segmented: the address space as viewed by an applications program 
(called the logical address space) 
is a much larger space of up to 246 bytes (64 terabytes).

Actual transfers of data between processor and memory take place in units of 
doublewords beginning at addresses evenly divisible by four; however, the
processor converts requests for misaligned words or doublewords into the
appropriate sequences of requests acceptable to the memory interface. Such
misaligned data transfers reduce performance by requiring extra memory
cycles
*/

#define _RAM_SIZE 4294967296UL // 4GB. This Value should not be changed!

/*Reads a byte from the RAM*/
_byte ram_read(_ram_ptr ram_ptr, _addr addr);

/*Writes a byte to the RAM*/
void ram_write(_byte byte, _ram_ptr ram_ptr, _addr addr);

/*Allocate memory and inits the RAM*/
_ram_ptr ram_start(void);

#endif //_RAM_H_