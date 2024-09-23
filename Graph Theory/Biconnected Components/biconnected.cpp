// Notice the IMP comments! Choose which type to compute.
struct biconnected {
	int n, b;
	vector<vector<int>> g, ans;
	vector<int> st, link, dep;
	biconnected(const vector<vector<int>> &g) : n(g.size()), b(-1), g(g), link(n), dep(n, -1) {}
	void append(int anc, int d, int r = -1) {
		if (link[anc] < d) return;
		ans.push_back({});
		if (r != -1) ans.back().push_back(r);
		while (st.back() != b)
			ans.back().push_back(st.back()), st.pop_back();
	}
	int dfs(int v, int prev, int d) {
		dep[v] = link[v] = d;
		st.push_back(v);
		for (auto &i : g[v]) {
			if (i == prev) continue;
			if (dep[i] != -1) link[v] = min(link[v], dep[i]);
			else {
				int check = st.size(); st.push_back(b);
				link[v] = min(link[v], dfs(i, v, d + 1));
				append(i, d, v); // IMP: vertex biconnected only!
				swap(st[check], st.back()); st.pop_back();
			}
		}
		append(v, d); // IMP: edge biconnected only!
		return link[v];
	}
	vector<vector<int>> calc() {
		st.push_back(b);
		for (int i = 0; i < n; i++)
			if (dep[i] == -1) {
				if (g[i].size()) dfs(i, i, 0);
				else ans.push_back({ i });
			}
		return ans;
	}
};