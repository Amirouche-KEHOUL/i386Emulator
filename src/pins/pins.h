#ifndef _PINS_H_
#define _PINS_H_

#include "../status/status.h"
#include "../config.h"

/* Chip pins data structure */
typedef int _pin ; 

typedef struct pins_st
{
    _pin BUSY:1;
    _pin RESET:1;

}_pins_st;


/* functions */

void pins_pow_up (_pins_st* pins_st, _status* status);

#endif // _PINS_H_