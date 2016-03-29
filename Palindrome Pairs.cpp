///@file	Palindrome Pairs
///@author	zhaowei
///@date	2016.03.29
///@version	1.0
///@version	2.0

#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class Solution_tle {
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

class Solution {
public:
	///@note	1. 哈希表
	//			2. 将哈希表存储单词和对应的下标，然后对每个单词来进行截取，看其是否存在已经在哈希表中的项
	//			3. 注意处理words[i]和""的情形，如果words[i]为回文字符串，则words[i] + ""也是回文字符串。
	//			4. 时间复杂度为O(nk^2)，其中n为单词数目，k为单词平均长度；空间复杂度为O(nk)。
	vector<vector<int>> palindromePairs(vector<string>& words) {
		unordered_map<string, int> hash_tbl;
		vector<vector<int>> rslt;
		if (words.empty())	return rslt;
		for (int i = 0; i != words.size(); i++) {
			string rstr(words[i].rbegin(), words[i].rend());
			hash_tbl[rstr] = i;
		}

		if (hash_tbl.find("") != hash_tbl.end()) {
			for (int i = 0; i != words.size(); i++) {
				if (words[i] == "")	continue;
				if (isPalindrome(words[i])) {
					vector<int> indx_pair;
					indx_pair.push_back(hash_tbl[""]);
					indx_pair.push_back(i);
					rslt.push_back(indx_pair);
				}
			}
		}

		for (int i = 0; i != words.size(); i++) {
			for (int j = 0; j != words[i].size(); j++) {
				string left = words[i].substr(0, j);
				string right = words[i].substr(j, words[i].size() - j);

				if (hash_tbl.find(left) != hash_tbl.end() && isPalindrome(right) && i != hash_tbl[left]) {
					vector<int> indx_pair;
					indx_pair.push_back(i);
					indx_pair.push_back(hash_tbl[left]);					
					rslt.push_back(indx_pair);
				}

				if (hash_tbl.find(right) != hash_tbl.end() && isPalindrome(left) && i != hash_tbl[right]) {
					vector<int> indx_pair;
					indx_pair.push_back(hash_tbl[right]);
					indx_pair.push_back(i);									
					rslt.push_back(indx_pair);
				}
			}			
		}
		return rslt;
	}

	///@brief	判断字符串a是否是回文字符串
	///@param	a	字符串
	///@return	如果a是回文字符串，则返回true；否则返回false
	bool isPalindrome(string a) {		
		for (int i = 0; i != a.size() / 2; i++) {
			if (a[i] != a[a.size()-1-i])		return false;
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