# Compiler and Assembler
CC = gcc
ASM = nasm

# Output executable
TARGET = erdem-linux

# Source files
ASM_SRC = erdem-linux.s
C_SRC = main.c

# Object files
ASM_OBJ = erdem-linux.o
C_OBJ = main.o

# Default rule
all: $(TARGET) run

# Assemble the NASM file
$(ASM_OBJ): $(ASM_SRC)
	$(ASM) -f elf64 $< -o $@

# Compile the C file
$(C_OBJ): $(C_SRC)
	$(CC) -c $< -o $@

# Link everything into the final executable
$(TARGET): $(ASM_OBJ) $(C_OBJ)
	$(CC) $(ASM_OBJ) $(C_OBJ) -o $(TARGET)

run:
	./$(TARGET)

# Clean up build files
clean:
	rm -f $(ASM_OBJ) $(C_OBJ) $(TARGET)
