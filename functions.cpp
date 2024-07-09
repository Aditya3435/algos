#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9 + 7;
int power(int a, int b) {
    int ans = 1;
    while(b) {
        if(b&1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans;
}


int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1}; 
bool valid(int x, int y, int N, int M) {
    return x >= 0 && x < N && y >= 0 && y < M;
}



int countSetBits(int n) { 
    int ans = 0;
    for(int i=0; i<32; i++) {
        int g = (n>>(i+1)); 
        int setBits = 1<<i;
        int ct = g * setBits;
        if(n>>i&1) ct += (n%setBits)+1;
        ans += ct;
    }
    return ans;
}



int toDecimal(string s) {
    int x = 0;
    for (char c : s) {
        x <<= 1;
        x += (c - '0');
    }
    return x;
}



string toBinary(int n) {
    string ans;
    for(int i=0; i<32; i++) ans += (n >> i & 1) + '0';
    reverse(ans.begin(), ans.end());
    return ans;
}



vector<int> divisors(int n) {
	vector<int> v;
    v.push_back(1);
	for (int i = 2; i * i <= n; i++){
		if (n % i == 0){
			v.push_back(i);
			if (i * i != n) v.push_back(n / i);
		}
	}
    v.push_back(n);
	return v;
}




vector<int> prime_factorization(int n) {
	vector<int> v;
	for (int i = 2; i * i <= n; i++) {
        if(n % i == 0) {
            v.push_back(i);
		    while (n % i == 0) n /= i;
        }
	}
	if (n != 1) v.push_back(n);
	return v;
}

int kadane(vector<int> &arr) {
    int n = arr.size();
    vector<int> dp(n);
    for(int i=0; i<n; i++) {
        dp[i] = arr[i];
        if(i) dp[i] = max(dp[i], dp[i-1] + arr[i]);
    }
    int maxSum = *max_element(dp.begin(), dp.end());
    return maxSum;
}

int sqrt(int a){
    int l = 0, r = a, ans = 0;
    while (l <= r) {
        int mid = l + ((r - l) / 2);
        if (mid * mid <= a)ans = mid,l = mid + 1;
        else r = mid - 1;
    }
    return ans;
}



bool isPerfectSquare(int x){
    if (x >= 0) {
        int sr = sqrt(x);
        return (sr * sr == x);
    }
    return false;
}




int LCM(int a, int b) { 
    return (a / __gcd(a, b) * b); 
}




int findMex(vector<int> arr) {
    sort(arr.begin(), arr.end());
    int mex = 0;
    for (int i = 0; i < static_cast<int>(arr.size()); i++){
        if (arr[i] == mex)mex++;
    }
    return mex;
}




int countDigits(int n) {
    return to_string(n).size();
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n = n / 10;
    }
    return sum;
}




int lower_bound(vector<int> &nums, int k) {
    int l = 0, r = nums.size() - 1;
    while (l <= r) {
        int m = l + r >> 1;  
        if (nums[m] >= k) r = m - 1;
        else l = m + 1;
    }
    return l;
}




int upper_bound(vector<int> &nums, int k) {
		int l = 0, r = nums.size() - 1;
		while (l <= r) {
			int m = l + r >> 1;;
			if (nums[m] > k) r = m - 1;
			else l = m + 1;
		}
		return l;
} 



bool isPrime(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}




const int maxP = 2002;
bool prime[maxP];
void sieve(int n) {
    for(int i=0; i<=n; i++) prime[i] = 1;
    prime[0] = prime[1] = 0; 
    for (int i = 2; i*i <= n; i++){
        if (prime[i]){
            for (int j = i * i; j <= n; j += i){
                prime[j] = 0; 
            }
        }
    }
}

vector<int> nextSmaller(vector<int> &v) {
    int n = v.size();
    stack<int> st;
    vector<int> next(n, -1);
    vector<int> prev(n, -1);
    for(int i=0; i<n; i++) {
        // v[st.top()] < v[i] // for nextGreater
        while(st.size() && v[st.top()] > v[i]) { 
            next[st.top()] = i;
            prev[i] = st.top();
            st.pop();
        }

        st.push(i);
    }
    return prev;
}

vector<int> previousSmaller(vector<int> &v) {
    int n = v.size();
    stack<int> st;
    vector<int> prev(n, -1);
    for(int i=n-1; i>=0; i--) {
        while(st.size() && v[st.top()] > v[i]) { 
            prev[st.top()] = i;
            st.pop();
        }

        st.push(i);
    }
    return prev;
}
