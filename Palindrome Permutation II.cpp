///@file	Palindrome Permutation II
///@author	zhaowei
///@date	2016.02.02
///@version	1.0

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
	///@brief	给定一个字符串，通过重新排列，组成回文字符串
	///@param	s	字符串
	///@return	返回所有可能的回文字符串 
	///@note	1. 类似与排列组合遍历算法，候选数组来自于原字符串的一半；
	//			2. 先判断原字符串是否可以组成回文字符串，如果不可以直接返回空；否则逐个递归遍历；
	vector<string> generatePalindromes(string s) {
		if (s.empty() || !isPalindrome(s))	return rslt;
		string str;
		for (unordered_map<char, int>::iterator i = hash_tbl.begin(); i != hash_tbl.end(); i++) {
			if (i->second % 2) {
				str = i->first;
				i->second--;
				if (!i->second)	hash_tbl.erase(i);
				break;
			}
		}
		for (unordered_map<char, int>::iterator i = hash_tbl.begin(); i != hash_tbl.end(); i++)	i->second /= 2;
		dfs(hash_tbl, str);
		return rslt;

	}

	///@brief	判断字符串s是否可以通过重新排列变成回文字符串
	///@param	s	字符串
	///@return	如果字符串s可以通过重新排列变为回文字符串，则返回true；否则返回false
	bool isPalindrome(string s) {
		for (int i = 0; i != s.size(); i++)	hash_tbl[s[i]]++;
		int odd_cnt = 0;
		for (unordered_map<char, int>::iterator i = hash_tbl.begin(); i != hash_tbl.end(); i++)
			if (i->second % 2)	odd_cnt++;
		return odd_cnt < 2;
	}

	///@brief	通过递归来生成回文字符串的前半部分
	///@param	candidates	候选字符数组
	///@param	str			生成的回文子串的前半部分
	///@return	无
	///@note	1. 递归；
	//			2. 从候选数组中选择元素生成新的回文子串。
	void dfs(unordered_map<char, int>& hash_tbl, string& str) {
		if (hash_tbl.empty()) {
			rslt.push_back(str);
			return;
		}
	}

	unordered_map<char, int> hash_tbl;
	vector<string> rslt;
	
};

int main() {
	
	return 0;
}