///@file	Add Digits
///@author	zhaowei
///@date	2016.01.29
///@version	1.0
//	在不用任何循环或递归的条件下，如何做到O(1)的时间复杂度为？

#include <vector>
using namespace std;

class Solution {
public:
	///@brief	将非负整型数的各位相加，直到该数字只有1位为止
	///@param	num	整型数
	///@return	返回迭代后只有1位的整型数
	///@note	1. 迭代；
	//			2. 先将整型数的各位拆分出来，然后求和，直至只剩1位为止；
	//			3. 时间复杂度为O(n)，空间复杂度为O(n)，其中n为整型数的位数。
	int addDigits(int num) {
		while (num >= 10) {
			vector<int> digits = decompose(num);
			num = compose(digits);
		}
		return num;
	}

	///@brief	将整型数的各位取出
	///@param	num	整型数
	///@return	返回整型数各位组成的数组
	vector<int> decompose(int num) {
		vector<int> digits;
		while (num) {
			digits.push_back(num % 10);
			num /= 10;
		}
		return digits;
	}

	///@brief	将数组中的各位求和
	///@param	digits	组成整型数的各位
	///@return	返回整型数
	int compose(const vector<int>& digits) {
		int num = 0;
		for (int i = 0; i != digits.size(); i++)	num += digits[i];
		return num;
	}
};

int main() {
	int num = 38;
	Solution slt;
	int rslt = slt.addDigits(num);
	return 0;
}