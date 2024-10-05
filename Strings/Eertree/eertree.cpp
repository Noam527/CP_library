struct eertree {
	static const int SIZE = 26;
	static int ord(char x) { return x - 'a'; }
	struct node {
		int len, link, to[SIZE], par;
		node(int len = 0, int par = 0, int link = 0) : len(len), link(link), par(par) {
			memset(to, 0, sizeof(to));
		}
		int& operator[](int i) { return to[i]; }
	};
	int n, last; // current string size and node of last position
	string s; // the actual string
	vector<node> t; // the tree
	vector<int> longest; // node of longest palindrome ending at i
	eertree(int elen = 0) { // optional expected length
		elen += 2;
		s.reserve(elen), t.reserve(elen), longest.reserve(elen);
		n = last = 0;
		t = { node(-1), node(0) };
	}
	void walk(int& v, char c) {
		while (n - t[v].len < 2 || c != s[n - t[v].len - 2])
			v = t[v].link;
	}
	void add(char c) {
		n++, s.push_back(c);
		walk(last, c);
		if (!t[last][ord(c)]) {
			t[last][ord(c)] = t.size();
			t.push_back(node(t[last].len + 2, last));
			if (t[last].len == -1) t.back().link = 1; // len0 node
			else {
				walk(t.back().link = t[last].link, c);
				t.back().link = t[t.back().link][ord(c)];
			}
		}
		last = t[last][ord(c)], longest.push_back(last);
	}
};