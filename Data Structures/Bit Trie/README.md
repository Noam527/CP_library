### Problem Statement
Maintain a set of non-negative integers (insertions and deletions), while being able to answer the query:<br>
Given an integer `v`, which element currently in the set, minimizes / maximizes its xor with `v`.

### Complexity
- **Time**: $O(B)$ for each operation, where $B$ is the number of bits of the given numbers.
- **Memory**: $O(nB)$, where $n$ is the number of insertions made.

### Core Ideas
Trie over the bitstrings of the provided integers, starting from most significant bit. Each node holds its 2 children (possibly null children, represented by index 0), and the number of leaves currently existing in the subtree.<br>
To maintain that, just implement an `access` method to get to a leaf (and possibly create the path), then add or subtract occurrences on the path to the root.

### Tests and Benchmarks
- Same as problem statement, for minimization: https://judge.yosupo.jp/submission/236908

### Source / Credit
Own