
SRC = src/main.c src/memory/ram.c
OBJ = build/main.o build/sys/sys.o build/status/status.o build/memory/ram.o build/memory/registers.o build/pins/pins.o
OP = 
i386.out : $(OBJ)
	gcc $(OBJ) -o bin/i386Emulator.out

build/main.o : $(SRC) 
	gcc $(OP) -c src/main.c -o build/main.o

build/memory/ram.o : src/memory/ram.c
	gcc $(OP) -c src/memory/ram.c -o build/memory/ram.o

build/status/status.o : src/status/status.c 
	gcc $(OP) -c src/status/status.c -o build/status/status.o

build/memory/registers.o : src/memory/registers.c src/config.h
	gcc $(OP) -c src/memory/registers.c -o build/memory/registers.o

build/pins/pins.o : src/pins/pins.c src/config.h 
	gcc $(OP) -c src/pins/pins.c -o build/pins/pins.o

build/sys/sys.o : src/sys/sys.c 
	gcc $(OP) -c src/sys/sys.c -o build/sys/sys.o

clean: 
	rm -f $(OBJ)
