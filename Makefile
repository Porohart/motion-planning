CXX ?= g++

# path #
SRC_PATH = src
BUILD_PATH = build
BIN_PATH = $(BUILD_PATH)/bin

# executable # 
BIN_NAME = runner

# extensions #
SRC_EXT = cpp

# code lists #
# Find all source files in the source directory, excluding test files and main_gui.cpp
SOURCES = $(shell find $(SRC_PATH) -name '*.$(SRC_EXT)' ! -path '$(SRC_PATH)/tests/*' ! -name 'main_gui.cpp' | sort -k 1nr | cut -f2-)
# Find all test files
TEST_SOURCES = $(shell find $(SRC_PATH)/tests -name '*.$(SRC_EXT)' 2>/dev/null | sort)
# Set the object file names, with the source directory stripped
# from the path, and the build path prepended in its place
OBJECTS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
# Set the dependency files that will be used to add header dependencies
DEPS = $(OBJECTS:.o=.d)
# Test executables (one per test file)
TEST_BINS = $(TEST_SOURCES:$(SRC_PATH)/tests/%.$(SRC_EXT)=$(BIN_PATH)/test_%)

# flags #
COMPILE_FLAGS = -std=c++11 -Wall -Wextra -g
INCLUDES = -I src -I src/framework -I src/robots/2d -I src/planners/2d -I /usr/local/include -I /usr/include/SFML
# Space-separated pkg-config libraries used by this project
# SFML libraries (adjust paths if SFML is installed elsewhere)
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

.PHONY: default_target
default_target: release

.PHONY: release
release: export CXXFLAGS := $(CXXFLAGS) $(COMPILE_FLAGS)
release: dirs
	@$(MAKE) all

.PHONY: dirs
dirs:
	@echo "Creating directories"
	@mkdir -p $(dir $(OBJECTS))
	@mkdir -p $(BIN_PATH)
	@mkdir -p $(BUILD_PATH)/tests

.PHONY: clean
clean:
	@echo "Deleting $(BIN_NAME) symlink"
	@$(RM) $(BIN_NAME)
	@echo "Deleting directories"
	@$(RM) -r $(BUILD_PATH)
	@$(RM) -r $(BIN_PATH)

# checks the executable and symlinks to the output
.PHONY: all
all: $(BIN_PATH)/$(BIN_NAME)
	@echo "Making symlink: $(BIN_NAME) -> $<"
	@$(RM) $(BIN_NAME)
	@ln -s $(BIN_PATH)/$(BIN_NAME) $(BIN_NAME)

# Run the executable
.PHONY: run
run: all
	@echo "Running $(BIN_NAME)..."
	@./$(BIN_NAME)

# Build all tests
.PHONY: tests
tests: $(TEST_BINS)
	@echo "All tests built"

# Run all tests
.PHONY: test
test: tests
	@echo "Running all tests..."
	@for test_bin in $(TEST_BINS); do \
		echo "Running $$test_bin..."; \
		$$test_bin || exit 1; \
		echo ""; \
	done
	@echo "All tests passed!"

# Run a specific test (e.g., make test_1)
.PHONY: test_1
test_1: $(BIN_PATH)/test_1
	@echo "Running test_1..."
	$(BIN_PATH)/test_1

# Build GUI executable
GUI_OBJECTS = $(filter-out $(BUILD_PATH)/main.o, $(OBJECTS)) $(BUILD_PATH)/main_gui.o
$(BIN_PATH)/gui_runner: $(SRC_PATH)/main_gui.cpp $(GUI_OBJECTS) | dirs
	@echo "Building GUI executable: $@"
	@mkdir -p $(BIN_PATH)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $(SRC_PATH)/main_gui.cpp -o $(BUILD_PATH)/main_gui.o
	$(CXX) $(BUILD_PATH)/main_gui.o $(filter-out $(BUILD_PATH)/main.o, $(OBJECTS)) -o $@ ${LIBS}
	@rm -f $(BUILD_PATH)/main_gui.d

# Run GUI
.PHONY: gui
gui: $(BIN_PATH)/gui_runner
	@echo "Running GUI..."
	$(BIN_PATH)/gui_runner

# Creation of the executable
$(BIN_PATH)/$(BIN_NAME): $(OBJECTS)
	@echo "Linking: $@"
	$(CXX) $(OBJECTS) -o $@ ${LIBS}

# Add dependency files, if they exist
-include $(DEPS)

# Source file rules
# After the first compilation they will be joined with the rules from the
# dependency files to provide header dependencies
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@echo "Compiling: $< -> $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@

# Test executable rules
# Each test file gets compiled with all source objects (excluding main.cpp and other test files)
TEST_OBJECTS = $(filter-out $(BUILD_PATH)/main.o, $(OBJECTS))
$(BIN_PATH)/test_%: $(SRC_PATH)/tests/%.$(SRC_EXT) $(TEST_OBJECTS) | dirs
	@echo "Building test: $@"
	@mkdir -p $(BUILD_PATH)/tests $(BIN_PATH)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $(BUILD_PATH)/tests/$*.o
	$(CXX) $(BUILD_PATH)/tests/$*.o $(TEST_OBJECTS) -o $@ ${LIBS}
	@rm -f $(BUILD_PATH)/tests/$*.d