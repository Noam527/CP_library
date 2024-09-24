### Problem Statement
Given a string $S$, the suffix automaton is a minimum-sized DFA whose language is precisely the suffixes of $S$.<br>
It turns out that such DFA has at most $2|S| - 1$ vertices and $3|S| - 4$ edges (each edge corresponds to a single character).

### Complexity
- **Time**: $O(n)$ for constant alphabet, $O(n \log k)$ for non-constant alphabet of size $k$.
- **Memory**: $O(nk)$ in constant alphabet version, $O(n)$ in non-constant alphabet.
- **Amortized**

### Core Ideas
The main idea behind what each node represents is the Myhill-Nerode theorem.<br>
For a string $x$, let $I(x)$ be the set of indicies at which $x$ *ends* as a substring in $S$. Let two substrings $x, y$ of $S$ be in the same equivalence class (from now "class"), if $I(x) = I(y)$. It is clear that we can allow all strings of the same class to arrive at the same node, when walked on from the start of the DFA, and this is minimal.

This is exactly the DFA that is being built. Some observations and definitions:
- All strings of the same class are suffixes of one another, and their lengths are contiguous. Denote with $len(v)$ the maximum length of the class corresponding to node $v$.
- For every $x, y$, the sets $I(x), I(y)$ are either disjoint or contain one another. This is already enough to notice that the size of the DFA is bounded by $2|S| - 1$.
- For every node $u$ there exists a minimal class that strictly contains the class of $u$, denoted by vertex $v$. Then the length ranges of $u$ and $v$ are together contiguous. We will define the link / suffix link of u: $link(u) = v$.
- Suffix links form a tree that directs into the root / starting vertex, which represents the empty string (all indicies). We will define the link of the root to be a fictive node (in practice, with ID -1).

With this in mind, the automaton is built character by character. An addition is $O(1)$ **amortized**, and works as follows:
- Let the new character be $c$. Create a new node for the entire string, and an edge from the previous entire string to the new node.
- Keep jumping to the suffix links of the previous entire string, and while they have no $c$-edge, direct them to the new node.
- Once you arrive at a node $u$ that already has a $c$-edge to $v$, the only thing left to compute is the suffix link of the new node. This part is tricky since it might require creating another new node:<br>
We are looking for the longest proper suffix of the new string that appears more than once. The longest substring of node $u$ with the addition of $c$ (of length $len(u) + 1$) is indeed a suffix that appears twice, but it is also the longest one - had there been a longer one, we would stop jumping on suffix links before reaching $u$. **However**, node $v$ might be of greater length! So here is what happens:
  - If $len(v) = len(u) + 1$, you can set the suffix link to $v$ and finish.
  - Otherwise, a new node $w$ must be created, that is a clone of $v$, except that $len(w) = len(u) + 1$. Now the suffix link of both $v$ and the entire string will be to $w$, but we must also redirect $c$-edges going into $v$, into $w$. So we keep jumping from $u$ and as long as their $c$-edge is to $v$, we change it to $w$.

Finally, here are some nice properties helpful to problemsolving:
- A string $x$ is a substring of $S$ iff there exists a path for $x$. We can use this to count distinct substrings as the number of paths in the DAG.
- The accepting states of the automaton can be found by looking at the node of the entire string, and its path to root in the suffix link chain.
- To find the lexicographically minimum suffix, simply jump on the smallest edges until an accepting state is reached. The $k$-th lexicographically minimal suffix / substring can also be found in a similar manner.
- To count the number of occurrences of a substring, we need to compute $|I(x)|$ for every node. Observe that it is exactly 1 for the nodes created not be cloning, and otherwise, if we look at the suffix links tree, then it is the number of such nodes in the subtree. So we can set it to `1` for all non-cloned nodes, and then iterate on nodes in decreasing order of length and do `count[link[v]] += count[v]`.

### Tests and Benchmarks
- Longest common substring: https://judge.yosupo.jp/submission/237849
- Number of distinct substrings: https://judge.yosupo.jp/submission/237848
- Minimal cyclic shift: https://cses.fi/problemset/result/10615012/
- Find if pattern exists: https://cses.fi/problemset/result/10615040/
- Count pattern occurrences: https://cses.fi/problemset/result/10615158/
- Find first pattern occurrence: https://cses.fi/problemset/result/10615165/

### Source / Credit
- Read up on: https://cp-algorithms.com/string/suffix-automaton.html