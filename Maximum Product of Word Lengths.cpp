﻿///@file	Maximum Product of Word Lengths
///@author	zhaowei
///@date	2016.03.22
///@version	1.0
///@version 1.1

#include <string>
#include <unordered_map>
#include <vector>
#include <cstdlib>

using namespace std;

class Solution_v1 {
public:
	///@brief	给定一组单词，找到没有相同字母的两个单词的最大乘积
	///@param	words	单词组
	///@return	返回最大乘积
	///@note	1. 枚举法；
	//			2. 用双重循环遍历，找到没有相同字母的两个单词的最大乘积；
	//			3. 时间复杂度为O(n^2)，n为单词数目；
	//			4. TLE.
	int maxProduct(vector<string>& words) {
		if (words.empty())	return 0;
		int max_product = 0;
		for (int i = 0; i != words.size() - 1; i++) {
			for (int j = i + 1; j != words.size(); j++) {
				if (!hasCommonChar(words[i], words[j]))	max_product = max_product < words[i].size() * words[j].size() ? words[i].size() * words[j].size() : max_product;
			}
		}
		return max_product;
	}

	///@brief	比较两个单词是否含有相同的字母
	///@param	a, b	两个互相比较的单词
	///@return	如果a和b有相同的字母，则返回true；否则返回false
	bool hasCommonChar(const string a, const string b) {
		int hash_tbl_a[26] = {0}, hash_tbl_b[26] = {0};
		for (int i = 0; i != a.size(); i++)	hash_tbl_a[a[i] - 'a']++;
		for (int i = 0; i != b.size(); i++)	hash_tbl_b[b[i] - 'a']++;
		for (int i = 0; i != 26; i++)
			if (hash_tbl_a[i] && hash_tbl_b[i])	return true;
		return false;
	}
};

struct word {
	vector<int> hash_tbl;
	string w;
	int length;
	word() : hash_tbl(26, 0), w(), length(0) {}
};

class Solution {
public:
	///@brief	给定一组单词，找到没有相同字母的两个单词的最大乘积
	///@param	words	单词组
	///@return	返回最大乘积
	///@note	1. 枚举法；
	//			2. 在v1的基础上进行优化，在比较两个单词是否有相同字母的方法中，对两个单词的哈希表进行化简，已经出现的字母不再进行比较；
	//			3. 在进行比较前对单词进行预处理，对每个单词计算好它的长度，出现了那些字母以及它本身是什么，然后再进行双重循环的匹配；
	//			4. 时间复杂度为O(n^2)，n为单词数目；	
	//			5. TLE.
	int maxProduct(vector<string>& words) {
		if (words.empty())	return 0;
		int max_product = 0;
		vector<word> w_vec;
		for (int i = 0; i != words.size(); i++) {
			word wd;
			wd.w = words[i];
			wd.length = words[i].length();
			for (int j = 0; j != words[i].length(); j++) {
				wd.hash_tbl[words[i][j] - 'a']++;
			}
			w_vec.push_back(wd);
		}
		for (int i = 0; i != w_vec.size() - 1; i++) {
			for (int j = i + 1; j != w_vec.size(); j++) {
				if (!hasCommonChar(w_vec[i], w_vec[j]))	max_product = max_product < w_vec[i].length * w_vec[j].length ? w_vec[i].length * w_vec[j].length : max_product;
			}
		}
		return max_product;
	}

	///@brief	比较两个单词是否含有相同的字母
	///@param	a, b	两个互相比较的单词
	///@return	如果a和b有相同的字母，则返回true；否则返回false
	bool hasCommonChar(word a, word b) {
		for (int i = 0; i != 26; i++)
			if (a.hash_tbl[i] && b.hash_tbl[i])	return true;
		return false;
	}
};

int main() {
	string w[6] = {"abcw", "baz", "foo", "bar", "xtfn", "abcdef"};
	string w1[7] = {"a", "ab", "abc", "d", "cd", "bcd", "abcd"};
	string w2[4] = {"a", "aa", "aaa", "aaaa"};
	vector<string> words;
	for (int i = 0; i != 6; i++)	words.push_back(w[i]);
	Solution slt;
	int rslt = slt.maxProduct(words);
	return 0;
}