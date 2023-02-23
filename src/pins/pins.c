#include "pins.h"

_pin_state_enum pin_read (const _pins* pins,_pin_name_enum pin_name_enum, _status* status)
{
    if (pins == NULL)
    {
        *status = _ERR_PIN_NULL_POINTER_ARG;
        err_handler(status,"");
        return -1 ;
    }
    if (*pins & (1 << pin_name_enum )) 
    {
        return ON;
    }
    return OFF;
}


void  pin_write (_pins* pins,_pin_name_enum pin_name_enum,_pin_state_enum pin_state_enum, _status* status)
{
    if (pins == NULL)
    {
        *status = _ERR_PIN_NULL_POINTER_ARG;
        err_handler(status,"");
        return;
    }
    if ( pin_state_enum == OFF )
    {
       *pins = *pins & ~( 1 << pin_name_enum );
       return; 
    }
    if ( pin_state_enum == ON )
    {
       *pins = *pins | (1 << pin_name_enum ); 
        return;
    }
}



void pin_pow_up (_pins* pins, _status* status)
{
    if (pins == NULL )
    {
        *status = _ERR_PIN_NULL_POINTER_ARG;
        err_handler(status,"");        
        return ;
    }
                
}
