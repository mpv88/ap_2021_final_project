# compiler
CXX := g++

# directories
DOC_DIR := ./doxygen
ICL_DIR := ./include
OBJ_DIR := ./build
TGT_DIR := ./bin
TST_DIR := ./test

# flags
CXXFLAGS := -g -Wall -Wextra -std=c++17
INCLFLAGS := -I $(ICL_DIR)

# extensions
SRC_EXT := .cpp
ICL_EXT := .hpp || .h
OBJ_EXT := .o
EXE_EXT := .x

# paths
TESTES := $(shell find $(TST_DIR) -type f -name *$(SRC_EXT)) # $(wildcard $(TST_DIR)/*$(SRC_EXT))
INCLUDES := $(wildcard $(ICL_DIR)/*$(ICL_EXT))
OBJECTS := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SOURCES:$(SRC_EXT)=$(OBJ_EXT))) # OBJECTS := $(SOURCES:$(SRC_DIR)/%$(SRC_EXT)=$(OBJ_DIR)/%$(OBJ_EXT))
TESTS := $(patsubst $(TST_DIR)/%,$(OBJ_DIR)/%,$(TESTES:$(SRC_EXT)=$(OBJ_EXT)))

# output
BMK := bmk
TST := tests

# directives
RM := rm -rf

#---------------------------------------------------------------------------------------------------------------------

$(TGT_DIR)/$(TST)$(EXE_EXT): $(TESTS)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@
	@echo "linking completed, executable is ready!"

$(TESTS): $(OBJ_DIR)/%$(OBJ_EXT): $(TST_DIR)/%$(SRC_EXT)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLFLAGS) -c $^ -o $@
	@echo "compiled "$^" successfully!"


bmk:



clean:
	@$(RM) $(DOC_DIR)/html $(DOC_DIR)/latex $(OBJ_DIR) $(TGT_DIR)/*
	@echo "cleaned!"

clears:
	@clear
	@echo "screen cleared!"

docs: $(DOC_DIR)/doxy_config
	doxygen $<

format: $(SOURCES) $(INCLUDES) $(TESTES)
	@clang-format -i $^ -verbose || echo "Please install clang-format to run this command"
	@echo "formatted "$^" successfully!"
	
print:
	@echo "just a recurring utility for debugging Makefile"
	@echo $(INCLUDES)
	@echo $(TESTES)
		
.PHONY: all bmk clean clears docs format print

# end of file