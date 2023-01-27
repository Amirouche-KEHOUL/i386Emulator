
SRC = src/main.c src/memory/ram.c
OBJ = build/main.o build/memory/ram.o 

i386.out : $(OBJ)
	gcc $(OBJ) -o bin/i386Emulator.out

build/main.o : $(SRC) 
	gcc -c src/main.c -I src/memory -o build/main.o

build/memory/ram.o : src/memory/ram.c
	gcc -c src/memory/ram.c -o build/memory/ram.o

clean: 
	rm -f $(OBJ)
