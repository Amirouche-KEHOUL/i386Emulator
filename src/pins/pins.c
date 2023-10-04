#include <stddef.h>

#include "pins.h"

extern int status;

_pin_state_enum pin_read(_pin_name_enum pin_name_enum)
{
    if (pins & (1 << pin_name_enum))
    {
        return ON;
    }
    return OFF;
}

void pin_write(_pin_name_enum pin_name_enum, _pin_state_enum pin_state_enum)
{
    if (pin_state_enum == OFF)
    {
        pins = pins & ~(1 << pin_name_enum);
        return;
    }
    if (pin_state_enum == ON)
    {
        pins = pins | (1 << pin_name_enum);
        return;
    }
}

void pin_pow_up(void)
{
}
