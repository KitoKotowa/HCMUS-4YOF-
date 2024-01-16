#include <iostream>
using namespace std;

int main() {
	int a, b, ucln = 0;
	cout << "Nhap a: ";
	cin >> a;
	cout << "Nhap b: ";
	cin >> b;
	for (int i = 1; i <= min(a, b); i++) {
		if (a % i == 0 && b % i == 0) {
			ucln = i;
		}
	}
	cout << "UCLN cua a va b la: " << ucln << endl;
	cout << "BCNN cua a va b la: " << a * b / ucln << endl;
	if (a < b) {
		for (int x = (b / a + 1); x <= (b / a + 1) * ucln; ++x) {
			for (int y = -1; y >= -ucln; y--)
			{
				if (a * x + b * y == ucln) {
					cout << "(x,y) = " << x << "," << y;
					exit(0);
				}
			}
		}
	}
	if (a > b) {
		for (int x = (a / b + 1); x <= (a / b + 1) * ucln; ++x) {
			for (int y = -1; y >= -ucln; y--)
			{
				if (a * x + b * y == ucln) {
					cout << "(x,y) = " << x << "," << y;
					exit(0);
				}
			}
		}
	}

	return 0;
}