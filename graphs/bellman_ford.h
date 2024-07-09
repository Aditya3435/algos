vector<array<int,3>> edges;
vector<int> dist;
vector<int> parent;
void solve() {
    int n,m;
    cin >> n >> m;
    dist.resize(n,inf);
    parent.resize(n,-1);
    fl(i,0,m) {
        int u, v, w;
        cin >> u >> v >> w;
        --u,--v;
        edges.push_back({u,v,w});
    }
    dist[0] = 0;
    for(int i=0; i<n-1; i++) {
        for(auto &[u,v,w] : edges) {
            if(dist[u] + w < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + w;
            }
        }
    }
    // one more time to check negative edge cycle
    ll e = -1;
    for(auto &[u,v,w] : edges) {
        if(dist[u] + w < dist[v]) {
            parent[v] = u;
            e = v;
            break;
        }
    }
    if(e==-1) { // no negative edge
        cout << "No\n";
        return;
    }
    // negative edge found
    vector<int> cycle;
    fl(i,0,n) e = parent[e];    
    for(int s=e;;s=parent[s]) {
        cycle.pb(s+1);
        if(s==e&&cycle.sz>1) break;
    }
    cout << "Yes\n";
    reverse(cycle.begin(), cycle.end());
    for(auto &c : cycle) cout << c<< " ";
    cout << '\n';
}