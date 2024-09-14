// 1-indexed!! min path version, untested
struct linkcut {
	struct node {
		int ch[2] = {}, p = 0;
		int flip = 0;
		ll val = 0, mn = 0; // IMP: hold some values
		ll add = 0; // IMP: hold some lazy tags
		int& operator [](int i) {
			return ch[i];
		}
	};
	vector<node> T;
	linkcut(int size) {
		T.resize(size + 1);
		// IMP: initialize T[0] with null values:
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
		// IMP: apply lazy tags
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
		// IMP: fix node values
		T[x].mn = min(min(T[x].val, T[l].mn), T[r].mn);
	}
	void setchild(int p, int d, int x) { // assumes p is pushed.
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
	// IMP: specific operations
	void setvalue(int v, ll value) {
		access(v);
		// IMP: initialize node
		T[v].val = T[v].mn = value;
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

// 1-indexed! sum path version, tested
struct linkcut {
	struct node {
		int ch[2] = {}, p = 0;
		int flip = 0;
		ll val = 0, s = 0; // IMP: hold some values
		// IMP: hold some lazy tags
		int& operator [](int i) {
			return ch[i];
		}
	};
	vector<node> T;
	linkcut(int size) {
		T.resize(size + 1);
		// IMP: initialize T[0] with null values:
		T[0].s = 0;
	}
	void push(int x) {
		if (!x) return;
		int l = T[x][0], r = T[x][1];
		if (T[x].flip) {
			swap(T[x][0], T[x][1]);
			T[l].flip ^= 1, T[r].flip ^= 1;
			T[x].flip = 0;
		}
		// IMP: apply lazy tags
	}
	void fix(int x) {
		if (!x) return;
		int l = T[x][0], r = T[x][1];
		push(l); push(r);
		// IMP: fix node values
		T[x].s = T[x].val + T[l].s + T[r].s;
	}
	void setchild(int p, int d, int x) { // assumes p is pushed.
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
	int parent(int v) {
		access(v);
		int u = T[v][1];
		if (!u) return 0;
		while (T[u][0]) u = T[u][0];
		access(u);
		return u;
	}
	// IMP: specific operations
	void addvalue(int v, ll value) {
		access(v);
		// IMP: initialize node
		T[v].val += value;
		fix(v);
	}
	ll sumpath(int v) {
		access(v);
		int r = T[v][1];
		ll result = T[v].val;
		if (r) {
			push(r);
			result += T[r].s;
		}
		return result;
	}
};