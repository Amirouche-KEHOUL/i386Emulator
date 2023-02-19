
BUILD_DIR = ../../build/assembler
BIN_DIR = ../../bin/assembler
OBJ = $(BUILD_DIR)/main.o $(BUILD_DIR)/status/status.o $(BUILD_DIR)/parser/parser.o 
OP =

$(BIN_DIR)/i386asm.out : $(OBJ)
	gcc $(OBJ) -o $(BIN_DIR)/i386asm.out

$(BUILD_DIR)/main.o : main.c
	gcc $(OP) -c main.c -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/status/status.o : status/status.c
	gcc $(OP) -c status/status.c -o $(BUILD_DIR)/status/status.o

$(BUILD_DIR)/parser/parser.o : parser/parser.c
	gcc $(OP) -c parser/parser.c -o $(BUILD_DIR)/parser/parser.o

clean: 
	rm -f $(OBJ)

mkdir : 
	mkdir -p $(BIN_DIR) $(BUILD_DIR) $(BUILD_DIR)/status $(BUILD_DIR)/parser 
