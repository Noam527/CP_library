struct node {
	int rank, v;
	ll k;
	node* l, * r;
	node(int rank, ll k, int v, node* l, node* r) :
		rank(rank), k(k), v(v), l(l), r(r) {}
	bool operator < (const node& a) const { return 0; }
};
node* insert(node* t, ll k, int v) {
	if (!t || k < t->k)
		return new node(1, k, v, t, nullptr);
	node* l = t->l, * r = insert(t->r, k, v);
	if (!l || l->rank < r->rank) swap(l, r);
	return new node(r ? r->rank + 1 : 1, t->k, t->v, l, r);
}
// Dijkstra from library
struct edge {
	int from, to; // directed from -> to
	ll w;
	edge(int f, int t, ll w) : from(f), to(t), w(w) {}
	bool operator < (const edge& e) const { return w > e.w; } // DIJKSTRA ONLY, `>` INTENTIONAL
};
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

vector<ll> k_shortest(const vector<vector<edge>>& g, int s, int t, int k) {
	int n = g.size();
	vector<vector<edge>> rev(n);
	vector<vector<int>> to(n);
	vector<int> par;
	vector<ll> dist, ans;
	vector<node*> h(n);
	queue<int> q;
	
	for (int i = 0; i < n; i++)
		for (auto& j : g[i])
			rev[j.to].emplace_back(j.to, i, j.w);
	dijkstra(rev, t, par, dist);
	if (dist[s] == inf) return {}; // no paths
	for (int i = 0; i < n; i++)
		if (par[i] != -1) to[par[i]].push_back(i);
	q.push(t);
	while (q.size()) {
		int u = q.front(); q.pop();
		bool found = false;
		for (auto& i : g[u]) {
			if (dist[i.to] == inf) continue;
			ll cost = dist[i.to] + i.w - dist[u];
			if (!found && i.to == par[u] && cost == 0) {
				found = true;
				continue;
			}
			h[u] = insert(h[u], cost, i.to);
		}
		for (auto& i : to[u]) {
			h[i] = h[u];
			q.push(i);
		}
	}
	using pln = pair<ll, node*>;
	priority_queue<pln, vector<pln>, greater<pln>> pq;
	ans.push_back(dist[s]);
	if (!h[s]) return ans; // just 1 path...
	pq.emplace(dist[s] + h[s]->k, h[s]);
	while (ans.size() < k && pq.size()) {
		ll w;
		node* u;
		tie(w, u) = pq.top(); pq.pop();
		ans.push_back(w);
		if (h[u->v]) pq.emplace(w + h[u->v]->k, h[u->v]);
		if (u->l) pq.emplace(w + u->l->k - u->k, u->l);
		if (u->r) pq.emplace(w + u->r->k - u->k, u->r);
	}
	return ans;
}