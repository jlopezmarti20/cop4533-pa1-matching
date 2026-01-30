# cop4533-pa1-matching

## Members:

- Jesus Lopez: 1328-5108
- Christian Betancourt Dias: 3082-3881

---

## Build Instructions

This project uses a Makefile to compile all programs.

To build everything (matcher, verifier, and timing program), run:

`make`

Note that the user must have a compiler locally installed such as `g++` or `clang++` with support for `c++17` for Makefile to work as intended.

---

## Running the Matcher

### Assumptions for input structure:

- First line: integer `n`
- Next `n` lines: hospital preference lists.
- Next `n` lines: student preference lists.

Each preference list must be composed of `n` distinct choices from `1 to n`

To run the matcher using the provided sample input file:

`make run_matcher`

---

## Running the Verifier

### Assumptions for input structure:

- First line: integer `n`
- Next `x` lines: hospital preference lists, which may or may not contain duplicates.
- Next `y` lines: student preference lists, which may or may not contain duplicates.
- Next `n` lines: Pairs in the form of `h s` where h and/or s may or may not be duplicates.

The verifier does not assume that each preference list for each hospital is of size `n` or that each preference is a permutation of `1 ... n`. Additionally, a pair may or may not be stable (hence why we have the verifier).

To run the verifier using the provided sample input file:

`make run_verifier`

---

Both `matcher` and `verifier` can be run using an optional input file as follows:

`make run_matcher INPUT=path/to/input.txt`

`make run_verifier INPUT=path/to/input.txt`

---

## Example Inputs and Outputs

Example input files are provided under the `testcases/` directory:

- `testcases/matcher/sample_input.txt`
- `testcases/verifier/sample_input.txt`

The corresponding expected outputs are:

- `testcases/matcher/expected_output.txt`
- `testcases/verifier/expected_output.txt`

These outputs can be reproduced by running the matcher or verifier with the sample input files and redirecting the output to a file.

## Task C: Scalability Analysis

We evaluated how the runtime of the hospital-proposing Gale Shapley matcher and the verifier scales as the number gospitals/students increases. We tested values of n = 1,2,4,8,16,32,64,128,256, and 512.

For each n, random preference lists were generated in memory. The matcher was run first, and its output was then passed directly to the verifier using the same preferences. For ensuring accuurate results, all input is valid (no duplicates, right size, etc), additionally, matches passed to `verifier` for time tests are stable and of correct size. Both components were timed using `chrono`, and the measured runtimes were written to CSV files.

The collected timing data was plotted using a Python script (`analysis/graph.py`) with matplotlib to visualize how runtime changes as n grows.

### Observed Trend

As n increases, the runtime of both the matcher and verifier increases. The matcher grows at a steady rate, consistent with the expected quadratic behavior of the GS algorithm. In contrast, the verifier grows much faster, since checking validity and stability requires examining many hospital–student pairs such as blocking pair, missing matches, etc. This difference becomes especially noticeable at larger values of n, where verification dominates the total runtime.

![Matcher vs Verifier Runtime](analysis/figures/runtime_plot.png)
