///@file	Plus One
/*
Given a non-negative number represented as an array of digits, plus one to the number.

The digits are stored such that the most significant digit is at the head of the list.
*/
///@author	zhaowei
///@date	2015.07.08
///@version

#include <iostream>
#include <vector>

using namespace std;

class Solution {
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