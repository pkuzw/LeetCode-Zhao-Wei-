///@file	Longest Substring Without Repeating Characters
/*
Given a string, find the length of the longest substring without repeating characters. For example, 

the longest substring without repeating letters for "abcabcbb" is "abc", which the length is 3. 

For "bbbbb" the longest substring is "b", with the length of 1.
*/
///@author	zhaowei
///@date	2015.09.10
///@version	1.0

#include <vector>
#include <string>
using namespace std;

class Solution {
public:
	///@brief	计算最长无重复字符的子串长度
	///@param	s	字符串
	///@return	返回最长无重复字符的子串长度
	///@note	设last_occur[i]表示字符i上次出现的位置。那么如果在遍历字符串时，如果当前下标减去上次出现该字符的下标的长度小于等于
	//			最长长度时，最长长度应该为当前下标减去上次出现该字符的下标；否则最长长度自增1. 在每遍历一个字符时，就要更新每个字符的上次
	//			出现位置，并同时更新最长子串长。
	//			时间复杂度为O(n)，空间复杂度为O(1)。
	int lengthOfLongestSubstring(string s) {
		vector<int> last_occur(128, -1);
		int rslt = 0;
		int longest_len = 0;
		for (int i = 0; i != s.size(); i++) {
			if (i - last_occur[s[i]] <= longest_len)	longest_len = i - last_occur[s[i]];
			else	longest_len++;
			last_occur[s[i]] = i;
			rslt = max(rslt, longest_len);
		}
		return rslt;
	}
};

int main()
{
	string s = "abcdcfg";
	Solution slt;
	int rslt = slt.lengthOfLongestSubstring(s);

	return 0;
}