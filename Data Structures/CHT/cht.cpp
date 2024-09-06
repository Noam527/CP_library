/*
For efficiency, there are multiple template variables:
- type: Use 1 for maximum CHT, or -1 for minimum CHT.
- slope_t: type for the slopes
- const_t: type for the constants
- eval_t: type for both the queries and the evaluation of lines on given queries.
- db_t: type for calculation of intersection points. Use double or long double.
*/
template<int type, typename slope_t = long long, typename const_t = long long, typename eval_t = long long, typename db_t = double>
struct CHT {
	static constexpr db_t MAX_INTERSECT = std::numeric_limits<db_t>::max();
	struct line {
		slope_t sl;
		const_t c;
		bool query;
		size_t id;
		db_t intersect;
		line(slope_t sl, const_t c, bool query = false, size_t id = -1, db_t intersect = MAX_INTERSECT) :
			sl(sl), c(c), query(query), id(id), intersect(intersect) {}
		bool operator < (const line& other) const {
			if (!query && !other.query) return sl < other.sl;
			return intersect < other.intersect;
		}
	};
	db_t cut(const line& x, const line& y) {
		return db_t(x.c - y.c) / db_t(y.sl - x.sl);
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
	void insert(slope_t slope, const_t constant, size_t id = -1) {
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
	eval_t query(eval_t x) {
		line l = *hull.lower_bound(line(0, 0, true, 0, db_t(x)));
		return type * (eval_t(l.sl) * x + eval_t(l.c));
	}
	// id of the line instead of the evaluation, used for dp reconstruction.
	size_t iquery(eval_t x) {
		return hull.lower_bound(line(0, 0, true, 0, db_t(x)))->id;
	}
};