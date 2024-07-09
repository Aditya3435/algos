struct SCC{
	int n;
	vector<int>order, rt;
	vector<bool>vis;
	vector<vector<int> >g1,g2,scc;
	SCC(int _n=0):n(_n),vis(_n,false),g1(_n),g2(_n), rt(_n){}
	void add_edge(int u,int v)
	{
		g1[u].push_back(v);
		g2[v].push_back(u);
	}
	void dfs1(int u) {
        vis[u] = 1;
        for(int v : g1[u]) {
            if(!vis[v])dfs1(v);
        }
        order.push_back(u);
    }
    void dfs2(int u, vector<int> &comp) {
        vis[u] = 1;
        rt[u] = scc.size();
        comp.push_back(u);
        for(int v : g2[u]) {
            if(!vis[v]) dfs2(v, comp);
        }
    }
	int build()
	{
		for(int i=0; i<n; i++) if(!vis[i])dfs1(i);
        fill(vis.begin(), vis.end(),0);
        int k = 0;
        for(int j=order.size()-1; j>=0; j--) {
            int i = order[j];
            if(!vis[i]) {
                k++;
                vector<int> comp;
                dfs2(i,comp);
                scc.push_back(comp); // scc[i-1] has an edge towards scc[i]
            }
        }
        return k;
	}
};