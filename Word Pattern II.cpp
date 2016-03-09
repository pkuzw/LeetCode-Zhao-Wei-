///@file	Word Pattern II
///@author	zhaowei
///@date	2016.03.09
///@version	1.0

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
	///@brief	判断给定字符串是否符合给定的模式
	///@param	pattern	模式字符串
	///@param	str		给定字符串
	///@return	如果给定的字符串的顺序符合模式字符串，返回true；否则返回false
	///@note	1. 先根据模式字符串的长度和待判断字符串的长度，计算出待判断字符串中对应模式一个字符的子串长度，然后对其进行切分；
	//			2. 然后通过双射，来判断是否符合模式。
	//			3. 这个思路有错误，在于单字符对应的子串不一定都是等长的。
	bool wordPatternMatch(string pattern, string str) {
		if (pattern.empty() || str.empty())	return false;
		int pattern_len = pattern.length(), str_len = str.length();
		if (str_len % pattern_len)	return false;
		int sub_len = str_len / pattern_len;
		vector<string> sub_strs;
		for (int i = 0; i != str_len; i += sub_len)	sub_strs.push_back(str.substr(i, sub_len));
		for (int i = 0; i != pattern_len; i++) {
			if (hash_tbl.find(pattern[i]) == hash_tbl.end())	hash_tbl[pattern[i]] = sub_strs[i];
			else if (hash_tbl[pattern[i]] != sub_strs[i])	return false;			
		}
		for (int i = 0; i != sub_strs.size(); i++) {
			if (hash_tbl_.find(sub_strs[i]) == hash_tbl_.end())	hash_tbl_[sub_strs[i]] = pattern[i];
			else if (hash_tbl_[sub_strs[i]] != pattern[i])	return false;			
		}
		return true;
	}

	unordered_map<char, string> hash_tbl;
	unordered_map<string, char> hash_tbl_;
};

int main() {
	Solution slt;
	string pattern = "abab", str = "redblueredblue";
	bool rslt = slt.wordPatternMatch(pattern, str);
	return 0;
}