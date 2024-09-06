// *****OLD*****
// uses old implementation
// https://codeforces.com/contest/1442/submission/240382290
/* ---------- UPDATE TYPES ---------- */
struct update {
	int sz;
	ll w;
	update() {}
	update(int ss, ll ww) : sz(ss), w(ww) {}
};
/* ---------- UNDERLYING DS ---------- */
struct knapsack {
	int n;
	vector<ll> dp;
	// stack memory
	vector<update> updates;
	vector<vector<ll>> st;

	knapsack(int sz = 0) {
		n = sz;
		dp.resize(n + 1, -inf);
		dp[0] = 0;
	}
	ll& operator [](int i) {
		return dp[i];
	}
private:
	void add(int sz, ll val) {
		for (int i = n; i >= sz; i--)
			dp[i] = max(dp[i], dp[i - sz] + val);
	}
public:
	// update convention: push and switch case
	void upd(const update &u) {
		st.push_back(dp);
		updates.push_back(u);
		add(u.sz, u.w);
	}
	// undo convention: return the update that was undone
	update undo() {
		dp = st.back();
		st.pop_back();
		update tmp = move(updates.back());
		updates.pop_back();
		return tmp;
	}
};

#define ds knapsack
struct queuesack : ds {
	vector<bool> st;
	vector<update> tmp[2];
	int nxtA;
	queuesack() : nxtA(0) {}
	queuesack(int sz) : ds(sz) {
		nxtA = 0;
	}
	void upd(const update &u) {
		st.push_back(1);
		ds::upd(u);
	}
	void undo() {
		while (nxtA < st.size() && st[nxtA]) nxtA++;
		if (nxtA == st.size()) {
			// reverse
			nxtA = 0;
			tmp[0].clear();
			for (int i = 0; i < st.size(); i++) {
				tmp[0].push_back(ds::undo());
				st[i] = 0;
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
