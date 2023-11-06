#ifndef _MAP_H_
#define _MAP_H_

#include "../typedefs.h"
#include "./prefetch_queue.h"

#include "./operations/ADD.h"
#include "./operations/OR.h"
#include "./operations/ADC.h"
#include "./operations/SBB.h"
#include "./operations/AND.h"
#include "./operations/SUB.h"
#include "./operations/XOR.h"
#include "./operations/CMP.h"
#include "./operations/INC.h"
#include "./operations/DEC.h"

void map_operations_to_opcode_maps(void);

#endif // _MAP_H_