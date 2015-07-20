///@file	Gray Code
/*
The gray code is a binary numeral system where two successive values differ in only one bit.

Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.

For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:

00 - 0
01 - 1
11 - 3
10 - 2
Note:
For a given n, a gray code sequence is not uniquely defined.

For example, [0,2,3,1] is also a valid gray code sequence according to the above definition.

For now, the judge is able to judge based on one instance of gray code sequence. Sorry about that.
*/
///@author	zhaowei
///@date	2015.07.20
///@version	1.3

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	///@brief	计算0到n的格雷码数组。格雷码数组的定义是二进制表示的整数数组，其第一个数是0，后面的任意连续两个数互相之间只相差一个bit位。
	///@param	n	格雷码的位数
	///@param	tmp	标记除了最高位之外其余部分是否逆序输出
	///@return	返回格雷码数组
	/* @note	观察OJ给出的样例，
				n = 2: 00 = 0, 01 = 1, 11 = 3, 10 = 2；
				n = 3: 000 = 0, 001 = 1, 011 = 3, 010 = 2, 110 = 6, 111 = 7, 101 = 5, 100 = 4
				通过观察发现，第i位（i = 1..n，从左往右数）的重复周期是2^(i+1)，每个周期中以i个0+i个1+i个1+i个0的方式交替出现。
				通过枚举，给出所有格雷码序列，然后再将二进制整数转换为十进制即可。时间复杂度为O(n*2^n)，空间复杂度为O(n*2^n)。				
	*/			
	vector<int> grayCode(int n) {
		binary_gray_codes.clear();		
		vector<int> binary_gcode;	//	存储一个二进制格雷码
		for (int i = 0; i != n; i++)
			binary_gcode.push_back(0);

		int k = 1;
		k <<= n;	//	格雷码数组大小
		for (int i = 0; i != k; i++)
			binary_gray_codes.push_back(binary_gcode);	//	初始化binary_gray_codes
		

		for (int i = 0; i != k; i++)
		{
			for (int j = 0; j != n; j++)
			{
				int period = 1;	// 每一列01串出现的周期长度
				period <<= j + 2;
				int bit = i % period;	//	计算[i][j]应该位于周期中的哪一位
				int seg_len = period / 4;	//	周期的四分之一长，前四分之一和后四分之一为0，中间的二分之一为1
				int seg_num = bit / seg_len;	//	计算[i][j]位于周期中的第几部分

				binary_gray_codes[i][j] = (seg_num == 1 || seg_num == 2) ? 1 : 0;
			}
		}		

		vector<int> rslt;
		for (int i = 0; i != binary_gray_codes.size(); i++)
		{
			rslt.push_back(convertBinaryToDecimal(binary_gray_codes[i]));	//	转换为十进制
		}
		return rslt;
	}
	
private:
	///@brief	将二进制数转换成十进制数
	///@param	binary_num	二进制数
	///@return	返回二进制数表示的十进制数
	int convertBinaryToDecimal(vector<int> &binary_num)
	{
		int dec_num = 0;
		for (int i = 0; i != binary_num.size(); i++)
		{
			int k = binary_num[i];
			k <<= i;
			dec_num += k;
		}
		return dec_num;
	}

	vector<vector<int>> binary_gray_codes;	//	二进制格雷码序列
};

int main()
{
	int n = 0;
	Solution slt;

	cout << "input n: ";
	while (cin >> n)
	{
		vector<int> rslt = slt.grayCode(n);

		for (int i = 0; i != rslt.size(); i++)
		{
			cout << rslt[i] << ' ';
		}
		cout << endl;
		cout << "input n: ";
	}
	return 0;
}