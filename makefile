
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

