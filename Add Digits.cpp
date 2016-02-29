///@file	Add Digits
///@author	zhaowei
///@date	2016.01.29
///@version	1.0

///@date	2016.02.29
///@version	2.0
//	在不用任何循环或递归的条件下，如何做到O(1)的时间复杂度为？

#include <vector>
using namespace std;

class Solution_v1 {
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

class Solution {
public:
	///@brief	将一个正整数各位相加，直到和为一个个位数为止。要求不使用循环或递归，时间复杂度为O(1)。
	///@param	num	正整数
	///@return	返回一个个位的正整数
	///@note	1. 对于num来说，可以看做是 num = 1 * a[0] + 10 * a[1] + 100 * a[2] + ... + 10^k * a[k]，而待求的结果值应该是
	//			sum = a[0] + a[1] + a[2] + ... + a[k]；又因为10^k % 9 = 1，故num % 9 = sum。又因为当num % 9 == 0时，结果应该是9，
	//			而不是0，所以可以将num % 9改进成(num - 1) % 9 + 1即可。
	int addDigits(int num) {
		return (num - 1) % 9 + 1;
	}
};

int main() {
	int num = 38;
	Solution slt;
	int rslt = slt.addDigits(num);
	return 0;
}