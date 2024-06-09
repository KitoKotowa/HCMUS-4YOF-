#include <iostream>

using namespace std;

int main() {
	long long n, a = 0, sodu = 1, t = 1;
	cout << "Nhap n: ";
	cin >> n;
	while (n>0) {
	sodu = n % 2;		
	n = n / 2;
	a = a + (sodu * t);
	t = t * 10;
	}
	cout << "Gia tri nhi phan: " << a << endl;
	return 0;
}
