/*
This HLD implementation provides a re-indexing of tree vertices, so that every path can be represented as O(log n) ranges.
In addition, every subtree can be represented as a single range.
The provided functions:
- segtree_index: the new index of the vertex in the segment tree.
- subtree_range: a range representing a subtree
- upward_path_ranges: a collection of O(log n) ranges representing a path from a lower vertex to an upper vertex, in this order.
*/
struct HLD {
	int n;
	vector<vector<int>> g;
	vector<int> in, out, root, dep, par;
	HLD() {}
	HLD(const vector<vector<int>>& G, int tree_root = 0) {
		g = G;
		n = g.size();
		in.resize(n), out.resize(n), root.resize(n), dep.resize(n), par.resize(n);
		dfs0(tree_root, -1, 0);
		int tim = 0;
		dfs1(tree_root, tree_root, tim);
	}
	// put heaviest at 0 and remove prev
	int dfs0(int v, int prev, int d) {
		dep[v] = d;
		par[v] = prev;
		int sz = 1, mx = 0;
		auto prev_it = find(g[v].begin(), g[v].end(), prev);
		if (prev_it != g[v].end())
			g[v].erase(prev_it);
		for (int i = 0; i < g[v].size(); i++) {
			int s = dfs0(g[v][i], v, d + 1);
			if (mx < s) {
				mx = s;
				swap(g[v][0], g[v][i]);
			}
			sz += s;
		}
		return sz;
	}
	// define order and chain roots
	void dfs1(int v, int r, int &tim) {
		root[v] = r;
		in[v] = tim++;
		if (g[v].size()) {
			dfs1(g[v][0], r, tim);
			for (int i = 1; i < g[v].size(); i++)
				dfs1(g[v][i], g[v][i], tim);
		}
		out[v] = tim - 1;
	}
	
	int segtree_index(int vertex) {
		return in[vertex];
	}

	pair<int, int> subtree_range(int vertex) {
		return { in[vertex], out[vertex] };
	}

	vector<pair<int, int>> upward_path_ranges(int lower, int upper) {
		vector<pair<int, int>> result;
		int pupper = par[upper];
		while (lower != pupper) {
			int r = root[lower];
			if (dep[r] < dep[upper])
				r = upper;
			result.emplace_back(in[r], in[lower]);
			lower = par[r];
		}
		return result;
	}
};