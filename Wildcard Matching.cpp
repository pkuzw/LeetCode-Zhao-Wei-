///@file	Wildcard Matching
/*
			Implement wildcard pattern matching with support for '?' and '*'.

			'?' Matches any single character.
			'*' Matches any sequence of characters (including the empty sequence).

			The matching should cover the entire input string (not partial).

			The function prototype should be:
			bool isMatch(const char *s, const char *p)

			Some examples:
			isMatch("aa","a") → false
			isMatch("aa","aa") → true
			isMatch("aaa","aa") → false
			isMatch("aa", "*") → true
			isMatch("aa", "a*") → true
			isMatch("ab", "?*") → true
			isMatch("aab", "c*a*b") → false
*/
///@author	zhaowei
///@date	2015.06.22
///@version	1.0

#include <iostream>
#include <string>
using namespace std;

class Solution
{
public:
	bool isMatch(string s, string p) {

	}
};
int main()
{
	string a, b;
	Solution slt;
	while (cin >> a >> b)
	{
		cout << slt.isMatch(a, b);
		cout <<	endl;
	}
	return 0;
}