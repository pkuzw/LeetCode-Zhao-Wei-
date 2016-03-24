///@file	Coin Change
///@author	zhaowei
///@date	2016.03.24
///@version	1.0
///@version	2.0

#include <vector>
#include <algorithm>
using namespace std;

class Solution_v1 {
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

class Solution {
public:
	///@note	1. 动态规划
	//			2. 设dp[i]为金额为i时的最小硬币数目，初始化dp[i] = i == coins[j] ? 1 : -1;
	//			3. 递推关系式为dp[i] = dp[i-coins[j]] == -1 ? -1 : dp[i] == -1 ? dp[i-coins[j]] + 1 : min(dp[i], dp[i-coins[j]] + 1).
	//			4. 时间复杂度为O(nk)，空间复杂度为O(n)，其中n为金额大小，k为硬币种类。
	int coinChange(vector<int>& coins, int amount) {
		if (coins.empty() || !amount)	return 0;
		int k = coins.size();		
		vector<int> dp(amount+1, -1);
		sort(coins.begin(), coins.end());		

		for (int i = 0; i < k; i++) {
			if (coins[i] <= amount)	dp[coins[i]] = 1;
			else	break;
		}

		for (int i = 1; i <= amount; i++) {
			for (int j = 0; j < k && coins[j] <= i; j++) {
				if (dp[i-coins[j]] == -1)		continue;
				else {
					dp[i] = dp[i] == -1 ? dp[i-coins[j]] + 1 : min(dp[i], dp[i-coins[j]] + 1);
				}
			}
		}
		return dp[amount];
	}
};

int main() {
	vector<int> coins;
	int c[] = {46, 45, 35};
	for (int i = 0; i != 3; i++)
		coins.push_back(c[i]);
	Solution slt;
	int rslt = slt.coinChange(coins, 93);
	return 0;
}