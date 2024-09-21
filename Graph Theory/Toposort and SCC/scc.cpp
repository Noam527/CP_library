void dfs(const vector<vector<int>>& g, vector<int>& vis, vector<int>& comp, int v) {
	if (vis[v]++) return;
	for (auto& i : g[v]) dfs(g, vis, comp, i);
	comp.push_back(v);
}
vector<vector<int>> scc(const vector<vector<int>>& g) {
	int n = g.size();
	vector<vector<int>> rev(n);
	for (int i = 0; i < n; i++) for (auto& j : g[i])
		rev[j].push_back(i);
	vector<int> vis(n), ord;
	vector<vector<int>> ans;
	for (int i = 0; i < n; i++) dfs(g, vis, ord, i);
	reverse(ord.begin(), ord.end());
	// `ord` is toposort, if graph has no cycles
	vis.assign(n, 0);
	for (auto &i : ord) {
		if (!vis[i]) {
			ans.push_back(vector<int>());
			dfs(rev, vis, ans.back(), i);
		}
	}
	return ans;
}