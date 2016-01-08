///@file	Best Time to Buy and Sell Stock II
/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like 
(ie, buy one and sell one share of the stock multiple times). 

However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
*/
///@author	zhaowei
///@date	2015.07.24
///@version	1.0

///@date	2015.08.22
///@version	1.1

///@date	2016.01.08
///@version	2.0

#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	计算多次股票交易的最大利润
	///@param	prices	股票每一天的价格
	///@return	返回所能挣到的最大利润
	/* @note	因为可以多次交易，所以只需要找到所有的单调递增区间即可。利润就是所有单增区间的差值之和。
				时间复杂度为O(n)，空间复杂度为O(n)。
				*/
	int maxProfit(vector<int>& prices) {
		if (prices.empty() || prices.size() == 1)	return 0;

		int max_profit = 0;

		int start = 0, end = 0;
		bool flg = true;	//	标记处于递增区间还是递减区间，初始为递增
		for (int i = 0; i != prices.size()-1; i++)
		{
			if (prices[i+1] > prices[i])
			{
				if (!flg)
					start = i;	//	递增区间开始				
				flg = true;

				if (i == prices.size()-2)	//	处理最后一个单增区间
					max_profit += prices.back() - prices[start];		
			}
			else
			{
				if (flg)
				{
					end = i;	//	递增区间结束
					max_profit += prices[end] - prices[start];
				}
				flg = false;
			}			
		}
		return max_profit;
	}
};

class Solution_v1_1 {
public:
	int maxProfit(vector<int>& prices) {
		if (prices.size() < 2)	return 0;
		int start = 0, end = 0;
		bool flg = true;	//false: 递减区间，true: 递增区间
		int max_profit = 0;
		for (int i = 0; i != prices.size()-1; i++)
		{
			if (prices[i+1] > prices[i])
			{
				if (!flg)	start = i;
				flg = true;
				if (i == prices.size()-2)	max_profit += prices[i+1] - prices[start];
			}
			else
			{
				if (flg)
				{
					end = i;
					max_profit += prices[end] - prices[start];
				}
				flg = false;
			}
		}
		return max_profit;
	}
};

class Solution {
public:
	///@brief	计算多次股票交易的最大利润
	///@param	prices	股票每一天的价格
	///@return	返回所能挣到的最大利润
	///@note	1. 遍历；2. 通过枚举出所有单增相邻区间和即可；3. 时间复杂度为O(n)，空间复杂度为O(1)。n为交易天数。
	int maxProfit(vector<int>& prices) {
		int rslt = 0;
		for (int i = 1; i < prices.size(); i++) 
			rslt += max(prices[i] - prices[i - 1], 0);
		return rslt;
	}
};

int main()
{
	int n[13] = {1,9,6,9,9,1,7,1,1,5,9,9,9};
	vector<int> prices;
	for (int i = 0; i != 12; i++)
		prices.push_back(n[i]);

	Solution slt;
	int r = slt.maxProfit(prices);

	Solution_v1 slt_v1;
	int r1 = slt_v1.maxProfit(prices);
	return 0;
}