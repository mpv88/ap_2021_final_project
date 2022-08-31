# compiler
CXX := g++
CXXFLAGS := -Wall -Wextra -g -std=c++17

# directories
DOC_DIR := ./doxygen
SRC_DIR := ./src
OBJ_DIR := ./build
TGT_DIR := ./bin

# extensions
SRC_EXT := .cpp
ICL_EXT := .h
OBJ_EXT := .o
TARGET := rbt.x

# paths
SOURCES := $(shell find $(SRC_DIR) -type f -name *$(SRC_EXT)) # $(wildcard $(SRC_DIR)/*$(SRC_EXT))
INCLUDES := $(wildcard $(SRC_DIR)/*$(ICL_EXT))
INCLFLAGS := $(addprefix -I,$(INCLUDES))
OBJECTS := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SOURCES:$(SRC_EXT)=$(OBJ_EXT))) # OBJECTS := $(SOURCES:$(SRC_DIR)/%$(SRC_EXT)=$(OBJ_DIR)/%$(OBJ_EXT))

# directives
RM := rm -rf

#---------------------------------------------------------------------------------------------------------------------

$(TGT_DIR)/$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@ # $(CXX) $(LDFLAGS) $(OBJECTS) -o $(TGT_DIR)/$(TARGET) 
	@echo "linking completed!"

$(OBJECTS): $(OBJ_DIR)/%$(OBJ_EXT): $(SRC_DIR)/%$(SRC_EXT)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $^ -o $@
	@echo "compiled "$^" successfully!"

clean:
	@$(RM) $(OBJ_DIR) $(TGT_DIR)/$(TARGET)
	@echo "cleaned!"

clears:
	@clear
	@echo "screen cleared!"

docs: ./doxygen/doxy_config
	doxygen $<

format: 
	$(SOURCES) $(INCLUDES)
	@clang-format -i $^ -verbose || echo "Please install clang-format to run this command"
	@echo "formatted "$^" successfully!"
	
print:
	echo $(SOURCES)
	
.PHONY: all clean clears docs format test valgrind print