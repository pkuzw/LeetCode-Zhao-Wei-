﻿///@brief	Letter Combinations of a Phone Number 
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
///@version 1.1
///@note	将所有的字母组合看做一棵树，树的每一个非叶节点就是一个原先的数字，每一条边相当于上层节点对应的字母，利用深度优先遍历即可

///@date    2015.09.07
///@version 2.0

///@date	2016.04.05
///@version	2.1

///@date    July 12, 2018
///@version 2.2

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution_v1
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

class Solution_v2 {
public:
	///@brief	计算电话号码所有可能的字符组合
	///@param	digits	电话号码，由阿拉伯数字组成
	///@return	返回其所对应的所有字符串
	///@note	递归。利用dfs搜索所有可能的组合。时间复杂度为O(3^n)，空间复杂度为O(n)。
	vector<string> letterCombinations(string digits) {
		vector<string> rslt;
		if (digits.empty())	return rslt;
		vector<string> dict;	//	不处理'0'和'1'
		string htbl[8] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
		for (int i = 0; i != 8; i++)	dict.push_back(htbl[i]);
		string out;
		dfs(rslt, dict, digits, 0, out);
		return rslt;
	}

	void dfs(vector<string>& rslt, vector<string>& dict, string& digits, int indx, string& out) {
		if (indx == digits.size()) {
			rslt.push_back(out);
			return;
		}
		for (int i = 0; i != dict[digits[indx] - '2'].size(); i++) {
			out.push_back(dict[digits[indx] - '2'][i]);
			dfs(rslt, dict, digits, indx + 1, out);
			out.pop_back();
		}
	}
};

class Solution_v2_1 {
public:
	vector<string> letterCombinations(string digits) {
		vector<string> hash_tbl;
		string htbl[8] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
		for (int i = 0; i != 8; i++)	hash_tbl.push_back(htbl[i]);
		vector<string> rslt;
		if (digits.empty())	return rslt;
		string str;
		dfs(rslt, str, digits, 0, hash_tbl);
		return rslt;
	}

	void dfs(vector<string>& rslt, string& str, string& digits, int indx, const vector<string>& hash_tbl) {
		if (indx == digits.size()) {
			rslt.push_back(str);
			return;
		}
		for (int i = 0; i != hash_tbl[digits[indx]-'2'].size(); i++) {
			str += hash_tbl[digits[indx] - '2'][i];
			dfs(rslt, str, digits, indx + 1, hash_tbl);
			str.pop_back();
		}
	}
};

class Solution {
public:
    ///@brief   给定一串由2 - 9组成的数字字符串，每个数字像手机键盘一样对应若干英文字母，求所有可能的对应字母字符串。
    ///@param   digits  数字字符串
    ///@return  返回数字字符串对应的所有可能字母字符串组合。
    ///@note    1. 将数字字符串中的每一个数字所对应的英文字母看作是一棵树的一层，那么一个可能的英文字符串就是从根节点到叶节点的一条路径上的所有节点依次串起来。那么问题就转换成了求解一个森林的所有路径。根据树的深度优先遍历算法求解即可。
    vector<string> letterCombinations(string digits) {
        vector<string> rslt;
        string str = "";
        if (digits.empty()) return rslt;
        string s[8] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> hash_table;
        for (int i = 0; i < 8; i++) hash_table.push_back(s[i]);
        dfs(rslt, str, digits, 0, hash_table);
        return rslt;
    }
    
    
    ///@brief   深度优先遍历树算法
    ///@param   rslt    结果数组，每个元素都是一个可能字母字符串。
    ///@param   str     一个可能的英文字母字符串，初始为空。
    ///@param   digits  数字字符串
    ///@param   index   当前正在遍历的数字字符串的下标
    ///@param   hash_table  数字字符所对应的英文字符表
    ///@note    1. 深度优先遍历的时间复杂度为O(n^m)，空间复杂度为O(n^m)。其中n为数字字符串的长度，m为一个数字所对应的英文字符的平均数目。
    void dfs(vector<string>& rslt, string& str, const string& digits, int index, const vector<string>& hash_table) {
        if (index == digits.size()) {
            rslt.push_back(str);
            return;
        }
        for (int i = 0; i < hash_table[digits[index] - '2'].size(); i++) {
            str += hash_table[digits[index] - '2'][i];
            dfs(rslt, str, digits, index + 1, hash_table);
            str.pop_back();
        }
        return;
    }
};

int main()
{
	string s = "234";	
	Solution slt;
	vector<string> rslt = slt.letterCombinations(s);	

	Solution_v2 s2;
	vector<string> r2 = s2.letterCombinations(s);
	return 0;
}
