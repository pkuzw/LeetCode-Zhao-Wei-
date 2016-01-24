///@file	Isomorphic Strings
/*
Given two strings s and t, determine if they are isomorphic.

Two strings are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the order of characters.

No two characters may map to the same character but a character may map to itself.

For example,
Given "egg", "add", return true.

Given "foo", "bar", return false.

Given "paper", "title", return true.

Note:
You may assume both s and t have the same length.
*/
///@author	zhaowei
///@date	2015.07.28
///@version	1.0

///@date	2015.08.11
///@version	1.1

///@date	2016.01.24
///@version	1.2

#include <unordered_map>
#include <string>

using namespace std;

class Solution_v1 {
public:
	///@brief	给定两个等长字符串，判断它们能否互相转换，转换时要求每个字符只能对应为另一种字符，包括它自己
	///@param	s, t	两个字符串
	///@return	如果能够转换，则返回true；否则返回false
	/* @note	遍历其中的一个字符串，如果这个字符还没有遍历过，则记录下这个字符串中的字符与另一个字符串的对应关系*，如果遍历过就判断
				之前的对应是否与现在该字符的对应相同，如果不相同返回false，相同则继续遍历。遍历完字符串后返回true。对s做完匹配后要再对t
				做一遍匹配，因为不允许同样的字符匹配给不同字符。这样做两次匹配就能保证字符之间是一一对应的。否则类似"ab"->"aa"的情况
				则会处理成true。时间复杂度为O(n)，空间复杂度为O(n)。*/
	bool isIsomorphic(string s, string t) {
		if (s.empty())	return true;

		bool flg1 = true;
		bool flg2 = true;
		unordered_map<char, char> hash_table1, hash_table2;
		for (int i = 0; i < s.length(); i++)
		{
			if (hash_table1.find(s[i]) == hash_table1.end())
				hash_table1[s[i]] = t[i];
			else
			{
				if (hash_table1[s[i]] != t[i])
					flg1 = false;
			}
		}

		for (int i = 0; i < t.length(); i++)
		{
			if (hash_table2.find(t[i]) == hash_table2.end())
				hash_table2[t[i]] = s[i];
			else
			{
				if (hash_table2[t[i]] != s[i])
					flg2 = false;
			}
		}
		return flg1 && flg2;
	}
};

class Solution {
public:
	///@note	1. 注意处理ab -> cc的情形
	bool isIsomorphic(string s, string t) {
		if (s.size() != t.size())	return false;		
		unordered_map<char, char> hash_tbl;
		for (int i = 0; i != s.size(); i++) {
			if (hash_tbl.find(s[i]) == hash_tbl.end())	hash_tbl[s[i]] = t[i];
			else if (hash_tbl[s[i]] != t[i])	return false;
		}
		hash_tbl.clear();
		for (int i = 0; i != t.size(); i++) {
			if (hash_tbl.find(t[i]) == hash_tbl.end())	hash_tbl[t[i]] = s[i];
			else if (hash_tbl[t[i]] != s[i])	return false;
		}
		return true;
	}
};

int main()
{
	string s = "aab";
	string t = "dde";

	Solution slt;
	bool rslt = slt.isIsomorphic(s, t);

	Solution_v1 slt_v1;
	bool rslt1 = slt_v1.isIsomorphic(s, t);
	return 0;
}