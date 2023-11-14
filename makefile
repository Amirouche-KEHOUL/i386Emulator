
SRC = src/main.c \
	src/memory/physical_memory.c \
	src/memory/IO.c \
	src/memory/address_translator.c \
	src/bios/bios.c src/sys/sys.c \
	src/pins/pins.c \
	src/memory/registers.c \
	src/status/status.c \
	src/utils/utils.c \
	src/interrupts/interrupts.c \
	src/decoder/decoder.c  \
	src/decoder/map.c \
	src/decoder/prefetch_queue.c \
	src/decoder/operations/ADD.c \
	src/decoder/operations/OR.c \
	src/decoder/operations/ADC.c \
	src/decoder/operations/SBB.c \
	src/decoder/operations/AND.c \
	src/decoder/operations/SUB.c \
	src/decoder/operations/XOR.c \
	src/decoder/operations/CMP.c \
	src/decoder/operations/INC.c \
	src/decoder/operations/DEC.c \
	src/decoder/operations/PUSH.c \
	src/decoder/operations/POP.c \
	src/decoder/operations/DAA.c \
	src/decoder/operations/DAS.c \
	src/decoder/operations/AAA.c \
	src/decoder/operations/AAS.c \
	src/decoder/operations/PUSHA.c \
	src/decoder/operations/POPA.c \
	src/decoder/operations/BOUND.c \
	src/decoder/operations/ARPL.c \
	src/decoder/operations/IMUL.c \
	src/decoder/operations/INSB.c \
	src/decoder/operations/INSW_D.c \
	src/decoder/operations/OUTSB.c \
	src/decoder/operations/OUTSW_D.c \
	src/decoder/operations/JO_SHORT.c \
	src/decoder/operations/JNO_SHORT.c \
	src/decoder/operations/JB_SHORT.c \
	src/decoder/operations/JNB_SHORT.c \
	src/decoder/operations/JZ_SHORT.c \
	src/decoder/operations/JNZ_SHORT.c \
	src/decoder/operations/JBE_SHORT.c \
	src/decoder/operations/JNBE_SHORT.c \
	src/decoder/operations/JS_SHORT.c \
	src/decoder/operations/JNS_SHORT.c \
	src/decoder/operations/JP_SHORT.c \
	src/decoder/operations/JNP_SHORT.c \
	src/decoder/operations/JL_SHORT.c \
	src/decoder/operations/JNL_SHORT.c \
	src/decoder/operations/JLE_SHORT.c \
	src/decoder/operations/JNLE_SHORT.c \
	src/decoder/operations/TEST.c \
	src/decoder/operations/XCNG.c \
	src/decoder/operations/MOV.c \
	src/decoder/operations/LEA.c \
	src/decoder/operations/NOP.c \
	src/decoder/operations/XCHG.c \
	src/decoder/operations/CBW.c \
	src/decoder/operations/CALL.c \
	src/decoder/operations/WAIT.c \
	src/decoder/operations/PUSHF.c \
	src/decoder/operations/POPF.c \
	src/decoder/operations/SAHF.c \
	src/decoder/operations/LAHF.c \
	src/decoder/operations/MOVSB.c \
	src/decoder/operations/MOVSW.c \
	src/decoder/operations/CMPSB.c \
	src/decoder/operations/CMPSW.c \
	src/decoder/operations/STOSB.c \
	src/decoder/operations/STOSW.c \
	src/decoder/operations/LODSB.c \
	src/decoder/operations/LODSW.c \
	src/decoder/operations/SCASB.c \
	src/decoder/operations/SCASW.c \
	src/decoder/operations/RET_NEAR.c \
	src/decoder/operations/LES.c \
	src/decoder/operations/LDS.c \
	src/decoder/operations/ENTER.c \
	src/decoder/operations/LEAVE.c \
	src/decoder/operations/RET_FAR.c \
	src/decoder/operations/INT.c \
	src/decoder/operations/INTO.c \
	src/decoder/operations/IRET.c \
	src/decoder/operations/AAM.c \
	src/decoder/operations/AAD.c \
	src/decoder/operations/XLAT.c \
	src/decoder/operations/ESC_COP.c \
	src/decoder/operations/LOOPNE.c \
	src/decoder/operations/LOOPE.c \
	src/decoder/operations/LOOP.c \
	src/decoder/operations/JCXZ.c \
	src/decoder/operations/IN.c \
	src/decoder/operations/OUT.c \
	src/decoder/operations/CMC.c \
	src/decoder/operations/CLC.c \
	src/decoder/operations/STC.c \
	src/decoder/operations/CLI.c \
	src/decoder/operations/STI.c \
	src/decoder/operations/CLD.c \
	src/decoder/operations/STD.c \
	src/decoder/operations/LAR.c \
	src/decoder/operations/LSL.c \
	src/decoder/operations/CLTS.c \
	src/decoder/operations/JO_LONG.c \
	src/decoder/operations/JNO_LONG.c \
	src/decoder/operations/JB_LONG.c \
	src/decoder/operations/JNB_LONG.c \
	src/decoder/operations/JZ_LONG.c \
	src/decoder/operations/JNZ_LONG.c \
	src/decoder/operations/JBE_LONG.c \
	src/decoder/operations/JNBE_LONG.c \
	src/decoder/operations/JS_LONG.c \
	src/decoder/operations/JNS_LONG.c \
	src/decoder/operations/JP_LONG.c \
	src/decoder/operations/JNP_LONG.c \
	src/decoder/operations/JL_LONG.c \
	src/decoder/operations/JNL_LONG.c \
	src/decoder/operations/JLE_LONG.c \
	src/decoder/operations/JNLE_LONG.c \
	src/decoder/operations/SETO.c \
	src/decoder/operations/SETNO.c \
	src/decoder/operations/SETB.c \
	src/decoder/operations/SETNB.c \
	src/decoder/operations/SETZ.c \
	src/decoder/operations/SETNZ.c \
	src/decoder/operations/SETBE.c \
	src/decoder/operations/SETNBE.c \
	src/decoder/operations/SETS.c \
	src/decoder/operations/SETNS.c \
	src/decoder/operations/SETP.c \
	src/decoder/operations/SETNP.c \
	src/decoder/operations/SETL.c \
	src/decoder/operations/SETNL.c \
	src/decoder/operations/SETLE.c \
	src/decoder/operations/SETNLE.c \
	src/decoder/operations/BT.c \
	src/decoder/operations/SHLD.c \
	src/decoder/operations/BTS.c \
	src/decoder/operations/SHRD.c \
	src/decoder/operations/LSS.c \
	src/decoder/operations/BTR.c \
	src/decoder/operations/LFS.c \
	src/decoder/operations/LGS.c \
	src/decoder/operations/MOVZX.c \
	src/decoder/operations/BTC.c \
	src/decoder/operations/BSF.c \
	src/decoder/operations/BSR.c \
	src/decoder/operations/MOVSX.c \
	src/decoder/operations/ROL.c \
	src/decoder/operations/ROR.c \
	src/decoder/operations/RCL.c \
	src/decoder/operations/RCR.c \
	src/decoder/operations/SHL.c \
	src/decoder/operations/SHL.c \
	src/decoder/operations/SHR.c \
	src/decoder/operations/SAR.c \
	src/decoder/operations/NOT.c \
	src/decoder/operations/NEG.c \
	src/decoder/operations/MUL.c \


OBJ = build/main.o \
	build/bios/bios.o \
	build/sys/sys.o \
	build/status/status.o \
	build/memory/physical_memory.o \
	build/memory/IO.o \
	build/memory/registers.o  \
	build/memory/address_translator.o \
	build/pins/pins.o  \
	build/utils/utils.o \
	build/interrupts/interrupts.o \
	build/decoder/decoder.o  \
	build/decoder/map.o  \
	build/decoder/prefetch_queue.o  \
	build/decoder/operations/ADD.o \
	build/decoder/operations/OR.o \
	build/decoder/operations/ADC.o \
	build/decoder/operations/SBB.o  \
	build/decoder/operations/AND.o \
	build/decoder/operations/SUB.o \
	build/decoder/operations/XOR.o \
	build/decoder/operations/CMP.o  \
	build/decoder/operations/INC.o \
	build/decoder/operations/DEC.o \
	build/decoder/operations/PUSH.o \
	build/decoder/operations/POP.o \
	build/decoder/operations/DAA.o \
	build/decoder/operations/DAS.o \
	build/decoder/operations/AAA.o \
	build/decoder/operations/AAS.o \
	build/decoder/operations/PUSHA.o \
	build/decoder/operations/POPA.o \
	build/decoder/operations/BOUND.o \
	build/decoder/operations/ARPL.o \
	build/decoder/operations/IMUL.o \
	build/decoder/operations/INSB.o \
	build/decoder/operations/INSW_D.o \
	build/decoder/operations/OUTSB.o \
	build/decoder/operations/OUTSW_D.o \
	build/decoder/operations/JO_SHORT.o \
	build/decoder/operations/JNO_SHORT.o \
	build/decoder/operations/JB_SHORT.o \
	build/decoder/operations/JNB_SHORT.o \
	build/decoder/operations/JZ_SHORT.o \
	build/decoder/operations/JNZ_SHORT.o \
	build/decoder/operations/JBE_SHORT.o \
	build/decoder/operations/JNBE_SHORT.o \
	build/decoder/operations/JS_SHORT.o \
	build/decoder/operations/JNS_SHORT.o \
	build/decoder/operations/JP_SHORT.o \
	build/decoder/operations/JNP_SHORT.o \
	build/decoder/operations/JL_SHORT.o \
	build/decoder/operations/JNL_SHORT.o \
	build/decoder/operations/JLE_SHORT.o \
	build/decoder/operations/JNLE_SHORT.o \
	build/decoder/operations/TEST.o \
	build/decoder/operations/XCNG.o \
	build/decoder/operations/MOV.o \
	build/decoder/operations/LEA.o \
	build/decoder/operations/NOP.o \
	build/decoder/operations/XCHG.o \
	build/decoder/operations/CBW.o \
	build/decoder/operations/CWD.o \
	build/decoder/operations/CALL.o \
	build/decoder/operations/WAIT.o \
	build/decoder/operations/PUSHF.o \
	build/decoder/operations/POPF.o \
	build/decoder/operations/SAHF.o \
	build/decoder/operations/LAHF.o \
	build/decoder/operations/MOVSB.o \
	build/decoder/operations/MOVSW.o \
	build/decoder/operations/CMPSB.o \
	build/decoder/operations/CMPSW.o \
	build/decoder/operations/STOSB.o \
	build/decoder/operations/STOSW.o \
	build/decoder/operations/LODSB.o \
	build/decoder/operations/LODSW.o \
	build/decoder/operations/SCASB.o \
	build/decoder/operations/SCASW.o \
	build/decoder/operations/RET_NEAR.o \
	build/decoder/operations/LES.o \
	build/decoder/operations/LDS.o \
	build/decoder/operations/ENTER.o \
	build/decoder/operations/LEAVE.o \
	build/decoder/operations/RET_FAR.o \
	build/decoder/operations/INT.o \
	build/decoder/operations/INTO.o \
	build/decoder/operations/IRET.o \
	build/decoder/operations/AAM.o \
	build/decoder/operations/AAD.o \
	build/decoder/operations/XLAT.o \
	build/decoder/operations/ESC_COP.o \
	build/decoder/operations/LOOPNE.o \
	build/decoder/operations/LOOPE.o \
	build/decoder/operations/LOOP.o \
	build/decoder/operations/JCXZ.o \
	build/decoder/operations/IN.o \
	build/decoder/operations/OUT.o \
	build/decoder/operations/HLT.o \
	build/decoder/operations/CMC.o \
	build/decoder/operations/CLC.o \
	build/decoder/operations/STC.o \
	build/decoder/operations/CLI.o \
	build/decoder/operations/STI.o \
	build/decoder/operations/CLD.o \
	build/decoder/operations/STD.o \
	build/decoder/operations/LAR.o \
	build/decoder/operations/LSL.o \
	build/decoder/operations/CLTS.o \
	build/decoder/operations/JO_LONG.o \
	build/decoder/operations/JNO_LONG.o \
	build/decoder/operations/JB_LONG.o \
	build/decoder/operations/JNB_LONG.o \
	build/decoder/operations/JZ_LONG.o \
	build/decoder/operations/JNZ_LONG.o \
	build/decoder/operations/JBE_LONG.o \
	build/decoder/operations/JNBE_LONG.o \
	build/decoder/operations/JS_LONG.o \
	build/decoder/operations/JNS_LONG.o \
	build/decoder/operations/JP_LONG.o \
	build/decoder/operations/JNP_LONG.o \
	build/decoder/operations/JL_LONG.o \
	build/decoder/operations/JNL_LONG.o \
	build/decoder/operations/JLE_LONG.o \
	build/decoder/operations/JNLE_LONG.o \
	build/decoder/operations/SETO.o \
	build/decoder/operations/SETNO.o \
	build/decoder/operations/SETB.o \
	build/decoder/operations/SETNB.o \
	build/decoder/operations/SETZ.o \
	build/decoder/operations/SETNZ.o \
	build/decoder/operations/SETBE.o \
	build/decoder/operations/SETNBE.o \
	build/decoder/operations/SETS.o \
	build/decoder/operations/SETNS.o \
	build/decoder/operations/SETP.o \
	build/decoder/operations/SETNP.o \
	build/decoder/operations/SETL.o \
	build/decoder/operations/SETNL.o \
	build/decoder/operations/SETLE.o \
	build/decoder/operations/SETNLE.o \
	build/decoder/operations/BT.o \
	build/decoder/operations/SHLD.o \
	build/decoder/operations/BTS.o \
	build/decoder/operations/SHRD.o \
	build/decoder/operations/LSS.o \
	build/decoder/operations/BTR.o \
	build/decoder/operations/LFS.o \
	build/decoder/operations/LGS.o \
	build/decoder/operations/MOVZX.o \
	build/decoder/operations/BTC.o \
	build/decoder/operations/BSF.o \
	build/decoder/operations/BSR.o \
	build/decoder/operations/MOVSX.o \
	build/decoder/operations/ROL.o \
	build/decoder/operations/ROR.o \
	build/decoder/operations/RCL.o \
	build/decoder/operations/RCR.o \
	build/decoder/operations/SHL.o \
	build/decoder/operations/SHR.o \
	build/decoder/operations/SAR.o \
	build/decoder/operations/NOT.o \
	build/decoder/operations/NEG.o \
	build/decoder/operations/MUL.o \

BINDIRS = bin/ \
	build/memory \
	build/pins \
	build/status \
	build/sys \
	build/bios \
	build/utils \
	build/interrupts \
	build/decoder \
	build/decoder/operations\

OP = -std=c99 -Wall -Wvla -g -Wno-unused-variable -Wno-unused-but-set-variable -Wconversion -D DBG

GCC=gcc

bin/i386Emulator.out : mkdir  $(OBJ) 
	@echo
	@echo "-----LINK-----"
	$(GCC) $(OP) $(OBJ) -o $@
	@cp device.bin bin/
	@echo
	@echo "|-----------SUCCESSFUL-----------|"
	@echo

build: build/main.o
	
build/main.o : $(SRC) 
	@echo
	@echo "-----BUILD-----"
	$(GCC) $(OP) -c src/main.c -o $@

build/memory/physical_memory.o : src/memory/physical_memory.c src/memory/physical_memory.h
	$(GCC) $(OP) -c src/memory/physical_memory.c -o $@

build/status/status.o : src/status/status.c src/status/status.h 
	$(GCC) $(OP) -c src/status/status.c -o $@

build/memory/registers.o : src/memory/registers.c src/config.h
	$(GCC) $(OP) -c src/memory/registers.c -o $@

build/pins/pins.o : src/pins/pins.c src/config.h 
	$(GCC) $(OP) -c src/pins/pins.c -o $@

build/sys/sys.o : src/sys/sys.c  src/sys/sys.h
	$(GCC) $(OP) -c src/sys/sys.c -o $@

build/bios/bios.o : src/bios/bios.c src/bios/bios.h
	$(GCC) $(OP) -c src/bios/bios.c -o $@	

build/utils/utils.o : src/utils/utils.c src/utils/utils.h
	$(GCC) $(OP) -c src/utils/utils.c -o $@	

build/interrupts/interrupts.o : src/interrupts/interrupts.c src/interrupts/interrupts.h
	$(GCC) $(OP) -c src/interrupts/interrupts.c -o $@	

build/memory/IO.o : src/memory/IO.c src/memory/IO.h
	$(GCC) $(OP) -c src/memory/IO.c -o $@	

build/memory/address_translator.o : src/memory/address_translator.c src/memory/address_translator.h
	$(GCC) $(OP) -c src/memory/address_translator.c -o $@	

build/decoder/decoder.o : src/decoder/decoder.c src/decoder/decoder.h
	$(GCC) $(OP) -c src/decoder/decoder.c -o $@	

build/decoder/map.o : src/decoder/map.c src/decoder/map.h
	$(GCC) $(OP) -c src/decoder/map.c -o $@	

build/decoder/prefetch_queue.o : src/decoder/prefetch_queue.c src/decoder/prefetch_queue.h
	$(GCC) $(OP) -c src/decoder/prefetch_queue.c -o $@	

build/decoder/operations/ADD.o : src/decoder/operations/ADD.c src/decoder/operations/ADD.h
	$(GCC) $(OP) -c src/decoder/operations/ADD.c -o $@	

build/decoder/operations/OR.o : src/decoder/operations/OR.c src/decoder/operations/OR.h
	$(GCC) $(OP) -c src/decoder/operations/OR.c -o $@	

build/decoder/operations/ADC.o : src/decoder/operations/ADC.c src/decoder/operations/ADC.h
	$(GCC) $(OP) -c src/decoder/operations/ADC.c -o $@	

build/decoder/operations/SBB.o : src/decoder/operations/SBB.c src/decoder/operations/SBB.h
	$(GCC) $(OP) -c src/decoder/operations/SBB.c -o $@	

build/decoder/operations/AND.o : src/decoder/operations/AND.c src/decoder/operations/AND.h
	$(GCC) $(OP) -c src/decoder/operations/AND.c -o $@	

build/decoder/operations/SUB.o : src/decoder/operations/SUB.c src/decoder/operations/SUB.h
	$(GCC) $(OP) -c src/decoder/operations/SUB.c -o $@	

build/decoder/operations/XOR.o : src/decoder/operations/XOR.c src/decoder/operations/XOR.h
	$(GCC) $(OP) -c src/decoder/operations/XOR.c -o $@	

build/decoder/operations/CMP.o : src/decoder/operations/CMP.c src/decoder/operations/CMP.h
	$(GCC) $(OP) -c src/decoder/operations/CMP.c -o $@	

build/decoder/operations/INC.o : src/decoder/operations/INC.c src/decoder/operations/INC.h
	$(GCC) $(OP) -c src/decoder/operations/INC.c -o $@	

build/decoder/operations/DEC.o : src/decoder/operations/DEC.c src/decoder/operations/DEC.h
	$(GCC) $(OP) -c src/decoder/operations/DEC.c -o $@	

build/decoder/operations/PUSH.o : src/decoder/operations/PUSH.c src/decoder/operations/PUSH.h
	$(GCC) $(OP) -c src/decoder/operations/PUSH.c -o $@	

build/decoder/operations/POP.o : src/decoder/operations/POP.c src/decoder/operations/POP.h
	$(GCC) $(OP) -c src/decoder/operations/POP.c -o $@	

build/decoder/operations/DAA.o : src/decoder/operations/DAA.c src/decoder/operations/DAA.h
	$(GCC) $(OP) -c src/decoder/operations/DAA.c -o $@	

build/decoder/operations/DAS.o : src/decoder/operations/DAS.c src/decoder/operations/DAS.h
	$(GCC) $(OP) -c src/decoder/operations/DAS.c -o $@	

build/decoder/operations/AAA.o : src/decoder/operations/AAA.c src/decoder/operations/AAA.h
	$(GCC) $(OP) -c src/decoder/operations/AAA.c -o $@	

build/decoder/operations/AAS.o : src/decoder/operations/AAS.c src/decoder/operations/AAS.h
	$(GCC) $(OP) -c src/decoder/operations/AAS.c -o $@	

build/decoder/operations/PUSHA.o : src/decoder/operations/PUSHA.c src/decoder/operations/PUSHA.h
	$(GCC) $(OP) -c src/decoder/operations/PUSHA.c -o $@	

build/decoder/operations/POPA.o : src/decoder/operations/POPA.c src/decoder/operations/POPA.h
	$(GCC) $(OP) -c src/decoder/operations/POPA.c -o $@	
	
build/decoder/operations/BOUND.o : src/decoder/operations/BOUND.c src/decoder/operations/BOUND.h
	$(GCC) $(OP) -c src/decoder/operations/BOUND.c -o $@	

build/decoder/operations/ARPL.o : src/decoder/operations/ARPL.c src/decoder/operations/ARPL.h
	$(GCC) $(OP) -c src/decoder/operations/ARPL.c -o $@	

build/decoder/operations/IMUL.o : src/decoder/operations/IMUL.c src/decoder/operations/IMUL.h
	$(GCC) $(OP) -c src/decoder/operations/IMUL.c -o $@

build/decoder/operations/INSB.o : src/decoder/operations/INSB.c src/decoder/operations/INSB.h
	$(GCC) $(OP) -c src/decoder/operations/INSB.c -o $@

build/decoder/operations/INSW_D.o : src/decoder/operations/INSW_D.c src/decoder/operations/INSW_D.h
	$(GCC) $(OP) -c src/decoder/operations/INSW_D.c -o $@

build/decoder/operations/OUTSB.o : src/decoder/operations/OUTSB.c src/decoder/operations/OUTSB.h
	$(GCC) $(OP) -c src/decoder/operations/OUTSB.c -o $@

build/decoder/operations/OUTSW_D.o : src/decoder/operations/OUTSW_D.c src/decoder/operations/OUTSW_D.h
	$(GCC) $(OP) -c src/decoder/operations/OUTSW_D.c -o $@

build/decoder/operations/JO_SHORT.o : src/decoder/operations/JO_SHORT.c src/decoder/operations/JO_SHORT.h
	$(GCC) $(OP) -c src/decoder/operations/JO_SHORT.c -o $@

build/decoder/operations/JNO_SHORT.o : src/decoder/operations/JNO_SHORT.c src/decoder/operations/JNO_SHORT.h
	$(GCC) $(OP) -c src/decoder/operations/JNO_SHORT.c -o $@

build/decoder/operations/JB_SHORT.o : src/decoder/operations/JB_SHORT.c src/decoder/operations/JB_SHORT.h
	$(GCC) $(OP) -c src/decoder/operations/JB_SHORT.c -o $@

build/decoder/operations/JNB_SHORT.o : src/decoder/operations/JNB_SHORT.c src/decoder/operations/JNB_SHORT.h
	$(GCC) $(OP) -c src/decoder/operations/JNB_SHORT.c -o $@

build/decoder/operations/JZ_SHORT.o : src/decoder/operations/JZ_SHORT.c src/decoder/operations/JZ_SHORT.h
	$(GCC) $(OP) -c src/decoder/operations/JZ_SHORT.c -o $@

build/decoder/operations/JNZ_SHORT.o : src/decoder/operations/JNZ_SHORT.c src/decoder/operations/JNZ_SHORT.h
	$(GCC) $(OP) -c src/decoder/operations/JNZ_SHORT.c -o $@

build/decoder/operations/JBE_SHORT.o : src/decoder/operations/JBE_SHORT.c src/decoder/operations/JBE_SHORT.h
	$(GCC) $(OP) -c src/decoder/operations/JBE_SHORT.c -o $@

build/decoder/operations/JNBE_SHORT.o : src/decoder/operations/JNBE_SHORT.c src/decoder/operations/JNBE_SHORT.h
	$(GCC) $(OP) -c src/decoder/operations/JNBE_SHORT.c -o $@

build/decoder/operations/JS_SHORT.o : src/decoder/operations/JS_SHORT.c src/decoder/operations/JS_SHORT.h
	$(GCC) $(OP) -c src/decoder/operations/JS_SHORT.c -o $@

build/decoder/operations/JNS_SHORT.o : src/decoder/operations/JNS_SHORT.c src/decoder/operations/JNS_SHORT.h
	$(GCC) $(OP) -c src/decoder/operations/JNS_SHORT.c -o $@

build/decoder/operations/JP_SHORT.o : src/decoder/operations/JP_SHORT.c src/decoder/operations/JP_SHORT.h
	$(GCC) $(OP) -c src/decoder/operations/JP_SHORT.c -o $@

build/decoder/operations/JNP_SHORT.o : src/decoder/operations/JNP_SHORT.c src/decoder/operations/JNP_SHORT.h
	$(GCC) $(OP) -c src/decoder/operations/JNP_SHORT.c -o $@

build/decoder/operations/JL_SHORT.o : src/decoder/operations/JL_SHORT.c src/decoder/operations/JL_SHORT.h
	$(GCC) $(OP) -c src/decoder/operations/JL_SHORT.c -o $@

build/decoder/operations/JNL_SHORT.o : src/decoder/operations/JNL_SHORT.c src/decoder/operations/JNL_SHORT.h
	$(GCC) $(OP) -c src/decoder/operations/JNL_SHORT.c -o $@

build/decoder/operations/JLE_SHORT.o : src/decoder/operations/JLE_SHORT.c src/decoder/operations/JLE_SHORT.h
	$(GCC) $(OP) -c src/decoder/operations/JLE_SHORT.c -o $@

build/decoder/operations/JNLE_SHORT.o : src/decoder/operations/JNLE_SHORT.c src/decoder/operations/JNLE_SHORT.h
	$(GCC) $(OP) -c src/decoder/operations/JNLE_SHORT.c -o $@

build/decoder/operations/TEST.o : src/decoder/operations/TEST.c src/decoder/operations/TEST.h
	$(GCC) $(OP) -c src/decoder/operations/TEST.c -o $@

build/decoder/operations/XCNG.o : src/decoder/operations/XCNG.c src/decoder/operations/XCNG.h
	$(GCC) $(OP) -c src/decoder/operations/XCNG.c -o $@

build/decoder/operations/MOV.o : src/decoder/operations/MOV.c src/decoder/operations/MOV.h
	$(GCC) $(OP) -c src/decoder/operations/MOV.c -o $@

build/decoder/operations/LEA.o : src/decoder/operations/LEA.c src/decoder/operations/LEA.h
	$(GCC) $(OP) -c src/decoder/operations/LEA.c -o $@

build/decoder/operations/NOP.o : src/decoder/operations/NOP.c src/decoder/operations/NOP.h
	$(GCC) $(OP) -c src/decoder/operations/NOP.c -o $@

build/decoder/operations/XCHG.o : src/decoder/operations/XCHG.c src/decoder/operations/XCHG.h
	$(GCC) $(OP) -c src/decoder/operations/XCHG.c -o $@

build/decoder/operations/CBW.o : src/decoder/operations/CBW.c src/decoder/operations/CBW.h
	$(GCC) $(OP) -c src/decoder/operations/CBW.c -o $@

build/decoder/operations/CWD.o : src/decoder/operations/CWD.c src/decoder/operations/CWD.h
	$(GCC) $(OP) -c src/decoder/operations/CWD.c -o $@

build/decoder/operations/CALL.o : src/decoder/operations/CALL.c src/decoder/operations/CALL.h
	$(GCC) $(OP) -c src/decoder/operations/CALL.c -o $@

build/decoder/operations/WAIT.o : src/decoder/operations/WAIT.c src/decoder/operations/WAIT.h
	$(GCC) $(OP) -c src/decoder/operations/WAIT.c -o $@

build/decoder/operations/PUSHF.o : src/decoder/operations/PUSHF.c src/decoder/operations/PUSHF.h
	$(GCC) $(OP) -c src/decoder/operations/PUSHF.c -o $@

build/decoder/operations/POPF.o : src/decoder/operations/POPF.c src/decoder/operations/POPF.h
	$(GCC) $(OP) -c src/decoder/operations/POPF.c -o $@

build/decoder/operations/SAHF.o : src/decoder/operations/SAHF.c src/decoder/operations/SAHF.h
	$(GCC) $(OP) -c src/decoder/operations/SAHF.c -o $@

build/decoder/operations/LAHF.o : src/decoder/operations/LAHF.c src/decoder/operations/LAHF.h
	$(GCC) $(OP) -c src/decoder/operations/LAHF.c -o $@

build/decoder/operations/MOVSB.o : src/decoder/operations/MOVSB.c src/decoder/operations/MOVSB.h
	$(GCC) $(OP) -c src/decoder/operations/MOVSB.c -o $@

build/decoder/operations/MOVSW.o : src/decoder/operations/MOVSW.c src/decoder/operations/MOVSW.h
	$(GCC) $(OP) -c src/decoder/operations/MOVSW.c -o $@

build/decoder/operations/CMPSB.o : src/decoder/operations/CMPSB.c src/decoder/operations/CMPSB.h
	$(GCC) $(OP) -c src/decoder/operations/CMPSB.c -o $@

build/decoder/operations/CMPSW.o : src/decoder/operations/CMPSW.c src/decoder/operations/CMPSW.h
	$(GCC) $(OP) -c src/decoder/operations/CMPSW.c -o $@

build/decoder/operations/STOSB.o : src/decoder/operations/STOSB.c src/decoder/operations/STOSB.h
	$(GCC) $(OP) -c src/decoder/operations/STOSB.c -o $@

build/decoder/operations/STOSW.o : src/decoder/operations/STOSW.c src/decoder/operations/STOSW.h
	$(GCC) $(OP) -c src/decoder/operations/STOSW.c -o $@

build/decoder/operations/LODSB.o : src/decoder/operations/LODSB.c src/decoder/operations/LODSB.h
	$(GCC) $(OP) -c src/decoder/operations/LODSB.c -o $@

build/decoder/operations/LODSW.o : src/decoder/operations/LODSW.c src/decoder/operations/LODSW.h
	$(GCC) $(OP) -c src/decoder/operations/LODSW.c -o $@

build/decoder/operations/SCASB.o : src/decoder/operations/SCASB.c src/decoder/operations/SCASB.h
	$(GCC) $(OP) -c src/decoder/operations/SCASB.c -o $@

build/decoder/operations/SCASW.o : src/decoder/operations/SCASW.c src/decoder/operations/SCASW.h
	$(GCC) $(OP) -c src/decoder/operations/SCASW.c -o $@

build/decoder/operations/RET_NEAR.o : src/decoder/operations/RET_NEAR.c src/decoder/operations/RET_NEAR.h
	$(GCC) $(OP) -c src/decoder/operations/RET_NEAR.c -o $@

build/decoder/operations/LES.o : src/decoder/operations/LES.c src/decoder/operations/LES.h
	$(GCC) $(OP) -c src/decoder/operations/LES.c -o $@

build/decoder/operations/LDS.o : src/decoder/operations/LDS.c src/decoder/operations/LDS.h
	$(GCC) $(OP) -c src/decoder/operations/LDS.c -o $@

build/decoder/operations/ENTER.o : src/decoder/operations/ENTER.c src/decoder/operations/ENTER.h
	$(GCC) $(OP) -c src/decoder/operations/ENTER.c -o $@


build/decoder/operations/LEAVE.o : src/decoder/operations/LEAVE.c src/decoder/operations/LEAVE.h
	$(GCC) $(OP) -c src/decoder/operations/LEAVE.c -o $@
 
build/decoder/operations/RET_FAR.o : src/decoder/operations/RET_FAR.c src/decoder/operations/RET_FAR.h
	$(GCC) $(OP) -c src/decoder/operations/RET_FAR.c -o $@

build/decoder/operations/INT.o : src/decoder/operations/INT.c src/decoder/operations/INT.h
	$(GCC) $(OP) -c src/decoder/operations/INT.c -o $@

build/decoder/operations/INTO.o : src/decoder/operations/INTO.c src/decoder/operations/INTO.h
	$(GCC) $(OP) -c src/decoder/operations/INTO.c -o $@

build/decoder/operations/IRET.o : src/decoder/operations/IRET.c src/decoder/operations/IRET.h
	$(GCC) $(OP) -c src/decoder/operations/IRET.c -o $@

build/decoder/operations/AAM.o : src/decoder/operations/AAM.c src/decoder/operations/AAM.h
	$(GCC) $(OP) -c src/decoder/operations/AAM.c -o $@

build/decoder/operations/AAD.o : src/decoder/operations/AAD.c src/decoder/operations/AAD.h
	$(GCC) $(OP) -c src/decoder/operations/AAD.c -o $@

build/decoder/operations/XLAT.o : src/decoder/operations/XLAT.c src/decoder/operations/XLAT.h
	$(GCC) $(OP) -c src/decoder/operations/XLAT.c -o $@

build/decoder/operations/ESC_COP.o : src/decoder/operations/ESC_COP.c src/decoder/operations/ESC_COP.h
	$(GCC) $(OP) -c src/decoder/operations/ESC_COP.c -o $@

build/decoder/operations/LOOPNE.o : src/decoder/operations/LOOPNE.c src/decoder/operations/LOOPNE.h
	$(GCC) $(OP) -c src/decoder/operations/LOOPNE.c -o $@

build/decoder/operations/LOOPE.o : src/decoder/operations/LOOPE.c src/decoder/operations/LOOPE.h
	$(GCC) $(OP) -c src/decoder/operations/LOOPE.c -o $@

build/decoder/operations/LOOP.o : src/decoder/operations/LOOP.c src/decoder/operations/LOOP.h
	$(GCC) $(OP) -c src/decoder/operations/LOOP.c -o $@

build/decoder/operations/JCXZ.o : src/decoder/operations/JCXZ.c src/decoder/operations/JCXZ.h
	$(GCC) $(OP) -c src/decoder/operations/JCXZ.c -o $@

build/decoder/operations/IN.o : src/decoder/operations/IN.c src/decoder/operations/IN.h
	$(GCC) $(OP) -c src/decoder/operations/IN.c -o $@

build/decoder/operations/OUT.o : src/decoder/operations/OUT.c src/decoder/operations/OUT.h
	$(GCC) $(OP) -c src/decoder/operations/OUT.c -o $@

build/decoder/operations/HLT.o : src/decoder/operations/HLT.c src/decoder/operations/HLT.h
	$(GCC) $(OP) -c src/decoder/operations/HLT.c -o $@

build/decoder/operations/CMC.o : src/decoder/operations/CMC.c src/decoder/operations/CMC.h
	$(GCC) $(OP) -c src/decoder/operations/CMC.c -o $@

build/decoder/operations/CLC.o : src/decoder/operations/CLC.c src/decoder/operations/CLC.h
	$(GCC) $(OP) -c src/decoder/operations/CLC.c -o $@

build/decoder/operations/STC.o : src/decoder/operations/STC.c src/decoder/operations/STC.h
	$(GCC) $(OP) -c src/decoder/operations/STC.c -o $@

build/decoder/operations/CLI.o : src/decoder/operations/CLI.c src/decoder/operations/CLI.h
	$(GCC) $(OP) -c src/decoder/operations/CLI.c -o $@

build/decoder/operations/STI.o : src/decoder/operations/STI.c src/decoder/operations/STI.h
	$(GCC) $(OP) -c src/decoder/operations/STI.c -o $@

build/decoder/operations/CLD.o : src/decoder/operations/CLD.c src/decoder/operations/CLD.h
	$(GCC) $(OP) -c src/decoder/operations/CLD.c -o $@

build/decoder/operations/STD.o : src/decoder/operations/STD.c src/decoder/operations/STD.h
	$(GCC) $(OP) -c src/decoder/operations/STD.c -o $@

build/decoder/operations/LAR.o : src/decoder/operations/LAR.c src/decoder/operations/LAR.h
	$(GCC) $(OP) -c src/decoder/operations/LAR.c -o $@

build/decoder/operations/LSL.o : src/decoder/operations/LSL.c src/decoder/operations/LSL.h
	$(GCC) $(OP) -c src/decoder/operations/LSL.c -o $@

build/decoder/operations/CLTS.o : src/decoder/operations/CLTS.c src/decoder/operations/CLTS.h
	$(GCC) $(OP) -c src/decoder/operations/CLTS.c -o $@

build/decoder/operations/JO_LONG.o : src/decoder/operations/JO_LONG.c src/decoder/operations/JO_LONG.h
	$(GCC) $(OP) -c src/decoder/operations/JO_LONG.c -o $@

build/decoder/operations/JNO_LONG.o : src/decoder/operations/JNO_LONG.c src/decoder/operations/JNO_LONG.h
	$(GCC) $(OP) -c src/decoder/operations/JNO_LONG.c -o $@

build/decoder/operations/JB_LONG.o : src/decoder/operations/JB_LONG.c src/decoder/operations/JB_LONG.h
	$(GCC) $(OP) -c src/decoder/operations/JB_LONG.c -o $@

build/decoder/operations/JNB_LONG.o : src/decoder/operations/JNB_LONG.c src/decoder/operations/JNB_LONG.h
	$(GCC) $(OP) -c src/decoder/operations/JNB_LONG.c -o $@

build/decoder/operations/JZ_LONG.o : src/decoder/operations/JZ_LONG.c src/decoder/operations/JZ_LONG.h
	$(GCC) $(OP) -c src/decoder/operations/JZ_LONG.c -o $@

build/decoder/operations/JNZ_LONG.o : src/decoder/operations/JNZ_LONG.c src/decoder/operations/JNZ_LONG.h
	$(GCC) $(OP) -c src/decoder/operations/JNZ_LONG.c -o $@

build/decoder/operations/JBE_LONG.o : src/decoder/operations/JBE_LONG.c src/decoder/operations/JBE_LONG.h
	$(GCC) $(OP) -c src/decoder/operations/JBE_LONG.c -o $@

build/decoder/operations/JNBE_LONG.o : src/decoder/operations/JNBE_LONG.c src/decoder/operations/JNBE_LONG.h
	$(GCC) $(OP) -c src/decoder/operations/JNBE_LONG.c -o $@

build/decoder/operations/JS_LONG.o : src/decoder/operations/JS_LONG.c src/decoder/operations/JS_LONG.h
	$(GCC) $(OP) -c src/decoder/operations/JS_LONG.c -o $@

build/decoder/operations/JNS_LONG.o : src/decoder/operations/JNS_LONG.c src/decoder/operations/JNS_LONG.h
	$(GCC) $(OP) -c src/decoder/operations/JNS_LONG.c -o $@

build/decoder/operations/JP_LONG.o : src/decoder/operations/JP_LONG.c src/decoder/operations/JP_LONG.h
	$(GCC) $(OP) -c src/decoder/operations/JP_LONG.c -o $@

build/decoder/operations/JNP_LONG.o : src/decoder/operations/JNP_LONG.c src/decoder/operations/JNP_LONG.h
	$(GCC) $(OP) -c src/decoder/operations/JNP_LONG.c -o $@

build/decoder/operations/JL_LONG.o : src/decoder/operations/JL_LONG.c src/decoder/operations/JL_LONG.h
	$(GCC) $(OP) -c src/decoder/operations/JL_LONG.c -o $@

build/decoder/operations/JNL_LONG.o : src/decoder/operations/JNL_LONG.c src/decoder/operations/JNL_LONG.h
	$(GCC) $(OP) -c src/decoder/operations/JNL_LONG.c -o $@

build/decoder/operations/JLE_LONG.o : src/decoder/operations/JLE_LONG.c src/decoder/operations/JLE_LONG.h
	$(GCC) $(OP) -c src/decoder/operations/JLE_LONG.c -o $@

build/decoder/operations/JNLE_LONG.o : src/decoder/operations/JNLE_LONG.c src/decoder/operations/JNLE_LONG.h
	$(GCC) $(OP) -c src/decoder/operations/JNLE_LONG.c -o $@

build/decoder/operations/SETO.o : src/decoder/operations/SETO.c src/decoder/operations/SETO.h
	$(GCC) $(OP) -c src/decoder/operations/SETO.c -o $@

build/decoder/operations/SETNO.o : src/decoder/operations/SETNO.c src/decoder/operations/SETNO.h
	$(GCC) $(OP) -c src/decoder/operations/SETNO.c -o $@

build/decoder/operations/SETB.o : src/decoder/operations/SETB.c src/decoder/operations/SETB.h
	$(GCC) $(OP) -c src/decoder/operations/SETB.c -o $@

build/decoder/operations/SETNB.o : src/decoder/operations/SETNB.c src/decoder/operations/SETNB.h
	$(GCC) $(OP) -c src/decoder/operations/SETNB.c -o $@

build/decoder/operations/SETZ.o : src/decoder/operations/SETZ.c src/decoder/operations/SETZ.h
	$(GCC) $(OP) -c src/decoder/operations/SETZ.c -o $@

build/decoder/operations/SETNZ.o : src/decoder/operations/SETNZ.c src/decoder/operations/SETNZ.h
	$(GCC) $(OP) -c src/decoder/operations/SETNZ.c -o $@

build/decoder/operations/SETBE.o : src/decoder/operations/SETBE.c src/decoder/operations/SETBE.h
	$(GCC) $(OP) -c src/decoder/operations/SETBE.c -o $@

build/decoder/operations/SETNBE.o : src/decoder/operations/SETNBE.c src/decoder/operations/SETNBE.h
	$(GCC) $(OP) -c src/decoder/operations/SETNBE.c -o $@

build/decoder/operations/SETS.o : src/decoder/operations/SETS.c src/decoder/operations/SETS.h
	$(GCC) $(OP) -c src/decoder/operations/SETS.c -o $@

build/decoder/operations/SETNS.o : src/decoder/operations/SETNS.c src/decoder/operations/SETNS.h
	$(GCC) $(OP) -c src/decoder/operations/SETNS.c -o $@

build/decoder/operations/SETP.o : src/decoder/operations/SETP.c src/decoder/operations/SETP.h
	$(GCC) $(OP) -c src/decoder/operations/SETP.c -o $@

build/decoder/operations/SETNP.o : src/decoder/operations/SETNP.c src/decoder/operations/SETNP.h
	$(GCC) $(OP) -c src/decoder/operations/SETNP.c -o $@

build/decoder/operations/SETL.o : src/decoder/operations/SETL.c src/decoder/operations/SETL.h
	$(GCC) $(OP) -c src/decoder/operations/SETL.c -o $@

build/decoder/operations/SETNL.o : src/decoder/operations/SETNL.c src/decoder/operations/SETNL.h
	$(GCC) $(OP) -c src/decoder/operations/SETNL.c -o $@

build/decoder/operations/SETLE.o : src/decoder/operations/SETLE.c src/decoder/operations/SETLE.h
	$(GCC) $(OP) -c src/decoder/operations/SETLE.c -o $@

build/decoder/operations/SETNLE.o : src/decoder/operations/SETNLE.c src/decoder/operations/SETNLE.h
	$(GCC) $(OP) -c src/decoder/operations/SETNLE.c -o $@

build/decoder/operations/BT.o : src/decoder/operations/BT.c src/decoder/operations/BT.h
	$(GCC) $(OP) -c src/decoder/operations/BT.c -o $@

build/decoder/operations/SHLD.o : src/decoder/operations/SHLD.c src/decoder/operations/SHLD.h
	$(GCC) $(OP) -c src/decoder/operations/SHLD.c -o $@

build/decoder/operations/BTS.o : src/decoder/operations/BTS.c src/decoder/operations/BTS.h
	$(GCC) $(OP) -c src/decoder/operations/BTS.c -o $@

build/decoder/operations/SHRD.o : src/decoder/operations/SHRD.c src/decoder/operations/SHRD.h
	$(GCC) $(OP) -c src/decoder/operations/SHRD.c -o $@

build/decoder/operations/LSS.o : src/decoder/operations/LSS.c src/decoder/operations/LSS.h
	$(GCC) $(OP) -c src/decoder/operations/LSS.c -o $@

build/decoder/operations/BTR.o : src/decoder/operations/BTR.c src/decoder/operations/BTR.h
	$(GCC) $(OP) -c src/decoder/operations/BTR.c -o $@

build/decoder/operations/LFS.o : src/decoder/operations/LFS.c src/decoder/operations/LFS.h
	$(GCC) $(OP) -c src/decoder/operations/LFS.c -o $@

build/decoder/operations/LGS.o : src/decoder/operations/LGS.c src/decoder/operations/LGS.h
	$(GCC) $(OP) -c src/decoder/operations/LGS.c -o $@

build/decoder/operations/MOVZX.o : src/decoder/operations/MOVZX.c src/decoder/operations/MOVZX.h
	$(GCC) $(OP) -c src/decoder/operations/MOVZX.c -o $@

build/decoder/operations/BTC.o : src/decoder/operations/BTC.c src/decoder/operations/BTC.h
	$(GCC) $(OP) -c src/decoder/operations/BTC.c -o $@

build/decoder/operations/BSF.o : src/decoder/operations/BSF.c src/decoder/operations/BSF.h
	$(GCC) $(OP) -c src/decoder/operations/BSF.c -o $@

build/decoder/operations/BSR.o : src/decoder/operations/BSR.c src/decoder/operations/BSR.h
	$(GCC) $(OP) -c src/decoder/operations/BSR.c -o $@

build/decoder/operations/MOVSX.o : src/decoder/operations/MOVSX.c src/decoder/operations/MOVSX.h
	$(GCC) $(OP) -c src/decoder/operations/MOVSX.c -o $@

build/decoder/operations/ROL.o : src/decoder/operations/ROL.c src/decoder/operations/ROL.h
	$(GCC) $(OP) -c src/decoder/operations/ROL.c -o $@

build/decoder/operations/ROR.o : src/decoder/operations/ROR.c src/decoder/operations/ROR.h
	$(GCC) $(OP) -c src/decoder/operations/ROR.c -o $@

build/decoder/operations/RCL.o : src/decoder/operations/RCL.c src/decoder/operations/RCL.h
	$(GCC) $(OP) -c src/decoder/operations/RCL.c -o $@

build/decoder/operations/RCR.o : src/decoder/operations/RCR.c src/decoder/operations/RCR.h
	$(GCC) $(OP) -c src/decoder/operations/RCR.c -o $@

build/decoder/operations/SHL.o : src/decoder/operations/SHL.c src/decoder/operations/SHL.h
	$(GCC) $(OP) -c src/decoder/operations/SHL.c -o $@

build/decoder/operations/SHR.o : src/decoder/operations/SHR.c src/decoder/operations/SHR.h
	$(GCC) $(OP) -c src/decoder/operations/SHR.c -o $@

build/decoder/operations/SAR.o : src/decoder/operations/SAR.c src/decoder/operations/SAR.h
	$(GCC) $(OP) -c src/decoder/operations/SAR.c -o $@

build/decoder/operations/NOT.o : src/decoder/operations/NOT.c src/decoder/operations/NOT.h
	$(GCC) $(OP) -c src/decoder/operations/NOT.c -o $@

build/decoder/operations/NEG.o : src/decoder/operations/NEG.c src/decoder/operations/NEG.h
	$(GCC) $(OP) -c src/decoder/operations/NEG.c -o $@

build/decoder/operations/MUL.o : src/decoder/operations/MUL.c src/decoder/operations/MUL.h
	$(GCC) $(OP) -c src/decoder/operations/MUL.c -o $@

remake: 
	make clean && make

mkdir: 
	mkdir -p ${BINDIRS}

run: 
	bin/i386Emulator.out device.bin

clean: 
	rm -rf build bin

doc: 
	mkdir -p documentation
	doxygen 
rmdoc:
	rm -rf documentation
