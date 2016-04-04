﻿///@brief	Write a function to find the longest common prefix string amongst an array of strings.
///@author	zhaowei
///@date	2015.06.03
///@version	1.0

///@date    2015.09.07
///@version 2.0

///@date	2016.04.04
///@version	2.1

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution_v1
{
public:
	///@brief	找出一组字符串的最长公共前缀
	///@param	strs	待处理的字符串数组
	///@return	返回该字符串数组的最长公共前缀
	///@author	zhaowei
	///@date	2015.06.03
	/* @note	先找到最短字符串，然后根据它的长度来进行遍历，一旦出现不一致的字符，中断循环即可。注意处理空字符串数组的情况。
	*/
	string longestCommonPrefix(vector<string>& strs) {

		string lcp;	// 保存最大公共前缀
		int min_slen = INT_MAX;	// 最小字符串的长度
		int min_sid = -1;	// 最小字符串的id

		// 需要注意处理strs为空的情形
		if (strs.empty())
		{
			return lcp;
		}

		// 找到最短字符串的长度和id
		for (int i = 0; i < strs.size(); i++)
		{
			if (strs[i].length() < min_slen)
			{
				min_slen = strs[i].length();
				min_sid = i;
			}
		}

		bool bit_same = true;	// 记录该字符是否属于公共前缀
		for (int j = 0; j < min_slen; j++)
		{
			for (int i = 0; i < strs.size()-1; i++)
			{
				if (strs[i][j] != strs[i+1][j])
				{
					bit_same = false;
					break;
				}					
			}
			if (bit_same)
			{
				lcp += strs[min_sid][j];
			}			
		}
		return lcp;
	}
};

class Solution_v2 {
public:
	///@brief	计算一组字符串的最长公共前缀
	///@param	strs	字符串数组
	///@return	返回最长公共前缀
	///@ntoe	从这组字符串中任选一个作为比较对象（比如第一个字符串），如果遇到比它长的且前面都一样，则直接返回较短的字符串；如果遇到二者不一样的，
	//			则返回截断后一致的部分即可。时间复杂度为O(mn)，其中m为公共前缀的长度，n为字符串数组的大小。空间复杂度为O(1)。
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";
        for (int i = 0; i < strs[0].size(); i++) {
            for (int j = 0; j < strs.size() - 1; j++) {
                if (i >= strs[j].size() || strs[j][i] != strs[j+1][i]) {
                    return strs[j].substr(0, i);
                }
            }
        }
        return strs[0];
    }
};

class Solution {
public:
	string longestCommonPrefix(vector<string>& strs) {
		if (strs.empty())	return "";
		for (int i = 0; i != strs[0].size(); i++) {
			for (int j = 0; j != strs.size() - 1; j++) {
				if (i >= strs[j].size() || strs[j][i] != strs[j+1][i])	return strs[j].substr(0, i);
			}
		}
		return strs[0];
	}
};

int main()
{
	vector<string> str_vec;
	for (int i = 0; i < 5; i++)
	{
		string s;
		cin >> s;
		str_vec.push_back(s);
	}

	Solution slt;
	cout << slt.longestCommonPrefix(str_vec) << endl;
	return 0;
}
