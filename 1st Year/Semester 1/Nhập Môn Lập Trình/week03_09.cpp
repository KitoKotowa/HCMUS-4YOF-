#include <iostream>

using namespace std;

int main() {
	int h, f, g, kcach, i, sao;
	cout << "Nhap chieu cao h = ";
	cin >> h;
	sao = 2 * h - 1;
	kcach = (sao - 1) / 2;
	sao = 1;
	for (i = 1; i <= h; i++) {
		for (f = kcach; f > 0; f--) {
			cout << " ";
		}
		for (g = 1; g <= sao; g++) {
			cout << "*";
		}
		kcach = kcach - 1;
		sao = sao + 2;
		cout << endl;
	}
	return 0;
}