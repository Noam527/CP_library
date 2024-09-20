struct xor_basis {
	vector<ll> b; // kept in decreasing order
	ll min_xor(ll x) { // MUST
		for (auto& i : b) x = min(x ^ i, x);
		return x;
	}
	ll max_xor(ll x) { // OPTIONAL
		for (auto& i : b) x = max(x ^ i, x);
		return x;
	}
	void add(ll x) {
		x = min_xor(x);
		if (!x) return;
		b.push_back(x);
		for (int i = b.size() - 1; i > 0 && b[i - 1] < b[i]; i--)
			swap(b[i - 1], b[i]);
	}
	int dim() { return b.size(); }
	bool can_repr(ll x) { return min_xor(x) == 0; }
	
};