# compiler
CXX := g++
CXXFLAGS := -Wall -Wextra -g -std=c++17

# directories
DOC_DIR := ./doxygen
SRC_DIR := ./src
OBJ_DIR := ./build
TGT_DIR := ./bin
TST_DIR := ./test

# extensions
SRC_EXT := .cpp
ICL_EXT := .hpp || .h
OBJ_EXT := .o
EXE_EXT := .x

# paths
SOURCES := $(shell find $(SRC_DIR) -type f -name *$(SRC_EXT)) # $(wildcard $(SRC_DIR)/*$(SRC_EXT))
TESTES := $(shell find $(TST_DIR) -type f -name *$(SRC_EXT))
INCLUDES := $(wildcard $(SRC_DIR)/*$(ICL_EXT))
INCLFLAGS := $(addprefix -I,$(INCLUDES))
OBJECTS := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SOURCES:$(SRC_EXT)=$(OBJ_EXT))) # OBJECTS := $(SOURCES:$(SRC_DIR)/%$(SRC_EXT)=$(OBJ_DIR)/%$(OBJ_EXT))
TESTS := $(patsubst $(TST_DIR)/%,$(OBJ_DIR)/%,$(TESTES:$(SRC_EXT)=$(OBJ_EXT)))

# output
TGT := rbt
TST := tests

# directives
RM := rm -rf

#---------------------------------------------------------------------------------------------------------------------

$(TGT_DIR)/$(TGT)$(EXE_EXT): $(OBJECTS)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@
	@echo "linking completed, executable is ready!"

$(OBJECTS): $(OBJ_DIR)/%$(OBJ_EXT): $(SRC_DIR)/%$(SRC_EXT)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $^ -o $@
	@echo "compiled "$^" successfully!"

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

test: 
	$(CXX) $(CXXFLAGS) -c $(TESTES) -o $(TESTS)
	@echo "compiled "$^" successfully!"
	#$(CXX) $(CXXFLAGS) $(LDFLAGS) $(TESTS) ./build/RBT.o -o $(TGT_DIR)/$(TST)$(EXE_EXT)
	#@echo "linking completed, tests are ready!"

		
.PHONY: all clean clears docs format print test

# end of file