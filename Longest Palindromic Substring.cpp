///@file	Given a string S, find the longest palindromic substring in S. 
///			You may assume that the maximum length of S is 1000, and there exists one unique longest palindromic substring.
///@author	zhaowei
///@date	2015.05.25
///@version 1.0
///@note	最简单的方法就是O(n^2)的复杂度枚举所有子序列，会超时。
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
	string longestPalindrome(string s) {
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
		char buff[1000] = "";
		s.copy(buff, pstr_len, pstr_head);		//通过string自带的copy函数将回文字符串拷贝到字符串数组
		pstr = buff;
		return pstr;
	}
};

int main()
{
	Solution slt;
	string s = "aabbaacccc";
	string pstr = slt.longestPalindrome(s);
	cout << pstr;
	cout << endl;
	return 0;
};