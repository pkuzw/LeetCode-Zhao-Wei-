///@brief	Write a function to find the longest common prefix string amongst an array of strings.
///@author	zhaowei
///@date	2015.06.03
///@version	1.0

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
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
