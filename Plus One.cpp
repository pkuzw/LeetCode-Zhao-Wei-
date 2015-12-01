///@file	Plus One
/*
Given a non-negative number represented as an array of digits, plus one to the number.

The digits are stored such that the most significant digit is at the head of the list.
*/
///@author	zhaowei
///@date	2015.07.08
///@version	1.0

///@date	2015.08.27
///@version	2.0

///@date	2015.12.01
///@version	2.1

#include <iostream>
#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	将保存为整型vector的非负整数加1
	///@param	digits	非负整数
	///@return	返回该整数加1后的和
	///@note	注意进位
	vector<int> plusOne(vector<int>& digits) 
	{
		bool flg = false;	//	标记是否需要进位
		digits.back() += 1;
		if (digits.back() == 10)
		{
			flg = true;
			digits.back() = 0;
		}

		for (int i = digits.size()-2; i >= 0; i--)
		{
			if (flg)
			{
				digits[i]++;
				if (digits[i] == 10)
				{
					digits[i] = 0;					
				}
				else	
					flg = false;
			}			
		}

		vector<int> rslt;
		if (flg) rslt.push_back(1);	//	如果和比原来的整数多了一位，则需要把1提前加入结果
		for (int i = 0; i != digits.size(); i++)
		{
			rslt.push_back(digits[i]);
		}
		return rslt;
	}
};

class Solution_v2 {
public:
	///@brief	将整数存储在一维数组当中，将其末位加1后，计算所得结果
	///@param	digits	被加数
	///@return	返回加1后的和
	///@note	1. 从末位向前遍历；2. 设置一个标识符标记进位；3. 如果最高位也需要进位，则要在最前端插入1；4. 时间复杂度为O(n)，空间复杂度为O(1)，其中n为数字的长度。
	vector<int> plusOne(vector<int>& digits) {
		bool flg = false;
		digits.back()++;
		if (digits.back() == 10)
		{
			digits.back() = 0;
			flg = true;				 
		}
		for (int i = digits.size() - 2; i >= 0; i--)
		{			
			digits[i] = flg ? digits[i] + 1 : digits[i];
			if (digits[i] == 10)
			{
				digits[i] = 0;
				flg = true;
			}
			else	flg = false;			
		}
		if (flg)	digits.insert(digits.begin(), 1);
		return digits;
	}
};

class Solution {
public:
	///@brief	将整数存储在一维数组当中，将其末位加1后，计算所得结果
	///@param	digits	被加数
	///@return	返回加1后的和
	///@note	1. 从末位向前遍历；2. 设置一个标识符标记进位；3. 如果最高位也需要进位，则要在最前端插入1；4. 时间复杂度为O(n)，空间复杂度为O(1)，其中n为数字的长度。
	vector<int> plusOne(vector<int>& digits) {
		if (digits.empty()) {
			vector<int> rslt(1, 0);
			return rslt;
		}
		bool flg = false;
		digits.back()++;
		if (digits.back() == 10) {
			digits.back() = 0;
			flg = true;
		}
		for (int i = digits.size() - 2; i >= 0; i--) {
			if (flg) {
				digits[i]++;
				flg = false;
				if (digits[i] == 10) {
					digits[i] = 0;
					flg = true;
				}
			}
		}
		if (flg) digits.insert(digits.begin(), 1);
		return digits;
	}
};

int main()
{
	vector<int> sum;
	vector<int> digits;
	digits.push_back(9);
	digits.push_back(9);
	digits.push_back(8);

	for (int i = 0; i != digits.size(); i++)
	{
		cout << digits[i];
	}
	cout << endl;

	Solution slt;
	sum = slt.plusOne(digits);
	for (int i = 0; i != sum.size(); i++)
	{
		cout << sum[i];
	}
	cout << endl;
	return 0;
}