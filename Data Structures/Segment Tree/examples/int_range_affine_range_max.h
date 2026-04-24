struct tag {
	int mult, add;
	tag() : mult(1), add(0) {}
	tag(int m, int a) : mult(m), add(a) {}
	bool empty() const {
		return mult == 1 && add == 0;
	}
	tag operator * (const tag &other) const {
		return tag(mult * other.mult, other.mult * add + other.add);
	}
};

// NOTE: assuming mult >= 0
struct emax {
	int v;
	emax() : v(numeric_limits<int>::min() / 2) {} // IMP: make sure this is sufficient
	emax(int v) : v(v) {}
	emax operator * (const emax &other) const {
		return emax(max(v, other.v));
	}
	emax operator * (const tag &other) const {
		return emax(other.mult * v + other.add);
	}
};