/* computes for each row, the index of the minimum. assumptions:
* T implements the operator <
* c(x, y) >(=) c(x, y + 1) -> c(x + 1, y) >(>=) c(x + 1, y + 1)
*/
template<typename T>
vector<int> smawk(int n, int m, function<T(int, int)> c) {
	int i, j;
	if (m == 1) return vector<int>(n, 0);
	if (n >= m) {
		function<T(int, int)> c2 = [c](int x, int y) { return c(2 * x + 1, y); };
		vector<int> r = smawk(n / 2, m, c2);
		vector<int> out(n, 0);
		for (i = 0; i < n; i += 2) {
			for (j = (i ? r[i / 2 - 1] : 0); j <= (i < n - 1 ? r[i / 2] : m - 1); j++) {
				if (c(i, j) < c(i, out[i])) out[i] = j;
			}
			if (i < n - 1) out[i + 1] = r[i / 2];
		}
		return out;
	}
	else {
		vector<int> cols(n, 0);
		for (i = j = 1; j < m; j++) {
			while (i && c(i - 1, j) < c(i - 1, cols[i - 1])) i--;
			if (i < n) cols[i++] = j;
		}
		function<T(int, int)> c2 = [c, cols](int x, int y) { return c(x, cols[y]); };
		vector<int> r = smawk(n, i, c2);
		for (int& e : r) e = cols[e];
		return r;
	}
}