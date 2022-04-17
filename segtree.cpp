/*
the struct 'element' must have:
* neutral element (as default constructor)
* operator *, to combine with a right operand and return the result
*/
template<typename element>
struct segtree {
	int n;
	vector<element> t;
	segtree() {}
	segtree(int sz) {
		n = max(2, sz);
		t.resize(2 * n, element());
	}
	segtree(const vector<element> &a) {
		n = max(2, (int)a.size());
		t.resize(2 * n);
		for (int i = 0; i < a.size(); i++)
			t[i + n - 1] = a[i];
		for (int i = n - 2; i >= 0; i--)
			t[i] = t[2 * i + 1] * t[2 * i + 2];
	}
	void update(int pos, element val) {
		pos += n - 1;
		t[pos] = val;
		while (pos) {
			pos = (pos - 1) / 2;
			t[pos] = t[2 * pos + 1] * t[2 * pos + 2];
		}
	}
	// iterative, without assuming commutativity.
	element iquery(int l, int r) {
		if (l > r) return element();
		element L = element(), R = element();
		for (l += n - 1, r += n - 1; l < r; l = (l - 1) / 2, r = (r - 1) / 2) {
			if (!(l & 1)) L = L * t[l++];
			if (r & 1) R = t[r--] * R;
		}
		if (l == r) L = L * t[l];
		return L * R;
	}
};
