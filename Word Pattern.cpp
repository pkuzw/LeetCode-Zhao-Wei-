///@file	Word Pattern
///@author	zhaowei
///@date	2016.03.08
///@version	1.0

#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	///@brief	判断字符串str中的单词出现模式是否和pattern中的一致
	///@param	pattern	模式
	///@param	str		字符串，单词组
	///@return	如果匹配则返回true，反之返回false
	///@note	1. 先抽取出来str中的单词；
	//			2. 然后用一个哈希表来保存已经探测到的模式中的字母所代表的单词，如果出现的单词和前面的字母所对应的单词不一致则返回false；否则循环完毕返回true。
	//			3. 再用一个哈希表保存单词到模式的映射，这样双射才能保证互相一致；
	//			4. 时间复杂度为O(n)，空间复杂度为O(n)，其中n为模式字符串的长度。
	bool wordPattern(string pattern, string str) {
		if (pattern.empty() && str.empty())	return true;
		int j = 0;
		for (int i = 0; i != str.size(); i++) {
			if (str[i] == ' ') {
				words.push_back(str.substr(j, i - j));
				j = i + 1;
			}
		}
		words.push_back(str.substr(j, str.size() - j));
		if (words.size() != pattern.size())	return false;
		for (int i = 0; i != pattern.size(); i++) {
			if (hash_tbl.find(pattern[i]) == hash_tbl.end())	hash_tbl[pattern[i]] = words[i];			
			else {
				if (hash_tbl[pattern[i]] != words[i])	return false;
			}			
		}
		for (int i = 0; i != words.size(); i++) {
			if (hash_tbl_.find(words[i]) == hash_tbl_.end())	hash_tbl_[words[i]] = pattern[i];
			else {
				if (hash_tbl_[words[i]] != pattern[i])	return false;
			}			
		}
		return true;
	}

	vector<string> words;
	unordered_map<char, string> hash_tbl;
	unordered_map<string, char> hash_tbl_;
};

int main() {
	string pattern = "abba", str = "dog dog dog dog";
	Solution slt;
	bool rslt = slt.wordPattern(pattern, str);
	return 0;
}