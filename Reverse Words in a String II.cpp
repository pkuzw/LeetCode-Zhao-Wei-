///@file	Reverse Words in a String II
/*
Given an input string, reverse the string word by word. A word is defined as a sequence of non-space characters.

The input string does not contain leading or trailing spaces and the words are always separated by a single space.

For example,
Given s = "the sky is blue",
return "blue is sky the".

Could you do it in-place without allocating extra space?
*/
///@author	zhaowei
///@date	2015.08.12
///@version	1.0

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	///@brief	将字符串中的单词反转过来
	///@param	s	字符串
	///@return	无
	///@note	先遍历一边数组，记录下空格的位置，然后利用reverse函数将单词逐个翻转。时间复杂度为O(n)，空间复杂度为O(1)。
	void reverseWords(string &s) {		
		vector<int> sp;
		for (int i = 0; i != s.size(); i++)
			if (s[i] == ' ') sp.push_back(i);
		
		if (sp.empty())	return;
		
		reverse(s.begin(), s.end());
		reverse(s.begin(), s.begin() + s.size() - 1 - sp.back());

		for (int i = sp.size()-1; i > 0; i--)
			reverse(s.begin() + s.size() - sp[i], s.begin() + s.size() - 1 - sp[i - 1]);
		
		reverse(s.begin() + s.size() - sp.front(), s.end());
	}
};

int main()
{
	string s = "";
	Solution slt;
	slt.reverseWords(s);
	return 0;
}