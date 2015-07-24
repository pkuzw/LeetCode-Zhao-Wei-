///@file	Best Time to Buy and Sell Stock
/*
Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), 

design an algorithm to find the maximum profit.
*/
///@author	zhaowei
///@date	2015.07.24
///@version	1.0

#include <vector>

using namespace std;

class Solution {
public:
	///@brief	计算最多只能有一次股票交易的最大利润
	///@param	prices	股票每一天的价格
	///@return	返回所能挣到的最大利润
	/* @note	动态规划：设dp[i]表示第i天卖出的最大利润。初始条件为dp[0] = 0。
				递推关系式为dp[i] = (prices[i] > prices[i-1]) ?	dp[i-1] + (prices[i] - prices[i-1]) : ((dp[i-1] > prices[i-1] - prices[i]) ? dp[i-1] - (prices[i-1] - prices[i]) : 0)
				时间复杂度为O(n)，空间复杂度为O(n)。
				*/
	int maxProfit(vector<int>& prices) {
		if (prices.empty() || prices.size() == 1)	return 0;

		vector<int> dp(prices.size(), 0);	//	dp[i]表示第i天卖出的最大利润
		dp[0] = 0;
		for (int i = 1; i < prices.size(); i++)
			dp[i] = (prices[i] > prices[i-1]) ?	dp[i-1] + (prices[i] - prices[i-1]) : ((dp[i-1] > prices[i-1] - prices[i]) ? dp[i-1] - (prices[i-1] - prices[i]) : 0);	

		int max_profit = 0;
		for (int i = 0; i != dp.size(); i++)
			if (dp[i] > max_profit)
				max_profit = dp[i];

		return max_profit;
	}
};

int main()
{
	vector<int> prices;
	prices.push_back(31);
	prices.push_back(22);
	prices.push_back(15);
	prices.push_back(13);
	prices.push_back(22);
	prices.push_back(5);
	prices.push_back(1);

	Solution slt;
	int r = slt.maxProfit(prices);
	return 0;
}