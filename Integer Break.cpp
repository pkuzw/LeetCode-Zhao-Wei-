///@file	Integer Break
///@author	zhaowei
///@date	2016.04.20
///@version	1.0
///@version	1.1
///@version	1.2


#include <vector>
using namespace std;

class Solution_wa1 {
public:
	///@brief	将一个不小于2的自然数n分解成若干个正数的和，使得这些正数的积最大
	///@param	n	自然数
	///@return	返回最大的因子积
	///@note	1. 通过观察，易知对于自然数n来说，n/2 * n/2是最大的；
	//			2. 如果n是大于4的数，则继续向下分解；如果是小于等于4的数则停止分解，因为4 = 2 + 2，而且2 * 2 = 4；3 = 1 + 2，且3 > 1 * 2.
	//			3. 时间复杂度为O(logn)，空间复杂度为O(1)。其中n是待分解的自然数。
	//			4. wa，挂在了8上，8 = 3 + 3 + 2的因子积大于8 = 4 + 4的因子积。
	int integerBreak(int n) {
		if (n == 2)	return 1;
		if (n == 3)	return 2;
		if (n == 4)	return 4;
		int rslt = 1;
		dfs(n, rslt);
		return rslt;
	}

	///@brief	递归辅助函数，帮助计算因子数可以为1的情形的最大积
	///@param	n		自然数
	///@param	rslt	最大积
	void dfs(int n, int& rslt) {
		if (n < 5) {
			rslt *= n;
			return;
		}
		int a = 0, b = 0;
		if (n % 2) {
			a = n / 2;
			b = n / 2 + 1;			
		}
		else a = b = n / 2;
		dfs(a, rslt);
		dfs(b, rslt);
	}
};

class Solution_wa2 {
public:
	///@note	1. 在wa的基础上改进，把n为偶数的情况改为两种。如果n / 4为偶数，则a = n / 2 - 1和b = n / 2 + 1；
	//			2. 如果n / 4为偶数，则a = n / 2和b = n / 2
	//			3. wa. 挂在n = 24上。
	int integerBreak(int n) {
		if (n == 2)	return 1;
		if (n == 3)	return 2;
		if (n == 4)	return 4;
		int rslt = 1;
		dfs(n, rslt);
		return rslt;
	}

	void dfs(int n, int& rslt) {
		if (n < 5) {
			rslt *= n;
			return;
		}
		int a = 0, b = 0;
		if (n % 2) {
			a = n / 2;
			b = n / 2 + 1;			
		}
		else {
			if ((n / 4) % 2) {
				a = n / 2;
				b = n / 2;
			}
			else {
				a = n / 2 - 1;			
				b = n / 2 + 1;
			}
		}
		dfs(a, rslt);
		dfs(b, rslt);
	}
};

class Solution {
public:
	///@note	1. 动态规划；
	//			2. 设dp[i]为数值为i的最大因子积，初始设置dp[2] = 2，dp[3] = 3；如果n = 2, 3，则直接返回1, 2；
	//			3. 递推关系式为dp[i] = dp[j] * dp[k].其中j + k = i且j > 1，k > 1.
	//			4. 时间复杂度为O(n^2)，空间复杂度为O(n)。
	int integerBreak(int n) {
		if (n == 2)	return 1;
		if (n == 3)	return 2;
		vector<int> dp(n + 1, 0);
		dp[1] = 1;
		dp[2] = 2;
		dp[3] = 3;		
		for (int i = 4; i <= n; i++) {
			for (int j = 2; j < i; j++) {
				int k = i - j;
				dp[i] = max(dp[i], dp[j] * dp[k]);
			}
		}
		return dp[n];
	}
};

int main() {
	Solution slt;
	vector<int> rslt;
	rslt.push_back(0);rslt.push_back(0);
	for (int i = 2; i < 13; i++)
		rslt.push_back(slt.integerBreak(24));
	return 0;
}