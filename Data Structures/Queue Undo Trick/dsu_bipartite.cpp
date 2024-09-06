// https://codeforces.com/contest/1386/submission/247538111

/* -------------------- BASE CLASS -------------------- */

template<typename upd_t>
struct queue_undo_trick {
	vector<bool> st;
	vector<upd_t> tmp[2];
	int nxt0;
	queue_undo_trick() : nxt0(0) {}
	void qupdate(const upd_t &u) {
		st.push_back(1);
		supdate(u);
	}
	void qundo() {
		while (nxt0 < st.size() && st[nxt0]) nxt0++;
		if (nxt0 == st.size()) {
			// reverse. we assume st.size() > 0.
			nxt0 = 0;
			tmp[0].clear();
			for (int i = 0; i < st.size(); i++) {
				tmp[0].push_back(sundo());
				st[i] = 0;
			}
			st.pop_back();
			tmp[0].pop_back();
			for (auto &u : tmp[0])
				supdate(u);
			return;
		}
		if (!st.back()) {
			// A on top
			st.pop_back();
			sundo();
			return;
		}
		// fix
		tmp[0].clear(), tmp[1].clear();
		do {
			tmp[st.back()].push_back(sundo());
			st.pop_back();
		} while (nxt0 < st.size() && tmp[0].size() < tmp[1].size());
		for (int i : {1, 0}) {
			reverse(tmp[i].begin(), tmp[i].end());
			if (i == 0) tmp[0].pop_back();
			for (auto &u : tmp[i]) {
				supdate(u);
				st.push_back(i);
			}
		}
	}
	// to be implemented by inheriting class
	virtual upd_t sundo() = 0;
	virtual void supdate(const upd_t &u) = 0;
};

/* -------------------- UPDATE TYPES -------------------- */
// declare all update types here
enum uid {
	EDGE
};
// unionize them here
struct update {
	uid id;
	update(uid ID) {
		id = ID;
	}
	union data {
		struct edge {
			int u, v;
			edge() {}
			edge(int uu, int vv) {
				u = uu;
				v = vv;
			}
		} e;
		data() {}
		~data() {}
	} data;
};
// declare constructors
update make_edge(int u, int v) {
	update x(EDGE);
	x.data.e.u = u;
	x.data.e.v = v;
	return x;
}

/* -------------------- INHERITING CLASS -------------------- */

struct queue_dsu : public queue_undo_trick<update> {
	int n;
	vector<int> p;
	vector<int> up;
	vector<int> r;
	int first_violate;
	// stack memory
	vector<update> updates;
	// tailored implementation of changes
	struct change {
		int i;
		int v1, v2;
		int ir;
		change() {
			i = v1 = v2 = ir = -1;
		}
	};
	vector<change> changes; // p[index] was value

	queue_dsu(int sz = 0) {
		n = sz;
		p.resize(n);
		up.resize(n);
		r.resize(n);
		for (int i = 0; i < n; i++) p[i] = i;
		first_violate = -1;
	}
	// queries
	pair<int, int> find(int x) {
		if (x == p[x]) return{ x, 0 };
		pair<int, int> tmp = find(p[x]);
		tmp.second ^= up[x];
		return tmp;
	}
	bool is_bipartite() {
		return first_violate == -1;
	}
	// updates
private:
	void unite(int u, int v) {
		int col = 1;
		auto tmp = find(u);
		u = tmp.first, col ^= tmp.second;
		tmp = find(v);
		v = tmp.first, col ^= tmp.second;
		if (u == v) {
			if (col == 1 && first_violate == -1) first_violate = updates.size();
			return;
		}
		change &lst = changes.back();
		if (r[u] < r[v]) {
			lst.i = u;
			lst.v1 = p[u], lst.v2 = up[u];
			p[u] = v;
			up[u] = col;
		}
		else {
			lst.i = v;
			lst.v1 = p[v], lst.v2 = up[v];
			p[v] = u;
			up[v] = col;
			if (r[u] == r[v])
				r[u]++, lst.ir = u;
		}
		return;
	}

	// update convention: push and switch case
	// TODO: choose the return value
	virtual void supdate(const update &u) {
		changes.push_back(change());
		updates.push_back(u);
		switch (u.id) {
		case EDGE:
			unite(u.data.e.u, u.data.e.v);
			return;
		}
		exit(1);
	}
	// undo convention: return the update that was undone
	virtual update sundo() {
		if (changes.back().i != -1) {
			p[changes.back().i] = changes.back().v1;
			up[changes.back().i] = changes.back().v2;
			if (changes.back().ir != -1)
				r[changes.back().ir]--;
		}
		if (first_violate >= updates.size())
			first_violate = -1;
		changes.pop_back();
		update tmp = move(updates.back());
		updates.pop_back();
		return tmp;
	}
};
