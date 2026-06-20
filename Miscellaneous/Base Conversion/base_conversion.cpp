/*
 * Converts `u` under base `b` (0 <= u[i] < b), to a vector in base `c`.
 * Does not preserve leading zeroes! Use this when you can recover the length of the converted vectors.
*/
vector<int> base_conversion(vector<int> u, const int b, const int c) {
	int n = (int)u.size();
	vector<int> result;
	while (1) {
		ll rem = 0;
		bool found = false;
		for (int i = 0; i < n; i++) {
			if (u[i]) found = true;
			rem = rem * b + u[i];
			u[i] = rem / c;
			rem %= c;
		}
		if (!found) break;
		result.push_back((int)rem);
	}
	reverse(result.begin(), result.end());
	return result;
}

/*
 * Converts `u` with given `bases` to each index (0 <= u[i] < bases[i]), to a vector in base `c`.
 * Does not preserve leading zeroes! Use this when you can recover the length of the converted vectors.
*/
vector<int> base_conversion(vector<int> u, const vector<int> &bases, const int c) {
	int n = (int)u.size();
	vector<int> result;
	while (1) {
		ll rem = 0;
		bool found = false;
		for (int i = 0; i < n; i++) {
			if (u[i]) found = true;
			rem = rem * bases[i] + u[i];
			u[i] = rem / c;
			rem %= c;
		}
		if (!found) break;
		result.push_back((int)rem);
	}
	reverse(result.begin(), result.end());
	return result;
}

/*
 * Converts `u` with given `bases` to each index (0 <= u[i] < bases[i]), to a vector in bases `c`.
 * If `c` does not suffice to represent `u`, then a vector of {-1} is returned.
 * Otherwise, a vector of length exactly |c| is returned.
*/
vector<int> base_conversion(vector<int> u, const vector<int> &bases, const vector<int> &c) {
	int n = (int)u.size();
	int m = (int)c.size();
	vector<int> result(m);
	for (int j = m - 1; j >= 0; j--) {
		ll rem = 0;
		for (int i = 0; i < n; i++) {
			rem = rem * bases[i] + u[i];
			u[i] = rem / c[j];
			rem %= c[j];
		}
		result[j] = (int)rem;
	}
	// check if `c` was sufficient
	for (auto &x : u) {
		if (x > 0) return {-1};
	}
	return result;
}