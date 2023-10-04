#ifndef _PINS_H_
#define _PINS_H_

#include "../typedefs.h"
#include "../status/status.h"
#include "../config.h"

extern _pins pins;

/* functions */
_pin_state_enum pin_read(_pin_name_enum pin_name_enum);
void pin_write(_pin_name_enum pin_name_enum, _pin_state_enum pin_state_enum);
void pin_pow_up(void);

#endif // _PINS_H_