/*
* Dinitz's algorithm to compute maximum flow, with capacity scaling.
* Template variable:
*   - flow_t: Integer type big enough to store the flow on every edge and the maximum flow.
*/
template<typename flow_t = int>
struct MaxFlow {
	struct edge {
		int to;
		flow_t c;
		edge(int to = -1, flow_t c = 0) : to(to), c(c) {}
	};
	int n;
	vector<edge> edges;
	vector<vector<int>> g; // indicies in edges list
	MaxFlow(int n) : n(n) {
		g.resize(n);
	}
	void add_edge(int from, int to, flow_t cap, flow_t rev_cap = 0) {
		g[from].push_back(edges.size());
		edges.push_back(edge(to, cap));
		g[to].push_back(edges.size());
		edges.push_back(edge(from, rev_cap));
	}
	// dinic blocking flow (with required f)
	bool bflow(vector<int>& curedge, const vector<int>& level, int v, int t, flow_t f) {
		if (v == t) return true;
		for (int& i = curedge[v]; i < g[v].size(); i++) {
			int eind = g[v][i];
			edge& e = edges[eind];
			if (e.c >= f && level[e.to] == level[v] + 1) {
				if (bflow(curedge, level, e.to, t, f)) {
					e.c -= f;
					edges[eind ^ 1].c += f;
					return true;
				}
			}
		}
		return false;
	}
	flow_t calc(int s, int t) {
		flow_t result = 0;
		flow_t D = numeric_limits<flow_t>::max();
		while (D != (D & -D)) D ^= D & -D;

		vector<int> level(n), curedge(n);
		while (D > 0) {
			do {
				level.assign(n, -1);
				curedge.assign(n, 0);
				queue<int> q;
				q.push(s);
				level[s] = 0;
				while (q.size()) {
					int x = q.front();
					q.pop();
					for (const auto& i : g[x]) {
						edge& e = edges[i];
						if (e.c >= D && level[e.to] == -1) {
							level[e.to] = level[x] + 1;
							q.push(e.to);
						}
					}
				}
				while (bflow(curedge, level, s, t, D))
					result += D;
			} while (level[t] != -1);
			D /= 2;
		}
		return result;
	}
	// example feature: get all edges from v s.t their final flow is 0.
	vector<int> get_saturated_edges(int from) {
		vector<int> result;
		for (const auto& i : g[from])
			if (edges[i].c == 0)
				result.push_back(edges[i].to);
		return result;
	}
};