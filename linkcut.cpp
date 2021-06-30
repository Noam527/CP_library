// essentially https://codeforces.com/blog/entry/75885 just reimplemented for myself.
// btw, indexed from 1! sorry, makes the implementation cleaner but you can add 1 to all inputs if you want.
struct linkcut {
	// to be nonlazy, if efficiency is necessary, remove the definition of push() and uncomment the next line:
	//#define push(X) ;
	struct node {
		int ch[2] = {}, p = 0;
		ll val = 0, mn = 0; // hold some values
		int flip = 0; // hold some lazy tags
		ll add = 0;
		int& operator [](int index) {
			return ch[index];
		}
	};
	vector<node> T;
	linkcut(int size) {
		T.resize(size + 1);
		// initialize T[0] with null values:
		T[0].mn = inf;
	}
	void push(int x) {
		if (!x) return;
		int l = T[x][0], r = T[x][1];
		if (T[x].flip) {
			swap(T[x][0], T[x][1]);
			T[l].flip ^= 1, T[r].flip ^= 1;
			T[x].flip = 0;
		}
		if (T[x].add) {
			T[x].val += T[x].add;
			T[x].mn += T[x].add;
			T[l].add += T[x].add, T[r].add += T[x].add;
			T[x].add = 0;
		}
	}
	void fix(int x) {
		if (!x) return;
		int l = T[x][0], r = T[x][1];
		push(l); push(r);
		T[x].mn = min(min(T[x].val, T[l].mn), T[r].mn); // works fine for 0 because T[0].mn = inf.
	}
	// assumes p is pushed.
	void setchild(int p, int d, int x) {
		T[p][d] = x, T[x].p = p;
		fix(p);
	}
	int dir(int x) {
		int p = T[x].p;
		if (!p) return -1;
		if (T[p][0] == x) return 0;
		if (T[p][1] == x) return 1;
		return -1;
	}
	// assumes the chain (x, x.p, x.p.p) is all pushed.
	void rotate(int x) {
		int y = T[x].p, z = T[y].p, dx = dir(x), dy = dir(y);
		setchild(y, dx, T[x][!dx]);
		setchild(x, !dx, y);
		if (dy >= 0) setchild(z, dy, x);
		else T[x].p = z; // needs to happen regardless.
	}
	// guarantees the new root is pushed.
	void splay(int x) {
		for (push(x); dir(x) >= 0;) {
			int y = T[x].p, z = T[y].p;
			push(z); push(y); push(x);
			int dx = dir(x), dy = dir(y);
			if (dy >= 0) rotate(dx == dy ? y : x);
			rotate(x);
		}
	}
	void access(int x) {
		int v = x, lst = -1;
		while (v) {
			splay(v);
			if (lst != -1)
				setchild(v, 0, lst);
			lst = v;
			v = T[v].p;
		}
		splay(x);
	}
	
	// standard operations
	void reroot(int v) {
		access(v);
		T[v][0] = 0;
		fix(v);
		T[v].flip ^= 1;
	}
	void link(int u, int v) {
		reroot(u);
		access(v);
		T[u].p = v;
		fix(v);
	}
	void cut(int v) {
		access(v);
		T[T[v][1]].p = 0;
		T[v][1] = 0;
		fix(v);
	}
	// specific operations
	void setvalue(int v, ll value) {
		access(v);
		T[v].val = value;
		fix(v);
	}
	void addpath(int v, ll add) {
		access(v);
		T[v].val += add;
		if (T[v][1])
			T[T[v][1]].add += add;
		fix(v);
	}
	ll minpath(int v) {
		access(v);
		int r = T[v][1];
		ll result = T[v].val;
		if (r) {
			push(r);
			result = min(result, T[r].mn);
		}
		return result;
	}
};

/*
void solve() {
	linkcut T = linkcut(4);
	while (1) {
		string op;
		cin >> op;
		if (op == "set") {
			int v;
			ll val;
			cin >> v >> val;
			T.setvalue(v, val);
		}
		else if (op == "addpath") {
			int v;
			ll add;
			cin >> v >> add;
			T.addpath(v, add);
		}
		else if (op == "minpath") {
			int v;
			cin >> v;
			cout << T.minpath(v) << '\n';
		}
		else if (op == "reroot") {
			int v;
			cin >> v;
			T.reroot(v);
		}
		else if (op == "link") {
			int u, v;
			cin >> u >> v;
			T.link(u, v);
		}
		else if (op == "cut") {
			int v;
			cin >> v;
			T.cut(v);
		}
	}
}
*/
