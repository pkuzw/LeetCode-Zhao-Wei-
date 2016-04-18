///@file	Power of Four
///@author	zhaowei
///@date	2016.04.18
///@version	1.0

#include <vector>
#include <set>
using namespace std;

class Solution {
public:
	///@brief	判断一个32位带符号整型变量是否是4的倍数
	///@param	num	整型变量
	///@return	如果是，返回true；否则返回false
	///@note	1. 枚举
	//			2. 先计算出所有的在整型表示范围内的4的幂；
	//			3. 如果被检测的数是这些幂中的一个，则返回true，否则返回false；
	//			4. 时间复杂度为O(logn)，空间复杂度为O(logn)，其中n为待检测数目的大小。
	bool isPowerOfFour(int num) {
		int k = 1;
		set<int> candidates;
		while (k <= INT_MAX && k > 0) {
			candidates.insert(k);
			k *= 4;
		}
		return !(candidates.find(num) == candidates.end());
	}
};

int main() {
	Solution slt;
	int num = 16;
	bool rslt = slt.isPowerOfFour(num);
	return 0;
}