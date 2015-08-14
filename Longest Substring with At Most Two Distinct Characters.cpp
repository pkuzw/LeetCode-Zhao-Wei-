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
	///@brief	计算最多只有两个不同字符组成的字符串的最大长度
	///@param	s	字符串
	///@return	返回字符串的最大长度
	///@note	用左右指针l和r标定包含两个不同字符的字符串的最左边界和最右边界。遍历字符串即可。时间复杂度为O(n)，空间复杂度为O(1)。
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
				while (s[l] == a)
					l++;
				a = s[l];
			}
			else
			{
				if (r != len-1)
				{
					b = s[r];
					while (s[r] == b)
						r++;					
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