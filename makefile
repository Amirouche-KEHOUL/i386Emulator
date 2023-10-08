
SRC = src/main.c src/memory/physical_memory.c src/memory/IO.c src/memory/address_translator.c src/bios/bios.c src/sys/sys.c \
		src/pins/pins.c src/memory/registers.c src/status/status.c src/utils/utils.c src/interrupts/interrupts.c 

OBJ = build/main.o build/bios/bios.o build/sys/sys.o build/status/status.o build/memory/physical_memory.o build/memory/IO.o build/memory/registers.o \
		build/memory/address_translator.o build/pins/pins.o  build/utils/utils.o build/interrupts/interrupts.o 

BINDIRS = bin/ build/memory build/pins build/status build/sys build/bios build/utils build/interrupts

OP = -std=c99 -Wall -Wvla -g -Wno-unused-variable -Wno-unused-but-set-variable -D DBG 

GCC=gcc

bin/i386Emulator.out : mkdir  $(OBJ) 
	$(GCC) $(OP) $(OBJ) -o $@
	@cp device.bin bin/
	@echo
	@echo "|-----------SUCCESSFUL-----------|"

build/main.o : $(SRC) 
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

remake: 
	make clean && make

mkdir: 
	mkdir -p ${BINDIRS}

run: 
	bin/i386Emulator.out $(word 2, $(MAKECMDGOALS))

clean: 
	rm -rf build bin

doc: 
	mkdir -p documentation
	doxygen 
rmdoc:
	rm -rf documentation
