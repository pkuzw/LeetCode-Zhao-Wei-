///@file	Factor Combinations
///@author	zhaowei
///@date	2016.01.27
///@version	1.0

#include <vector>
using namespace std;

class Solution {
public:
	///@brief	计算n的所有因式分解
	///@param	n	正整数n
	///@return	返回其所有可能的因式分解，在每种分解中，因子按照升序排列
	///@note	1. dfs；2. TLE
	vector<vector<int>> getFactors(int n) {
		if (n == 1)	return rslt;		
		vector<int> factor;
		dfs(factor, n);
		return rslt;
	}

	///@brief	递归辅助函数
	///@param	factor	一个分解
	///@param	n		待分解数
	void dfs(vector<int>& factor, int n) {
		for (int i = 2; i * i <= n; i++) {		
			for (int j = i; j < n; j++) {
				if (i * j == n) {
					if (!factor.empty() && i < factor.back())	continue;	//	保持分解因子的升序
					factor.push_back(i);
					factor.push_back(j);
					rslt.push_back(factor);	//	完成一次分解
					factor.pop_back();
					dfs(factor, j);
					factor.pop_back();
				}
			}
		}
	}

	vector<vector<int>> rslt;
};

int main() {
	Solution slt;	
	vector<vector<int>> rslt = slt.getFactors(100);
	return 0;
}