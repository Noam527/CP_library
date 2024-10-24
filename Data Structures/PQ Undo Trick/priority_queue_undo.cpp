template<typename upd_t, typename pr_t>
struct pq_undo_trick {
	map<pr_t, int> m;
	vector<int> spos;
	vector<tuple<upd_t, pr_t, int>> st;
	pq_undo_trick() {}
	void qupdate(const upd_t& u, pr_t p) { // do const& if needed
		supdate(u);
		m.emplace(p, spos.size());
		spos.push_back(st.size());
		st.emplace_back(u, p, spos.size() - 1);
	}
	upd_t qundo() { // returns the undone update
		int k = 1;
		pr_t bound;
		vector<tuple<upd_t, pr_t, int>> small, big;
		auto it = m.end();
		for (int i = 0; i++ < (k + 1) / 2;) {
			bound = (--it)->first;
			int at = spos[it->second];
			if (i > 1) big.push_back(st[at]);
			k = max(k, (int)st.size() - at);
		}
		for (int i = 0; i < k; i++) {
			sundo();
			auto [u, p, ind] = st.back();
			st.pop_back();
			if (p < bound) small.emplace_back(u, p, ind);
		}
		it = prev(m.end());
		upd_t undone_update = get<upd_t>(st[spos[it->second]]);
		m.erase(it);
		small.insert(small.end(), big.begin(), big.end());
		for (auto [u, p, ind] : small) {
			supdate(u);
			spos[ind] = st.size();
			st.emplace_back(u, p, ind);
		}
		return undone_update;
	}
	// to be implemented by inheriting class
	virtual void sundo() = 0;
	virtual void supdate(const upd_t& u) = 0;
};