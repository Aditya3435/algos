const int maxP = 2002;
bool isPrime[maxP];

void sieve(int n) {
    for(int i=0; i<=n; i++) isPrime[i] = 1;
    isPrime[0] = isPrime[1] = 0; 
    for (int i = 2; i*i <= n; i++){
        if (isPrime[i]){
            for (int j = i * i; j <= n; j += i){
                isPrime[j] = 0; 
            }
        }
    }
}