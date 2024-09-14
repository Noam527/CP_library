### Problem Statement
Link Cut tree - supports structure changes along with rerooting, path updates and path queries.

### Complexity
- **Time**: $O(\log n)$ per operation
- **Memory**: $O(n)$
- **Amortized**
- **High constant factor**

### Core Ideas
Theoretical ideas can be read elsewhere. Here's what's important to know about the idea and implementation:<br>
The tree is held as a set of vertical chains. Each vertical chain is represented by a splay tree, such that the inorder traversal of the splay tree is the order of vertices from bottom to top of the chain.<br>
The main operation is `access(v)`, which works in $O(\log n)$ (amortized) and makes it so that the path from `v` to the root is completely inside a single chain. This way, after calling access we can query about the path from `v` to the root, by looking at `v`'s value along with its right subtree value (since the right subtree is what's above it).<br>
Another basic operation is `reroot(v)` - works by accessing `v`, cutting its left child, and then reversing the splay by applying a lazy `flip` operation. So the inner splay must be lazy.<br>
For path queries, you can simply reroot at one of the ends and query on the other's path to root.<br>
As per the inner structure, each node holds its left and right child and its parent, and as for virtual children, only parent edges are held.

The current state contains 2 implementations - a tested vertex update, path sum queries, and an untested vertex update, path min queries.

### Tests and Benchmarks
- link cut, vertex modify, path sum: https://judge.yosupo.jp/submission/235661

### Source / Credit
Written by me, inspired by https://codeforces.com/blog/entry/75885