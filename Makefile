# compiler
CC := g++	#simple assignment
CFLAGS = -Wall -Wextra -g -std=c++17

# directories
SRC_DIR := src
OBJ_DIR := build
TGT_DIR := bin

#extensions
SRC_EXT := .cpp
ICL_EXT := .h
OBJ_EXT := .o
TGT_EXT := .x

 # paths
SOURCES := $(wildcard $(SRC_DIR)/*$(SRC_EXT))
INCLUDE := $(wildcard $(SRC_DIR)/*$(ICL_EXT))
OBJECTS := $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SOURCES):.$(SRC_EXT)=$(OBJ_DIR):.$(OBJ_EXT))

# directives
RM := rm -f

all:



clean:
	@$(RM) $(TGT_DIR)/* $(OBJECTS)
	@echo -e "cleaned!\n"

clears:
	@clear
	@echo -e screen cleared!\n"

.PHONY: all clean clears extend_flags format test tests valgrind