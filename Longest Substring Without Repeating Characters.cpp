///@file	Longest Substring Without Repeating Characters
/*
Given a string, find the length of the longest substring without repeating characters. For example, 

the longest substring without repeating letters for "abcabcbb" is "abc", which the length is 3. 

For "bbbbb" the longest substring is "b", with the length of 1.
*/
///@author	zhaowei
///@date	2015.09.10
///@version	1.0

///@date	2016.03.31
///@version	1.1

///@date    June 13, 2018
///@version 1.2

#include <vector>
#include <string>
using namespace std;

class Solution_v1 {
public:
	///@brief	计算最长无重复字符的子串长度
	///@param	s	字符串
	///@return	返回最长无重复字符的子串长度
	///@note	设last_occur[i]表示字符i上次出现的位置。那么如果在遍历字符串时，如果当前下标减去上次出现该字符的下标的长度小于等于
	//			最长长度时，最长长度应该为当前下标减去上次出现该字符的下标；否则最长长度自增1. 在每遍历一个字符时，就要更新每个字符的上次
	//			出现位置，并同时更新最长子串长。
	//			时间复杂度为O(n)，空间复杂度为O(1)。
	int lengthOfLongestSubstring(string s) {
		vector<int> last_occur(128, -1);
		int rslt = 0;
		int longest_len = 0;
		for (int i = 0; i != s.size(); i++) {
			if (i - last_occur[s[i]] <= longest_len)	longest_len = i - last_occur[s[i]];
			else	longest_len++;
			last_occur[s[i]] = i;
			rslt = max(rslt, longest_len);
		}
		return rslt;
	}
};

class Solution_v1_1 {
public:
	///@note	1. 哈希表；
	//			2. 找到每一个不含有重复字符的子串，每当遇到重复字符，就更新子串长度，并重新开始计算其最大长度；
	//			3. 哈希表初始化为-1是为了处理只有一个字符的情形；
	//			4. 时间复杂度为O(n)，空间复杂度为O(1)，其中n为字符串长度。
	int lengthOfLongestSubstring(string s) {
		int hash_tbl[256] = {0};
		memset(hash_tbl, -1, 256*sizeof(int));
		int rslt = 0;
		int longest_len = 0;
		for (int i = 0; i != s.size(); i++) {
			if (i - hash_tbl[s[i]] <= longest_len)
                longest_len = i - hash_tbl[s[i]];
			else
                longest_len++;
			hash_tbl[s[i]] = i;
			rslt = max(rslt, longest_len);
		}
		return rslt;
	}
};

class Solution {
public:
    ///@brief   计算字符串s的最长公共子串（不含有重复字符）。
    ///@param    s   字符串
    ///@return  返回字符串的最长公共子串（不含重复字符）的长度。
    ///@note    这个算法的关键点有两个：
    ///         1. 用int hash_table[256]来保存子串字符出现的最新下标。
    ///         2. 将hash_table[256]初始化为-1，这样的话利用i - hash_table['c']就能计算出当前子串的大小了。
    ///         算法的时间复杂度为O(n)，空间复杂度为O(1)，其中n为字符串s的长度。
    int lengthOfLongestSubstring(string s) {
        int maxLen = 0, subLen = 0;
        int hash_table[256];
        memset(hash_table, -1, 256 * sizeof(int));
        
        for (int i = 0; i < s.length(); i++) {
            if (i - hash_table[s[i]] <= subLen) subLen = i - hash_table[s[i]];
            else    subLen++;
            hash_table[s[i]] = i;
            maxLen = max(maxLen, subLen);
        }
        return maxLen;
    }
};

int main()
{
	Solution slt;
    string s = "HongLisaLiWenhao";
	int rslt = slt.lengthOfLongestSubstring(s);

	return 0;
}
