///@file	Valid Anagram
/*
Given two strings s and t, write a function to determine if t is an anagram of s.

For example,
s = "anagram", t = "nagaram", return true.
s = "rat", t = "car", return false.

Note:
You may assume the string contains only lowercase alphabets.
*/
///@author	zhaowei
///@date	2015.08.03
///@version	1.0

///@author	zhaowei
///@date	2015.08.05
///@version	2.0

#include <string>
#include <unordered_map>

using namespace std;

class Solution_v1 {
public:
	///@brief	判断两个字符串是否是变形字符串关系
	///@param	s, t	字符串
	///@return	如果是，则返回true；否则返回false
	///@note	用一个哈希表保存s中出现的字符，然后再遍历字符串t，减去s中出现的字符次数，如果字符不存在或者已经减为0，则返回false。否则就返回true。时间复杂度为O(n)，空间复杂度为O(n)。
	bool isAnagram(string s, string t) {
		if (s.size() != t.size())	return false;

		unordered_map<char, int> ht;
		for (int i = 0; i != s.size(); i++)
			ht[s[i]]++;

		for (int i = 0; i != t.size(); i++)
		{
			if (ht.find(t[i]) == ht.end() || ht[t[i]] == 0)
			{
				return false;
			}
			ht[t[i]]--;
		}
		return true;
	}
};

class Solution {
public:
	bool isAnagram(string s, string t) {
		if (s.size() != t.size())	return false;
		
		unordered_map<char, int> hash_table;
		for (int i = 0; i != s.size(); i++)
			hash_table[s[i]]++;

		for (int i = 0; i != t.size(); i++)
		{
			if (hash_table.find(t[i]) == hash_table.end() || hash_table[t[i]] == 0)	return false;
			hash_table[t[i]]--;
		}
		return true;
	}
};

int main()
{
	string s = "anagram";
	string t = "nagrama";
	Solution slt;
	bool rslt = slt.isAnagram(s, t);
	return 0;
}