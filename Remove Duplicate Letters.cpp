///@file	Remove Duplicate Letters
///@author	zhaowei
///@date	2016.03.21
///@version	1.0

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	///@brief	移除字符串中的多余字符，使得字符串最简，且是所有可能最简字符串中按照字母顺序排序最靠前的那一个。
	///@param	s	字符串
	///@return	返回结果字符串
	///@note	1. 迭代；
	//			2. 维护两个数组，一个数组用于保存字符串中字符的出现次数，另一个用来保存该字符是否已经出现在结果数组中；
	//			3. 如果当前字符比结果字符串的末尾字符小，且它的出现次数不为0，则一直将结果字符串从尾部弹出，然后压入当前字符；
	//			4. 时间复杂度为O(n)，空间复杂度为O(k)，k为字符的种类数目。
	string removeDuplicateLetters(string s) {
		vector<int> count(26, 0);
		vector<bool> visited(26, false);
		string rslt = "";
		if (s.empty())	return rslt;
		for (int i = 0; i != s.size(); i++)	count[s[i]-'a']++;
		for (int i = 0; i != s.size(); i++) {
			count[s[i]-'a']--;
			if (visited[s[i]-'a'])	continue;
			while (!rslt.empty() && rslt.back() > s[i] && count[rslt.back()-'a'] > 0) {
				visited[rslt.back()-'a'] = false;
				rslt.pop_back();				
			}
			rslt.push_back(s[i]);
			visited[s[i]-'a'] = true;
		}
		return rslt;
	}
};

int main() {
	string rslt;
	Solution slt;
	string s = "cbacdcbc";
	rslt = slt.removeDuplicateLetters(s);
	return 0;	
}