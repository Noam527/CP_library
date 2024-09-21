struct Dinic {
	struct Edge {
		int to, rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};
	vector<int> lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void add_edge(int a, int b, ll c, ll rcap = 0) {
		adj[a].push_back({ b, (int)adj[b].size(), c, c });
		adj[b].push_back({ a, (int)adj[a].size() - 1, rcap, rcap });
	}
	ll dfs(int v, int t, ll f) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < adj[v].size(); i++) {
			Edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0; q[0] = s;
		for (int L = 30; L >= 0; L--) do {
			lvl = ptr = vector<int>(q.size());
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (Edge e : adj[v])
					if (!lvl[e.to] && e.c >> L)
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool leftOfMinCut(int a) { return lvl[a] != 0; }
	// OPTIONAL: implement for bipartite matching
	vector<pair<int, int>> get_match(int n, int m) {
		vector<pair<int, int>> a;
		for (int i = 0; i < n; i++)
			for (auto &j : adj[i])
				if (j.c == 0 && n <= j.to && j.to < n + m)
					a.emplace_back(i, j.to - n);
		return a;
	}
};