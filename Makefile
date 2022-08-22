# compiler
CXX := g++	#simple assignment
CXXFLAGS := -Wall -Wextra -g -std=c++17

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
INCLUDES := $(wildcard $(SRC_DIR)/*$(ICL_EXT))
OBJECTS := $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SOURCES):.$(SRC_EXT)=$(OBJ_DIR):.$(OBJ_EXT))

# directives
RM := rm -rf

all:
	$(TGT_DIR)/%.$(TGT_EXT): $(OBJECTS) (INCLUDES) 													# alternative $(TGT_DIR):
		$(CXX) $^ -o $(TGT_DIR)
		@echo "linking completed!\n"

	$(OBJ_DIR)/%.$(OBJ_EXT): $(SRC_DIR)/%.$(SRC_EXT) $(INCLUDES)
		@mkdir -p $(OBJ_DIR) $(TGT_DIR)
		$(CXX) -c $< -o $@ $(CXXFLAGS)
		@echo "compiled "$<" successfully!\n"

clean:
	@$(RM) $(OBJECTS) $(TGT_DIR)
	@echo "cleaned!\n"

clears:
	@clear
	@echo "screen cleared!\n"

format: $(SOURCES) $(INCLUDES)
	@clang-format -i $^ -verbose || echo "Please install clang-format to run this command" 			# '2>/dev/null' alternative to verbose
	@echo "formatted "$^" successfully!\n"

.PHONY: all clean clears extend_flags format test tests valgrind