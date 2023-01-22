
i386.out : main.c
	gcc main.c -I memory/ram.h -o i386Emulator.out
	
clean : 
	rm -f i386Emulator
