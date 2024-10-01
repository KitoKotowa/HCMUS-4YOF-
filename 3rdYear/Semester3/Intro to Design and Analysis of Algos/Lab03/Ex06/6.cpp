#include <iostream>
#include <vector>
#include <fstream>
using namespace std; 

struct Coins {
    int price;
    int num = 0;
};

void readFile(string& filePath, int& k, vector<int>& denominations, int& n) {
    ifstream fin(filePath);
    if (fin.is_open()) {
        fin >> k;
        denominations.resize(k);
        for (int i = 0; i < k; ++i) {
            fin >> denominations[i];
        }
        fin >> n;
        fin.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}

void moneyChange(int money, vector<Coins> &coinsUsed) {
    if (money <= 0) 
        return;

    for (Coins &coin : coinsUsed) { 
        if (coin.price == money) {
            coin.num = 1;
        }
        break;
    }

	for (Coins &coin : coinsUsed) {
		if (money > coin.price) {
			++coin.num;
			moneyChange(money - coin.price, coinsUsed);
			break;
		}
	}
}

int main() {
    int k, n;
    vector<int> denominations;
    string filePath = "6.txt";

    readFile(filePath, k, denominations, n);
    
    vector<Coins> coinsUsed;
    for (int i = 0; i < k; ++i) {
        coinsUsed.push_back({denominations[i], 0});
    }
    
    moneyChange(n, coinsUsed);

    for (int i = 0; i < k; ++i) {
        cout << coinsUsed[i].price << ": " << coinsUsed[i].num << endl;
    }

    return 0;
}