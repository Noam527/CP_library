/*
Description:
This structure is a minimum-sized DFA that accepts exactly the suffixes of a given string.
Its size is linear, and its construction is also linear (up to language related complexities).

The starting node is 0. Each node has its outgoing edges via "to".
Each node represents a set of indicies of the given string: the equivalence class that corresponds to this node.
in other words, a path T in the automaton reaches this node, iff the string T appears as a substring of S, ending at exactly those indicies.
the length of a node is the maximum such string T: the maximum length of a path from the source to this node.
Lastly, each node has a suffix link: if you consider any substring whose occurrences end up at exactly the set of indicies of our node,
then take the largest suffix of this substring that occurs strictly more in S - the suffix link points to the node corresponding to that suffix.
Equivalently, a node representing index set I, has a suffix link to the node whose index set is the smallest one containing I.
*/
// constant alphabet
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

// dynamic alphabet
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
