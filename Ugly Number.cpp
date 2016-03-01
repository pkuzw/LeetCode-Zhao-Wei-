///@file	Ugly Number
///@author	zhaowei
///@date	2016.01.30
///@version	1.0

///@date	2016.03.01
///@version	1.1

#include <vector>
using namespace std;

class Solution_v1 {
public:
	///@brief	判断一个正整数是否为丑数。丑数的定义为一个正整数的因子只能为2，3，5。
	///@param	num	正整数
	///@return	返回一个正整数是否为丑数
	///@note	1. 递归；
	//			2. 当num能被2，3，5整除且其商亦能被上述3数整除时，直至商为1时，返回true；
	//			3. 注意排除掉非正数的情形。
	bool isUgly(int num) {
		if (num <= 0)	return false;
		if (num == 1)	return true;
		return (!(num % 2) && isUgly(num / 2))
			|| (!(num % 3) && isUgly(num / 3))
			|| (!(num % 5) && isUgly(num / 5));
	}
};

class Solution {
public:
	bool isUgly(int num) {
		if (num <= 0)	return false;
		return num == 1 || (!(num % 2) && isUgly(num / 2)) || (!(num % 3) && isUgly(num / 3)) || (!(num % 5) && isUgly(num / 5));
	}
};

int main() {
	Solution slt;
	bool rslt = slt.isUgly(0);
	return 0;
}