///@file	Shortest Palindrome 
/*
Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.

For example:

Given "aacecaaa", return "aaacecaaa".

Given "abcd", return "dcbabcd"
*/
///@author	zhaowei
///@date	2015.07.30
///@version	1.0

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
	///@brief	计算字符串需要添加最短的字符就可以变成回文字符串
	///@param	s	原字符串
	///@return	返回回文字符串	
	///@note	先将字符串翻转，然后和原字符串之间添加一个额外的非字母字符'@'进行连接，形成了新字符串t。维护一个一维数组p，p[i]表示
	//			t[0..i-1]的最长公共前缀后缀子串长度。最后再将翻转的字符串截出非公共前后子串的长度，与原字符串进行拼接即可。时间复杂度为O(n)，空间复杂度为O(n)。
	string shortestPalindrome(string s) {
		string r = s;
		reverse(r.begin(), r.end());

		string t = s + "@" + r;
		vector<int> p(t.length(), 0);

		for (int i = 1; i != t.length(); i++)
		{
			int j = p[i-1];	// p就相当于kmp中的next数组前身：t[0..i]的最长公共前缀后缀长度
			while (j > 0 && t[i] != t[j])
				j = p[j-1];
				
			p[i] = (j += t[i] == t[j]);
		}
		return r.substr(0, s.length()-p[t.length()-1]) + s;
	}
};

int main()
{
	string s = "cdcba";
	Solution slt;
	string rslt = slt.shortestPalindrome(s);
	return 0;
}