#include <iostream>

using namespace std;

int Josephus(int n) {
    int p = 1;
    while (p <= n) {
        p *= 2;
    }
    p /= 2; 
    int l = n - p;
    return 2 * l + 1; 
}

int main() {
    int n;
    cin >> n;

    int position = Josephus(n);
    cout << position << endl;

    return 0;
}
