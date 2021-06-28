// edit this with lazy values.
template<bool lazy, typename T = int>
struct node {
	node<lazy, T> *l, *r, *p;
	T value;
	// normal values. keep size!
	int size;
	// lazy values, for instance:
	T add;
	node() {}
	node(T val) {
		l = r = p = nullptr;
		value = val;
		size = 1;
		add = 0;
	}
	void push() {
		if (!lazy) return;
		if (add) {
			if (l) l->add += add;
			if (r) r->add += add;
			value += add;
			add = 0;
		}
	}
	// a call on this assumes the current node has been pushed.
	void fix() {
		if (lazy) {
			if (l) l->push();
			if (r) r->push();
		}
		size = 1;
		if (l) size += l->size;
		if (r) size += r->size;
	}
	~node<lazy, T>() {
		if (l) delete l;
		if (r) delete r;
	}
};

template<bool lazy, typename T = int>
struct splaytree {
	typedef node<lazy, T> node;
	node *root;
	splaytree() {
		root = nullptr;
	}
	splaytree(node *r) {
		root = r;
	}
	// assumes y and its relevant child pushed.
	void rright(node *y) {
		node *x = y->l, *b = x->r, *d = y->p;
		if (lazy) {
			if (d) {
				d->push();
				y->push();
				x->push();
			}
		}
		if (d) {
			if (d->l == y) d->l = x;
			else d->r = x;
		}
		y->p = x;
		x->p = d;
		x->r = y;
		y->l = b;
		if (b) b->p = y;
		y->fix();
		x->fix();
		if (d) d->fix();
	}
	// assumes y and its relevant child pushed.
	void rleft(node *y) {
		node *x = y->r, *b = x->l, *d = y->p;
		if (lazy) {
			if (d) {
				d->push();
				y->push();
				x->push();
			}
		}
		if (d) {
			if (d->l == y) d->l = x;
			else d->r = x;
		}
		y->p = x;
		x->p = d;
		x->l = y;
		y->r = b;
		if (b) b->p = y;
		y->fix();
		x->fix();
		if (d) d->fix();
	}
	// guarantees that the root pushed.
	node* splay(node *x) {
		if (x == nullptr) return nullptr;
		node *p, *pp;
		while ((p = x->p) != nullptr) {
			pp = p->p;
			if (lazy) {
				if (pp) pp->push();
				p->push();
				x->push();
			}
			if (!pp) {
				if (p->l == x) rright(p);
				else rleft(p);
				break;
			}
			if (pp->l == p) {
				if (p->l == x)
					rright(pp), rright(p);
				else
					rleft(p), rright(pp);
			}
			else {
				if (p->l == x)
					rright(p), rleft(pp);
				else
					rleft(pp), rleft(p);
			}
		}
		x->push();
		x->fix();
		return root = x;
	}

	// basic operations: some re-implement ideas for better constant factors.
	int size() {
		return root ? root->size : 0;
	}
	// get node by index: from 0 to size() - 1. guarantees that the root pushed.
	node* index(int k) {
		if (k < 0 || size() <= k) {
			cerr << "splaytree index: tried to access " << k << " while the size was " << size() << '\n';
			return nullptr;
		}
		node *x = root;
		while (true) {
			x->push();
			int lsz = x->l ? x->l->size : 0;
			if (k == lsz)
				return splay(x);
			if (k < lsz)
				x = x->l;
			else
				x = x->r, k -= (lsz + 1);
		}
		return nullptr; // shouldn't reach here
	}
	// split by value (<= x, > x)
	pair<splaytree, splaytree> split(T x) {
		if (!root) {
			return{ splaytree(), splaytree()};
		}
		node *z = root;
		while (true) {
			z->push();
			if (z->value <= x) {
				if (z->r) z = z->r;
				else break;
			}
			else {
				if (z->l) z = z->l;
				else break;
			}
		}
		splay(z);
		splaytree B, C;
		if (z->value <= x) {
			B = splaytree(z), C = splaytree(z->r);
			if (z->r) {
				z->r->p = nullptr;
				z->r = nullptr;
			}
		}
		else {
			B = splaytree(z->l), C = splaytree(z);
			if (z->l) {
				z->l->p = nullptr;
				z->l = nullptr;
			}
		}
		z->fix();
		return{ B, C };
	}
	// split by size (size k, rest of them).
	pair<splaytree, splaytree> sizesplit(int k) {
		if (k == 0) return{ splaytree(), splaytree(root) };
		if (k == size()) return{ splaytree(root), splaytree() };
		node *x = index(k);
		splaytree B(x->l), C(x);
		if (x->l) {
			x->l->p = nullptr;
			x->l = nullptr;
		}
		x->fix();
		return{ B, C };
	}
	// merges the current tree with B from the right.
	node* merge(splaytree B) {
		if (!B.root) return root;
		if (!root) return root = B.root;
		node *x = root;
		if (lazy) x->push();
		while (x->r) {
			x = x->r;
			if (lazy) x->push();
		}
		splay(x);
		root->r = B.root;
		if (B.root) B.root->p = root;
		root->fix();
		return root;
	}
	// roots the tree at the first node with value >= x (and returns it).
	// if none exists, returns null (the root changes though).
	node* lowerbound(T x) {
		if (!root) return nullptr;
		node *z = root, *lst = nullptr;
		while (true) {
			if (lazy) z->push();
			if (z->value < x) {
				if (z->r) z = z->r;
				else break;
			}
			else {
				lst = z;
				if (z->l) z = z->l;
				else break;
			}
		}
		if (lst == nullptr) {
			splay(z);
			return nullptr;
		}
		return splay(lst);
	}
	// roots the tree at the first node with value > x (and returns it).
	// if none exists, returns null.
	node* upperbound(T x) {
		if (!root) return nullptr;
		node *z = root, *lst = nullptr;
		while (true) {
			if (lazy) z->push();
			if (z->value <= x) {
				if (z->r) z = z->r;
				else break;
			}
			else {
				lst = z;
				if (z->l) z = z->l;
				else break;
			}
		}
		if (lst == nullptr) {
			splay(z);
			return nullptr;
		}
		return splay(lst);
	}
	// number of elements strictly less than / at most some x.
	int lessthan(T x) {
		if (!root) return 0;
		node *z = lowerbound(x);
		if (z == nullptr) return size();
		return z->l ? z->l->size : 0;
	}
	int atmost(T x) {
		if (!root) return 0;
		node *z = upperbound(x);
		if (z == nullptr) return size();
		return z->l ? z->l->size : 0;
	}

	// build upon the basic operations:
	node* insert(T value) {
		if (!root) return root = new node(value);
		pair<splaytree, splaytree> X = split(value);
		node *n = new node(value);
		n->l = X.first.root, n->r = X.second.root;
		if (X.first.root) X.first.root->p = n;
		if (X.second.root) X.second.root->p = n;
		n->fix();
		return root = n;
	}
	// after the insertion, the value will be at index k.
	node* insert_at(T value, int k) {
		if (!root) return root = new node(value);
		pair<splaytree, splaytree> X = sizesplit(k);
		node *n = new node(value);
		n->l = X.first.root, n->r = X.second.root;
		if (X.first.root) X.first.root->p = n;
		if (X.second.root) X.second.root->p = n;
		n->fix();
		return root = n;
	}
	void erase(T value) {
		node *x = lowerbound(value);
		splaytree A(x->l), B(x->r);
		if (x->l) x->l->p = nullptr;
		if (x->r) x->r->p = nullptr;
		x->l = x->r = nullptr;
		delete x;
		root = A.merge(B);
	}
	void erase_at(int k) {
		node *x = index(k);
		splaytree A(x->l), B(x->r);
		if (x->l) x->l->p = nullptr;
		if (x->r) x->r->p = nullptr;
		x->l = x->r = nullptr;
		delete x;
		root = A.merge(B);
	}
	// add your own.


	void gettree(node *x, vector<T> &result) {
		if (!x) return;
		x->push();
		gettree(x->l, result);
		result.push_back(x->value);
		gettree(x->r, result);
	}
	vector<T> gettree() {
		vector<T> result;
		gettree(root, result);
		return result;
	}
};

void solve() {
	splaytree<0> T;
	while (1) {
		string op;
		cin >> op;
		if (op == "rst") {
			T = splaytree<0>();
		}
		else if (op == "insert") {
			int x;
			cin >> x;
			T.insert(x);
		}
		else if (op == "insertat") {
			int k, x;
			cin >> k >> x;
			T.insert_at(x, k);
		}
		else if (op == "erase") {
			int x;
			cin >> x;
			T.erase(x);
		}
		else if (op == "eraseat") {
			int k;
			cin >> k;
			T.erase_at(k);
		}
		else if (op == "lowerbound") {
			int x;
			cin >> x;
			node<0> *z = T.lowerbound(x);
			if (!z) cout << "null\n";
			else cout << z->value << '\n';
		}
		else if (op == "upperbound") {
			int x;
			cin >> x;
			node<0> *z = T.upperbound(x);
			if (!z) cout << "null\n";
			else cout << z->value << '\n';
		}
		else if (op == "lessthan") {
			int x;
			cin >> x;
			cout << T.lessthan(x) << '\n';
		}
		else if (op == "index") {
			int k;
			cin >> k;
			node<0> *z = T.index(k);
			if (!z) cout << "null\n";
			else cout << z->value << '\n';
		}
		else if (op == "size") {
			cout << T.size() << '\n';
		}


		cout << "fixed: " << T.isfixed() << '\n';
		vector<int> t = T.gettree();
		for (const auto &i : t) cout << i << " "; cout << '\n';
	}

}
