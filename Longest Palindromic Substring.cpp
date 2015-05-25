///@file	Given a string S, find the longest palindromic substring in S. 
///			You may assume that the maximum length of S is 1000, and there exists one unique longest palindromic substring.
///@author	zhaowei
///@date	2015.05.25
///@version 1.0
///@note	最简单的方法就是O(n^2)的复杂度枚举所有子串，然后再验证每一个子串是否是回文字符串（O(n)），总计O(n^3)，会超时。
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
	///@brief	枚举法
	///@param	s	待处理的字符串
	///@return  返回最长回文字符串
	///@author	zhaowei
	///@date	2015.05.25
	///@note	时间复杂度O(n^3)，空间复杂度O(n)
	string longestPalindrome_BruteForce(string s) {
		int pstr_head = 0;	//最大回文序列的首字符坐标
		int pstr_len = 1;	//最大回文序列的长度
		string pstr;
		for (int i = 0; i < s.length(); i++)	//枚举
		{
			int l = i;
			int count = 0;						//计算回文序列的长度
			int k = 1;							//用于标记第二层循环的字符串末尾字符
			for (int j = s.length() - 1; j >= i-1 && j >= 0; j--)
			{				
				if (s[l] == s[j] && l != j && l != j+1)	//i != j是回文字符串为奇数长度的情形；i == j+!是回文序列为偶数长度的情形
				{
					l++;
					count++;
					continue;
				}
				else
				{
					if (j - l == 0)				//回文字符串为奇数长度的情形
					{
						if (pstr_len < count*2 + 1)
						{
							pstr_head = i;
							pstr_len = count * 2 + 1;
							break;
						}
					}
					else if (l == j+1)			//回文字符串为偶数长度的情形
					{
						if (pstr_len < count*2)
						{
							pstr_head = i;
							pstr_len = count * 2;
							break;
						}
					}
					else						//如果枚举的子字符串不是回文字符串，重置末尾字符和起始字符
					{						
						j = s.length() - k;
						k++;
						l = i;
						count = 0;
					}
				}
			}
		}
		/*
		char buff[1000] = "";
		s.copy(buff, pstr_len, pstr_head);		//通过string自带的copy函数将回文字符串拷贝到字符串数组
		pstr = buff;
		return pstr;
		*/
		return s.substr(pstr_head, pstr_len);	//或者使用substring函数也可以，这样更简洁
	}

	///@brief	动态规划法
	///@param	s	待处理字符串
	///@return	返回最长回文子串
	///@note	时间复杂度O(n^2)，空间复杂度O(n^2)
	///			考虑到"a"和"aa"就是最简单的回文子串，如果存在子串P[i, j]是回文子串且S[i-1] = S[j+1]，则P[i-1, j+1]也是回文子串
	string longestPalindrome_DP(string s)
	{
		int pstr_head = 0;	//回文子串的起始下标
		int pstr_len = 1;	//回文子串的长度
		bool table[1000][1000] = {false};	//用于记录回文子串的首末位置


		for (int i = 0; i < s.length(); i++)	//处理基本情况1：只有1个字符的子串一定是回文子串
		{
			table[i][i] = true;
		}

		for (int i = 0; i < s.length()-1; i++)	//处理基本情况2：2个重复字符的子串一定是回文子串
		{			
			if (s[i] == s[i+1])
			{
				table[i][i+1] = true;
				pstr_head = i;
				pstr_len = 2;
			}
		}

		for (int len = 3; len <= s.length(); len++)	//开始处理3个字符以上的情形
		{
			for (int i = 0; i < s.length()-len+1; i++)	//i是子串的首字符
			{
				int j = i + len - 1;		//j是子串的末尾字符
				if (table[i+1][j-1] && s[i] == s[j])		//如果P[i+1, j-1]是回文子串且S[i] = S[j]，则P[i, j]也是回文子串
				{
					table[i][j] = true;
					pstr_head = i;
					pstr_len = len;
				}
			}
		}
		return s.substr(pstr_head, pstr_len);	//返回计算结果
	}
};

int main()
{
	Solution slt;
	string s = "abbaaaaa";
	string pstr_bf = slt.longestPalindrome_BruteForce(s);
	string pstr_dp = slt.longestPalindrome_DP(s);
	cout << pstr_bf << endl;
	cout << pstr_dp;
	cout << endl;
	return 0;
};