///@file	Power of Three
///@author	zhaowei
///@date	2016.03.25
///@version	1.0

#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
	///@brief	判断一个整数是否是3的幂
	///@param	n	正整数
	///@return	如果是则返回true；否则返回false
	///@note	1. 不得使用任何递归或者循环；
	//			2. 哈希表，当待判断数能被3模且除以3后剩下的商属于哈希表中的3的幂，则待判断数是3的幂。
	//			3. 为了省事，我用循环初始化了哈希表。
	bool isPowerOfThree(int n) {
		unordered_map<int, int> hash_tbl;
		int k = 1;
		for (int i = 0; k < INT_MAX && k > 0 ; i++) {	//	当正整数越界时会变为负数，注意限制。
			hash_tbl[k] = i;
			k *= 3;
		}
		return n == 1 || (n % 3 == 0 && (hash_tbl.find(n / 3) != hash_tbl.end()));
	}
};

int main() {
	int n = 0;
	Solution slt;
	bool rslt = slt.isPowerOfThree(n);
	return 0;
}