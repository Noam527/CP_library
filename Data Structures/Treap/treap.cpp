struct Treap {
	static int trand() {
		return (rand() % (1 << 15)) | ((rand() % (1 << 15)) << 15);
	}
	struct node {
		int l, r;
		int size, pr;
		ll val, mn; // IMP: values
		ll add; // IMP: lazy tags
		// IMP: default value for val (according to operation)
		node(ll val = inf, int l = 0, int r = 0, int size = 1) : val(val), l(l), r(r), size(size) {
			mn = val;
			add = 0;
			pr = trand();
		}
	};
	vector<node> t;
	int root;
	Treap() {
		srand(123123123); // IMP: choose seed
		t.push_back(node()); // dummy
		root = 0;
		t[root].size = 0;
	}
	int add_node(ll val) {
		t.push_back(node(val));
		return (int)t.size() - 1;
	}
	node& left(int n) {
		return t[t[n].l];
	}
	node& right(int n) {
		return t[t[n].r];
	}
	void push(int n) {
		// IMP: lazy push. leave empty if treap is not lazy
		t[n].val += t[n].add, t[n].mn += t[n].add;
		left(n).add += t[n].add;
		right(n).add += t[n].add;
		t[n].add = 0;
	}
	void fix(int n) {
		push(t[n].l), push(t[n].r);
		t[n].size = 1 + left(n).size + right(n).size;
		// IMP: fix values from children
		t[n].mn = min(min(t[n].val, left(n).mn), right(n).mn);
	}
	int merge(int l, int r) {
		if (!l || !r)
			return l ^ r;
		if (t[l].pr < t[r].pr) {
			push(l);
			t[l].r = merge(t[l].r, r);
			fix(l);
			return l;
		}
		push(r);
		t[r].l = merge(l, t[r].l);
		fix(r);
		return r;
	}
	// IMP: if needed, operations by indicies
	// split to l, r so that left size is `size`.
	void split_size(int n, int& l, int& r, int size) {
        if (!n || !size) {
            l = 0, r = n;
            return;
        }
        push(n);
        if (left(n).size >= size) {
            split_size(t[n].l, l, r, size);
            t[n].l = r, r = n;
        }
        else {
            split_size(t[n].r, l, r, size - 1 - left(n).size);
            t[n].r = l, l = n;
        }
        fix(n);
    }
	void insert_at(int index, ll val) {
		int n = add_node(val), l, r;
		split_size(root, l, r, index);
		root = merge(merge(l, n), r);
	}
	// IMP: if needed, operations by values
	// split to l, r so that everything in left is < val.
	void split(int n, int& l, int& r, ll val) {
		if (!n) {
			l = r = 0;
			return;
		}
		push(n);
		if (t[n].val >= val) {
			split(t[n].l, l, r, val);
            t[n].l = r, r = n;
        }
		else {
			split(t[n].r, l, r, val);
            t[n].r = l, l = n;
        }
		fix(n);
	}
	void insert(ll val) {
		int n = add_node(val), l, r;
		split(root, l, r, val);
		root = merge(merge(l, n), r);
	}
};