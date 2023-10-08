#ifndef _PHYSICAL_MEMORY_H_
#define _PHYSICAL_MEMORY_H_

#include "../typedefs.h"
#include "../status/status.h"

extern int status;

/*
The physical memory of an 80386 system is organized as a sequence of 8-bit bytes.
Each byte is assigned a unique address that ranges from zero to a maximum of 232-1 (4 gigabytes).

The 80386 can address up to four gigabytes (232 bytes, addresses OOOOOOOOH-FFFFFFFFH)
of physical memory and up to 64 kilobytes (216 bytes, addresses OOOOOOOOH-OOOOFFFFH)
of I/O. The 80386 maintains separate physical memory and I/O spaces.

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

#define _PHYSICAL_MEMORY_ADDRESS_SPACE 4294967296UL // 4G. This Value should not be changed!

/*Reads a byte from the physical memory*/
_byte physical_memory_read(_physical_memory_ptr physical_memory_ptr, _32addr addr);

/*Writes a byte to the physical memory*/
void physical_memory_write(_byte byte, _physical_memory_ptr physical_memory_ptr, _32addr addr);

/*Allocate memory and inits the  physical memory*/
_physical_memory_ptr physical_memory_start(void);

#endif //_PHYSICAL_MEMORY_H_