#ifndef _IO_H_
#define _IO_H_

#include "../typedefs.h"
#include "../status/status.h"
/**
I/O Addressing:
    - separate I/O address space (using specific I/O instructions)
    - Memory-mapped I/O (using general-purpose operand manipulationinstructions).
*/

extern int status;

#define _IO_ADDRESS_SPACE 65536UL // 64K. This Value should not be changed!

/*Reads a byte from the IO space */
_byte IO_read(_IO_ptr IO_ptr, _32_physical_addr addr);

/*Writes a byte to the IO space */
void IO_write(_byte byte, _IO_ptr IO_ptr, _32_physical_addr addr);

/*Allocate memory and inits the  IO memory*/
_IO_ptr IO_start(void);

#endif // _IO_H_