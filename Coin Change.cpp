///@file	Coin Change
///@author	zhaowei
///@date	2016.03.24
///@version	1.0

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	///@brief	给定一组正整数，表示货币的面值，求能够兑换的指定面额的最小货币数目
	///@param	coins	货币面值
	///@param	amount	指定的额度
	///@return	返回兑换成指定额度的最少货币数量
	///@note	1. 贪心法
	//		2. 找到比当前兑换金额小的最大面额货币，尽可能的多的兑换该面额，然后对剩下的金额进行上述迭代，直至剩余金额为0.
	//		3. wa.
	int coinChange(vector<int>& coins, int amount) {
		if (coins.empty())	return 0;
		sort(coins.begin(), coins.end());
		int rslt = 0;		
		int j = coins.size() - 1;
		while (amount) {
			if (coins[0] > amount)	return -1;
			int i = 0;
			for (i = j; i >= 0; i--) {
				if (coins[i] <= amount)	break;
			}					
			j = i - 1;
			int n = amount / coins[i];
			amount %= coins[i];
			rslt += n;			
		}
		return rslt;
	}
};

int main() {
	vector<int> coins;
	int c[] = {1, 2, 5};
	for (int i = 0; i != 3; i++)
		coins.push_back(c[i]);
	Solution slt;
	int rslt = slt.coinChange(coins, 11);
	return 0;
}