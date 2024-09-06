/*
Template variable:
- type: Use 1 for maximum, or -1 for minimum.
*/
template<int type>
struct CHT {
	typedef long long ll;
	typedef long double ldb;
	static constexpr ldb MAX_INTERSECT = std::numeric_limits<ldb>::max();
	struct line {
		ll sl;
		ll c;
		bool query;
		size_t id;
		ldb intersect;
		line(ll sl, ll c, bool query = false, size_t id = -1, ldb intersect = MAX_INTERSECT) :
			sl(sl), c(c), query(query), id(id), intersect(intersect) {}
		bool operator < (const line& other) const {
			if (!query && !other.query) return sl < other.sl;
			return intersect < other.intersect;
		}
	};
	ldb cut(const line& x, const line& y) {
		return ldb(x.c - y.c) / ldb(y.sl - x.sl);
	}
	typedef typename set<line>::iterator sit;
	set<line> hull;
	void update_intersection(sit& it) {
		auto nit = next(it);
		line l = *it;
		hull.erase(it);
		if (nit == hull.end())
			l.intersect = MAX_INTERSECT;
		else
			l.intersect = cut(l, *nit);
		it = hull.insert(l).first;
	}
	bool is_ok(sit &it) {
		if (it == hull.begin())
			return true;
		auto pit = prev(it), nit = next(it);
		return nit == hull.end() || cut(*pit, *it) < cut(*it, *nit);
	}
	void insert(ll slope, ll constant, size_t id = -1) {
		line n(type * slope, type * constant, false, id);
		auto it = hull.insert(n).first;
		if (!is_ok(it)) {
			hull.erase(it);
			return;
		}
		sit other;
		// clear behind
		while (it != hull.begin()) {
			other = prev(it);
			if (is_ok(other))
				break;
			hull.erase(other);
		}
		// clear ahead
		other = next(it);
		while (other != hull.end()) {
			if (is_ok(other))
				break;
			hull.erase(other);
			other = next(it);
		}
		update_intersection(it);
		if (it != hull.begin()) {
			other = prev(it);
			update_intersection(other);
		}
	}
	ll query(ll x) {
		line l = *hull.lower_bound(line(0, 0, true, 0, ldb(x)));
		return type * (l.sl * x + l.c);
	}
	// id of the line instead of the evaluation, used for dp reconstruction.
	size_t iquery(ll x) {
		return hull.lower_bound(line(0, 0, true, 0, ldb(x)))->id;
	}
};