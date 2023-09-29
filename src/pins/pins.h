#ifndef _PINS_H_
#define _PINS_H_

#include "../status/status.h"

// TODO confirm how to limit enum to a given values

/* Chip pins data structure */

typedef unsigned int _pins;

typedef enum pin_name_enum
{
    pin_reset = 0,
    pin_busy = 1,
    pin_error = 2,
    pin_INTR = 3, // used to signal Maskable interrupts
    pin_NMI = 4,  // used to signal Non Maskable Interrupts

} _pin_name_enum;

typedef enum pin_state_enum
{
    OFF = 0,
    ON = 1
} _pin_state_enum;

/* functions */
_pin_state_enum pin_read(const _pins *pins, _pin_name_enum pin_name_enum);
void pin_write(_pins *pins, _pin_name_enum pin_name_enum, _pin_state_enum pin_state_enum);
void pin_pow_up(_pins *pins);

#endif // _PINS_H_