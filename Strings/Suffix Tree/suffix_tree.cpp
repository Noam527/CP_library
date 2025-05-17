struct suffix_tree {
	static const int INFLEN = 1e9;
	int sz, n, node, pos;
	string s;
	vector<int> len, fpos, link;
	vector<int> node_of_suffix; // map suffix starting at index i to its node
	vector<int> total_len; // total length of path from root to node
	vector<map<char, int>> to;
	suffix_tree(int final_size = 0) : sz(1), n(0), node(0), pos(0) {
		int x = 2 * final_size + 10;
		s.resize(final_size);
		len.resize(x), fpos.resize(x), link.resize(x),to.resize(x);
		len[0] = INFLEN;
	}
	int make_node(int p, int l) {
		fpos[sz] = p, len[sz] = l;
		return sz++;
	}
	void go_edge() {
		while (pos > len[to[node][s[n - pos]]]) {
			node = to[node][s[n - pos]];
			pos -= len[node];
		}
	}
	void add_letter(int c) {
		s[n++] = c, pos++;
		int last = 0;
		while (pos > 0) {
			go_edge();
			int edge = s[n - pos];
			int& v = to[node][edge];
			int t = s[fpos[v] + pos - 1];
			if (v == 0) {
				v = make_node(n - pos, INFLEN);
				link[last] = node;
				last = 0;
			}
			else if (t == c) {
				link[last] = node;
				return;
			}
			else {
				int u = make_node(fpos[v], pos - 1);
				to[u][c] = make_node(n - 1, INFLEN);
				to[u][t] = v;
				fpos[v] += pos - 1;
				len[v] -= pos - 1;
				v = u;
				link[last] = u;
				last = u;
			}
			if (node == 0) pos--;
			else node = link[node];
		}
	}
	void finalize() {
		len[0] = 0;
		// fix lengths of leaves
		for (int i = 0; i < sz; i++) {
			if (to[i].size() == 0) {
				len[i] = n - fpos[i];
			}
		}
		// compute `node_of_suffix`
		node_of_suffix.assign(n, 0);
		total_len.assign(sz, 0);
		dfs(0, 0);
	}
	void dfs(int v, int totlen) {
		// IMP: you can add stuff here if needed
		total_len[v] = totlen;
		if (to[v].size() == 0) {
			node_of_suffix[fpos[v] - totlen] = v;
			return;
		}
		totlen += len[v];
		for (auto &[c, u] : to[v]) {
			dfs(u, totlen);
		}
	}
};