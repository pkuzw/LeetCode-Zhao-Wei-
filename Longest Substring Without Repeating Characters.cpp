///@file	Longest Substring Without Repeating Characters
/*
Given a string, find the length of the longest substring without repeating characters. For example, 

the longest substring without repeating letters for "abcabcbb" is "abc", which the length is 3. 

For "bbbbb" the longest substring is "b", with the length of 1.
*/
///@author	zhaowei
///@date	2015.09.10
///@version	1.0

#include <unordered_map>
#include <string>
using namespace std;

class Solution {
public:
	///@brief	计算最长无重复字符的子串长度
	///@param	s	字符串
	///@return	返回最长无重复字符的子串长度
	///@note	
	int lengthOfLongestSubstring(string s) {
		int m[256] = {0}, res = 0, left = 0;
		for (int i = 0; i < s.size(); ++i) {
			if (m[s[i]] == 0 || m[s[i]] < left) {
				res = max(res, i - left + 1);
			} else {
				left = m[s[i]];
			}
			m[s[i]] = i + 1;
		}
		return res;
	}
};

int main()
{
	return 0;
}