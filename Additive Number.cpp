///@file	Additive Number
///@author	zhaowei
///@date	2016.03.17
///@version	1.0

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
	///@brief	判断一个字符串能否划分成加法串
	///@param	num	字符串
	///@return	如果可以则返回true；否则返回false
	///@note	1. 递归；
	//			2. 第一个数字的长度不可能超过总长度的一半，因为要给第三个数留空间；
	//			3. 第二个数的长度应该保证在刨掉第一个数和第二个数的长度后，第三个数的长度比前两个数的最长长度长；
	bool isAdditiveNumber(string num) {
		for (int i = 1; i <= num.size() / 2; i++)
			for (int j = 1; j <= (num.size() - i) / 2; j++)
				if (check(num.substr(0, i), num.substr(i, j), num.substr(i+j)))	return true;;
		return false;
	}

	///@brief	计算两个字符串之和
	///@param	num1	加数1
	///@param	num2	加数2
	///@return	返回num1 + num2的结果
	string add(string num1, string num2) {
		return to_string(static_cast<long long>(stoll(num1) + stoll(num2)));
	}

	///@brief	检查三个字符子串是否满足加法关系
	///@param	num1	加数1
	///@param	num2	加数2
	///@param	num		待检查的和
	///@return	如果两个加数之和为num，则返回true，否则返回false
	bool check(string num1, string num2, string num) {
		if ((num1.size() > 1 && num1[0] == '0') || (num2.size() > 1 && num2[0] == '0'))	return false;
		string sum = add(num1, num2);
		if (sum == num)	return true;
		else if (sum.size() >= num.size() || num.substr(0, sum.size()) != sum)	return false;
		else	return check(num2, sum, num.substr(sum.size()));
	}
};

int main() {
	string a= "apple";
	string b = "apple";
	string num = "211738";
	Solution slt;
	bool rslt = slt.isAdditiveNumber(num);
	return 0;
}