// for non-decreasing, make T a pair; call LIS for b[i] = {a[i],i}
template<typename T>
vector<int> lis(const vector<T>& a) {
	map<T, int> m;
	vector<int> p(a.size(), -1), ans;
	for (int i = 0; i < a.size(); i++) {
		auto it = m.lower_bound(a[i]);
		if (it != m.end()) m.erase(it);
		it = m.emplace(a[i], i).first;
		if (it != m.begin()) p[i] = prev(it)->second;
	}
	int cur = m.rbegin()->second;
	while (cur != -1)
		ans.push_back(cur), cur = p[cur];
	reverse(ans.begin(), ans.end());
	return ans;
}