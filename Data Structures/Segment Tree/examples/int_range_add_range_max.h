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
struct emax {
	int v;
	emax() : v(numeric_limits<int>::min() / 2) {} // IMP: make sure this is sufficient
	emax(int v) : v(v) {}
	emax operator * (const emax &other) const {
		return emax(max(v, other.v));
	}
	emax operator * (const tag &other) const {
		return emax(v + other.add);
	}
};