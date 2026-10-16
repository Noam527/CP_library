template<typename index_t, typename value_t>
struct interval_container {
	map<index_t, pair<index_t, value_t>> m;
	interval_container() {}
	virtual void interval_added(index_t l, index_t r, value_t x) = 0;
	virtual void interval_removed(index_t l, index_t r, value_t x) = 0;
	void insert(index_t l, index_t r, value_t x) {
		if (l > r) return;
		if (m.size() == 0) {
			interval_added(l, r, x);
			m[l] = make_pair(r, x);
			return;
		}
		auto it = m.upper_bound(l);
		if (it != m.begin()) {
			it--;
		}
		if (it->first <= l && it->second.first >= r) {
			// an existing interval contains us
			interval_removed(it->first, it->second.first, it->second.second);
			if (it->second.first > r) {
				interval_added(r + 1, it->second.first, it->second.second);
				m[r + 1] = it->second;
			}
			if (it->first < l) {
				interval_added(it->first, l - 1, it->second.second);
				it->second.first = l - 1;
			}
			else {
				m.erase(it);
			}
			interval_added(l, r, x);
			m[l] = make_pair(r, x);
			return;
		}
		while (it != m.end() && it->first <= r) {
			if (it->second.first < l) {
				it++;
				continue;
			}
			// regardless, report interval removal first
			interval_removed(it->first, it->second.first, it->second.second);
			if (it->first < l) {
				// earlier interval shortened
				interval_added(it->first, l - 1, it->second.second);
				it->second.first = l - 1;
				it++;
				continue;
			}
			if (it->second.first <= r) {
				// completely removed
				it = m.erase(it);
				continue;
			}
			// later interval shortened
			interval_added(r + 1, it->second.first, it->second.second);
			m[r + 1] = it->second;
			m.erase(it);
			break;
		}
		interval_added(l, r, x);
		m[l] = make_pair(r, x);
	}
};