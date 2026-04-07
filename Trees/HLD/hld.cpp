/*
This HLD implementation provides a re-indexing of tree vertices, so that every path can be represented as O(log n) ranges.
In addition, every subtree can be represented as a single range.
The provided functions:
- segtree_index: the new index of the vertex in the segment tree.
- subtree_range: a range representing a subtree
- upward_path_ranges: a collection of O(log n) ranges representing a path from a lower vertex to an upper vertex, in this order.
- lca + path_ranges: if asked for, can also provide O(log n) ranges for arbitrary paths by computing lca.
*/
struct HLD {
	int n;
	vector<vector<int>> g;
	vector<int> in, out, root, dep, par;
	// lca component
	int l;
	vector<vector<int>> up;
	HLD() {}
	HLD(const vector<vector<int>>& G, bool prepare_lca, int tree_root = 0) {
		g = G;
		n = g.size();
		in.resize(n), out.resize(n), root.resize(n), dep.resize(n), par.resize(n);
		dfs0(tree_root, -1, 0);
		int tim = 0;
		dfs1(tree_root, tree_root, tim);
		if (prepare_lca) {
			l = 1;
			while ((1 << l) <= n) l++;
			up.resize(l, vector<int>(n));
			for (int i = 0; i < n; i++)
				up[0][i] = par[i];
			up[0][tree_root] = tree_root;
			for (int b = 1; b < l; b++)
				for (int i = 0; i < n; i++)
					up[b][i] = up[b - 1][up[b - 1][i]];
		}
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
	
	// jump up from v, d edges
	int jump(int v, int d) {
		d = min(d, n - 1);
		for (int b = 0; (1 << b) <= d; b++)
			if (d & (1 << b))
				v = up[b][v];
		return v;
	}

	int lca(int u, int v) {
		if (dep[u] < dep[v]) swap(u, v);
		u = jump(u, dep[u] - dep[v]);
		if (u == v) return u;
		for (int b = l - 1; b >= 0; b--) {
			if (up[b][u] != up[b][v]) {
				u = up[b][u];
				v = up[b][v];
			}
		}
		return up[0][u];
	}
	vector<pair<int, int>> path_ranges(int u, int v) {
		int ancestor = lca(u, v);
		vector<pair<int, int>> left = upward_path_ranges(u, ancestor), right = upward_path_ranges(v, ancestor);
		// remove the lca from v's path before merging
		right.back().first++;
		if (right.back().first > right.back().second)
			right.pop_back();
		for (auto& i : right)
			left.push_back(i);
		return left;
	}
};