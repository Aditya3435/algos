struct node {
    int freq, sum;
    node(int f, int sum) : freq(f), sum(sum){};
    friend node operator+(node a, const node& b) {
        a.freq += b.freq;;
        a.sum += b.sum;;
        return a;
    }
};
template<typename T>
struct rangefreq{ // strictly less than x
    int n;
    vector<vector<T>> freq;
    vector<vector<long>> sum;
    rangefreq(const vector<T> &v = {}) {
        n = 1;
        while (n < v.size()) n <<= 1;
        freq.assign(2 * n - 1, {});
        sum.assign(2 * n - 1, {});
        for (int i = 0; i < v.size(); i++) {
            freq[i + n - 1].push_back(v[i]);
            sum[i + n - 1].push_back(0);
            sum[i + n - 1].push_back(v[i]);
        }
        for (int i = n - 2; i >= 0; i--) {
            freq[i].resize(freq[i * 2 + 1].size() + freq[i * 2 + 2].size());
            merge(freq[i * 2 + 1].begin(), freq[i * 2 + 1].end(),
                  freq[i * 2 + 2].begin(), freq[i * 2 + 2].end(),
                  freq[i].begin());
            sum[i].resize(freq[i].size() + 1, 0LL);
            for (int j = 0; j < freq[i].size(); j++) sum[i][j + 1] = sum[i][j] + freq[i][j];
        }
    }
    node query(int a, int b, T x, int k = 0, int l = 0, int r = -1) const  { 
        if (r < 0) r = n;
        if (b <= l || r <= a) return node(0, 0);
        else if (a <= l && r <= b) {
            int L = lower_bound(freq[k].begin(), freq[k].end(), x) - freq[k].begin();
            node no(L, sum[k][L]);
            return no;
        }
        else return query(a, b, x, k * 2 + 1, l, (l + r) / 2) + query(a, b, x, k * 2 + 2, (l + r) / 2, r);
    }
};
//  rangefreq<int> rf(v); rf.query(l,r).freq
