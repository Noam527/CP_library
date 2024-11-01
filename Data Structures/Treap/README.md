### Problem Statement
BBST, with range updates and range queries

### Complexity
- **Time**: $(\log n)$ *expected* per operation
- **Memory**: $O(n)$

### Core Ideas
Treap assigns each node a random priority, and maintains the tree so that it is:
- a BST based on node values
- a heap based on node priorities

Then, by identical analysis to quicksort, the expected depth is $O(\log n)$. It can also hold an implicit list, instead of holding sorted values.<br>
In practice it is very easy to implement, since all you need to implement are short codes for splitting and merging - then any other operation takes a few lines.<br>
The only downside is that it is recursive.

### Tests and Benchmarks
- Range flip updates, range sum queries: https://judge.yosupo.jp/submission/235609
- Same problem, after fix: https://judge.yosupo.jp/submission/245864
- Dynamic array (insert and erase), with range reverse & affine updates, and range sum queries: https://judge.yosupo.jp/submission/246281

### Source / Credit
Own