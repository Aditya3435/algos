class DSU {
public:
    vector<int> parent; 
    vector<int> size;
    DSU(int n) {
        parent.resize(n+1);
        size.resize(n+1);
        for (int i = 0; i <= n; i++) {
            make(i);
        }
    }

    void make(int v) {
        parent[v] = v;
        size[v] = 1;
    }

    int find(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find(parent[v]);
    }
    bool Union(int a, int b) {
        a = find(a);
        b = find(b);
        if(a==b) return false;
        if (a != b) {
            if (size[a] < size[b])
                swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
        return true;
    }
    vector<vector<int>> getComponents() {
        unordered_map<int, vector<int>> mp;
        for (int i = 1; i < parent.size(); i++) {
            mp[find(i)].push_back(i);
        }
        
        vector<vector<int>> components;
        for (auto& m : mp) {
            components.push_back(m.second);
        }
        return components;
    }
   
};

// only if i == find(i) => cnt[i] = nodes count, edges[i] = edges count
// vector<int> cnt(n), edges(n); 
// for(int i=0; i<n; i++) cnt[d.find(i)]++;
// for(int i=0; i<m; i++) edges[d.find(A[i])]++;
