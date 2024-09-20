template<typename T>
void invert(vector<vector<T>>& a) {
	int n = a.size(), m = 2 * n;
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
		a[i].push_back(T(i == j));
	T det = gaussian(a);
	if (det == 0) {
		a.clear();
		return;
	}
	for (int r = 0; r < n; r++) {
		T coef = T(1) / a[r][r];
		for (int c = r; c < m; c++) a[r][c] = a[r][c] * coef;
		for (int i = 0; i < r; i++) {
			coef = a[i][r];
			for (int c = r; c < m; c++)
				a[i][c] = a[i][c] - coef * a[r][c];
		}
	}
	for (int i = 0; i < n; i++)
		a[i] = vector<T>(a[i].begin() + n, a[i].end());
}