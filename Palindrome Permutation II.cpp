///@file	Palindrome Permutation II
///@author	zhaowei
///@date	2016.02.02
///@version	1.0

///@date	2016.03.01
///@version	1.1

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution_v1 {
public:
	///@brief	给定一个字符串，通过重新排列，组成回文字符串
	///@param	s	字符串
	///@return	返回所有可能的回文字符串 
	///@note	1. 类似与排列组合遍历算法，候选数组来自于原字符串的一半；
	//			2. 先判断原字符串是否可以组成回文字符串，如果不可以直接返回空；否则逐个递归遍历；
	vector<string> generatePalindromes(string s) {
		if (s.empty() || !isPalindrome(s))	return rslt;
		string mid, str;
		int len = s.size();
		for (unordered_map<char, int>::iterator i = hash_tbl.begin(); i != hash_tbl.end(); i++) {
			if (i->second % 2) {
				mid = i->first;
				i->second--;
				break;
			}
		}
		for (unordered_map<char, int>::iterator i = hash_tbl.begin(); i != hash_tbl.end(); i++)	i->second /= 2;
		dfs(hash_tbl, str, len / 2);
		for (int i = 0; i != rslt.size(); i++) {
			string tmp(rslt[i].rbegin(), rslt[i].rend());
			rslt[i] += mid + tmp;
		}
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
	///@param	len			回文子串的长度
	///@return	无
	///@note	1. 递归；
	//			2. 从候选数组中选择元素生成新的回文子串；
	//			3. 当子串的长度为原来字符串的一半时，生成完毕，压入结果数组；
	//			4. 否则就是从哈希表中逐个遍历，把哈希表中的字符压入子串，然后减少其计数器，如果计数器为零，应该跳过；
	void dfs(unordered_map<char, int> hash_tbl, string& str, const int len) {
		if (str.size() == len) {
			rslt.push_back(str);
			return;
		}
		for (unordered_map<char, int>::iterator i = hash_tbl.begin(); i != hash_tbl.end(); i++) {
			if (!i->second)	continue;
			str += i->first;
			i->second--;
			dfs(hash_tbl, str, len);
			hash_tbl[i->first]++;
			str.pop_back();
		}
	}

	unordered_map<char, int> hash_tbl;
	vector<string> rslt;
};

class Solution {
public:
	///@note	1. 在处理中间字符时，不能使用char型变量，因为无法表示空字符；暂时用string类型来表达；
	//			2. 与v1.0不同，这里使用一维整型数组来保存字符的出现次数，更加直观简洁；
	//			3. 在递归前要将哈希表中的字符次数减半，这样能形成半个字符串；否则后半个字符串会出现前面已经用完的字符。
	vector<string> generatePalindromes(string s) {
		if (s.empty() || !isPalindrome(s))	return rslt;
		string str;
		int len = s.size() / 2;
		string mid = "";
		for (int i = 0; i != 256; i++) {	//	将哈希表中的字符出现次数减半，并找出中间字符
			if (hash_tbl[i] % 2) {
				mid = (char)i;
				hash_tbl[i]--;				
			}
			hash_tbl[i] /= 2;
		}		
		dfs(str, len, hash_tbl);
		for (int i = 0; i != rslt.size(); i++) {
			string tmp(rslt[i].rbegin(), rslt[i].rend());
			rslt[i] += mid + tmp;
		}
		return rslt;
	}

	bool isPalindrome(string s) {
		if (s.empty())	return true;
		memset(hash_tbl, 0, sizeof(int)*256);
		for (int i = 0; i != s.size(); i++)	hash_tbl[s[i]]++;	//	初始化hash_tbl
		int odd_cnt = 0;
		for (int i = 0; i != 256; i++)
			if (hash_tbl[i] % 2)	odd_cnt++;
		return odd_cnt <= 1;
	}

	void dfs(string& str, int len, int* hash_tbl) {
		if (str.size() == len) {
			rslt.push_back(str);
			return;
		}
		for (int i = 0; i != 256; i++) {
			if (!hash_tbl[i])	continue;
			str += (char)i;
			hash_tbl[i]--;
			dfs(str, len, hash_tbl);
			hash_tbl[i]++;
			str.pop_back();
		}
	}

	int hash_tbl[256];
	vector<string> rslt;
};

int main() {
	string s = "aacccbb";
	Solution_v1 s1;
	vector<string> r1 = s1.generatePalindromes(s);

	Solution slt;
	vector<string> rslt = slt.generatePalindromes(s);
	return 0;
}