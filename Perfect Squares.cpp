///@file	Perfect Squares
///@author	zhaowei
///@date	2016.03.02
///@version	1.0

///@date	2016.03.04
///@version	1.1
///@version	2.0

#include <vector>
#include <cstdlib>
using namespace std;

class Solution_v1 {
public:
	///@brief	给定一个正整数n，计算它是最少多少个平方数的和
	///@param	n	正整数
	///@return	平方数的个数
	///@note	1. 动态规划；
	//			2. 用dp[i]表示正整数i能够被最少的平方数所表达的数目，初始化dp[0] = 0；
	//			3. 递推关系式为dp[i] = min(dp[i], dp[j*j] + dp[i-j*j])；
	//			4. 时间复杂度为O(n^2)，空间复杂度为O(n)，其中n为正整数。应该还有很大的优化空间。
	int numSquares(int n) {
		vector<int> dp(n + 1, INT_MAX);
		dp[0] = 0;
		for (int i = 1; i * i <= n; i++)	dp[i*i] = 1;
		for (int i = 1; i <= n; i++) {
			int min_partition = INT_MAX;
			int k = 0;
			for (int j = 1; j * j < i; j++) {
				if (min_partition >= dp[j*j]) {
					min_partition = dp[j*j];
					k = j * j;
				}
				if (dp[i] == 1)	continue;
				dp[i] = min(dp[i], min_partition + dp[i-k]);
			}			
		}
		return dp[n];
	}
};

class Solution_v1_1 {
public:
	///@note	1. 动规；
	//			2. 递推关系式为dp[i] = min(dp[i], dp[i-j*j] + 1)；初始值dp[0] = 0；
	//			3. 时间复杂度为O(nlogn)，空间复杂度为O(n)。
	int numSquares(int n) {
		if (n <= 0)	return 0;
		vector<int> dp(n + 1, INT_MAX);
		dp[0] = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j * j <= i; j++)
				dp[i] = min(dp[i], dp[i-j*j] + 1);
		return dp[n];		
	}
};

class Solution {
public:
	///@note	1. 在v1的基础上进行改良，因为dp[n]要依赖于前面的dp[0..n-1]，所以将dp[]设为静态变量，这样每次计算后的结果就能被下次调用所利用上。
	//			2. 注意静态变量的初始化。
	int numSquares(int n) {
		if (n <= 0)	return 0;
		static vector<int> dp(1, 0);	//	注意dp是静态变量，需要在初始化时设置好，否则每次调用就会累积它的该变量。		
		while (dp.size() <= n) {
			int i = dp.size();
			int cnt = INT_MAX;
			for (int j = 1; j*j <= i; j++)	cnt = min(cnt, dp[i-j*j] + 1);
			dp.push_back(cnt);
		}
		return dp[n];
	}
};

int main() {
	Solution slt;
	int rslt = slt.numSquares(2);
	return 0;
}