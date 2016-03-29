///@file	Counting Bits
///@author	zhaowei
///@date	2016.03.29
///@version	1.0

#include <vector>
using namespace std;

class Solution {
public:
	///@brief	计算从0到num的整数二进制表示的1的数目
	///@param	num	自然数
	///@return	返回从0到num的整数二进制表示的1的数目
	///@note	1. 通过观察发现，从2^(k-1)+1到2^k的二进制整数的1数目是从0到2^(k-1)的1数目加1
	//			2. 时间复杂度为O(n)，空间复杂度为O(n)。one-pass搞定。
	vector<int> countBits(int num) {
		vector<int> binary_flg;
		int n = 1;
		for (int i = 0; n < INT_MAX && n >= 0; i++) {
			n <<= i;
			binary_flg.push_back(n);
		}

		vector<int> rslt(num, 0);
		int i = 0;
		while (i < num) {

		}
	}
};

int main() {
	return 0;
}