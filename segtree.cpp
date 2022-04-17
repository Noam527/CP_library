/*
the struct 'element' must have:
* neutral element (as default constructor)
* operator *, to combine with a right operand and return the result
* operator *=
*/
template<typename element>
struct segtree {
	int n;
	vector<element> t;
	segtree() {}
	segtree(int sz) {
		n = max(2, sz);
		while (n != (n & -n)) n += (n & -n);
		t.resize(2 * n, element());
	}
	segtree(const vector<element> &a) {
		n = max(2, (int)a.size());
		while (n != (n & -n)) n += (n & -n);
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
	// iterative: this assumes the monoid is commutative!!!
	element iquery(int l, int r) {
		if (l > r) return element();
		element result = element();
		for (l += n - 1, r += n - 1; l < r; l = (l - 1) / 2, r = (r - 1) / 2) {
			if (!(l & 1)) result *= t[l++];
			if (r & 1) result *= t[r--];
		}
		if (l == r) result *= t[l];
		return result;
	}
	// recursive: no commutativity assumption, might be slower.
	element rquery(int l, int r) {
		if (l > r) return element();
		return rquery(l, r, 0, 0, n - 1);
	}
	element rquery(int l, int r, int node, int nl, int nr) {
		if (r < nl || nr < l) return element();
		if (l <= nl && nr <= r) return t[node];
		int mid = (nl + nr) / 2;
		return
			rquery(l, r, 2 * node + 1, nl, mid) * rquery(l, r, 2 * node + 2, mid + 1, nr);
	}
};

struct emin {
	int val, ind;
	emin() {
		val = md;
		ind = -1;
	}
	emin(int vv, int ii) {
		val = vv;
		ind = ii;
	}
	emin operator * (const emin &a) const {
		if (val < a.val) return *this;
		return a;
	}
	void operator *= (const emin &a) {
		if (val > a.val) {
			val = a.val;
			ind = a.ind;
		}
	}
};
struct emax {
	int val, ind;
	emax() {
		val = -md;
		ind = -1;
	}
	emax(int vv, int ii) {
		val = vv;
		ind = ii;
	}
	emax operator * (const emax &a) const {
		if (val > a.val) return *this;
		return a;
	}
	void operator *= (const emax &a) {
		if (val < a.val) {
			val = a.val;
			ind = a.ind;
		}
	}
};
