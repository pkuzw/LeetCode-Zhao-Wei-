﻿///@file	Best Time to Buy and Sell Stock III
/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most two transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
*/
///@author	zhaowei
///@date	2015.07.24
///@version	1.1

#include <vector>

using namespace std;

class Solution {
public:
	///@brief	如果最多只能进行2次交易，计算最大收益
	///@param	prices	股价数组
	///@return	返回最多进行两次交易时的最大收益
	/* @note	设mp[i]表示在第i天第一次卖出股票的最大利润。它由两部分构成，第一部分是第一次卖出股票的收益，第二部分是第二次卖出股票的收益。
				mp[i] = dp[0..i]+dp[i+1..n]。计算dp[i]的方法利用"Best Time to Buy and Sell Stock"中的算法即可。
				时间复杂度为O(n^2)，空间复杂度为O(n)。OJ报TLE。*/
	int maxProfit_Time_O_n2(vector<int>& prices) {
		if (prices.empty() || prices.size() == 1)	return 0;
		
		vector<int> mp(prices.size(), 0);
		for (int i = 0; i != prices.size(); i++)
		{
			vector<int>::iterator it = prices.begin();
			while (*it != prices[i])
				it++;

			vector<int> pa(prices.begin(), it+1);	//	有可能发生第一次交易的区间
			vector<int> pb(it+1, prices.end());		//	有可能发生第二次交易的区间

			mp[i] = maxProfit_OneTransaction(pa) + maxProfit_OneTransaction(pb);
		}

		int max_profit = 0;
		for (int i = 0; i != mp.size(); i++)
			if (mp[i] > max_profit)
				max_profit = mp[i];

		return max_profit;
	}

	///@brief	如果最多只能进行2次交易，计算最大收益
	///@param	prices	股价数组
	///@return	返回最多进行两次交易时的最大收益
	/* @note	设mp[i]表示在第i天第一次卖出股票的最大利润。它由两部分构成，第一部分是第一次卖出股票的收益，第二部分是第二次卖出股票的收益。
				mp[i] = dp_sell[0..i] + dp_buy_anyday[i+1..n]。dp_sell[i]表示在第i天卖出获得的最大利润，dp_buy_anyday[i]表示在第i天之后
				任何一天买入获得的最大利润。因为不一定卖出立即就要买入。dp_buy_anyday的计算方法与dp_sell类似，只不过是先倒着算出来dp_buy[i]，
				dp_buy[i]表示在第i天买入获得的最大利润。然后再倒着遍历一遍dp_buy，计算出dp_buy_anyday。
				时间复杂度为O(n)，空间复杂度为O(n)。*/
	int maxProfit_Time_O_n(vector<int>& prices) {
		if (prices.empty() || prices.size() == 1)	return 0;

		vector<int> dp_sell(prices.size(), 0);	//	dp_sell[i]表示第i天卖出的最大利润
		dp_sell[0] = 0;
		for (int i = 1; i < prices.size(); i++)
			dp_sell[i] = (prices[i] > prices[i-1]) ?	 dp_sell[i-1] + (prices[i] - prices[i-1]) : ((dp_sell[i-1] > prices[i-1] - prices[i]) ? dp_sell[i-1] - (prices[i-1] - prices[i]) : 0);	

		vector<int> dp_buy(prices.size(), 0);	//	dp_buy[i]表示第i天买入的最大利润
		dp_buy.back() = 0;
		for (int i = prices.size()-2; i >= 0; i--)
			dp_buy[i] = (prices[i+1] > prices[i]) ? dp_buy[i+1] + (prices[i+1] - prices[i]) : ((dp_buy[i+1] > prices[i] - prices[i+1]) ? dp_buy[i+1] - (prices[i] - prices[i+1]) : 0);

		vector<int> dp_buy_anyday(prices.size(), 0);	//	dp_buy_anyday[i]表示在第i天之后任何一天买入获得的最大利润
		int mprofit = 0;
		for (int i = prices.size()-1; i >= 0; i--)
		{
			if (mprofit < dp_buy[i])
				mprofit = dp_buy[i];
			
			dp_buy_anyday[i] = mprofit;
		}

		vector<int> mp(prices.size(), 0);
		for (int i = 0; i != prices.size(); i++)
			mp[i] = dp_sell[i] + dp_buy_anyday[i];		
		
		int max_profit = 0;
		for (int i = 0; i != prices.size(); i++)
			if (mp[i] > max_profit)
				max_profit = mp[i];

		return max_profit;
	}

private:
	///@brief	计算最多只能有一次股票交易的最大利润
	///@param	prices	股票每一天的价格
	///@return	返回所能挣到的最大利润
	/* @note	动态规划：设dp[i]表示第i天卖出的最大利润。初始条件为dp[0] = 0。
				递推关系式为dp[i] = (prices[i] > prices[i-1]) ?	dp[i-1] + (prices[i] - prices[i-1]) : ((dp[i-1] > prices[i-1] - prices[i]) ? dp[i-1] - (prices[i-1] - prices[i]) : 0)
				时间复杂度为O(n)，空间复杂度为O(n)。
				*/
	int maxProfit_OneTransaction(vector<int>& prices) {
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
	int n[10] = {1,5,15,14,13,14,17,2,1,1};
	for (int i = 0; i != 10; i++)
		prices.push_back(n[i]);

	Solution slt;
	int r = slt.maxProfit_Time_O_n(prices);
	int s = slt.maxProfit_Time_O_n2(prices);

	return 0;
}