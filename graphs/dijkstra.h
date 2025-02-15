template <typename T>
pair<vector<T>, vector<int>> dijkstra(int s, const vector<vector<pair<int, T>>> &G, T INF = numeric_limits<T>::max())
{
    int n = G.size();
    vector<T> d(n, INF);
    vector<int> parent(n, -1);
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> P;
    d[s] = 0;
    P.push(make_pair(d[s], s));
    while (!P.empty()) {
        pair<T, int> p = P.top();
        P.pop();
        int v = p.second;
        if (d[v] < p.first)
            continue;
        for (const pair<int, T> &e : G[v]) {
            int u = e.first;
            T cost = d[v] + e.second;
            if (d[u] > cost) {
                d[u] = cost;
                parent[u] = v;
                P.push(make_pair(d[u], u));
            }
        }
    }
    return make_pair(d, parent);
}

// auto [dist, par] = dijkstr(0,g)