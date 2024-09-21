// usage: first add all edges, then call `finalize`, then query
struct bipartite_matching {
	int n, m, s, t;
	Dinic D;
	int match_val;
	bipartite_matching(int n, int m) : n(n), m(m), s(n + m), t(n + m + 1), D(t + 1) {
		for (int i = 0; i < n; i++) D.add_edge(s, i, 1);
		for (int i = 0; i < m; i++) D.add_edge(i + n, t, 1);
	}
	// 0 <= l < n, 0 <= r < m
	void add_edge(int l, int r) { D.add_edge(l, r + n, 1); }
	void finalize() { match_val = D.calc(s, t); }
	// Optionals below
	int match_size() { return match_val; }
	vector<pair<int, int>> match() { return D.get_match(n, m); }
	// returns vertices of minimum cover, with right side mapped to [n,n+m)
	vector<int> cover() {
		vector<int> res;
		for (int i = 0; i < n; i++)
			if (!D.leftOfMinCut(i)) res.push_back(i);
		for (int i = n; i < n + m; i++)
			if (D.leftOfMinCut(i)) res.push_back(i);
		return res;
	}
};