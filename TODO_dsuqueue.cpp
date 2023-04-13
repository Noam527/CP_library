#include <bits/stdc++.h>
typedef long long ll;
typedef long double ldb;
const int md = (int)1e9 + 7; // 998244353
const ll inf = 2e18;
const int OO = 1;
using namespace std;


/* ------------------------- update types ------------------------- */
// implement `update(...)` for every type of update
struct edge_update {
	int u, v;
	edge_update() {}
	edge_update(int uu, int vv) : u(uu), v(vv) {}
};
struct generic_update {
	uint8_t type; // for the i-th possible update, we assign the value 2i to indicate a new update of type i, and 2i+1 for an old one.
	union {
		// user: put all update types here
		edge_update edge;
	};
	bool isold() {

	}
	generic_update() : type(0) {}
	// user: define all constructors, with type increasing by 2
	generic_update(const edge_update &x) : type(0), edge(x) {}
	generic_update(edge_update &&x) : type(0), edge(x) {}
	// now would come another update with type 2...
};

/*
 * Assumes that the number of calls to `mov` is within uint32_t range, and that every singular change of memory is at most 255 bytes.
*/
struct stackify {
	stack<uint32_t> size_checkpoints;
	uint32_t num_of_updates;
	vector<uint8_t> changes;
	stackify() : num_of_updates(0) {}
	// call this on every new update
	void begin_new_update() {
		size_checkpoints.push(num_of_updates);
	}
	// use this function to record new changes that you want to rollback in the future
	template<typename T> void mov(T *addr, T &&new_val) {
		num_of_updates++;
		constexpr uint8_t s = sizeof(T);
		uint64_t start = changes.size();
		for (uint16_t i = 0; i < sizeof(addr) + sizeof(T); i++)
			changes.push_back(0);
		memcpy(&changes[start], &addr, sizeof(addr));
		memcpy(&changes[start + sizeof(addr)], addr, sizeof(T));
		changes.push_back(s);
		*addr = new_val;
	}
	template<typename T> void mov(T *addr, const T &new_val) {
		num_of_updates++;
		constexpr uint8_t s = sizeof(T);
		uint64_t start = changes.size();
		for (uint16_t i = 0; i < sizeof(addr) + s; i++)
			changes.push_back(0);
		memcpy(&changes[start], &addr, sizeof(addr));
		memcpy(&changes[start + sizeof(addr)], addr, sizeof(T));
		changes.push_back(s);
		*addr = new_val;
	}
	// undo one memory change (which may consist of multiple consecutive bytes)
	void undo_one() {
		if (!num_of_updates) return;
		num_of_updates--;
		uint8_t s = changes.back();
		changes.pop_back();
		uint64_t start = changes[changes.size() - s];
		void *addr;
		memcpy(&addr, &changes[start], sizeof(addr));
		memcpy(addr, &changes[start + sizeof(addr)], s);
		for (uint16_t i = 0; i < sizeof(addr) + s; i++)
			changes.pop_back();
	}
	// undo until the last checkpoint
	void undo() {
		if (size_checkpoints.empty()) return;
		uint32_t checkpoint = size_checkpoints.top();
		size_checkpoints.pop();
		while (num_of_updates > checkpoint)
			undo_one();
	}
};

/* ------------------------- the data structure, stackified ------------------------- */
struct dsu_stack : stackify {
	int n;
	vector<int> p, r;
	dsu_stack() {}
	dsu_stack(int sz) {
		n = sz;
		r.resize(n, 0);
	}
	/* ------------------------- all queries (must be const) ------------------------- */
	bool same_comp(int u, int v) const {
		return find(u) == find(v);
	}
	int find(int x) const {
		if (x == p[x]) return x;
		return find(p[x]);
	}
	/* ------------------------- all rollback updates (must call begin_new_update) ------------------------- */
	bool update(const edge_update &u) {
		begin_new_update();
		int x = find(u.u), y = find(u.v);
		if (x == y) return false;
		if (r[x] < r[y]) {
			mov(&p[x], y);
		}
		else {
			mov(&p[y], x);
			if (r[x] == r[y])
				mov(&r[x], r[x] + 1);
		}
		return true;
	}
};

/* ------------------------- queue undo time ------------------------- */
struct queue_update {
	char type; // 0 for old, 1 for new
	generic_update *u;
	queue_update() : type(1), u(nullptr) {}
	queue_update(generic_update &x) : type(1), u(&x) {}
	inline bool is_old() { return type == 0; }
	void make_old() { type = 1; }
};
/* ------------------------- the data structure, queueified ------------------------- */
struct dsu_queue : dsu_stack {
	vector<queue_update> s;
	uint32_t bottom; // bottom of the stack: s[0...bottom-1] is all "old".
	void advance_bottom() {
		while (bottom < s.size() && !s[bottom].is_old()) bottom++;
	}
	void fix() {
		if (s.empty() || s.back().is_old()) return;
		advance_bottom();
		stack<queue_update> save_old, save_new;
		save_new.push(s.back());
		s.pop_back(), undo();
		while (save_old.size() < save_new.size() && s.size() > bottom) {
			if (s.back().is_old())
				save_old.push(s.back());
			else
				save_new.push(s.back());
			s.pop_back(), undo();
		}
		while (!save_new.empty())
			
	}
	/* ------------------------- all user defined updates ------------------------- */
	bool qupdate(const edge_update &u) {
		s.push_back
	}
	/* ------------------------- user defined constructors ------------------------- */
	dsu_queue() : dsu_stack(), bottom(0) {}
	dsu_queue(int sz) : dsu_stack(sz), bottom(0) {}
};

void solve() {

}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	int tst = 1;
	cin >> tst;
	while (tst--) solve();
}
