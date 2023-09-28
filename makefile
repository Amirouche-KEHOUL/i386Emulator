
SRC = src/main.c src/memory/ram.c src/bios/bios.c src/sys/sys.c src/pins/pins.c src/memory/registers.c src/status/status.c src/screen/screen.c src/utils/utils.c
OBJ = build/main.o build/bios/bios.o build/sys/sys.o build/status/status.o build/memory/ram.o build/memory/registers.o build/pins/pins.o build/screen/screen.o build/utils/utils.o

OP = -Wall -Wvla -g -Wno-unused-variable

bin/i386Emulator.out : mkdir  $(OBJ) 
	gcc $(OP) $(OBJ) -o bin/i386Emulator.out
	@cp device.bin bin/
	@echo "----SUCCESSFUL----"

build/main.o : $(SRC) 
	gcc $(OP) -c src/main.c -o build/main.o

build/memory/ram.o : src/memory/ram.c src/memory/ram.h
	gcc $(OP) -c src/memory/ram.c -o build/memory/ram.o

build/status/status.o : src/status/status.c src/status/status.h 
	gcc $(OP) -c src/status/status.c -o build/status/status.o

build/memory/registers.o : src/memory/registers.c src/config.h
	gcc $(OP) -c src/memory/registers.c -o build/memory/registers.o

build/pins/pins.o : src/pins/pins.c src/config.h 
	gcc $(OP) -c src/pins/pins.c -o build/pins/pins.o

build/sys/sys.o : src/sys/sys.c  src/sys/sys.h
	gcc $(OP) -c src/sys/sys.c -o build/sys/sys.o

build/bios/bios.o : src/bios/bios.c src/bios/bios.h
	gcc $(OP) -c src/bios/bios.c -o build/bios/bios.o	

build/screen/screen.o : src/screen/screen.c src/screen/screen.h
	gcc $(OP) -c src/screen/screen.c -o build/screen/screen.o	

build/utils/utils.o : src/utils/utils.c src/utils/utils.h
	gcc $(OP) -c src/utils/utils.c -o build/utils/utils.o	


mkdir: 
	mkdir -p bin/ build/memory build/pins build/status build/sys build/bios build/screen build/utils

run: 
	bin/i386Emulator.out $(word 2, $(MAKECMDGOALS))

clean: 
	rm -rf build bin

doc: 
	mkdir -p documentation
	doxygen 
rmdoc:
	rm -rf documentation
