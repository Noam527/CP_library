// NOTE: not up to date with the constant alphabet one.
struct suffix_automaton {
	struct node {
		int len, link;
		map<char, int> to;
		node(int _len = -1, int _link = -1) {
			len = _len;
			link = _link;
		}
		bool has(char c) {
			return to.count(c);
		}
		int& operator [](char c) {
			return to[c];
		}
	};

	int last;
	vector<node> t;
	suffix_automaton(int size = -1) {
		if (size != -1)
			t.reserve(2 * size);
		last = 0;
		t.push_back(node(0));
	}
	void add(char ch) {
		t[last][ch] = t.size();
		t.push_back(node(t[last].len + 1));
		int cur = t[last].link;
		last = t.size() - 1;

		while (cur != -1) {
			if (t[cur].has(ch)) break;
			t[cur][ch] = last;
			cur = t[cur].link;
		}
		if (cur == -1) {
			t[last].link = 0;
			return;
		}
		if (t[cur].len + 1 == t[t[cur][ch]].len) {
			t[last].link = t[cur][ch];
			return;
		}
		int q = t[cur][ch], clone = t.size();
		t.push_back(node(t[cur].len + 1));
		t[clone].link = t[q].link;
		t[clone].to = t[q].to;
		t[last].link = t[q].link = clone;
		while (cur != -1) {
			if (t[cur][ch] != q) break;
			t[cur][ch] = clone;
			cur = t[cur].link;
		}
	}
	vector<ll> dp;
	ll dfs(int v) {
		if (dp[v] != -1) return dp[v];
		dp[v] = 1;
		for (auto &i : t[v].to)
			dp[v] += dfs(i.second);
		return dp[v];
	}
	ll diff_substrings() {
		dp.resize(t.size());
		for (auto &i : dp) i = -1;
		return dfs(0);
	}
};
