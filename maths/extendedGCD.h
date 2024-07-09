#include <bits/stdc++.h>
using namespace std;
int extendedGCD(int a, int b, int &x, int &y) {
    if(b == 0) {
        x = 1, y = 0; 
        return a;
    }
    int x1, y1;
    int d = extendedGCD(b, a % b, x1, y1);
    x = x1;
    y = x1 - y1 * (a / b);

    return d;
}
int main()
{   
	// x and y are modified by the extendedGCD function
    // and they are the coefficients such that ax + by = GCD(a, b)
    int x,y, a, b;
    cin >> a >> b;
    cout << extendedGCD(a, b, x, y) << endl;

    return 0;
}