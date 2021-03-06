﻿///@file	Multiply Strings
/*
			Given two numbers represented as strings, return multiplication of the numbers as a string.

			Note: The numbers can be arbitrarily large and are non-negative.
*/
///@author	zhaowei
///@date	2015.06.20
///@version	1.0

///@date    2015.09.04
///@version 2.0

///@date	2015.09.24
///@version	2.1

///@date	2016.04.11
///@version	2.2

///@date    October 18, 2018
///@version 2.3

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution_v1 {
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

class Solution_v2 {
public:
	///@brief	大整数相乘
	///@param	num1	乘数1
	///@param	num2	乘数2
	///@return	返回用字符串表示的积
	///@note	对乘数的各位分别相乘，需要开辟一个长度为n1 + n2的整型数组（假设乘数1的长度为n1，乘数2的位数为n2）来保存各位的积。然后对各个位的进位进行计算，最后再截取积首部的多余
	//			零，将它转换为字符串即可。需要注意结果数组的存放是高位存放在末尾而不是首部。类似于网络数据的小尾方式。时间复杂度为O(n1 * n2)，空间复杂度为O(n1 + n2)。
    string multiply(string num1, string num2) {
		int n1 = num1.size(), n2 = num2.size();
		int k = n1 + n2 - 2;
		vector<int> mult(n1 + n2, 0);
		for (int i = 0; i != n1; i++) 	//	注意：与手算不同的是，我们从高位向低位逐个相乘
			for (int j = 0; j != n2; j++) 
				mult[k - i - j] += (num1[i] - '0') * (num2[j] - '0');	//	我们的结果数组中，高位存放在末尾，而非开头
		int carry = 0;
		for (int i = 0; i != n1 + n2; i++) {	//	从结果的低位向高位计算进位
			mult[i] += carry;
			carry = mult[i] / 10;
			mult[i] %= 10;
		}
		int l = n1 + n2 - 1;	
		while (l >= 0 && !mult[l])	l--;		//	消除积首部多余0
		if (l < 0)	return "0";
		string rslt;
		while (l >= 0) {
			rslt += mult[l--] + '0';
		}
		return rslt;
    }
};

class Solution {
public:
    ///@brief   计算两个由字符串表示的大整数的乘法
    ///@param   nums1   乘数1
    ///@param   nums2   乘数2
    ///@return  返回由字符串表示的积
    ///@note    1. 枚举法。
    //          2. 设nums1和nums2的长度为len1和len2，设置一个长度为len1 + len2的整型数组变量来保存nums1 * nums2的结果；
    //          3. 在逐位累加时注意进位；在将整型数组转换成字符串时注意舍弃前缀的先导零。
    //          4. 时间复杂度为O(n*m），空间复杂度为O(n)，其中n和m分别是两个乘数的位数。
	string multiply(string num1, string num2) {
        int len1 = num1.length(), len2 = num2.length();
        vector<int> product(len1+len2, 0);
        for (int i = 0; i < len1; i++) {
            for (int j = 0; j < len2; j++) {
                product[len1 + len2 - 2 - i -j] += (num1[i] - '0') * (num2[j] - '0');
            }
        }
        int carry = 0;
        for (int i = 0; i < len1 + len2; i++) {
            product[i] += carry;
            carry = product[i] / 10;
            product[i] %= 10;
        }
        int k = len1 + len2 - 1;
        while (k >= 0 && product[k] == 0) k--;
        if (k < 0)  return "0";
        string rslt;
        while (k >= 0)
            rslt += product[k--] + '0';
        return rslt;
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
