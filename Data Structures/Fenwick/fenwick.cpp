/**
 * 0-indexed.
 * T should be a numeric type.
 */
template<typename T>
struct fenwick {
	int n;
	vector<T> t;
	fenwick() {}
	fenwick(int sz) {
		n = sz;
		t.resize(n + 1);
	}
	void add(int i, T x) {
		for (i++; i <= n; i += i & -i) t[i] += x;
	}
	T query(int i) {
		T res(0);
		for (i++; i; i ^= i & -i) res += t[i];
		return res;
	}
	T query(int l, int r) {
		return query(r) - query(l - 1);
	}
	// returns i for the first i >= 0 such that good(query(0, i)).
	// returns -1 if good(0).
	// returns n if none.
	template<class F>
	int first(const F &good) {
		if (good(0)) return -1;
		T val(0); // will always satisfy !good(val)
		int index = 0; // in our 1-indexed world, [1, index] is the current range
		int jmp = 1;
		while (2 * jmp <= n) jmp *= 2;
		while (jmp) {
			int nxt = index | jmp;
			if (nxt <= n && !good(val + t[nxt])) {
				index = nxt;
				val += t[nxt];
			}
			jmp /= 2;
		}
		return index;
	}
};