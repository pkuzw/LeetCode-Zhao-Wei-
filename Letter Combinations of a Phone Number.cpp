///@brief	Letter Combinations of a Phone Number 
/*			Given a digit string, return all possible letter combinations that the number could represent.

			A mapping of digit to letters (just like on the telephone buttons) is given below.

			Input:Digit string "23"

			Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

			Although the above answer is in lexicographical order, your answer could be in any order you want.
*/
///@author  zhaowei
///@date	2015.06.05
///@version	1.0
///@note	暴力枚举，提交后报Memory Limit Exceed

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
	///@brief	将电话键盘上的数字转换成字母
	///@param	digits	待输入的数字字符串
	///@return	输出所有字母组合
	///@author	zhaowei
	///@date	2015.06.08
	vector<string> letterCombinations(string digits) {

		vector<string> digitToChar;	//	记录所有字母组合
		string str[10] = {" ", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};	//	记录下数字键对应的符号
		int d_len = digits.length();
		int *d_cnt = new int[d_len];	//	新建长度为输入字符串长的动态int型数组，里面保存每一位数字的循环变量
		for (int i = 0; i < d_len; i++)	//	初始化为0
			d_cnt[i] = 0;

		int lmt[10] = {1, 1, 3, 3, 3, 3, 3, 4, 3, 4};	//	每个数字对应的字符种类
		bool flg = false;		//	判断输出结束的标记
		while (1)
		{ 			
			if (flg)
			{
				break;
			}

			string s;
			for (int i = 0; i < d_len; i++)
			{
				int indx = int(digits[i] - '0');		//	将字符表示的数字转换成int型变量
				s += str[indx][d_cnt[i]];

				if ((i < d_len-1 && d_cnt[i+1] == lmt[indx+1])	//	当下标为最后一位数字或者后一位已经满位，才能自增1
					|| (i == d_len-1))
				{
					d_cnt[i]++;
					if (d_cnt[i] == lmt[indx])	//	进位
					{
						d_cnt[i] = 0;
						int j = i-1;
						if (j < 0)
						{
							flg = true;
							break;
						}
						d_cnt[j]++;						
						while (d_cnt[j] == lmt[(int)(digits[j]-'0')])	//	从后向前逐位进位
						{
							if (j == 0)	//	遍历完了所有的可能
							{
								flg = true;	
								break;
							}
							d_cnt[j] = 0;
							j--;
							d_cnt[j]++;
						}						
					}					
				}				
			}
			digitToChar.push_back(s);
		}	
		delete []d_cnt;
		return digitToChar;
	}
};

int main()
{
	string s = "2334";	
	Solution slt;
	vector<string> rslt = slt.letterCombinations(s);
	for (int i = 0; i < rslt.size(); i++)
	{
		cout << rslt[i] << ' ';
	}
	cout << endl;

	return 0;
}