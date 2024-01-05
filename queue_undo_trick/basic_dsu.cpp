/* ---------- UPDATE TYPES ---------- */
// declare all update types here
enum uid {
	EDGE
};
// unionize them here
struct update {
	uid id;
	update() {}
	union {
		struct edge {
			int u, v;
			edge() {}
			edge(int uu, int vv) {
				u = uu;
				v = vv;
			}
		} e;
	};
};
// declare constructors
update make_edge(int u, int v) {
	update x;
	x.id = EDGE;
	x.e.u = u, x.e.v = v;
	return x;
}

/* ---------- UNDERLYING DS ---------- */
struct dsu {
	int n;
	vector<int> p;
	// stack memory
	vector<update> updates;
	// tailored implementation of changes
	vector<pair<int, int>> changes; // p[index] was value

	dsu(int sz = 0) {
		n = sz;
		p.resize(n);
		for (int i = 0; i < n; i++) p[i] = i;
	}
	// queries
	int find(int x) {
		return x == p[x] ? x : p[x] = find(p[x]);
	}
	// updates
private:
	bool unite(int u, int v) {
		// begin update, don't forget to edit changes.back()
		u = find(u), v = find(v);
		if (u == v) return false;
		if (rand() & 1) {
			changes.back() = { u, p[u] };
			p[u] = v;
		}
		else {
			changes.back() = { v, p[v] };
			p[v] = u;
		}
		return true;
	}
public:
	// update convention: push and switch case
	// choose the return value
	bool upd(const update &u) {
		changes.emplace_back(-1, -1);
		updates.push_back(u);
		switch (u.id) {
		case EDGE:
			return unite(u.e.u, u.e.v);
		}
		exit(1);
	}
	// undo convention: return the update that was undone
	update undo() {
		if (changes.back().first != -1)
			p[changes.back().first] = changes.back().second;
		changes.pop_back();
		update tmp = move(updates.back());
		updates.pop_back();
		return tmp;
	}
};

#define ds dsu
struct queuedsu : ds {
	vector<bool> st;
	vector<update> tmp[2];
	int nxtA;
	queuedsu() : nxtA(0) {}
	// imitate constructors
	queuedsu(int n) {
		ds::ds(n);
		nxtA = 0;
	}
	// choose return type
	bool upd(const update &u) {
		ds::upd(u);
		st.push_back(1);
	}
	void undo() {
		while (nxtA < st.size() && st[nxtA]) nxtA++;
		if (nxtA == st.size()) {
			// reverse
			tmp[0].clear();
			for (auto &i : st) {
				tmp[0].push_back(ds::undo());
				i = 0;
			}
			st.pop_back();
			tmp[0].pop_back();
			for (auto &u : tmp[0])
				ds::upd(u);
			return;
		}
		if (!st.back()) {
			// A on top
			st.pop_back();
			ds::undo();
			return;
		}
		// fix
		tmp[0].clear(), tmp[1].clear();
		do {
			tmp[st.back()].push_back(ds::undo());
			st.pop_back();
		} while (nxtA < st.size() && tmp[0].size() < tmp[1].size());
		for (int i : {1, 0}) {
			reverse(tmp[i].begin(), tmp[i].end());
			if (i == 0) tmp[0].pop_back();
			for (auto &u : tmp[i]) {
				ds::upd(u);
				st.push_back(i);
			}
		}
	}
};
#undef ds
