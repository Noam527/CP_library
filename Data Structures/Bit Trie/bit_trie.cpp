template<typename T>
struct trie {
	T bcnt; // bit count of each entry
	vector<array<int, 2>> ch;
	vector<int> c, p;
	trie(T bit_count = 31) : bcnt(bit_count) {
		ch.resize(2, { 0,0 });
		c = p = { 0, 0 };
	}
	int go(int u, int dir) {
		if (ch[u][dir]) return ch[u][dir];
		p.push_back(u), c.push_back(0);
		ch.push_back({ 0,0 });
		return ch[u][dir] = ch.size() - 1;
	}
	int access(T v) {
		int cur = 1;
		for (T b = bcnt; b--;)
			cur = go(cur, v >> b & 1);
		return cur;
	}
	void add_occ(T v, int occ) { // occurences can be negative!
		int cur = access(v);
		while (cur) c[cur] += occ, cur = p[cur];
	}
	void insert(T v) { add_occ(v, 1); }
	void erase(T v) { add_occ(v, -1); }
	T min_xor(T v) { // assumes nonempty
		int cur = 1;
		T res = 0;
		for (T b = bcnt; b--;) {
			int dir = (v >> b & 1);
			if (c[ch[cur][dir]] > 0)
				cur = ch[cur][dir];
			else
				cur = ch[cur][!dir], res |= 1LL << b;
		}
		return res;
	}
	T max_xor(T v) { return ((1LL << v) - 1) ^ min_xor(v); }
};