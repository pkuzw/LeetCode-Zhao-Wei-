///@file	Remove Invalid Parentheses
///@author	zhaowei
///@date	2016.03.15
///@version	1.0

#include <vector>
#include <string>
using namespace std;

class Solution {
public:
	///@brief	s中包含有左右括号和其他字符，计算出所有去掉最少非法括号的子串集合
	///@param	s	字符串
	///@return	返回子串集合
	///@note	1. 递归；
	//			2. 通过计数器stack来判定当前字符串是否合法，遇到'('自增1，遇到')'自减1；
	//			3. 对于'('比')'多的情形，需要去掉多余的'('，将字符串翻转就好；
	//			4. 为了避免产生重复结果，需要记录最后一个去掉的')'或'('位置。
	vector<string> removeInvalidParentheses(string s) {
		vector<string> rslt;
		const string parenth = "()";
		dfs(rslt, s, parenth, 0, 0);
		return rslt;
	}

	///@brief	递归辅助函数
	///@param	rslt	结果数组
	///@param	s		字符串
	///@param	parenth	括号的自增或自减映射
	///@param	last_i	字符串处理的下标
	///@param	last_j	最后一个删掉的'('或者')'位置
	void dfs(vector<string>& rslt, string s, const string parenth, int last_i, int last_j) {
		for (int i = last_i, stack = 0; i != s.size(); i++) {
			if (s[i] == parenth[0])	stack++;
			if (s[i] == parenth[1])	stack--;
			if (stack >= 0)	continue;
			for (int j = last_j; j <= i; j++) {
				if (s[j] == parenth[1] && (j == last_j || s[j-1] != parenth[1]))	 {	//	j为第一个')'或'('				
					string tmp = s.substr(0, j) + s.substr(j+1);
					dfs(rslt, tmp, parenth, i, j);
				}
			}
			return;
		}
		string revr_s(s.rbegin(), s.rend());
		if (parenth[0] == '(') {
			const string revr_parenth = ")(";
			dfs(rslt, revr_s, revr_parenth, 0, 0);
		}
		else	rslt.push_back(revr_s);
		return;
	}
};

int main() {
	string s = "((()";
	Solution slt;
	vector<string> rslt = slt.removeInvalidParentheses(s);
	return 0;
}