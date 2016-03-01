///@file	Palindrome Permutation
///@author	zhaowei
///@date	2016.01.31
///@version	1.0

///@date	2016.03.01
///@version	1.1

#include <vector>
#include <unordered_map>

using namespace std;

class Solution_v1 {
public:
	///@brief	判断一个字符串能否通过重新排列形成一个回文串
	///@param	s	字符串
	///@return	如果能够通过重新排列得到回文串，返回true；否则返回false
	///@note	1. 如果字符串中的字符出现的次数最多只有一个是奇数次，其余的都是偶数次，则为true；否则为false；
	//			2. 时间复杂度为O(n)，空间复杂度为O(n)，其中n为字符串s的长度。
	bool canPermutePalindrome(string s) {
		if (s.empty())	return true;
		unordered_map<char, int> hash_tbl;
		for (int i = 0; i != s.size(); i++)	hash_tbl[s[i]]++;
		int odd_cnt = 0;
		for (unordered_map<char, int>::iterator i = hash_tbl.begin(); i != hash_tbl.end(); i++)
			if (i->second % 2)	odd_cnt++;		
		return odd_cnt <= 1;

	}
};

class Solution {
public:
	///@note	1. 用一维数组代替unordered_map；
	//			2. 字符串可能出现的字符不限于小写字母，有可能是大写字母或其他字符。
	bool canPermutePalindrome(string s) {
		int hash_tbl[256] = {0};
		for (int i = 0; i != s.size(); i++)	hash_tbl[s[i]]++;
		int odd_cnt = 0;
		for (int i = 0; i != 256; i++) 
			if (hash_tbl[i] % 2)	odd_cnt++;		
		return odd_cnt <= 1;
	}
};

int main() {
	string s = "AaBb//a";
	Solution slt;
	bool rslt = slt.canPermutePalindrome(s);
	return 0;
}