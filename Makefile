# compiler
CXX := g++

# directories
BMK_DIR := ./bmk
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
BMKES := $(shell find $(BMK_DIR) -type f -name *$(SRC_EXT))
TESTES := $(shell find $(TST_DIR) -type f -name *$(SRC_EXT)) # $(wildcard $(TST_DIR)/*$(SRC_EXT))
INCLUDES := $(wildcard $(ICL_DIR)/*$(ICL_EXT))
BMKS := $(patsubst $(BMK_DIR)/%,$(OBJ_DIR)/%,$(BMKES:$(SRC_EXT)=$(OBJ_EXT)))
TESTS := $(patsubst $(TST_DIR)/%,$(OBJ_DIR)/%,$(TESTES:$(SRC_EXT)=$(OBJ_EXT)))

# output
BMK := bmk
TST := tests

# directives
RM := rm -rf

#---------------------------------------------------------------------------------------------------------------------

all: $(TGT_DIR)/$(TST)$(EXE_EXT) $(TGT_DIR)/$(BMK)$(EXE_EXT)

$(TGT_DIR)/$(TST)$(EXE_EXT): $(TESTS)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@
	@echo "linking completed, executable is ready!"

$(TESTS): $(OBJ_DIR)/%$(OBJ_EXT): $(TST_DIR)/%$(SRC_EXT)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLFLAGS) -c $^ -o $@
	@echo "compiled "$^" successfully!"

#------

$(TGT_DIR)/$(BMK)$(EXE_EXT): $(BMKS)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@
	@echo "linking completed, executable is ready!"

$(BMKS): $(OBJ_DIR)/%$(OBJ_EXT): $(BMK_DIR)/%$(SRC_EXT)
	$(CXX) $(CXXFLAGS) $(INCLFLAGS) -c $^ -o $@
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
	@echo $(BMKES)
		
.PHONY: all clean clears docs format print

# end of file