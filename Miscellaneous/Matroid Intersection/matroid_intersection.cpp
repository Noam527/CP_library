struct first_matroid {
	int n;
	vector<int> s; // s[i] = 0/1: current set, always independent
	// IMP: inner fields + ctor. graphic -> dsu, colorful -> freq
	void set(vector<int>& ns); // IMP: s = ns, update members
	bool can_add(int i); // IMP: return true if i can be added
	vector<int> neigh(int v); // IMP: list exchanges, s[v] = 1!
};
struct second_matroid {
	// IMP: same as above, except `neigh` is for s[v] = 0!
};
vector<int> matroid_intersection(first_matroid& m1, second_matroid& m2) {
	int n = m1.n, i;
	vector<int> s(n), vis, prev, right, adj;
	while (1) { // keep augmenting
		right.assign(n, 0);
		int total = 0;
		for (i = 0; i < n; i++) {
			if (s[i]) continue;
			if (m1.can_add(i)) right[i] |= 1;
			if (m2.can_add(i)) right[i] |= 2;
			if (right[i] == 3) break;
			total |= right[i];
		}
		if (i < n) { // easy take
			s[i] = 1;
			m1.set(s), m2.set(s);
			continue;
		}
		if (total != 3) break; // easy maximum
		vis.assign(n, 0), prev.assign(n, -1);
		queue<int> q;
		for (int i = 0; i < n; i++)
			if (right[i] & 1) q.push(i), vis[i] = 1;
		int found = -1;
		while (q.size() && found == -1) {
			int v = q.front(); q.pop();
			if (s[v]) adj = m1.neigh(v);
			else adj = m2.neigh(v);
			for (auto& i : adj) {
				if (vis[i]) continue;
				vis[i] = 1, prev[i] = v;
				if (right[i] & 2) {
					found = i;
					break;
				}
				q.push(i);
			}
		}
		if (found == -1) break; // no augmenting path
		while (found != -1)
			s[found] ^= 1, found = prev[found];
		m1.set(s), m2.set(s); // apply new
	}
	return s;
}