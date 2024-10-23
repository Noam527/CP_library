### Problem Statement
Big integer (as an array of `uint32_t`) and fractions with basic operations in bad time complexity - aimed at exact geometry problems.
The integer is signed.

### Complexity
- **Time**: Depending on operation, but a small polynomial in $N$, for a number with $32N$ bits.
- **Memory**: Exact number of required bits :)

### Core Ideas
To store a signed integer, I imitate how regular integers work:
- For operations `+`, `-`, `*` the number is regarded as an unsigned integer, since it really is just modulo with a specific shift.
- Comparison is signed by regarding the largest bits as signed.
- Division and modulo are signed.

### Tests and Benchmarks
- For local tests see the files beginning with `test`.

### Source / Credit
Own.