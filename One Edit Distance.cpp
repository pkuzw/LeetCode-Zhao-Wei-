///@file	One Edit Distance
///			Given two strings S and T, determine if they are both one edit distance apart.
///@author	zhaowei
///@date	2015.08.14
///@version	1.0

///@date	2016.01.16
///@version	1.1

#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
using namespace std;

class Solution_v1 {
public:
	///@brief	判断两个字符串是否能够修改、删除或者添加一次来变得一样
	///@param	s	字符串s
	///@param	t	字符串t
	///@return	如果可以，则返回true；否则返回false
	///@note	如果两个字符串的长度相差超过1，则肯定不能够通过一次操作（增删改）来使得二者一致。如果长度相同，则要看是否只存在一个不同字符；
	//			如果字符串长度差1，则要看短的那个字符串是长字符串的子串与否，如果是子串，则通过增删就可以做到一致，否则就不行。
	//			对于长度相等的两个字符串，从前向后遍历，如果差异字符超过1个或者为0，则返回false。对于长度不等的两个字符串，也是从前向后遍历，
	//			找到第一个不同的字符后，将较长的字符删除那个字符，比较两个新字符串是否相同即可。
	//			时间复杂度为O(n)，空间复杂度为O(1)。
	bool isOneEditDistance(string s, string t) {
		if (s.size() < t.size())	swap(s, t);
		int slen = s.size(), tlen = t.size();
		if (abs(slen - tlen) > 1)	return false;
		
		if (slen == tlen)
		{
			if (s == t)	return false;
			int diff_cnt = 0;
			for (int i = 0; i != tlen; i++)
			{
				if (s[i] != t[i])	diff_cnt++;
				if (diff_cnt > 1)	return false;
			}
			return true;
		}
		else
		{	
			for (int i = 0; i != tlen; i++)
			{
				if (t[i] != s[i])
				{
					string r = s.substr(0, i) + s.substr(i+1);
					if (t == r)	return true;
					else		return false;
				}
			}
			return true;
		}
	}
};

class Solution {
public:	
	///@brief	判断两个字符串是否能够修改、删除或者添加一次来变得一样
	///@param	s	字符串s
	///@param	t	字符串t
	///@return	如果可以，则返回true；否则返回false
	///@note	1. 枚举；2. 当两个字符串的长度相差超过1时，返回false；当两个字符串长度相同且不同的字符数累积值为1时，返回true，否则为false；
	//			当两个字符串长度相差为1，且较长的字符串除去其中的一个字符后的子串与较短字符串相同，则返回true，否则返回false。
	//			3. 时间复杂度为O(n)，空间复杂度为O(1)。
	bool isOneEditDistance(string s, string t) {
		if (s.size() > t.size())	swap(s, t);
		int slen = s.size(), tlen = t.size();
		if (tlen - slen > 1)		return false;
		else if (tlen == slen) {
			int diff_cnt = 0;
			for (int i = 0; i != tlen; i++) {
				if (s[i] != t[i])	diff_cnt++;
			}
			if (diff_cnt == 1)	return true;			
		}
		else {
			string r = t.substr(0, tlen - 1);
			for (int i = 0; i != slen; i++) {
				if (s[i] != t[i]) {
					r = t.substr(0, i) + t.substr(i + 1);
					break;
				}
			}
			if (r == s)	return true;
		}
		return false;
	}
};

int main()
{
	string s = "teacher";
	string t = "tedacher";
	Solution slt;
	bool rslt = slt.isOneEditDistance(s, t);
	return 0;
}