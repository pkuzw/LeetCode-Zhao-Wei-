///@file	Minimum Window Substring
/*
Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"
Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the emtpy string "".

If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S.
*/
///@author	zhaowei
///@date	2015.07.17
///@version	1.0

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <deque>

using namespace std;

class Solution {
public:
	///@brief	计算字符串s包含字符串t的最小子串
	///@param	s	字符串s
	///@param	t	字符串t
	///@return	返回s中包含t的最短子串
	///@note	用两个双端队列来存储已经匹配的字符串字符及其下标。当找到一个字符串时，则弹出队首元素，然后从当前队尾元素的后一个元素开始
	//			继续遍历。时间复杂度为O(n)，空间复杂度为O(m)。在何时终止有问题。
	string minWindow(string s, string t) {
		int min_len = INT_MAX;	//	最短子串长度
		int min_end = 0;		//	最短子串的终止下标
		deque<char> deq_str;		//	存储当前已经匹配的字符串
		deque<int>	deq_indx;		//	记录每个匹配字符的下标
		int start_indx = 0;		//	每个匹配的字符串的起始下标
		for (int i = start_indx; i < s.length(); i++)
		{
			char tmp = NULL;	//	当前匹配时缺少的字符
			if (deq_str.size() < t.length())
			{
				if (existChar(s[i]))
				{
					if (deq_str.empty() || s[i] == tmp)
					{
						deq_str.push_back(s[i]);
						deq_indx.push_back(i);
					}
				}
			}
			else if (deq_str.size() == t.length())
			{
				if (min_len > i - start_indx)
				{
					min_len = i - start_indx;
					min_end = i - 1; 
				}			
				deq_indx.pop_front();
				start_indx = deq_indx.back()+1;	//新的匹配起点

				tmp = deq_str.front();		//	需要匹配的新字符
				deq_str.pop_front();								
			}
		}
		string rslt = s.substr(min_end-min_len+1, min_len);
		return rslt;
	}
private:
	///@brief	判断某字符是否是字符串中的一个字符
	///@param	ch	字符	
	///@return	如果该字符是字符串中的一个，则返回true；否则返回false
	///@note	利用哈希表来存储字符串中的每个字符，小浩浩说C++中的unordered_map就是哈希表。这样使得查询效率提高到O(1)。
	bool existChar(const char ch)
	{
		if (char_app[ch] > 0)
			return true;		
		else
			return false;
	}

	///@brief	初始化字符串t的每个字符与其所出现的次数组成的哈希表
	///@param	t	字符串t
	///@return	无
	void initMap(const string t)
	{
		for (int i = 0; i != t.length(); i++)
		{
			char_app[t[i]]++;
		}
		return;
	}

	unordered_map<char, int> char_app;
};

int main()
{
	return 0;
}