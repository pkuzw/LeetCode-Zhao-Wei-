///@file	Reverse String
///@author	zhaowei
///@date	2016.04.22
///@version	1.0

#include <string>
using namespace std;

class Solution {
public:
	///@brief	将一个string进行翻转
	///@param	s	字符串
	///@return	返回翻转后的字符串
	string reverseString(string s) {
		if (s.empty())	return s;
		for (int i = 0; i < s.length() / 2; i++)	swap(s[i], s[s.size()-1-i]);
		return s;
	}
};

int main() {
	string s = "hell";
	Solution slt;
	string rslt = slt.reverseString(s);
	return 0;
}