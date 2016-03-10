///@file	Flip Game II
///@author	zhaowei
///@date	2016.03.10
///@version	1.0

//discuss中可以通过dp改进到O(n^2)的时间复杂度

#include <string>

using namespace std;

class Solution {
public:
	///@brief	给定一个只包含'+', '-'的字符串，两位玩家轮流出手，每次只能将连续的2个'+'修改为2个'-'，在给定初始字符串的情形下，判断先手是否会必胜
	///@param	s	字符串
	///@return	如果先手必胜，则返回true；否则返回false
	///@note	1. 回溯；
	//			2. 尝试所有可能的先手，如果先手之后的后手没有赢的可能（递归），则先手胜；
	//			3. 时间复杂度为O(2^n)
	bool canWin(string s) {
		if (s.length() < 2)	return false;
		return helper(s, s.length());
	}

	///@brief	辅助递归函数
	///@param	s	字符串
	///@param	len	字符串长度
	///@return	返回当前s先手是否必胜
	bool helper(string s, const int len) {
		for (int i = 0; i != len - 1; i++) {
			if (s[i] == '+' && s[i+1] == '+') {
				s[i] = s[i+1] = '-';				
				bool wins = !helper(s, len);
				s[i] = s[i+1] = '+';
				if (wins)	return true;
			}			
		}
		return false;
	}
};

int main() {
	string s = "+++++";
	Solution slt;
	bool rslt = slt.canWin(s);
	return 0;
}