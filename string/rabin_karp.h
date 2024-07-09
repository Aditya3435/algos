const int prime = 31;
const int mod = 1e9 + 7;

vector<int> rabin_karp(string &s, string &t) {
    int n = s.size();
    int m = t.size();
    vector<int> p(max(n, m));
    p[0] = 1;
    for (int i = 1; i < (int)p.size(); i++)
        p[i] = (p[i - 1] * prime) % mod;

    vector<int> hs(n + 1, 0);
    for (int i = 0; i < n; i++)
        hs[i + 1] = (hs[i] + (s[i] - 'a' + 1) * p[i]) % mod;

    int ht = 0;
    for (int i = 0; i < m; i++)
        ht = (ht + (t[i] - 'a' + 1) * p[i]) % mod;

    vector<int> occ;
    for (int i = 0; i < n - m + 1; i++) {
        int cur_hs = (hs[i + m] + mod - hs[i]) % mod;
        if (cur_hs == (ht * p[i]) % mod) {
            occ.push_back(i);
        }
    }
    return occ;
}
