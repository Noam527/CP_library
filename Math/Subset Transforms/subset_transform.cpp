// change int -> ll / add modulo if required.
void zeta(vector<int>& a) {
	for (int d = 1; d < a.size(); d *= 2)
		for (int i = 0; i < a.size(); i++)
			if (i & d) a[i] += a[i ^ d];
}
void mobius(vector<int>& a) {
	for (int d = 1; d < a.size(); d *= 2)
		for (int i = 0; i < a.size(); i++)
			if (i & d) a[i] -= a[i ^ d];
}
vector<int> subset_conv(const vector<int>& a, const vector<int>& b) {
	int n = a.size(), l;
	vector<int> bcnt(n); // bit count - use __builtin_popcount if you can
	for (int i = 1; i < n; i++) bcnt[i] = 1 + bcnt[i ^ (i & -i)];
	l = bcnt[n - 1];
	vector<int> A[32], B[32], C[32], res(n); // n < 2**32
	for (int i = 0; i <= l; i++)
		A[i].resize(n), B[i].resize(n), C[i].resize(n);
	for (int i = 0; i < n; i++)
		A[bcnt[i]][i] = a[i], B[bcnt[i]][i] = b[i];
	for (int i = 0; i <= l; i++) zeta(A[i]), zeta(B[i]);
	for (int x = 0; x <= l; x++) for (int y = 0; x + y <= l; y++)
		for (int i = 0; i < n; i++)
			C[x + y][i] += A[x][i] * B[y][i];
	for (int i = 0; i <= l; i++) mobius(C[i]);
	for (int i = 0; i < n; i++) res[i] = C[bcnt[i]][i];
	return res;
}