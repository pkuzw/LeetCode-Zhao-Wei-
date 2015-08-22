///@file	Valid Palindrome
/*
Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

For example,
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.

Note:
Have you consider that the string might be empty? This is a good question to ask during an interview.

For the purpose of this problem, we define empty string as valid palindrome.
*/
///@author	zhaowei
///@date	2015.07.24
///@version	1.0

///@date	2015.08.22
///@version	2.0

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution_v1 {
public:
	///@brief	判断一个字符串是否是回文字符串。忽略非字母和非数字字符
	///@param	s	字符串
	///@return	如果字符串是回文的，则返回true；否则返回false
	/* @note	先将字符串压缩到只有字符字符和数字字符，然后将后半部分翻转，再判断前后两部分是否相等。时间复杂度为O(n)，空间复杂度为O(n)。*/
	bool isPalindrome(string s) {
		string t;
		for (int i = 0; i != s.length(); i++)
			if ((s[i] <= 'z' && s[i] >= 'a') || (s[i] <= 'Z' && s[i] >= 'A') || (s[i] <= '9' && s[i] >= '0'))
			{
				if (s[i] <= 'Z' && s[i] >= 'A')
					s[i] += 'a'-'A';
				t += s[i];
			}

		int len = t.length();
		string half1, half2;
		int start = (len % 2 == 0) ? len / 2 : len / 2 + 1;
		half1 = t.substr(0, len/2);
		half2 = t.substr(start, len/2);

		reverse(half2.begin(), half2.end());

		return half1 == half2;
	}
};

///@note	先将字符串转换成只有小写字母和数字的形式，然后对其进行判断。
class Solution {
public:
	bool isPalindrome(string s) {
		if (s.empty())	return true;
		string pstr;
		for (int i = 0; i != s.size(); i++)
		{
			if (s[i] <= 'Z' && s[i] >= 'A')											pstr += s[i] + ('a' - 'A');
			else if ((s[i] <= 'z' && s[i] >= 'a') || (s[i] >= '0' && s[i] <= '9'))	pstr += s[i];
		}
		int start = 0, end = pstr.size()-1;
		while (pstr[start] == pstr[end])
		{
			start++;
			end--;
			if (start > end)	return true;
		}
		return false;
	}
};

int main()
{
	string s = "A man, a plan, a canal: Panama";
	Solution slt;
	bool r = slt.isPalindrome(s);
	return 0;
}