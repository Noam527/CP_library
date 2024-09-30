### Problem Statement
Given a set of **open** halfplanes, computes their intersection, with respect to the following points:
- If the intersection is infinite, returns early and notifies about it.
- If the intersection is empty, indicates it as well.
- Otherwise, returns the set of half planes defining the intersection, in counter-clockwise order. Thus their adjacent intersection points define the convex polygon that is the intersection.

### Complexity
- **Time**: $O(n \log n)$, or $O(n)$ if the half planes arrive sorted by angle (but you need to implement the logic yourself)
- **Memory**: $O(n)$
- **High constant factor**

### Core Ideas
After sorting by angle and removing half planes with identical angle (keeping only the most strict one), the main idea is to keep a stack of relevant half planes - when inserting a new one, repeatedly remove the last one from the stack if it is redundant with respect to its 2 neighbors (the previous one and the new half plane).

To handle the infinite case, before the stack loop we can check if there exists a neighboring pair of half planes whose angle is large enough to allow an infinite intersection.<br>
To handle the empty case, one can prove that throughout the stack loop, if a new half plane makes the intersection empty, then necessarily we will keep popping until we need to compute the intersection with a line that differs from us by at least 180 degrees. On this condition the stack loop stops popping, and checks whether the intersection of these 3 half planes is empty. If it isn't the popping breaks anyway.

The issue with the stack is that after going through the entire list, both the start of the list and the end may be invalid, and need to be compared against each other.<br>
To cover for this annoying issue, some people implement the logic using a deque and for every insertion, clear from both sides.<br>
What I prefer doing, is doing the entire loop 3 times. Then the stack is formed from 3 "increasing" subsegments of half planes, and I take the middle one, which got fixed properly from the first and last subsegments.

### Tests and Benchmarks
- Not a direct problem, but uses this only as an emptiness check: https://codeforces.com/gym/101309/submission/283818338
- Same as above, without calling `sort` since it is sorted beforehand, slightly faster: https://codeforces.com/gym/101309/submission/283825604

### Source / Credit
Own