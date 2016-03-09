///@file	Word Pattern II
///@author	zhaowei
///@date	2016.03.09
///@version	0.1
///@version	1.0

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution_v0_1 {
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

class Solution {
public:
	///@note	1. 递归 + 回溯；
	//			2. 用两个哈希表分别表示模式到字符串和字符串到模式的映射；
	//			3. 然后遍历所有可能的模式到字符串的匹配，当二者都到最末尾时返回true。
	bool wordPatternMatch(string pattern, string str) {
		return dfs(pattern, 0, str, 0);
	}

	///@brief	递归辅助函数
	///@param	pattern	模式
	///@param	i		模式串的下标
	///@param	str		待匹配字符串
	///@param	j		待匹配字符串下标
	///@return	如果匹配则返回true，否则返回false
	bool dfs(string pattern, int i, string str, int j) {
		int p_len = pattern.length(), s_len = str.length();
		if (i == p_len || j == s_len) {
			if (i == p_len && j == s_len)	return true;
			return false;
		}
		bool ins = false;	//	是否有新的映射插入哈希表
		for (int k = j; k < s_len; k++) {
			string s = str.substr(j, k-j+1);
			if (pDict.find(pattern[i]) != pDict.end()) {
				if (pDict[pattern[i]] != s)	continue;
			}
			else if (sDict.find(s) != sDict.end()) {
				if (sDict[s] != pattern[i])	continue;
			}
			else {
				pDict[pattern[i]] = s;
				sDict[s] = pattern[i];
				ins = true;
			}
			if (dfs(pattern, i+1, str, k+1))	return true;
			if (ins) {
				pDict.erase(pattern[i]);
				sDict.erase(s);
			}
		}
		return false;
	}

	unordered_map<char, string> pDict;
	unordered_map<string, char> sDict;
};

int main() {
	Solution slt;
	string pattern = "aabb", str = "xyzabcxzyabc";
	bool rslt = slt.wordPatternMatch(pattern, str);
	return 0;
}