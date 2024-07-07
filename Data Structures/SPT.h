class SPT {
private:
    vector<vector<int>> st;
    vector<int> logs; 
    function<int(int, int)> op;

public:
    SPT(vector<int> &v, function<int(int, int)> operation) : op(operation) {
        int n = v.size();
        int k = __lg(n)+1;
        logs.resize(n + 1);
        for (int i = 2; i <= n; ++i) logs[i] = 1 + logs[i >> 1];

        st.resize(n, vector<int>(k + 1));
        for (int i = 0; i < n; ++i) st[i][0] = v[i];

        for (int j = 1; j <= k; ++j) {
            for (int i = 0; i + (1 << (j - 1)) < n; ++i) {
                st[i][j] = op(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int l, int r) {
        int k = logs[r - l + 1];
        return op(st[l][k], st[r - (1 << k) + 1][k]);
    }
};

int op(int a, int b) { return min(a, b); }

// SPT spt(nums, op);
