///@file	Multiply Strings
/*
			Given two numbers represented as strings, return multiplication of the numbers as a string.

			Note: The numbers can be arbitrarily large and are non-negative.
*/
///@author	zhaowei
///@date	2015.06.20
///@version	1.0

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
	///@brief	计算两个由string表示的正整数乘积
	///@param	num1	因子1
	///@param	num2	因子2
	///@return	返回两个大整数的积
	///@note	先计算一位整数与大整数相乘的结果，然后再计算逐位计算的结果的和。就可以得到大整数相乘的积。默认num1长于num2，否则将二者交换。
	///			时间复杂度为O(n^2)，空间复杂度为O(n)
	///@author	zhaowei
	///@date	2015.06.20
	string multiply(string num1, string num2) 
	{
		num1 = trim(num1);	//	清除前缀0
		num2 = trim(num2);
		if (num1.size() < num2.size())
		{
			swap(num1, num2);
		}
		string rslt;
		for (int i = num2.size()-1; i >= 0; i--)
		{
			int num2_integer = (int)(num2[i]-'0');
			string tmp_rslt = multiply2(num1, num2_integer);

			//	string类型的一种初始化方法就是string s(size_t num, char ch)；
			string suffix(num2.size()-1-i, '0');		//	每一次乘法操作后结果的后缀	
			tmp_rslt += suffix;
			rslt = add(tmp_rslt, rslt);
		}
		return rslt;
	}

private:
	///@brief	计算一个string类型表示的大整数和1个1位整数相乘
	///@param	num1	大整数1
	///@param	num2	一位整数2
	///@return	返回两者的积
	string multiply2(string num1, int num2)
	{
		string rslt;
		int advance = 0;	//	记录进位
		for (int i = num1.size()-1; i >= 0; i--)
		{
			int bit = (int)(num1[i]-'0')*num2;
			bit += advance;		//	处理进位
			advance = bit/10;
			bit %= 10;			//	处理本位
			
			rslt = (char)(bit+'0') + rslt;
		}
		if (advance != 0)
		{
			rslt = (char)(advance+'0') + rslt;
		}

		rslt = trim(rslt);
		return rslt;
	}
	
	///@brief	计算两个字符串string类型表示的大整数的和
	///@param	num1	加数1
	///@param	num2	加数2
	///@return	返回两者之和
	///@note	默认num1比num2长，否则将两个加数交换	
	string add(string num1, string num2)
	{
		if (num2.empty() || num2 == "0")
		{
			return num1;
		}
		int len1 = num1.size(), len2 = num2.size();
		if (len1 < len2)
		{
			swap(num1, num2);
			len1 = num1.size();
			len2 = num2.size();
		}
		int interval = len1-len2;
		string rslt;
		bool advance = false;	//	标记是否需要进位，默认为false
		for (int i = len2-1; i >= 0; i--)
		{			
			//	一位的和
			int bit = (int)(num1[i+interval]-'0')+(int)(num2[i]-'0');
			
			if (advance)	//	进位
			{
				bit++;
			}
			if (bit >= 10)
			{
				advance = true;
				bit -= 10;
			}
			else
			{
				advance = false;
			}
			rslt = (char)(bit+'0') + rslt;			
		}
		string num1_sub;	//	计算num1比num2长出来的部分
		if (advance)	//	处理进位
		{
			num1_sub = add(num1.substr(0, interval), "1");
		}
		else
		{
			num1_sub = num1.substr(0, interval);
		}
		rslt = num1_sub + rslt;

		rslt = trim(rslt);
		return rslt;
	}

	///@brief	清除字符串中的前缀0
	///@param	s	字符串
	///@return	清除前缀0后的字符串	
	string trim(string s)
	{
		int i = 0;
		while (s[i] == '0' && i != s.size()-1)
		{
			i++;
		}
		return s.substr(i, s.size()-i);
	}
};

int main()
{
	string a, b;
	Solution slt;
	while (cin >> a >> b)
	{
		cout << slt.multiply(a, b) << endl;
	}
	return 0;
}