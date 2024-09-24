// Usage: call `add` on all chars, then finalize, then query.
struct suffix_automaton {
	static const int SIZE = 26;
	static int ord(char x) { return x - 'a'; }
	struct node {
		int len, link;
		int to[SIZE];
		bool term; // [OPT1] is terminal
		int fpos, lpos, cpos; // [OPT2] first/last/count occur
		node(int len = 0, int link = 0) : len(len), link(link) {
			memset(to, 0, sizeof(to));
			term = false; // [OPT1]
			fpos = 1e9, lpos = -1, cpos = 0; // [OPT2]
		}
		int& operator [](int i) { return to[i]; }
	};
	int last;
	vector<node> a;
	suffix_automaton(int size = -1) : last(1) {
		if (size != -1) a.reserve(2 * size + 10);
		a.push_back(node(-1)), a.push_back(node(0)); // dummy,root
	}
	void add(char ch) {
		int x = ord(ch), cur = a[last].link;
		a[last][x] = a.size();
		a.push_back(node(a[last].len + 1));
		last = a.size() - 1;
		a[last].cpos = 1; // [OPT2]
		while (cur) {
			if (a[cur][x]) break;
			a[cur][x] = last; cur = a[cur].link;
		}
		if (!cur) {
			a[last].link = 1; // root
			return;
		}
		if (a[cur].len + 1 == a[a[cur][x]].len) {
			a[last].link = a[cur][x];
			return;
		}
		int q = a[cur][x], clone = a.size();
		a.push_back(a[q]);
		a[clone].len = a[cur].len + 1;
		a[clone].cpos = 0; // [OPT2]
		a[last].link = a[q].link = clone;
		while (cur) {
			if (a[cur][x] != q) break;
			a[cur][x] = clone, cur = a[cur].link;
		}
	}
	// OPTIONALS
	void finalize() {
		calc_terminal(); // [OPT1]
		posdfs(1); // [OPT2]
		calc_cpos(); // [OPT2]
	}
	void calc_terminal() { // [OPT1]
		int cur = last;
		while (cur) a[cur].term = true, cur = a[cur].link;
	}
	void posdfs(int v) { // [OPT2]
		if (a[v].lpos != -1) return;
		if (a[v].term) a[v].fpos = a[v].lpos = a[last].len - 1;
		for (int i = 0; i < SIZE; i++) if (a[v][i]) {
			posdfs(a[v][i]);
			a[v].fpos = min(a[v].fpos, a[a[v][i]].fpos - 1);
			a[v].lpos = max(a[v].lpos, a[a[v][i]].lpos - 1);
		}
	}
	void calc_cpos() { // [OPT2]
		vector<vector<int>> b(a[last].len + 1);
		for (int i = 2; i < a.size(); i++)
			b[a[i].len].push_back(i);
		for (int s = a[last].len; s >= 1; s--)
			for (auto &i : b[s])
				a[a[i].link].cpos += a[i].cpos;
	}
	// Number of distinct substrings. No optionals needed.
	vector<ll> dp;
	ll dfs(int v) {
		if (dp[v]) return dp[v];
		dp[v] = 1;
		for (int i = 0; i < SIZE; i++)
			if (a[v][i]) dp[v] += dfs(a[v][i]);
		return dp[v];
	}
	ll distinct() {
		dp.assign(a.size(), 0LL);
		return dfs(1) - 1;
	}
	// Smallest substring of length k. No optionals needed.
	string smallest(int k) {
		if (k > a[last].len) return "";
		int v = 1, i;
		string ans = "";
		while (k--) {
			for (i = 0; i < SIZE && !a[v][i]; i++);
			ans.push_back('a' + i); // IMP: depending on alphabet
			v = a[v][i];
		}
		return ans;
	}
	// Longest common substring. Requires [OPT1][OPT2].
	// Returns (length, end index in s, end index in other)
	array<int, 3> common_substr(const string &other) {
		int v = 1, len = 0;
		int maxlen = 0, ps = -1, pother = -1;
		for (int i = 0; i < other.size(); i++) {
			int o = ord(other[i]);
			while (v > 1 && !a[v][o])
				v = a[v].link, len = a[v].len;
			if (a[v][o])
				v = a[v][o], len++;
			if (maxlen < len) {
				maxlen = len;
				pother = i;
				ps = a[v].fpos;
			}
		}
		return { maxlen, ps, pother };
	}
};