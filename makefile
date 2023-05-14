
SRC = src/main.c src/memory/ram.c src/bios/bios.c src/sys/sys.c src/pins/pins.c src/memory/registers.c src/status/status.c
OBJ = build/main.o build/bios/bios.o build/sys/sys.o build/status/status.o build/memory/ram.o build/memory/registers.o build/pins/pins.o
ASM_DIR = src/assembler
OP = -Wall -Wvla -g 

bin/i386Emulator.out : $(OBJ)
	gcc $(OP) $(OBJ) -o bin/i386Emulator.out

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

run: 
	bin/i386Emulator.out $(word 2, $(MAKECMDGOALS))

clean: 
	rm -f $(OBJ)

mkdir: 
	mkdir -p bin/ build/memory build/pins build/status build/sys build/bios 
