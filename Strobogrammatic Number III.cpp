///@file	Strobogrammatic Number III
///@author	zhaowei
///@date	2016.01.13
///@version	1.0

///@date	2016.02.26
///@version	1.1

#include <vector> 
#include <string>

using namespace std;

class Solution_v1 {
public:
	///@brief	计算在指定范围内[low, high]的旋转回文数的个数
	///@param	low, high	范围边界
	///@return	返回旋转回文数的数目
	///@note	1. 调用"Strobogrammatic Number II"中的算法，来计算不同位数的旋转回文数个数；
	//			2. 对于位数大于low，小于high的所有可能，直接并入结果，不需要逐个检查；在检查时需要转换为整型变量来判断，不要用字符串大小运算符；
	//			3. 注意在转换为整型变量时要转换为long long，否则会int型越界。
	int strobogrammaticInRange(string low, string high) {
		int snum = 0, m = low.size(), n = high.size();
		for (int i = m; i <= n; i++) {
			vector<string> svec = findStrobogrammatic(i);
			if (i > m && i < n)	{
				snum += svec.size();
				continue;
			}
			for (int j = 0; j < svec.size(); j++) {
				long long llhigh = stoll(high), lllow = stoll(low), llsvec = stoll(svec[j]);
				if (llsvec > INT_MAX)	
					break;
				if (llsvec <= llhigh && llsvec >= lllow)	
					snum++;
			}
		}
		return snum;
	}

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

class Solution {
public:
	int strobogrammaticInRange(string low, string high) {
		int m = low.size(), n = high.size(), rslt = 0;
		long long llhigh = stoll(high), lllow = stoll(low);
		for (int i = m; i <= n; i++) {
			vector<string> nums = findStrobogrammaticNum(i);
			if (i < n && i > m) {
				rslt += nums.size();
				continue;
			}
			for (int j = 0; j != nums.size(); j++) {
				long long k = stoll(nums[j]);
				if (k > INT_MAX)	break;
				else if (k <= llhigh && k >= lllow)	rslt++;
			}
		}
		return rslt;
	}

	vector<string> findStrobogrammaticNum(int n) {
		const char hash_tbl[5][2] = {{'0', '0'}, {'1', '1'}, {'6', '9'}, {'8', '8'}, {'9', '6'}};
		vector<string> rslt;
		string num(n, '$');
		dfs(rslt, num, 0, n - 1, hash_tbl);
		return rslt;
	}

	void dfs(vector<string>& rslt, string& num, int start, int end, const char hash_tbl[5][2]) {
		if (start > end) {
			if (rslt.empty() || num != rslt.back())	rslt.push_back(num);
			return;
		}
		for (int i = 0; i != 5; i++) {
			if (!start && end - start >= 1 && !i)	continue;
			if (start == end) {
				if (i == 0 || i == 1 || i == 3)	num[start] = hash_tbl[i][0];
			}
			else {
				num[start] = hash_tbl[i][0];
				num[end] = hash_tbl[i][1];
			}
			dfs(rslt, num, start + 1, end - 1, hash_tbl);
		}
	}
};

int main() {
	string low = "0", high = "2147483647";
	Solution slt;
	int rslt = slt.strobogrammaticInRange(low, high);
	Solution_v1 s1;
	int r1 = s1.strobogrammaticInRange(low, high);
	return 0;
}