///@file	Flip Game
///@author	zhaowei
///@date	2016.03.09
///@version	1.0
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
	///@brief	给定一个只有'+', '-'组成的字符串，每一步只能将两个连续的'+'转换成连续的'-'，直到无法再转换为止。
	///@param	s	字符串
	///@return	返回给定字符串的所有可能的下一步转换结果
	///@note	1. 遍历；
	//			2. 找到相连的连续两个'+'，将其转换为'-'，压入结果数组；
	//			3. 时间复杂度为O(n)，空间复杂度为O(k)，其中n为字符串长度，k为连续的两个'+'数量。
	vector<string> generatePossibleNextMoves(string s) {
		vector<string> rslt;
		if (s.size() <= 1)	return rslt;
		for (int i = 0; i < s.size() - 1; i++) {
			if (s[i] == '+' && s[i+1] == '+') {
				string tmp = s;
				tmp[i] = tmp[i+1] = '-';
				rslt.push_back(tmp);
			}
		}
		return rslt;
	}
};

int main () {
	string s = "";
	Solution slt;
	vector<string> rslt = slt.generatePossibleNextMoves(s);
	return 0;
}