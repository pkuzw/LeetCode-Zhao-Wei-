///@file	Strobogrammatic Number II
///@author	zhaowei
///@date	2016.01.11
///@version	1.0

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
	///@brief	找到所有长度为n的旋转回文数字串
	///@param	n	长度
	///@return	返回所有长度为n的旋转回文数字串
	///@note	1. dfs；2. 利用左右两个边界指针来递归寻找满足条件的旋转回文字符串；3. 当只有一个字符时，只能选0, 1, 8；4. 首尾字符不能为0；
	//			5. 另外，当压入的新字符串和上一个压入的字符串相同时，不要压入。
	vector<string> findStrobogrammatic(int n) {
		string num(n, '*');
		vector<string> rslt;
		if (n <= 0)	return rslt;
		const char hash_tbl[5][2] = {{'0', '0'}, {'1', '1'}, {'6', '9'}, {'8', '8'}, {'9', '6'}};
		helper(num, 0, n - 1, hash_tbl, rslt);
		return rslt;
	}

	///@brief	dfs辅助函数
	///@param	num		旋转回文数字串
	///@param	start	回文子串的起始下标
	///@param	end		回文子串的终止下标
	///@param	hash_tbl	旋转回文字对
	///@param	rslt	结果数组
	void helper(string& num, int start, int end, const char hash_tbl[5][2], vector<string>& rslt) {
		if (start > end) {
			if (rslt.empty() || num != rslt.back())
				rslt.push_back(num);
			return;
		}
		for (int i = 0; i != 5; i++) {
			if (!start && end - start >= 1 && hash_tbl[i][0] == '0')		continue;	//首尾字符不能为'0'
			if (start == end) {
				if (i == 0 || i == 1 || i == 3)
					num[start] = hash_tbl[i][0];
			}
			else {
				num[start] = hash_tbl[i][0];
				num[end] = hash_tbl[i][1];
			}
			helper(num, start + 1, end - 1, hash_tbl, rslt);
		}
	}
};

int main() {
	Solution slt;
	vector<string> rslt = slt.findStrobogrammatic(2);
	return 0;
}