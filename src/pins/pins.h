#ifndef _PINS_H_
#define _PINS_H_

#include "../typedefs.h"
#include "../status/status.h"
#include "../config.h"

/* functions */
_pin_state_enum pin_read(const _pins *pins, _pin_name_enum pin_name_enum);
void pin_write(_pins *pins, _pin_name_enum pin_name_enum, _pin_state_enum pin_state_enum);
void pin_pow_up(_pins *pins);

#endif // _PINS_H_