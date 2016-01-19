///@file	Best Time to Buy and Sell Stock IV
/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most k transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
*/
///@author	zhaowei
///@date	2015.07.31
///@version	1.0

///@date	2015.08.12
///@version	1.1

///@date	2016.01.19
///@version	2.0

#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	如果最多进行k次股票交易，求最大利润
	///@param	prices	每一天的股价
	///@return	返回最大利润
	/* @note	动态规划。当k < prices.size()时，设dp_local[i][j]表示到第i天至多j次交易且在第i天进行最后一次交易的的最大利润，
				dp_global[i][j]表示在第i天至多进行j次交易的最大利润。
				递推关系式为dp_local[i][j] = max(dp_local[i-1][j]+diff, dp_global[i-1][j-1]+max(diff, 0))，
				其中diff = prices[i] - prices[i-1]。
				如果前i-1天进行了j次交易，且第i-1	天完成了最后一次交易，那么为了保证最后一天i也有交易，那么必须要算上diff，
				但这也不会增加总的交易次数，因为在第i-1天卖出，然后在第i-1天买入，再在第i天卖出，相当于在第i天卖出，总的交易次数并没有改变。
				如果在前i-1天完成了j-1次交易，那么如果diff > 0，那么就选择算上最后一天的收益，如果diff < 0，为了能够满足在最后一天有交易的
				要求，则选择在当天买入，当天卖出。
				递推关系式dp_global[i][j] = max(dp_global[i-1][j], dp_local[i][j])，如果最后一次交易在第i天，那么就是dp_local[i][j]，
				如果最后一次交易不在第i天，那么就是dp_global[i-1][j]。
				时间复杂度为O(n^2)，空间复杂度为O(n^2).
				当k > prices时，问题转换成可以进行多次交易。参考"Best Time to Buy and Sell Stock II"的算法即可。*/
	int maxProfit(int k, vector<int>& prices) {
		if (prices.size() < 2)	return 0;
		if (k > prices.size())	return maxProfit_II(prices);

		vector<vector<int>> dp_global(prices.size(), vector<int>(k+1, 0));
		vector<vector<int>> dp_local(prices.size(), vector<int>(k+1, 0));

		for (int i = 1; i != prices.size(); i++)
		{
			int diff = prices[i] - prices[i-1];
			for (int j = 1; j <= k; j++)
			{
				dp_local[i][j] = max(dp_local[i-1][j] + diff, dp_global[i-1][j-1] + max(diff, 0));
				dp_global[i][j] = max(dp_global[i-1][j], dp_local[i][j]);
			}
		}
		return dp_global[prices.size()-1][k];
	}

//private:
	///@brief	当交易次数大于股票的天数时，相当于允许多次交易。问题转化为"Best Time to Buy and Sell Stock II"
	///@param	prices	股票每一天的价格
	///@return	返回所能挣到的最大利润
	/* @note	因为可以多次交易，所以只需要找到所有的单调递增区间即可。利润就是所有单增区间的差值之和。
				时间复杂度为O(n)，空间复杂度为O(n)。
				*/
	int maxProfit_II(vector<int>& prices) {
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

class Solution {
public:
	///@brief	如果能够最多进行k次股票交易，计算最大利润
	///@param	k	交易次数
	///@param	prices	每日股价
	///@return	返回最大利润
	///@note	1. 动态规划；
	//			2. 如果k >= prices.size()，则说明可以每天都进行交易，则计算出累积增量即可；
	//			3. 如果k < 2，则直接返回0；
	//			4. 如果2 <= k < prices.size()，则设dp_local[i][j]表示在第i天进行了第j次交易，dp_global[i][j]表示在前i天进行了j次交易，
	//			   递推关系式为dp_local[i][j] = max(dp_local[i-1][j] + diff, dp_global[i-1][j-1] + max(diff, 0));
	//			   dp_global[i][j] = max(dp_local[i][j], dp_global[i-1][j])。
	int maxProfit(int k, vector<int>& prices) {
		int days = prices.size();
		if (days < 2)	return 0;
		else if (days <= k)	return maxProfit_II(prices);
		vector<vector<int>> dp_local(days, vector<int>(k + 1, 0));
		vector<vector<int>> dp_global(days, vector<int>(k + 1, 0));
		for (int i = 1; i != days; i++) {
			int diff = prices[i] - prices[i-1];
			for (int j = 1; j <= k; j++) {
				dp_local[i][j] = max(dp_local[i-1][j] + diff, dp_global[i-1][j-1] + max(diff, 0));
				dp_global[i][j] = max(dp_local[i][j], dp_global[i-1][j]);
			}
		}
		return dp_global[days-1][k];
	}

	///@brief	能够进行多次交易的最大利润
	///@param	prices	股价
	///@return	返回最大利润
	int maxProfit_II(vector<int>& prices) {
		if (prices.size() < 2)	return 0;
		int rslt = 0;
		for (int i = 1; i != prices.size(); i++) 
			rslt += max(prices[i] - prices[i-1], 0);
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
	int r = slt.maxProfit(2, prices);
	int s = slt.maxProfit_II(prices);

	Solution_v1 slt_v1;
	int r1 = slt_v1.maxProfit(2, prices);
	int s1 = slt_v1.maxProfit_II(prices);
	return 0;
}