///@file	Best Time to Buy and Sell Stock with Cooldown
///@author	zhaowei
///@date	2016.03.19
///@version	1.0

///	在discuss中还有其他dp和自动状态机的解法，可以参考。
#include <vector>
using namespace std;

class Solution {
public:
	///@brief	能够多次进行股票交易，在买入时必须已经卖出上一次的买入，卖出后需要暂停一天才能再次买入
	///@param	prices	股票价格的时间数组
	///@return	返回能够获取的最大利润
	///@note	1. 动态规划；
	///			2. 考虑在第i天进行卖出操作的最大利润为profit1，在第i天什么都不做的最大利润为profit2；二者初始值为0；
	//			3. 如果在第i+1天进行卖出，则有两种情况，一种是在第i天进行了卖出，在第i天进行了买入并在第i+1天卖出；
	//			4. 另一种是在第i天什么都没做，则需要在第i+1天进行买入并同一天卖出；
	//			5. 由3和4得知，profit1[i+1] = max(profit1[i] + prices[i+1] - prices[i], profit2[i]);
	//			6. 而对于profit2[i+1]来说，也是两种情况，一种是在第i天卖出，另一种是在第i天什么都不做，profit2[i+1] = max(profit1[i], profit2[i])；
	//			7. 时间复杂度为O(n)，空间复杂度为O(1).

	int maxProfit(vector<int>& prices) {
		int profit1 = 0, profit2 = 0;
		if (prices.empty())	return 0;
		for (int i = 0; i < prices.size()-1; i++) {
			int tmp = profit1;
			profit1 = max(profit1 + prices[i+1] - prices[i], profit2);
			profit2 = max(tmp, profit2);
		}
		return max(profit1, profit2);
	}
};

int main() {
	vector<int> prices;
	prices.push_back(1);
	prices.push_back(2);
	prices.push_back(3);
	prices.push_back(0);
	prices.push_back(2);
	prices.clear();
	Solution slt;
	int rslt = slt.maxProfit(prices);
	return 0;
}