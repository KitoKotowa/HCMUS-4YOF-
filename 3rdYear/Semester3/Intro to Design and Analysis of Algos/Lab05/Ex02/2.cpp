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

// void moneyChange(int money, vector<Coins> &coinsUsed) {
//     if (money <= 0) 
//         return;

//     for (Coins &coin : coinsUsed) { 
//         if (coin.price == money) {
//             coin.num = 1;
//         }
//         break;
//     }

// 	for (Coins &coin : coinsUsed) {
// 		if (money > coin.price) {
// 			++coin.num;
// 			moneyChange(money - coin.price, coinsUsed);
// 			break;
// 		}
// 	}
// }

void moneyChange(int money, vector<Coins>& coinsUsed) {
    vector<int> dp(money + 1, INT_MAX);
    vector<int> lastCoin(money + 1, -1); 

    dp[0] = 0;

    for (int i = 1; i <= money; ++i) {
        for (int j = 0; j < coinsUsed.size(); ++j) {
            if (coinsUsed[j].price <= i && dp[i - coinsUsed[j].price] != INT_MAX) {
                if (dp[i] > dp[i - coinsUsed[j].price] + 1) {
                    dp[i] = dp[i - coinsUsed[j].price] + 1;
                    lastCoin[i] = j;
                }
            }
        }
    }

    for (int i = 0; i < coinsUsed.size(); ++i){
        for (int amount = coinsUsed[i].price; amount <= money; ++amount){
            if (dp[amount - coinsUsed[i].price] != INT_MAX && dp[amount - coinsUsed[i].price] + 1 < dp[amount]){
                dp[amount] = dp[amount - coinsUsed[i].price] + 1;
                lastCoin[amount] = i;
            }
        }
    }

    if (dp[money] == INT_MAX) {
        cout << "No solutions." << endl;
        return;
    }

    int currMoney = money;
    while (currMoney > 0) {
        int coinIndex = lastCoin[currMoney];
        if (coinIndex == -1) break;
        ++coinsUsed[coinIndex].num;
        currMoney -= coinsUsed[coinIndex].price;
    }
}

int changeMaking(const vector<int>& denomination, vector<int>& solution, int target) {
    vector<int> dp(target + 1, INT_MAX);
    vector<int> lastCoin(target + 1, -1);

    dp[0] = 0;

    for (int i = 0; i < denomination.size(); ++i){
        for (int amount = denomination[i]; amount <= target; ++amount){
            if (dp[amount - denomination[i]] != INT_MAX && dp[amount - denomination[i]] + 1 < dp[amount]){
                dp[amount] = dp[amount - denomination[i]] + 1;
                lastCoin[amount] = i;
            }
        }
    }

    if (dp[target] == INT_MAX)
        return -1;

    int amount = target;
    while (amount > 0) {
        int coinIndex = lastCoin[amount];
        solution[coinIndex]++;
        amount -= denomination[coinIndex];
    }

    return dp[target];
}

int main() {
    int k, n;
    vector<int> denominations;
    string filePath = "2.txt";

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