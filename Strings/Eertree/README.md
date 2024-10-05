### Problem Statement
Given a string, build the eertree of it (palindrome tree).<br>
Only constant size is implemented, but changing to dynamic alphabet is just changing `array` to `unordered_map`.

### Complexity
- **Time**: $O(n)$ for constant size alphabet, $O(n \log \Sigma)$ for non-constant alphabet.
- **Memory**: $O(n)$.
- **Amortized**

### Core Ideas
The eertree / palindromic tree of a string is a structure that efficiently maintains all palindromic substrings of the string.<br>
Since any string has at most $n$ distinct palindromic substrings, and any palindrome of length $l$ can be stripped to one of length $l - 2$, they can be maintained as a tree:
- Each node represents a palindrome, with 2 additional nodes - the empty even palindrome (length 0), and the empty odd palindrome (length -1). Thus, the tree will have at most $n + 2$ nodes.
- The node's children are palindromic substrings of length larger by 2, which contain it with an additional character $c$ at the start and end. The label of the edge to the child is $c$ - each node has at most $\Sigma$ children.
- Children of node of length -1 are palindromes of length 1, and children of node of length 0 are palindromes of length 2.
- Each node also maintains a suffix link - to the longest palindrome that is a strict suffix of it. Notice that:
  - any node of length at least 2 has a link to a node of length at least 1.
  - any node of length 1 has a link to the node of length 0.
  - the node of length 0 has a link to the node of length -1.

The structure is built by appending characters to the end of the string, while maintaining for each position the longest palindrome ending there. A character addition takes $O(1)$ amortized time, and may create at most 1 new node to the tree.<br>
Using the suffix links, it is quite simple to compute the node corresponding to the new string (after the character addition), and also to compute its suffix link.

### Tests and Benchmarks
- Directly eertree: https://judge.yosupo.jp/submission/240004

### Source / Credit
The implementation is my own, but the idea is from the paper: https://arxiv.org/pdf/1506.04862