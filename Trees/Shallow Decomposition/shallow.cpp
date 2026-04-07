/*
Provided a graph (by reference) and a root to begin from, performs a shallow decomposition:
  1. Every vertex is assigned a non-negative label, so that a path between two vertices of equal label goes through a larger label
  2. The largest used label is minimized, and is at most floor(log2(n)).
This runs in O(n), then provides the following:
  1. croot: the root of the decomposition
  2. label[v]: the label of vertex v
  3. par[v]: the parent of v in the decomposition; the unique vertex u of minimum label strictly larger than label[v],
             that is reachable via vertices of labels strictly less than label[v].
For any pair of vertices u v, their LCA on their parent chains is some node on the path between them.
*/
struct shallow_decomp {
	// floor(log2(x)), unless x is 0 and then it's -1
	static inline int flog2(int x) {
		return x ? 31 - __builtin_clz(x) : -1;
	}
	int n, croot;
	const vector<vector<int>> &g;
	vector<int> label, par;
	shallow_decomp(const vector<vector<int>> &graph, int root = 0) : g(graph), n((int)g.size()) {
		label.assign(n, -1);
		par.assign(n, -1);
		vector<vector<int>> stacks(flog2(n) + 1);
		dfs_label(root, root, stacks);
		int pre = -1;
		for (int i = flog2(n); i >= 0; i--) {
			if (stacks[i].size() == 0) continue;
			int v = stacks[i].back();
			if (pre == -1) croot = v;
			else par[v] = pre;
			pre = v;
		}
	}
	int dfs_label(int v, int pre, vector<vector<int>> &stacks) {
		int seen = 0, twice = 0;
		vector<int> vals;
		for (auto &i : g[v]) {
			if (i == pre) continue;
			int st = dfs_label(i, v, stacks);
			vals.push_back(st);
			twice |= seen & st;
			seen |= st;
		}
		int l = flog2(twice) + 1;
		while (seen & (1 << l)) l++;
		reverse(vals.begin(), vals.end());
		for (auto s : vals) {
			int b = flog2(s & -s);
			if (l <= b) continue;
			int u = stacks[b].back(); stacks[b].pop_back();
			s ^= s & -s;
			while (s) {
				b = flog2(s & -s);
				if (l <= b) break;
				int u2 = stacks[b].back(); stacks[b].pop_back();
				s ^= s & -s;
				par[u] = u2;
				u = u2;
			}
			par[u] = v;
		}
		label[v] = l;
		stacks[l].push_back(v);
		return seen & ~((1 << l) - 1) | (1 << l);
	}
};