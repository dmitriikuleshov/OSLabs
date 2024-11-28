# Makefile for dynamic library project

CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -I$(LIB_DIR) # Path to header files is specified
LDFLAGS = -shared

# Directories
SRC_DIR = src
LIB_DIR = lib
BUILD_DIR = build

# Libraries
LIB1 = $(BUILD_DIR)/lib1.so
LIB2 = $(BUILD_DIR)/lib2.so

# Header files
LAB1_H = $(LIB_DIR)/lib1.h
LAB2_H = $(LIB_DIR)/lib2.h

# Sources of the libraries
SRC1 = $(SRC_DIR)/lib1.c
SRC2 = $(SRC_DIR)/lib2.c

# Sources of the test programs
STATIC_TEST = $(SRC_DIR)/main_static.c
DYNAMIC_TEST = $(SRC_DIR)/main_dynamic.c

# Test programs
STATIC_BIN = $(BUILD_DIR)/test_static
DYNAMIC_BIN = $(BUILD_DIR)/test_dynamic

# Common flags
DLFLAGS = -ldl -lm

.PHONY: all clean

# Main goal: build the whole project
all: $(BUILD_DIR) $(LIB1) $(LIB2) $(STATIC_BIN) $(DYNAMIC_BIN)

# Create the build directory, if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build lib1.so
$(LIB1): $(SRC1) $(LAB1_H)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< -lm

# Build lib2.so
$(LIB2): $(SRC2) $(LAB2_H)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< -lm

# Build test_static (with linking to lib1.so)
$(STATIC_BIN): $(STATIC_TEST) $(LIB1)
	$(CC) $(CFLAGS) -o $@ $< -L$(BUILD_DIR) -l1 -Wl,-rpath=$(BUILD_DIR) -lm

# Build test_dynamic (dynamic linking of libraries)
$(DYNAMIC_BIN): $(DYNAMIC_TEST)
	$(CC) $(CFLAGS) -o $@ $< $(DLFLAGS)

# Clean up
clean:
	rm -rf $(BUILD_DIR)