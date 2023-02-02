#include "pins.h"


void pins_pow_up (_pins_st* pins_st, _status* status)
{
    if (pins_st == 0 )
    {
        *status = ERR_PIN_NULL_POINTER;
        return ;
    }
        
    pins_st->BUSY = CONF_PIN_BUSY_POW_UP;
    pins_st->RESET = CONF_PIN_RESET_POW_UP;
}
