### Problem Statement
Given a *commutative* data structure that handles, along with its updates and queries, an undo operation on the last operation (stack-like), and assuming each operation takes $O(f(n))$ including the undo's, this creates a the same data structure that supports undo's in a queue-like fashion, with $O(f(n)\cdot \log U)$, where $U$ is the number of updates - amortized.

### Complexity
- **Time**: Additional log factor to every update.
- **Memory**: Identical to underlying data structure
- **Amortized**

### Core Ideas
Uses commutativity to maintain the queue in the stack of updates. For proper details read the source.
In terms of implementation, you must create the underlying data structure and support `sundo` (stack-undo), then inherit from the provided class and you obtain `qundo` (queue-undo).

### Tests and Benchmarks
- DSU: https://codeforces.com/contest/1386/submission/247538111

### Source / Credit
Own. Blogpost: https://codeforces.com/blog/entry/83467