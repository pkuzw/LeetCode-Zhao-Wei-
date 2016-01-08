///@file	Best Time to Buy and Sell Stock III
/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most two transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
*/
///@author	zhaowei
///@date	2015.07.24
///@version	1.1

///@date	2015.08.22
///@version	2.0

///@date	2016.01.08
///@version	2.1
///@version	3.0

#include <vector>

using namespace std;

class Solution_v1 {
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

class Solution_v2 {
public:
	int maxProfit(vector<int>& prices) {
		if (prices.size() < 2)	return 0;
		vector<vector<int>> dp_local(prices.size(), vector<int>(3, 0));	//	dp_local[i][j]表示在第i天进行第j次交易的最大利润
		vector<vector<int>> dp_global(prices.size(), vector<int>(3, 0));//	dp_global[i][j]表示在前i天进行j次交易的最大利润
		for (int i = 1; i != prices.size(); i++)
		{
			int diff = prices[i] - prices[i-1];
			for (int j = 1; j <= 2; j++)
			{
				dp_local[i][j] = max(dp_local[i-1][j] + diff, dp_global[i-1][j-1] + max(diff, 0));	//	先算local，再算global
				dp_global[i][j] = max(dp_local[i][j], dp_global[i-1][j]);				
			}
		}
		return dp_global[prices.size()-1][2];
	}
};

class Solution_v2_1 {
public:
	///@brief	如果最多只能进行2次交易，计算最大收益
	///@param	prices	股价数组
	///@return	返回最多进行两次交易时的最大收益
	///@note	1. 动态规划；
	//			2. 设dp_local[i][j]表示在第i天进行第j次交易的最大利润，dp_global[i][j]表示在前i天进行j次交易的最大利润；
	//			3. 初始值为0；
	//			4. 设diff = prices[i] - prices[i - 1]，递推关系式为dp_local[i][j] = max(dp_local[i - 1][j] + diff, dp_global[i - 1][j - 1] +　max(diff, 0)),
	//			   dp_global[i][j] = max(dp_local[i][j], dp_global[i - 1][j])；
	//			5. 这里需要解释一下dp_local的递推关系式，因为对于dp_local[i][j]来说，意味着在第i天
	//			   进行第j次交易，所以可以分成两种情况，一种是第i-1天进行了第j次交易，那么则第i天必须进行交易，这样就可以将第i天和第i-1天两次卖出交易合并，转换为只
	//			   在第i天进行卖出交易，所以无论diff是否为负，都必须要加上；第二种情况是，第i-1天可能没进行第j次交易，所以就是dp[i - 1][j - 1]，即在前i-1天进行了
	//			   j-1次交易，最后一次交易安排在第i天，如果diff为负，则不用加上；
	//			6. 另外，dp_global[i][j]也分成两种情况，一种是在第i天进行了第j次交易，那么就是dp_local[i][j]；如果没在第i天进行交易，意味着在前i-1天进行了j次交易，
	//			   则是dp_global[i - 1][j]；
	//			7. 时间复杂度为O(n)，空间复杂度为O(n)。
	int maxProfit(vector<int>& prices) {
		int days = prices.size();
		if (days < 2)	return 0;
		vector<vector<int>> dp_local(days, vector<int>(3, 0));
		vector<vector<int>> dp_global(days, vector<int>(3, 0));
		for (int i = 1; i < days; i++) {
			int diff = prices[i] - prices[i - 1];
			for (int j = 1; j < 3; j++) {
				dp_local[i][j] = max(dp_local[i - 1][j] + diff, dp_global[i - 1][j - 1] + max(diff, 0));
				dp_global[i][j] = max(dp_local[i][j], dp_global[i - 1][j]);
			}
		}
		return dp_global[days - 1][2];
	}
};

class Solution {
public:
	///@brief	如果最多只能进行2次交易，计算最大收益
	///@param	prices	股价数组
	///@return	返回最多进行两次交易时的最大收益
	///@note	1. 动态规划；
	//			2. 建立4个临时变量：max_profit_2, lowest_buy_price_2, max_profit_1, lowest_buy_price_1，分别表示第二次卖出的最大利润，
	//			第二次买入的最低价格，第一次卖出的最大利润和第二次买入的最低价格。按照这个顺序依次对其进行更新。
	//			3. max_profit_2 = max(max_profit_2, prices[i] - lowest_buy_price_2);
	//			4. lowest_buy_price_2 = min(lowest_buy_price_2, prices[i] - max_profit_1);
	//			5. max_profit_1 = max(max_profit_1, prices[i] - lowest_buy_price_1);
	//			6. lowest_buy_price_1 = min(lowest_buy_price_1, p);
	//			7. 其中初始化为max_profit_1 & 2 = 0, lowest_buy_price_1 & 2 = INT_MAX；
	//			8. 时间复杂度为O(n)，空间复杂度为O(1)。
	int maxProfit(vector<int>& prices) {
		int max_profit[2] = {0, 0};
		int lowest_buy_price[2] = {INT_MAX, INT_MAX};
		for (int i = 0; i < prices.size(); i++) {
			max_profit[1] = max(max_profit[1], prices[i] - lowest_buy_price[1]);
			lowest_buy_price[1] = min(lowest_buy_price[1], prices[i] - max_profit[0]);
			max_profit[0] = max(max_profit[0], prices[i] - lowest_buy_price[0]);
			lowest_buy_price[0] = min(lowest_buy_price[0], prices[i]);
		}
		return max_profit[1];
	}
};

int main()
{
	vector<int> prices;
	int n[10] = {1,5,15,14,13,14,17,2,1,1};
	for (int i = 0; i != 10; i++)
		prices.push_back(n[i]);

	Solution_v1 slt_v1;
	int r = slt_v1.maxProfit_Time_O_n(prices);
	int s = slt_v1.maxProfit_Time_O_n2(prices);
	Solution slt;
	int t = slt.maxProfit(prices);

	return 0;
}