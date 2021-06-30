struct splaytree {
	// to be nonlazy, if efficiency is necessary, remove the definition of push() and uncomment the next line:
	//#define push(X) ;
	struct node {
		int ch[2] = {}, p;
		ll val, mn; // hold some values
		int size;
		ll add; // hold some lazy tags
		node(ll value = 0) {
			ch[0] = ch[1] = p = add = 0;
			size = 1;
			val = mn = value;
		}
		int& operator [](int index) {
			return ch[index];
		}
	};
	int root = 0; // will hold some root.
	vector<node> T;
	vector<int> free_nodes;
	splaytree(int expected_max) {
		T.reserve(expected_max + 1);
		// initialize T[0] with null values:
		T.push_back(node());
		T[0].mn = inf;
		T[0].size = 0;
	}
	int new_node(ll value) {
		if (free_nodes.size()) {
			int res = free_nodes.back();
			free_nodes.pop_back();
			T[res] = node(value);
			return res;
		}
		T.push_back(node(value));
		return (int)T.size() - 1;
	}
	// update push and fix accordingly
	void push(int x) {
		if (!x) return;
		int l = T[x][0], r = T[x][1];
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
		T[x].size = 1 + T[l].size + T[r].size;
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
		return T[T[x].p][1] == x ? 1 : 0;
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
	int splay(int x) {
		for (push(x); T[x].p;) {
			int y = T[x].p, z = T[y].p;
			push(z); push(y); push(x);
			int dx = dir(x), dy = dir(y);
			if (dy >= 0) rotate(dx == dy ? y : x);
			rotate(x);
		}
		return root = x;
	}
	// have at it
	// returns the new node at root
	int lowerbound(ll val, int start) {
		int v = 0, lst = 0;
		for (int cur = (start ? start : root); cur;) {
			push(cur);
			lst = cur;
			if (T[cur].val < val)
				cur = T[cur][1];
			else
				v = cur, cur = T[cur][0];
		}
		if (!v) return splay(lst);
		return splay(v);
	}
	// the actual value
	ll lowerbound(ll val) {
		int v = lowerbound(val, root);
		if (T[v].val >= val) return T[v].val;
		return inf;
	}
	// returns the new node at root
	int index(int k, int start) {
		while (1) {
			push(start);
			int l = T[start][0];
			if (T[l].size > k) start = l;
			else if (T[l].size < k) {
				start = T[start][1];
				k -= (1 + T[l].size);
			}
			else return splay(start);
		}
	}
	// the actual value
	ll index(int k) {
		return T[index(k, root)].val;
	}
	// splits the splay containing v into two splays with roots l, r:
	// l has all values < val, r has all values >= val.
	void split_value(int v, int &l, int &r, ll val) {
		splay(v);
		int u = lowerbound(val, v);
		if (T[u].val < val) {
			l = v, r = 0;
			return;
		}
		r = u, l = T[u][0];
		setchild(u, 0, 0);
		if (l) T[l].p = 0;
	}
	void split_size(int v, int &l, int &r, int lsz) {
		splay(v);
		if (T[v].size == lsz) {
			l = v, r = 0;
			return;
		}
		int u = index(lsz, v);
		r = u, l = T[u][0];
		setchild(u, 0, 0);
		if (l) T[l].p = 0;
	}
	// merge the trees rooted at l, r, return the new root.
	int merge(int l, int r) {
		if (!l || !r) return l | r;
		for (push(l); T[l][1]; push(l))
			l = T[l][1];
		splay(l);
		setchild(l, 1, r);
		return l;
	}

	int insert(ll val) {
		int l, r, n = new_node(val);
		split_value(root, l, r, val);
		setchild(n, 0, l), setchild(n, 1, r);
		return root = n;
	}
	int insert_at(ll val, int k) {
		int l, r, n = new_node(val);
		split_size(root, l, r, k);
		setchild(n, 0, l), setchild(n, 1, r);
		return root = n;
	}
	void erase(ll val) {
		int v = splay(lowerbound(val, root));
		free_nodes.push_back(v);
		int l = T[v][0], r = T[v][1];
		T[l].p = T[r].p = 0;
		root = merge(l, r);
	}
	void erase_at(int k) {
		int v = splay(index(k, root));
		free_nodes.push_back(v);
		int l = T[v][0], r = T[v][1];
		T[l].p = T[r].p = 0;
		root = merge(l, r);
	}
};
