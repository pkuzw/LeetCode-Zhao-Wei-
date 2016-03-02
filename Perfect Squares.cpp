///@file	Perfect Squares
///@author	zhaowei
///@date	2016.03.02
///@version	1.0

#include <vector>
#include <cstdlib>
using namespace std;

class Solution {
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

int main() {
	Solution slt;
	int rslt = slt.numSquares(1000000);
	return 0;
}