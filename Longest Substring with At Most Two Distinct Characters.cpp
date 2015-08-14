///@file	Longest Substring with At Most Two Distinct Characters
/*
Given a string, find the length of the longest substring T that contains at most 2 distinct characters.

For example, Given s = “eceba”,

T is "ece" which its length is 3.
*/
///@author	zhaowei
///@date	2015.08.14
///@version	1.0
#include <string>
using namespace std;

class Solution {
public:
	int lengthOfLongestSubstringTwoDistinct(string s) {
		if (s.size() < 3)	return s.size();	// 长度小于3的字符串，最多包含2个差异字符的长度为其本身长度		
		int l = 0, r = 2;	//	左右指针，用于标定最多只有两个不同字符的字符串
		int len = s.size();	
		char a = s[0], b = s[1];	//	差异字符，字符串由这两个字符组成

		int j = 1;
		while (j < len && b == a)
		{
			b = s[j++];		//	找到右边界的字符
		}
		r = j-1;		//	初始右边界
		int rslt = r + 1;
		while (r < len)
		{
			if (s[r] != a && s[r] != b)
			{
				rslt = max(rslt, r-l);
				l++;
				if (s[l] != a)	a = s[l];
			}
			else
			{
				if (r != len-1)
				{
					r++;
					if (s[r] != b)	b = s[r];
				}			
			}
		}
		return rslt;
	}
};

int main()
{
	string s = "eeeba";
	Solution slt;
	int rslt = slt.lengthOfLongestSubstringTwoDistinct(s);
	return 0;
}