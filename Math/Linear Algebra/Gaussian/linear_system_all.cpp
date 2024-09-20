template<typename T>
vector<vector<T>> solve_linear(vector<vector<T>>& a, vector<T>& b) {
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
	vector<vector<T>> solutions(1, vector<T>(m, 0));
	int nxt = m - 1;
	for (; r--;) {
		int first = -1;
		for (int c = m - 1; c >= 0; c--)
			if (a[r][c] != 0)
				first = c;
		while (first < nxt) {
			solutions.push_back(solutions[0]);
			solutions.back()[nxt--] = T(1);
		}
		nxt--;
		for (auto& x : solutions) {
			x[first] = a[r][m];
			for (int c = first + 1; c < m; c++)
				x[first] = x[first] - x[c] * a[r][c];
			x[first] = x[first] / a[r][first];
		}
	}
	while (nxt >= 0) {
		solutions.push_back(solutions[0]);
		solutions.back()[nxt--] = T(1);
	}
	return solutions;
}