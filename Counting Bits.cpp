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
		while(n < INT_MAX && n >= 0) {
			binary_flg.push_back(n);
			n *= 2;
		}

		vector<int> rslt(num+1, 0);

		for (int j = 1; binary_flg[j-1] <= num; j++) {
			for (int k = 0; k < binary_flg[j] - binary_flg[j-1]; k++) {
				if (binary_flg[j-1] + k <= num)
					rslt[binary_flg[j-1]+k] = rslt[k] + 1;
				else
					return rslt;
			}
		}
		return rslt;
	}
};

int main() {
	return 0;
}