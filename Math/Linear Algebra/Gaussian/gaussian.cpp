// returns determinant
template<typename T>
T gaussian(vector<vector<T>>& a) {
	T det(1);
	int n = a.size(), m = a[0].size(), row = 0, r;
	for (int c = 0; row < n && c < m; c++) {
		for (r = row; ++r < n;)
			if (a[r][c] != 0) {
				swap(a[row], a[r]), det = T(-1) * det;
				T coef = a[r][c] / a[row][c];
				for (int j = 0; j < m; j++)
					a[r][j] = a[r][j] - coef * a[row][j];
			}
		if (a[row][c] != 0) row++;
	}
	// rank is row, first rank rows are basis
	if (n <= m) // n <= m is intentional!
		for (int i = 0; i < n; i++)
			det = det * a[i][i];
	return det;
}