# Compiler and flags
CXX = clang++        # macOS / Linux default, works with g++ too
CXXFLAGS = -std=c++17 -Wall -Wextra
BUILD_DIR = build

# Source files
VERIFIER_SRC = src/verifier/verifier.cpp
# GS_SRC       = src/gale_shapley/gale_shapley.cpp
MATCHER_SRC  = src/matcher/matcher.cpp

# Executable names (inside build folder)
VERIFIER_EXE = $(BUILD_DIR)/verifier
# GS_EXE       = $(BUILD_DIR)/gale_shapley
MATCHER_EXE  = $(BUILD_DIR)/matcher

# Default target: build both
all: $(VERIFIER_EXE) $(MATCHER_EXE)

# Ensure build folder exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build verifier
$(VERIFIER_EXE): $(VERIFIER_SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Build matcher
$(MATCHER_EXE): $(MATCHER_SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Run verifier with optional input file
# Usage: make run_verifier INPUT=testcases/my_input.txt
run_verifier: $(VERIFIER_EXE)
	@INPUT_FILE=$(if $(INPUT),$(INPUT),testcases/verifier/sample_input.txt); \
	echo "Running verifier with $$INPUT_FILE"; \
	./$(VERIFIER_EXE) < $$INPUT_FILE

# Run matcher with optional input file
run_matcher: $(MATCHER_EXE)
	@INPUT_FILE=$(if $(INPUT),$(INPUT),testcases/matcher/sample_input.txt); \
	echo "Running matcher with $$INPUT_FILE"; \
	./$(MATCHER_EXE) < $$INPUT_FILE

# Run GS implementation with optional input file
# Usage: make run_gs INPUT=testcases/my_input.txt
run_gs: $(GS_EXE)
	@INPUT_FILE=$(if $(INPUT),$(INPUT),testcases/matcher/sample_input.txt); \
	./$(GS_EXE) < $$INPUT_FILE

# Clean all executables
clean:
	rm -rf $(BUILD_DIR)