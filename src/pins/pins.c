#include "pins.h"

_pin_state_enum pins_read (_pins* pins,_pin_name_enum pin_name_enum, _status* status)
{
    if (pins == NULL)
    {
        *status = ERR_PIN_NULL_POINTER;
        err_handler(status);
        return -1 ;
    }
    if (*pins & (pin_name_enum << 1)) 
    {
        return ON;
    }
    return OFF;
}


void  pins_wrtie (_pins* pins,_pin_name_enum pin_name_enum,_pin_state_enum pin_state_enum, _status* status)
{
    if (pins == NULL)
    {
        *status = ERR_PIN_NULL_POINTER;
        err_handler(status);
        return;
    }
    if ( pin_state_enum == OFF )
    {
       *pins = *pins & ~(pin_name_enum << 1 );
       return; 
    }
    if ( pin_name_enum == ON )
    {
       *pins = *pins | (pin_name_enum << 1 );
        return;
    }
}





void pins_pow_up (_pins* pins, _status* status)
{
    if (pins == 0 )
    {
        *status = ERR_PIN_NULL_POINTER;
        err_handler(status);        
        return ;
    }
        
}
