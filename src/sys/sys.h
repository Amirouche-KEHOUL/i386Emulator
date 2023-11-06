#ifndef _SYS_H_
#define _SYS_H_

#include <stddef.h>
#include <stdio.h>
#include "../typedefs.h"
#include "../pins/pins.h"
#include "../status/status.h"
#include "../memory/physical_memory.h"
#include "../memory/registers.h"
#include "../memory/IO.h"
#include "../decoder/map.h"

#define _SYS_FAULTY 1
#define _SYS_NOT_FAULTY 0
#define _SYS_SELF_TEST_REQUEST 1
#define _SYS_SELF_TEST_NOT_REQUEST 0

int sys_is_selftest_req(void);
int sys_isfaulty(void);
void sys_init(void);
void sys_shutdown(void);

#endif // _SYS_H_