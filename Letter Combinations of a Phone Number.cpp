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

///@date	2015.06.08
///@version 2.0
///@note	将所有的字母组合看做一棵树，树的每一个非叶节点就是一个原先的数字，每一条边相当于上层节点对应的字母，利用深度优先遍历即可

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
	vector<string> letterCombinations_mle(string digits) {

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

	vector<string> keyBoard;	//	数字和字母的对应

	///@brief	递归法将键盘上的数字转换成字母
	///@param	digits	待输入的数字字符串
	///@return	输出所有字母组合
	///@note	将所有的字母组合看做一棵树，树的每一个非叶节点就是一个原先的数字，每一条边相当于上层节点对应的字母，利用深度优先遍历即可
	vector<string> letterCombinations(string digits)
	{
		//	初始化
		keyBoard.push_back(" ");
		keyBoard.push_back("");
		keyBoard.push_back("abc");
		keyBoard.push_back("def");
		keyBoard.push_back("ghi");
		keyBoard.push_back("jkl");
		keyBoard.push_back("mno");
		keyBoard.push_back("pqrs");
		keyBoard.push_back("tuv");
		keyBoard.push_back("wxyz");
		vector<string> rslt;
		if (digits.empty())
		{
			return rslt;
		}
		dfs_tree(digits, 0, "", rslt);
		return rslt;
	}

	///@brief	深度优先遍历树
	///@param	digits	数字字符串
	///@param	cur		字符串的遍历下标
	///@param	path	节点下可能的边
	///@param	rslt	所有可能的字符串组成的数组	
	void dfs_tree(const string& digits, size_t cur, string path, vector<string>& rslt)
	{
		if (cur == digits.size())	//	如果遍历完成，将path压入结果数组
		{
			rslt.push_back(path);
			return;
		}
		for (int i = 0; i != keyBoard[digits[cur]-'0'].length(); i++)
		{
			char c = keyBoard[digits[cur]-'0'][i];
			dfs_tree(digits, cur+1, path+c, rslt);	//	递归遍历
		}
	}
};

int main()
{
	string s = "23";	
	Solution slt;
	vector<string> rslt = slt.letterCombinations(s);
	for (int i = 0; i != rslt.size(); i++)
	{
		cout << rslt[i] << ' ';
	}
	cout << endl;

	return 0;
}