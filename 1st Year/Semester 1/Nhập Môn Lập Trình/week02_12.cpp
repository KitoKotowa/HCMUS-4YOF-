#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	int x;
	cout << "Nhap x: ";
	cin >> x;
	cout << endl;
	if (x >= 0 && x <= 9)
		cout << x << endl;
	else if (x >=10 && x <= 35)
		cout << static_cast <char> (x - 10 + 'A') << endl;
	else cout << "Khong hop le";
	return 0;
}