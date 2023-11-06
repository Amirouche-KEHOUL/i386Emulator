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
#include "./operations/PUSH.h"
#include "./operations/POP.h"
#include "./operations/DAA.h"
#include "./operations/DAS.h"
#include "./operations/AAA.h"
#include "./operations/AAS.h"
#include "./operations/PUSHA.h"
#include "./operations/POPA.h"
#include "./operations/BOUND.h"
#include "./operations/ARPL.h"

void map_operations_to_opcode_maps(void);

#endif // _MAP_H_