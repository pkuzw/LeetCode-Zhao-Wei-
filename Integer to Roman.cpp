///@brief	Integer to Roman
///@author  zhaowei
///@date	2015.06.03
///@version 1.0

#include <string>
#include <iostream>
using namespace std;

class Solution
{
public:
	///@brief	整数转换成罗马字符
	///@param	num	待处理的整型变量
	///@return	返回转换后的罗马字符
	///@author	zhaowei
	///@date	2015.06.03
	///@note	逐位处理，每一位分成4种情况，<4, 4, 5-8, 9
	string intToRoman(int num) {

		string roman_elmnt[7] = {"I", "V", "X", "L", "C", "D", "M"};
		string roman_less[6] = {"IV", "IX", "XL", "XC", "CD", "CM"};


		int roman_bit[4] = {0};
		int num_bit[4] = {1000, 100, 10, 1};

		// 计算int型变量的各个位数
		for (int i = 0; i < 4; i++)
		{
			roman_bit[i] = num/num_bit[i];
			roman_bit[i] %= num_bit[2];
		}

		string rslt;	// 返回的字符串
		
		// 因为int型变量的千位不会有特殊字符，故先处理之。
		for (int j = 0; j < roman_bit[0]; j++)
		{
			rslt += roman_elmnt[6];
		}

		// 逐个处理百位、十位和个位
		// 分成4段，1-4，4，5-8，9 来对每一位进行转换
		for (int i = 1; i < 4; i++)
		{
			if (roman_bit[i] < 4)
			{
				for (int j = 0; j < roman_bit[i]; j++)
				{
					rslt += roman_elmnt[4-(i-1)*2];
				}
			}
			else if (roman_bit[i] == 4)
			{
				rslt += roman_less[4-(i-1)*2];
			}
			else if (roman_bit[i] >= 5 && roman_bit[i] < 9)
			{
				rslt += roman_elmnt[5-(i-1)*2];
				for (int j = 0; j < roman_bit[i]-5; j++)
				{
					rslt += roman_elmnt[4-(i-1)*2];
				}
			}
			else if (roman_bit[i] == 9)
			{
				rslt += roman_less[5-(i-1)*2];
			}
		}
	
		return rslt;		
	}
};

int main()
{
	Solution slt;

	int num = 10;
	while (cin >> num)
	{
		cout << slt.intToRoman(num) << endl;
	}
	

	return 0;
}