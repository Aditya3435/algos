struct LCA {
	int N;
	vector<vector<int>> G, par;
	vector<int> depth;
	LCA(int N_ = 0) : N(N_), G(N_), depth(N_) {
		int lg = 0;
		while ((1 << lg) + 1 < N_) lg++;
		par.assign(lg + 1, vector<int>(N_));
	}
	void add_edge(int u, int v) {
		G[u].push_back(v);
		G[v].push_back(u);
	}
	void dfs(int u, int p, int d) {
		depth[u] = d;
		par[0][u] = p;
		for (int v : G[u])
			if (v != p)
				dfs(v, u, d + 1);
	}
	void build(int root = 0) {
		dfs(root, -1, 0);
		for (int k = 1; k < par.size(); k++) {
			for (int i = 0; i < N; i++) {
				if (par[k - 1][i] == -1)
					par[k][i] = -1;
				else
					par[k][i] = par[k - 1][par[k - 1][i]];
			}
		}
	}
	int lca(int u, int v) {
		if (depth[u] > depth[v]) swap(u, v);
		for (int k = 0; k < par.size(); k++)
			if (depth[v] - depth[u] >> k & 1) v = par[k][v];
		if (u == v) return u;
		for (int k = par.size(); k--;)
			if (par[k][u] != par[k][v]) {
				u = par[k][u];
				v = par[k][v];
			}
		return par[0][u];
	}
	int dist(int u, int v) {
		int w = lca(u, v);
		return depth[u] + depth[v] - 2 * depth[w];
	}
};