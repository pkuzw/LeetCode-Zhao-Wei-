///@file	Ugly Number II
///@author	zhaowei
///@date	2016.01.30
///@version	1.0

#include <vector>
using namespace std;

class Solution {
public:
	///@brief	生成第n个丑数
	///@param	n	序号
	///@return	返回第n个丑数
	///@note	1. 动态规划；
	//			2. 设dp[i]表示第i个丑数；初始化dp[0] = 1；
	//			3. 设三个变量f2, f3, f5分别为dp[i-1]乘以2，3，5后的最小数；
	//			4. 设三个变量i2, i3, i5分别表示指向f2，f3，f5的下标；
	//			5. 递推关系式为dp[i] = min(f2 * 2, f3 * 3, f5 * 5)；
	//			6. 时间复杂度为O(n)，空间复杂度为O(n)。
	int nthUglyNumber(int n) {
		vector<int> dp(n, 0);
		dp[0] = 1;
		int i2 = 1, i3 = 1, i5 = 1;
		int min_val = 1, f2 = 2, f3 = 3, f5 = 5;
		for (int i = 1; i != n; i++) {
			min_val = min(min(f2, f3), f5);
			dp[i] = min_val;
			if (min_val == f2)	f2 = 2 * dp[i2++];
			if (min_val == f3)	f3 = 3 * dp[i3++];
			if (min_val == f5)  f5 = 5 * dp[i5++];
		}
		return dp[n-1];
	}
};

int main() {
	Solution slt;
	int rslt = slt.nthUglyNumber(10);
	return 0;
}