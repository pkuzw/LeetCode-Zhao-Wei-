///@file	Paint Fence
///@author	zhaowei
///@date	2016.03.01
///@version	1.0

#include <cmath>
#include <vector>
using namespace std;

class Solution {
public:
	///@brief	有n个柱子和k种颜色，要求给柱子刷漆，最多有两个相邻柱子的颜色相同，计算有多少种方法
	///@param	n	柱子数目
	///@param	k	颜色数目
	///@return	返回刷漆的方法数
	///@note	1. 动态规划；
	//			2. 设same表示当前柱子和前一个柱子刷一样颜色的方法数，diff表示当前柱子和前一个柱子刷不一样漆的方法数；
	//			3. 递推关系式为same = diff * 1；diff = same*(k-1) + diff * (k-1) = (same + diff) * (k-1)；
	//			4. 时间复杂度为O(n)，空间复杂度为O(1)。
	//			5. 详解见https://leetcode.com/discuss/71756/explanation-of-dp-o-n-time-complexity-o-1-space-complexity
	int numWays(int n, int k) {
		if (n == 0)	return 0;
		if (n == 1)	return k;
		if (n == 2)	return k * k;
		int same = k, diff = k*(k-1);
		for (int i = 3; i <= n; i++) {
			int same1 = diff;
			int diff1 = (same + diff) * (k - 1);
			same = same1;
			diff = diff1;
		}
		return same + diff;
	}
};

int main() {
	int n[5] = {1, 2, 3, 4, 5};
	vector<int> rslt;
	Solution slt;
	for (int i = 0; i != 5; i++)	rslt.push_back(slt.numWays(n[i], 3));
	return 0;
}