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
#include "./operations/IMUL.h"
#include "./operations/INSB.h"
#include "./operations/INSW_D.h"
#include "./operations/OUTSB.h"
#include "./operations/OUTSW_D.h"
#include "./operations/JO_SHORT.h"
#include "./operations/JNO_SHORT.h"
#include "./operations/JB_SHORT.h"
#include "./operations/JNB_SHORT.h"
#include "./operations/JZ_SHORT.h"
#include "./operations/JNZ_SHORT.h"
#include "./operations/JBE_SHORT.h"
#include "./operations/JNBE_SHORT.h"
#include "./operations/JS_SHORT.h"
#include "./operations/JNS_SHORT.h"
#include "./operations/JP_SHORT.h"
#include "./operations/JNP_SHORT.h"
#include "./operations/JL_SHORT.h"
#include "./operations/JNL_SHORT.h"
#include "./operations/JLE_SHORT.h"
#include "./operations/JNLE_SHORT.h"
#include "./operations/TEST.h"
#include "./operations/XCNG.h"
#include "./operations/MOV.h"
#include "./operations/LEA.h"
#include "./operations/NOP.h"
#include "./operations/XCHG.h"
#include "./operations/CBW.h"
#include "./operations/CWD.h"
#include "./operations/CALL.h"
#include "./operations/WAIT.h"
#include "./operations/PUSHF.h"
#include "./operations/POPF.h"
#include "./operations/SAHF.h"
#include "./operations/LAHF.h"
#include "./operations/MOVSB.h"
#include "./operations/MOVSW.h"
#include "./operations/CMPSB.h"
#include "./operations/CMPSW.h"
#include "./operations/STOSB.h"
#include "./operations/STOSW.h"
#include "./operations/LODSB.h"
#include "./operations/LODSW.h"
#include "./operations/SCASB.h"
#include "./operations/SCASW.h"
#include "./operations/RET_NEAR.h"
#include "./operations/LES.h"
#include "./operations/LDS.h"
#include "./operations/ENTER.h"
#include "./operations/LEAVE.h"
#include "./operations/RET_FAR.h"
#include "./operations/INT.h"
#include "./operations/INTO.h"
#include "./operations/IRET.h"
#include "./operations/AAM.h"
#include "./operations/AAD.h"
#include "./operations/XLAT.h"
#include "./operations/ESC_COP.h"
#include "./operations/LOOPNE.h"
#include "./operations/LOOPE.h"
#include "./operations/LOOP.h"
#include "./operations/JCXZ.h"
#include "./operations/IN.h"
#include "./operations/OUT.h"
#include "./operations/HLT.h"
#include "./operations/CMC.h"
#include "./operations/CLC.h"
#include "./operations/STC.h"
#include "./operations/CLI.h"
#include "./operations/STI.h"
#include "./operations/CLD.h"
#include "./operations/STD.h"
#include "./operations/LAR.h"
#include "./operations/LSL.h"
#include "./operations/CLTS.h"
#include "./operations/JO_LONG.h"
#include "./operations/JNO_LONG.h"
#include "./operations/JB_LONG.h"
#include "./operations/JNB_LONG.h"
#include "./operations/JZ_LONG.h"
#include "./operations/JNZ_LONG.h"
#include "./operations/JBE_LONG.h"
#include "./operations/JNBE_LONG.h"
#include "./operations/JS_LONG.h"
#include "./operations/JNS_LONG.h"
#include "./operations/JP_LONG.h"
#include "./operations/JNP_LONG.h"
#include "./operations/JL_LONG.h"
#include "./operations/JNL_LONG.h"
#include "./operations/JLE_LONG.h"
#include "./operations/JNLE_LONG.h"
#include "./operations/SETO.h"
#include "./operations/SETNO.h"
#include "./operations/SETB.h"
#include "./operations/SETNB.h"
#include "./operations/SETZ.h"
#include "./operations/SETNZ.h"
#include "./operations/SETBE.h"
#include "./operations/SETNBE.h"
#include "./operations/SETS.h"
#include "./operations/SETNS.h"
#include "./operations/SETP.h"
#include "./operations/SETNP.h"
#include "./operations/SETL.h"
#include "./operations/SETNL.h"
#include "./operations/SETLE.h"
#include "./operations/SETNLE.h"
#include "./operations/BT.h"
#include "./operations/SHLD.h"
#include "./operations/BTS.h"
#include "./operations/SHRD.h"
#include "./operations/LSS.h"
#include "./operations/BTR.h"
#include "./operations/LFS.h"
#include "./operations/LGS.h"
#include "./operations/MOVZX.h"
#include "./operations/BTC.h"
#include "./operations/BSF.h"
#include "./operations/BSR.h"
#include "./operations/MOVSX.h"
#include "./operations/ROL.h"
#include "./operations/ROR.h"

void map_operations_to_opcode_maps(void);

#endif // _MAP_H_