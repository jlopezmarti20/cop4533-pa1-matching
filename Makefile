# Compiler and flags
CXX = clang++        # macOS / Linux default, works with g++ too
CXXFLAGS = -std=c++17 -Wall -Wextra

# Source files
VERIFIER_SRC = src/verifier/verifier.cpp
# GS_SRC       = src/gale_shapley/gale_shapley.cpp

# Executable names
VERIFIER_EXE = verifier
# GS_EXE       = gale_shapley # change if needed

# Default target: build both
all: $(VERIFIER_EXE) #$(GS_EXE)

# Build verifier
$(VERIFIER_EXE): $(VERIFIER_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Build Gale–Shapley implementation
# $(GS_EXE): $(GS_SRC)
# 	$(CXX) $(CXXFLAGS) $^ -o $@

# Run verifier with optional input file
# Usage: make run_verifier INPUT=testcases/my_input.txt
run_verifier: $(VERIFIER_EXE)
	@INPUT_FILE=$(if $(INPUT),$(INPUT),testcases/sample_input.txt); \
	echo "Running verifier with $$INPUT_FILE"; \
	./$(VERIFIER_EXE) < $$INPUT_FILE

# Run GS implementation with optional input file
# Usage: make run_gs INPUT=testcases/my_input.txt
run_gs: $(GS_EXE)
	./$(GS_EXE) < ${INPUT:-testcases/sample_input.txt}

# Clean all executables
clean:
	rm -f $(VERIFIER_EXE) $(GS_EXE)