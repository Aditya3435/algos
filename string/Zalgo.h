vector<int>Zalgo(const string&s, const string &t)
{
    string ss = t + s;
    vector<int> ans(ss.size());
    if (ss.empty()) return ans;
    ans[0] = ss.size();
    int i = 1, j = 0;
    while (i < ss.size()) {
        while (i + j < ss.size() && ss[j] == ss[i + j]) j++;
        ans[i] = j;
        if (j == 0) {
            i++;
            continue;
        }
        int k = 1;
        while (i + k < ss.size() && k + ans[k] < j)
            ans[i + k] = ans[k], k++;
        i += k;
        j -= k;
    }
    return ans;
}

