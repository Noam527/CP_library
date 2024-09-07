struct Blossom {
    int n;
    vector<vector<int>> g;
    int timer;
    vector<int> mate, label, parent, orig, aux, q;
    Blossom() {}
    Blossom(int n) : n(n), g(n), timer(-1), mate(n, -1), aux(n, -1), label(n), parent(n), orig(n) {}
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int lca(int x, int y) {
        for (timer++; ; swap(x, y)) {
            if (x == -1) continue;
            if (aux[x] == timer) return x;
            aux[x] = timer;
            x = (mate[x] == -1 ? -1 : orig[parent[mate[x]]]);
        }
    }
    void blossom(int v, int w, int a) {
        while (orig[v] != a) {
            parent[v] = w; w = mate[v];
            if (label[w] == 1) label[w] = 0, q.push_back(w);
            orig[v] = orig[w] = a; v = parent[w];
        }
    }
    void augment(int v) {
        while (v != -1) {
            int pv = parent[v], nv = mate[pv];
            mate[v] = pv; mate[pv] = v; v = nv;
        }
    }
    int bfs(int root) {
        fill(label.begin(), label.end(), -1);
        iota(orig.begin(), orig.end(), 0);
        q.clear();
        label[root] = 0; q.push_back(root);
        for (int i = 0; i < (int)q.size(); ++i) {
            int v = q[i];
            for (auto x : g[v]) {
                if (label[x] == -1) {
                    label[x] = 1; parent[x] = v;
                    if (mate[x] == -1)
                        return augment(x), 1;
                    label[mate[x]] = 0; q.push_back(mate[x]);
                }
                else if (label[x] == 0 && orig[v] != orig[x]) {
                    int a = lca(orig[v], orig[x]);
                    blossom(x, v, a); blossom(v, x, a);
                }
            }
        }
        return 0;
    }
    vector<pair<int, int>> maximum_matching() {
        for (int i = 0; i < n; i++)
            if (mate[i] == -1)
                bfs(i);
        vector<pair<int, int>> result;
        for (int i = 0; i < n; i++)
            if (i < mate[i])
                result.emplace_back(i, mate[i]);
        return result;
    }
};