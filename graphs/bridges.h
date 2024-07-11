
struct Bridge {
    int n;
    vector<int> order, low;
    vector<bool> art;
    vector<vector<int>> G;

    Bridge(int n_, const vector<vector<int>>& _G) : n(n_), order(n_, -1), low(n_), art(n_, 0), G(_G) {}

    bool operator[](int i) const { return art[i]; }

    bool is_bridge(int a, int b) const {
        if (order[a] > order[b]) swap(a, b);
        return order[a] < low[b];
    }

    void dfs(int u, int p, int &k) {
        low[u] = order[u] = k++;
        bool curr = 0;
        int pc = 0;
        for (int v : G[u]) {
            if (order[v] == -1) {
                dfs(v, u, k);
                low[u] = min(low[u], low[v]);
                curr = curr || order[u] <= low[v];
            } else if (v != p || pc++) {
                low[u] = min(low[u], order[v]);
            }
        }
        art[u] = curr;
    }

    void build() {
        int k = 0;
        for (int u = 0; u < n; ++u) {
            if (order[u] == -1) {
                int cnt = 0;
                low[u] = order[u] = k++;
                for (int v : G[u]) {
                    if (order[v] == -1) {
                        dfs(v, u, k);
                        cnt++;
                    }
                }
                if (cnt >= 2) art[u] = true;
            }
        }
    }
};

struct TECC : Bridge {
    vector<int> comp;

    TECC(int n_, const vector<vector<int>>& _G) : Bridge(n_, _G), comp(n_, -1) {}

    int operator[](int i) const { return comp[i]; }

    void dfs(int u, int p, int& k) {
        comp[u] = p == -1 || is_bridge(p, u) ? k++ : comp[p];
        for (int v : G[u]) {
            if (comp[v] == -1) {
                dfs(v, u, k);
            }
        }
    }

    int build() {
        Bridge::build();
        int k = 0;
        for (int u = 0; u < n; ++u) {
            if (comp[u] == -1) {
                dfs(u, -1, k);
            }
        }
        return k;
    }

    int build(vector<vector<int>>& H) {
        int k = build();
        H.assign(k, vector<int>());
        for (int u = 0; u < n; ++u) {
            for (int v : G[u]) {
                if (comp[u] != comp[v]) {
                    H[comp[u]].push_back(comp[v]);
                }
            }
        }
        return k;
    }
};


/*
        vector<vector<int>> G(N);
        for (int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        // bridge
        Bridge bg(N, G);
        // 2 edge connected components
        TECC tecc(N, G);
        vector<vector<int>> H; // H is graph of 2EE components
        int numComponents = tecc.build(H);

*/