# Makefile located in the parent directory of libs

# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -O2

# Source files directory
SRC_DIR = libs

# Output files directory
BIN_DIR = $(SRC_DIR)/bin

# Collect all C files in the SRC_DIR
SOURCES = $(wildcard $(SRC_DIR)/*.c)

# Define object files based on source files
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SOURCES))

# Default target
all: $(OBJECTS) day1

# Rule to make object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile and link the day1 executable
day1: day1.c $(BIN_DIR)/utils.o $(BIN_DIR)/sort.o
	$(CC) $(CFLAGS) day1.c $(BIN_DIR)/sort.o $(BIN_DIR)/utils.o `pkg-config --cflags --libs glib-2.0` -o day1

# Clean target to remove object files and executables
clean:
	rm -f $(BIN_DIR)/*.o day1

