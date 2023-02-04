#ifndef _PINS_H_
#define _PINS_H_

#include "../status/status.h"
#include "../config.h"

// TODO confirm how to limit enum to a given values

/* Chip pins data structure */

typedef unsigned int _pins ; 

typedef enum  pin_name_enum
{
    pin_reset = 1,
    pin_busy  = 2,

}_pin_name_enum; 

typedef enum pin_state_enum { OFF = 0 , ON = 1 } _pin_state_enum;

#define PIN_MASK_RESET_1      0b00000000000000000000000000000001
#define PIN_MASK_BUSY_2       0b00000000000000000000000000000010

/* functions */
_pin_state_enum pins_read (_pins* pins,_pin_name_enum pin_name_enum, _status* status);
void  pins_wrtie (_pins* pins,_pin_name_enum pin_name_enum,_pin_state_enum pin_state_enum, _status* status);
void pins_pow_up (_pins* pins, _status* status);

#endif // _PINS_H_