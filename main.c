#include <stdio.h>
#include "memory/registers.h"
#include "memory/ram.h"

int main ()
{
    char* ram = start_ram();
    free(ram);
    return  0;
}