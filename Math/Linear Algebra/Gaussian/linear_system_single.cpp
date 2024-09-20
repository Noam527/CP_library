template<typename T>
vector<T> solve_linear(vector<vector<T>>& a, vector<T>& b) {
	int n = a.size(), m = a[0].size(), r;
	vector<int> firsts;
	for (int i = 0; i < n; i++)
		a[i].push_back(b[i]);
	gaussian(a);
	for (r = 0; r < n; r++) {
		int first = -1;
		for (int c = m; c >= 0; c--)
			if (a[r][c] != 0)
				first = c;
		if (first == -1) break;
		if (first == m) return {}; // no solution
	}
	vector<T> x(m, 0);
	for (; r--;) {
		int first = -1;
		for (int c = m - 1; c >= 0; c--)
			if (a[r][c] != 0)
				first = c;
		x[first] = a[r][m];
		for (int c = first + 1; c < m; c++)
			x[first] = x[first] - x[c] * a[r][c];
		x[first] = x[first] / a[r][first];
	}
	return x;
}