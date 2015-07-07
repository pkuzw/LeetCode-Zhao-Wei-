///@file	Length of Last Word
/*
Given a string s consists of upper/lower-case alphabets and empty space characters ' ', 
return the length of last word in the string.

If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space characters only.

For example, 
Given s = "Hello World",
return 5.
*/
///@author	zhaowei
///@date	2015.07.07
///@version	1.0

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	///@brief	给定一个字符串，包含大小写字母和' '字符，计算最后一个单词的长度
	///@param	s	字符串
	///@return	返回最后一个单词的长度
	///@note	从后向前进行遍历，找到最后一个单词，计算其连续的非空格字符长度。时间复杂度为O(n)，空间复杂度为O(1)。
	int lengthOfLastWord(string s)
	{
		bool flg = false;	//	用于标记是否为第一个单词
		int cnt = 0;	//	统计最后一个单词的长度
		for (int i = s.length()-1; i >= 0; i--)
		{
			if (s[i] == ' ' && !flg) continue;

			else if (s[i] == ' ' && flg) break;
			
			else if (s[i] != ' ')
			{
				cnt++;
				flg = true;
			}
		}
		return cnt;
	}
};

int main()
{
	string str;
	getline(cin, str);

	Solution slt;
	cout << slt.lengthOfLastWord(str) << endl;;
	return 0;
}