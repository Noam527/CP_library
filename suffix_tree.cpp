// currently works for lowercase letters. alter 'sigma' and 'toi' if you need otherwise.
// also change N to 2 * strlen + 10.
struct suffix_tree {
	static const int sigma = 26;
	static const int N = 2 * 100000 + 10;
	static int toi(char c) {
		return c - 'a';
	}
	string s;
	int to[N][sigma], link[N], pos[N], len[N], suf[N], par[N];
	int new_node;
	int next_suf, next_suf_pos, backwards;
	suffix_tree() {
		s = "";
		memset(to, 0, sizeof(to));
		memset(link, 0, sizeof(link));
		memset(pos, 0, sizeof(pos));
		memset(len, 0, sizeof(len));
		memset(suf, 0, sizeof(suf));
		memset(par, 0, sizeof(par));
		new_node = 1;
		next_suf = next_suf_pos = 0;
		backwards = 0;
	}
	int buy() {
		return new_node++;
	}
	void add(char ch) {
		int p = toi(ch);
		s.push_back(ch);
	}
};
