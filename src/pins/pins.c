#include "pins.h"


void pins_init (_pins_st* pins_st, _status* status)
{
    if (pins_st == 0 )
    {
        *status = ERR_PIN_NULL_POINTER;
        return ;
    }    
    pins_st->BUSY = CONF_PIN_POW_UP_BUSY;
}
