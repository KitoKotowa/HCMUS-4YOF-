#include <iostream>
using namespace std;

int main() {
	int a, b, c;
	cout << "Nhap a: ";
	cin >> a;
	cout << "Nhap a: ";
	cin >> b;
	c = (b % 100) / 10;
	cout << "      " << a << endl;
	cout << "      " << b << endl;
	cout << "__________" << endl;
	cout << "     " << a * (b % 10) << endl;
	cout << "    "  << a * c << endl;
	cout << "   "   << a * (b / 100) << endl;
	cout << "__________" << endl;
	cout << "   " << a * b << endl;
	return 0;
}
