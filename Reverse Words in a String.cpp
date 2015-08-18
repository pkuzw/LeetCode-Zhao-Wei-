///@file	Reverse Words in a String
/*
Given an input string, reverse the string word by word.

For example,
Given s = "the sky is blue",
return "blue is sky the".

Clarification:
1. What constitutes a word?
A sequence of non-space characters constitutes a word.

2. Could the input string contain leading or trailing spaces?
Yes. However, your reversed string should not contain leading or trailing spaces.

3. How about multiple spaces between two words?
Reduce them to a single space in the reversed string.
*/
///@author	zhaowei
///@date	2015.07.27
///@version	1.0

///@date	2015.08.18
///@version	2.0

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution_v1 {
public:
	///@brief	翻转字符串中的每个单词。
	///@param	s	字符串
	///@note	删去多余的空格，每个单词之间只能有一个空格。时间复杂度为O(n)，空间复杂度为O(n)。
	void reverseWords(string &s) {
		if (s.empty())	return;

		vector<string> svec;

		deleteHeadSpace(s);
		deleteTailSpace(s);

		s += ' ';	//	给最后补上一个空格，便于计算最后一个单词。

		int start = 0;
		int end = 0;
		int i = 0;
		while (!s.empty())
		{
			if (s[i] == ' ')
			{
				end = i-1;
				svec.push_back(s.substr(start, end-start+1));
				s = s.substr(i, s.length()-i);
				deleteHeadSpace(s);
				start = 0;
				i = 0;
				continue;
			}
			i++;
		}
				
		for (int i = svec.size()-1; i >= 0; i--)
		{
			s = s + svec[i] + " ";
		}

		deleteTailSpace(s);
	}

private:
	///@brief	删除字符串头部的空白字符
	///@param	s	字符串
	///@return	无
	void deleteHeadSpace(string &s)
	{
		int space_cnt = 0;
		for (int i = 0; i < s.length() && s[i] == ' '; i++)	//去掉首部空白符
			space_cnt++;		
		s = s.substr(space_cnt, s.length()-space_cnt);
	}

	///@brief	删除字符串尾部的空白字符
	///@param	s	字符串
	///@return	无
	void deleteTailSpace(string &s)
	{
		int space_cnt = 0;
		for (int i = s.length()-1; i >= 0 && s[i] == ' '; i--)//去掉尾部空白符
			space_cnt++;		
		s = s.substr(0, s.length()-space_cnt);
	}
};

///@note	先除去多余的空格，然后将每个单词按照相间1个空格的间距排列，然后将单个的单词反转，最后将整个的句子进行反转。
//			i标记出遍历的数组下标到达了哪个位置；j表示单词结束的下标；k表示单词开始的下标；word_cnt表示单词的数目。时间复杂度为O(n)，空间复杂度为O(1)。
class Solution {
public:
	void reverseWords(string &s)
	{
		int i = 0, j = 0, k = 0, word_cnt = 0;
		while (1)
		{
			while (i < s.size() && s[i] == ' ')
				i++;
			if (i == s.size())	break;
			if (word_cnt)	s[j++] = ' ';
			k = j;
			while (i < s.size() && s[i] != ' ')
				s[j++] = s[i++];
			reverse(s.begin() + k, s.begin() + j);
			word_cnt++;
		}
		s.resize(j);
		reverse(s.begin(), s.end());
	}
};

int main()
{
	string s = "     the  sky is blue        I am the   no.  1..  muri    ";
	Solution slt;
	slt.reverseWords(s);
	return 0;
}