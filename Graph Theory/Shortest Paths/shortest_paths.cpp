const ll inf = 2e18;
struct edge {
	int from, to; // directed from -> to
	ll w;
	edge(int f, int t, ll w) : from(f), to(t), w(w) {}
	bool operator < (const edge& e) const { return w > e.w; } // DIJKSTRA ONLY, `>` INTENTIONAL
};
// dist[v] == inf if no path, dist[v] == -inf if there exists a negative cycle on the path
void bellmanford(int n, const vector<edge>& e, int src, vector<int>& prev, vector<ll>& dist) {
	dist.assign(n, inf);
	prev.assign(n, -1);
	dist[src] = 0;
	for (int it = n; it--;) for (auto& i : e) {
		if (dist[i.from] != inf && dist[i.to] > dist[i.from] + i.w) {
			dist[i.to] = dist[i.from] + i.w;
			prev[i.to] = i.from;
			if (!it) dist[i.to] = -inf; // in negative cycle
		}
	}
	for (int it = n; it--;) for (auto& i : e)
		if (dist[i.from] == -inf)
			dist[i.to] = -inf;
}
void dijkstra(const vector<vector<edge>>& g, int src, vector<int>& prev, vector<ll>& dist) {
	int n = g.size();
	dist.assign(n, inf);
	prev.assign(n, -1);
	priority_queue<edge> q;
	q.push(edge(-1, src, 0));
	while (q.size()) {
		edge x = q.top(); q.pop();
		if (dist[x.to] < inf) continue;
		dist[x.to] = x.w, prev[x.to] = x.from;
		for (const auto& i : g[x.to])
			q.push(edge(x.to, i.to, x.w + i.w));
	}
}
void floyd_warshall(vector<vector<ll>>& D) { // D[i][j] = inf if no edge i->j
	int n = D.size();
	for (int i = 0; i < n; i++) D[i][i] = 0;
	for (int k = 0; k < n; k++) // K 1st
		for (int i = 0; i < n; i++) // I 2nd
			for (int j = 0; j < n; j++) // J 3rd
				D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
}