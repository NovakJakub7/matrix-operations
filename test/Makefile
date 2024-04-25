# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -I../src -I../unity/src   # Compiler flags

# Directories
SRC_DIR = ../src
UNITY_DIR = ../unity/src

# Source files
SRC_FILES = $(SRC_DIR)/matrix.c $(UNITY_DIR)/unity.c
TEST_FILE = test_matrix.c

# Object files
OBJ_FILES = $(patsubst %.c, %.o, $(SRC_FILES)) $(patsubst %.c, %.o, $(TEST_FILE))

# Executable file for unit tests
TEST_TARGET = test_matrix

# OS detection
ifeq ($(OS),Windows_NT)
    # Windows-specific settings
    RM = del /Q
    MKDIR = mkdir
    RMDIR = rmdir /Q /S
    TARGET_EXTENSION = .exe
    OBJ_FILES_DEL = $(subst /,\,$(OBJ_FILES))
else
    # Unix/Linux-specific settings
    RM = rm -f
    MKDIR = mkdir -p
    RMDIR = rm -rf
    TARGET_EXTENSION =
    OBJ_FILES_DEL = $(OBJ_FILES)
endif

# Main target
all: $(TEST_TARGET) run_tests

# Build test executable
$(TEST_TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run unit tests
run_tests: $(TEST_TARGET)
	./$(TEST_TARGET)$(TARGET_EXTENSION)

# Clean target to remove object files and executables
clean:
	$(RM) $(OBJ_FILES_DEL) $(TEST_TARGET) $(TARGET_EXTENSION)

# Create output directories if they don't exist
create_dirs:
	$(MKDIR) ../bin
	$(MKDIR) ../logs

.PHONY: all run_tests clean create_dirs