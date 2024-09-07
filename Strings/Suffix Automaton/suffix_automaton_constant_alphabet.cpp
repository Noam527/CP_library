struct suffix_automaton {
	static const int SIZE = 26;
	static int ord(char x) {
		return x - 'a';
	}
	struct node {
		int len, link;
		int to[SIZE];
		node(int _len = -1, int _link = -1) {
			len = _len;
			link = _link;
			for (int i = 0; i < SIZE; i++) to[i] = -1;
		}
		int& operator [](int i) {
			return to[i];
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
		int x = ord(ch);
		t[last][x] = t.size();
		t.push_back(node(t[last].len + 1));
		int cur = t[last].link;
		last = t.size() - 1;

		while (cur != -1) {
			if (t[cur][x] != -1) break;
			t[cur][x] = last;
			cur = t[cur].link;
		}
		if (cur == -1) {
			t[last].link = 0;
			return;
		}
		if (t[cur].len + 1 == t[t[cur][x]].len) {
			t[last].link = t[cur][x];
			return;
		}
		int q = t[cur][x], clone = t.size();
		t.push_back(node(t[cur].len + 1));
		t[clone].link = t[q].link;
		for (int i = 0; i < SIZE; i++) t[clone][i] = t[q][i];
		t[last].link = t[q].link = clone;
		while (cur != -1) {
			if (t[cur][x] != q) break;
			t[cur][x] = clone;
			cur = t[cur].link;
		}
	}
	vector<ll> dp;
	ll dfs(int v) {
		if (dp[v] != -1) return dp[v];
		dp[v] = 1;
		for (int i = 0; i < SIZE; i++)
			if (t[v][i] != -1)
				dp[v] += dfs(t[v][i]);
		return dp[v];
	}
	ll diff_substrings() {
		dp.resize(t.size());
		for (auto &i : dp) i = -1;
		return dfs(0);
	}
};