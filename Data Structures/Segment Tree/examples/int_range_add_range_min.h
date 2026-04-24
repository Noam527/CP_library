struct tag {
	int add;
	tag() : add(0) {}
	tag(int add) : add(add) {}
	bool empty() const {
		return add == 0;
	}
	tag operator * (const tag &other) const {
		return tag(add + other.add);
	}
};

struct emin {
	int v;
	emin() : v(numeric_limits<int>::max() / 2) {} // IMP: make sure this is sufficient
	emin(int v) : v(v) {}
	emin operator * (const emin &other) const {
		return emin(min(v, other.v));
	}
	emin operator * (const tag &other) const {
		return emin(v + other.add);
	}
};