///@file	Palindrome Pairs
///@author	zhaowei
///@date	2016.03.29
///@version	1.0

#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class Solution {
public:
	///@brief	给定一组单词组，找到所有的索引对<i, j>，使得words[i] + words[j]为回文字符串
	///@param	words	单词组
	///@return	返回所有回文字符串的索引对
	///@note	1. 枚举；
	//			2. 时间复杂度为O(n^2k)，其中n为单词数目，k为单词平均长度. TLE.
	vector<vector<int>> palindromePairs(vector<string>& words) {
		vector<vector<int>> rslt;
		if (words.empty())	return rslt;
		for (int i = 0; i != words.size() - 1; i++) {
			for (int j = i + 1; j != words.size(); j++) {
				if (isPalindrome(words[i], words[j])) {
					vector<int> indx_pair;
					indx_pair.push_back(i);
					indx_pair.push_back(j);
					rslt.push_back(indx_pair);
				}
				if (isPalindrome(words[j], words[i])) {
					vector<int> indx_pair;
					indx_pair.push_back(j);
					indx_pair.push_back(i);
					rslt.push_back(indx_pair);
				}
			}
		}
		return rslt;
	}

	///@brief	判断字符串a + b组成的字符串是否是回文字符串
	///@param	a, b	两个字符串
	///@return	如果a + b是回文字符串，则返回true；否则返回false
	bool isPalindrome(string a, string b) {
		string c = a + b;
		for (int i = 0; i != c.size() / 2; i++) {
			if (c[i] != c[c.size()-1-i])		return false;
		}
		return true;
	}
};

int main() {
	string w[] = {"abcd", "dcba", "lls", "s", "sssll"};
	vector<string> words;
	for (int i = 0; i != 5; i++)	words.push_back(w[i]);
	Solution slt;
	vector<vector<int>> rslt = slt.palindromePairs(words);
	return 0;
}