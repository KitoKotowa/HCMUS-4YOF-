#include <iostream>
#include <string>
using namespace std;

string padZeros(string &s, int n) {
    string result = s;
    for (int i = 0; i < n; ++i) {
        result = "0" + result;
    }
    return result;
}

string addStrings(const string &a, const string &b) {
    string result = "";
    int carry = 0, sum = 0;

    int lenA = a.length(), lenB = b.length();
    int i = lenA - 1, j = lenB - 1;

    while (i >= 0 || j >= 0 || carry) {
        sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';

        carry = sum / 10;
        result = char(sum % 10 + '0') + result;
    }

    return result;
}

string mul(string u, string v) {
    int n = max(u.length(), v.length());

    if (u == "0" || v == "0") {
        return "0";
    }

    if (n == 1) {
        int result = (u[0] - '0') * (v[0] - '0');
        return to_string(result);
    }

    if (u.length() < n) u = padZeros(u, n - u.length());
    if (v.length() < n) v = padZeros(v, n - v.length());

    int m = n / 2;

    string x = u.substr(0, n - m);
    string y = u.substr(n - m);
    string w = v.substr(0, n - m);
    string z = v.substr(n - m);

    // string xw = mul(x, w);
    // string yz = mul(y, z);
    // string xz = mul(x, z);
    // string yw = mul(y, w);

    string r = mul(addStrings(x, y), addStrings(w, z));
    string p = mul(x, w);
    string q = mul(y,z);    

    // string result = addStrings(addStrings(xw + string(2 * m, '0'), addStrings(xz, yw) + string(m, '0')), yz);
    string result = addStrings(addStrings(p + string(2 * m, '0'), string(to_string(stoi(r) - stoi(p) - stoi(q))) + string(m, '0')), q);
    return result;
}

int main() {
    string u;
    string v;
    getline(cin, u);
    getline(cin, v);
    cout << mul(u, v) << endl;
    return 0;
}
