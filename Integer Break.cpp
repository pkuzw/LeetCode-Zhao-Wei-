///@file	Integer Break
///@author	zhaowei
///@date	2016.04.20
///@version	1.0
///@version	1.1

#include <vector>
using namespace std;

class Solution_wa {
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

int main() {
	int n = 9;
	Solution slt;
	int rslt = slt.integerBreak(n);
	return 0;
}