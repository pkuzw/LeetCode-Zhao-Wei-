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
///@date	2015.07.18
///@version	1.1

///@date	2015.08.26
///@version	2.0

///@date	2015.12.07
///@version	2.1

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <deque>
#include <queue>

using namespace std;

class Solution_v1 {
public:
	///@brief	计算字符串s包含字符串t的最小子串
	///@param	s	字符串s
	///@param	t	字符串t
	///@return	返回s中包含t的最短子串
	///@note	用两个双端队列来存储已经匹配的字符串字符及其下标。当完成一次字符串匹配时，则弹出队首元素，清空两个队列和哈希表，
	//			然后然后将搜索的起始位置更新为队首元素的后一个元素，直到匹配的起始下标小于等于总长度减去待匹配字符串的长度时，
	//			循环停止。在匹配的过程中，当字符不匹配时，要及时更新起始下标的值。时间复杂度为O(n^2)，空间复杂度为O(m)。OJ报TLE。
	string minWindow_O_n2(string s, string t) {
		string rslt;
		if (s.length() < t.length())
		{
			return rslt;
		}
		int min_len = INT_MAX;	//	最短子串长度
		int min_end = 0;		//	最短子串的终止下标
		deque<char> deq_str;		//	存储当前已经匹配的字符串
		deque<int>	deq_indx;		//	记录每个匹配字符的下标
		int start_indx = 0;		//	每个匹配的字符串的起始下标

		initMap(t);

		for (int i = start_indx; start_indx <= s.length()-t.length(); i++)
		{
			if (deq_str.size() < t.length())
			{
				if (i < s.length() && existChar(s[i]))
				{
					deq_str.push_back(s[i]);
					deq_indx.push_back(i);
				}
				else if (i >= s.length() || deq_str.empty())	//	注意检查下标i不要超过字符串的总长度
					start_indx++;
			}
			else if (deq_str.size() == t.length())
			{
				if (min_len > i - start_indx)
				{
					min_len = i - start_indx;
					min_end = i - 1; 
				}			
				start_indx = deq_indx.front()+1;	//新的匹配起点
				deq_indx.clear();
				deq_str.clear();
				char_app.clear();
				initMap(t);
				i = start_indx-1;
			}
		}
		if (min_len == INT_MAX)
		{
			return rslt;
		}
		rslt = s.substr(min_end-min_len+1, min_len);
		return rslt;
	}

	///@brief 计算字符串s包含t的最小子串
	///@param	s	字符串s
	///@param	t	字符串t
	///@return	返回s中包含t的最短子串
	///@note	用两个整型数组来存储匹配字符串中出现的字符次数src_cnt和已经匹配的字符次数found_cnt。再用一个队列来保存在字符串s中所有属于
	//			匹配字符串的字符下标。用一个整型变量来保存已经匹配的字符数目，如果匹配的字符数目等于t的字符串长度，则找到了一个窗口。当找到
	//			了一个匹配窗口时，则尽量将窗口缩小：1. 当前窗口的起始元素不属于字符串t中的字符或者即使删去当前窗口的起始元素，也能够保证后续
	//			窗口中的同一个字符总数大于等于t中该字符的出现次数(found_cnt[s[k]] >= src_cnt[s[k]])。将窗口缩小到最小后，就可以来比较上一次
	//			存储的窗口大小，如果比上一次的小，则将其长度和起始下标存储起来。
	//			时间复杂度为O(n)，空间复杂度为O(n)。
	string minWindow(string s, string t)
	{
		int src_cnt[256] = {0};	//	字符串t中的每个字符的出现次数
		int found_cnt[256] = {0};	//	字符串s中已经匹配的字符个数
		queue<int> que;	//	存储字符串s中属于字符串t的字符下标
		int has_found = 0;	//	存储已经匹配了多少个字符
		for (int i = 0; i != t.length(); i++)
		{
			src_cnt[t[i]]++;
		}

		int win_start = -1;	//	匹配窗口的起始下标
		int win_end = s.length();	//	匹配窗口的终止下标

		for (int i = 0; i != s.length(); i++)
		{
			if (src_cnt[s[i]] != 0)	//	如果当前字符属于t中字符
			{
				que.push(i);	//	进入队列
				found_cnt[s[i]]++;	//	寻找到的该字符次数自增1
				if (found_cnt[s[i]] <= src_cnt[s[i]])	//	如果该字符的出现次数小于t中的出现次数，则认为又找到了一个匹配字符
				{
					has_found++;					
				}

				if (has_found == t.length())	//	如果已经匹配
				{

					int k = que.front();	//	匹配的第一个字符下标

					do 
					{
						k = que.front();	//	找到匹配字符串的起始下标
						que.pop();			//	出队列
						found_cnt[s[k]]--;	//	找到的次数自减1
					} while (src_cnt[s[k]] <= found_cnt[s[k]]);		// 将窗口缩减至最小			

					if (win_end - win_start > i - k)		//	找到最小窗口
					{
						win_start = k;
						win_end = i;
					}
					has_found--;		//	匹配的总字符数自减1
				}
			}			
		}
		return win_start == -1 ? "" : s.substr(win_start, win_end-win_start+1);
	}
private:
	///@brief	判断某字符是否是字符串中的一个字符，如果存在则将该map中的对应次数自减1
	///@param	ch	字符	
	///@return	如果该字符是字符串中的一个，则返回true；否则返回false
	///@note	利用哈希表来存储字符串中的每个字符，小浩浩说C++中的unordered_map就是哈希表。这样使得查询效率提高到O(1)。
	bool existChar(const char ch)
	{
		if (char_app[ch] > 0)
		{
			char_app[ch]--;	//	匹配过一次后，相应的出现次数应该自减1
			return true;		
		}
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

	unordered_map<char, int> char_app;		//	在t字符串中字符的出现次数	
};

class Solution {
public:
	///@brief	给定两个字符串s和t，在s中寻找包含t的所有字符的最小子串
	///@param	s	源字符串
	///@param	t	目标字符串
	///@return	返回包含所有t中字符的最小子串
	///@note	1. 利用hash map来保存t中的字符数目；2. 在s中进行遍历，用左右两个指针来控制子串的范围；3. 在遍历时如果找到一个与t中字符匹配的
	//			字符，则将hash map中的该字符数目自减1，如果值仍然不小于0，则说明可以组成子串中的一部分，总的计数器cnt自增1；4. 当计数器cnt
	//			的值等于t的长度时，说明找到了一个窗口，先比较原来的子串长度与当前窗口的长度，如果前者更大，则更新之；5. 然后要尽可能的缩短当前
	//			窗口，不断尝试移动窗口左指针，当窗口左指针所指向的字符属于hash map，则将对应的哈希值自增1，如果哈希值大于0，则将计数器自减1，说明有一个
	//			字符失配，需要再次找到能够匹配它的字符；6. 时间复杂度为O(m)，空间复杂度为O(n)，其中n为t的长度，m为s的长度。
	string minWindow(string s, string t) {
		if (s.size() < t.size())	return "";
		unordered_map<char, int> ht;
		for (int i = 0; i != t.size(); i++)	ht[t[i]]++;
		int left = 0, cnt = 0, len = s.size() + 1;
		string rslt = "";
		for (int right = 0; right < s.size(); right++) {
			if (ht.find(s[right]) != ht.end()) {
				ht[s[right]]--;
				if (ht[s[right]] >= 0)	cnt++;
			}
			while (cnt == t.size()) {	//	不断尝试缩小左边界
				if (len > right - left + 1) {
					len = right - left + 1;
					rslt = s.substr(left, len);
				}
				if (ht.find(s[left]) != ht.end()) {
					ht[s[left]]++;
					if (ht[s[left]] > 0)	cnt--;
				}
				left++;
			}
		}
		return rslt;
	}
};

int main()
{
	string s = "ADOBECODEBANC", t = "ABBC";
	Solution slt;
	string rslt = slt.minWindow(s, t);
	return 0;
}