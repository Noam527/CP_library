### Problem Statement
An extension of the queue undo trick - insert updates with unique priorities and undo the update of maximum priority.
Can be used to solve offline dynamic connectivity, for example.

### Complexity
- **Time**: Same as queue undo, with slightly bigger constant.
- **Memory**: Same as queue undo
- **Amortized**

### Core Ideas
Similar to queue undo. However what we do with each undo, is that we undo $k$ updates s.t the updates with the topmost $\frac{k}{2}$ priorities are among the undone updates. Then we redo updates, first the lower half and then the upper half.

With careful bookkeeping, the procedure of finding this $k$ takes an $O(k + \log U)$ per undo, which means it does not increase time complexity even if the underlying data structure operates in $O(1)$.

### Tests and Benchmarks
- Dynamic connectivity (1e5 vertices, 2e5 updates in 0.43s): https://cses.fi/problemset/result/10959592/
- Another super cool application (almost trivializes div1E): https://codeforces.com/contest/603/submission/287650823

### Source / Credit
Inspired by monogon's blogpost on the extension: https://codeforces.com/blog/entry/111117<br>
Implementation is my own