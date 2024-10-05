struct centroid_decomp {
	int n, cursize, mn, mnv, root;
	vector<int> level, par;
	vector<vector<int>>& g; // notice the &
	centroid_decomp(vector<vector<int>>& g) :
		g(g), n(g.size()), level(n, -1), par(n) {
		root = decomp(0, 0);
	}
	int find(int v, int p) {
		int sz = 1;
		for (auto& i : g[v])
			if (i != p && level[i] == -1) sz += find(i, v);
		if (2 * sz >= cursize && sz < mn)
			mn = sz, mnv = v;
		return sz;
	}
	int decomp(int v, int l) {
		cursize = find(v, v);
		mn = n + 1;
		find(v, v), v = mnv; // now v is centroid
		level[v] = l;
		for (auto& i : g[v])
			if (level[i] == -1) par[decomp(i, l + 1)] = v;
		return v;
	}
};