#include <iostream>

using namespace std;

int bit_length(int x) {
    int length = 0;

    if (x == 0) {
        return 1;
    }

    while (x > 0) {
        x >>= 1;
        length++;
    }

    return length;
}

int mul(int x, int y) {
    int n = max(bit_length(x), bit_length(y));  
    if (n <= 1) {  
        return x * y; 
    }

    int half_n = (n + 1) / 2;  
    int xL = x >> half_n;  
    int xR = x & ((1 << half_n) - 1);  
    int yL = y >> half_n; 
    int yR = y & ((1 << half_n) - 1);  

    int p = mul(xL, yL);  
    int q = mul(xR, yR);  
    int r = mul(xL + xR, yL + yR);  

    return p * (1 << (2 * half_n)) + (r - p - q) * (1 << half_n) + q;
}


int main() {
    int u;
    int v;
    cin >> u >> v;
    cout << mul(u, v) << endl;
    return 0;
}