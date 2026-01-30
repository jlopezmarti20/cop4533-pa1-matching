# =============================
# Compiler and flags
# =============================
CXX = clang++        # macOS / Linux default, works with g++ too
CXXFLAGS = -std=c++17 -Wall -Wextra
BUILD_DIR = build

# =============================
# Source files
# =============================
# Core logic (no main)
MATCHER_CORE   = src/matcher/matcher.cpp
VERIFIER_CORE  = src/verifier/verifier.cpp

# Executable mains
MATCHER_MAIN   = src/matcher/matcher_main.cpp
VERIFIER_MAIN  = src/verifier/verifier_main.cpp
TIMER_MAIN     = src/measure_time/measure_time.cpp

# =============================
# Executable names
# =============================
MATCHER_EXE    = $(BUILD_DIR)/matcher
VERIFIER_EXE   = $(BUILD_DIR)/verifier
TIMER_EXE      = $(BUILD_DIR)/measure_time

# =============================
# Default target: build all
# =============================
all: $(MATCHER_EXE) $(VERIFIER_EXE) $(TIMER_EXE)

# =============================
# Ensure build folder exists
# =============================
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# =============================
# Build matcher executable
# =============================
$(MATCHER_EXE): $(MATCHER_CORE) $(MATCHER_MAIN) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# =============================
# Build verifier executable
# =============================
$(VERIFIER_EXE): $(VERIFIER_CORE) $(VERIFIER_MAIN) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# =============================
# Build timer executable
# Links only the logic, no other mains
# =============================
$(TIMER_EXE): $(TIMER_MAIN) $(MATCHER_CORE) $(VERIFIER_CORE) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# =============================
# Run targets
# =============================
run_verifier: $(VERIFIER_EXE)
	@INPUT_FILE=$(if $(INPUT),$(INPUT),testcases/verifier/sample_input.txt); \
	echo "Running verifier with $$INPUT_FILE"; \
	./$(VERIFIER_EXE) < $$INPUT_FILE

run_matcher: $(MATCHER_EXE)
	@INPUT_FILE=$(if $(INPUT),$(INPUT),testcases/matcher/sample_input.txt); \
	echo "Running matcher with $$INPUT_FILE"; \
	./$(MATCHER_EXE) < $$INPUT_FILE

run_measure_time: $(TIMER_EXE)
	echo "Running timer function"; \
	./$(TIMER_EXE)

# =============================
# Clean all executables
# =============================
clean:
	rm -rf $(BUILD_DIR)