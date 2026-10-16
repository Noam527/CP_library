/**
 * 0-indexed.
 * T should be a numeric type.
 */
template<typename T>
struct fenwick2D {
	int n;
	vector<vector<T>> t;
	fenwick2D() {}
	fenwick2D(int sz) {
		n = sz;
		t.resize(n + 1, vector<T>(n + 1, 0));
	}
	void add(int i, int j, T x) {
		for (int ii = i + 1; ii <= n; ii += ii & -ii) {
			for (int jj = j + 1; jj <= n; jj += jj & -jj) {
				t[ii][jj] += x;
			}
		}
	}
	T query(int i, int j) {
		if (i < 0 || j < 0) return T(0);
		T res = 0;
		for (int ii = i + 1; ii; ii ^= ii & -ii) {
			for (int jj = j + 1; jj; jj ^= jj & -jj) {
				res += t[ii][jj];
			}
		}
		return res;
	}
	T query(int t, int b, int l, int r) {
		return query(b, r) - query(t - 1, r) - query(b, l - 1) + query(t - 1, l - 1);
	}
};