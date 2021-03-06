///@file	Factor Combinations
///@author	zhaowei
///@date	2016.01.27
///@version	1.0
///@version	1.1

#include <vector>
using namespace std;

class Solution_tle {
public:
	///@brief	计算n的所有因式分解
	///@param	n	正整数n
	///@return	返回其所有可能的因式分解，在每种分解中，因子按照升序排列
	///@note	1. dfs；2. TLE
	vector<vector<int>> getFactors(int n) {
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

class Solution_v1 {
public:
	///@brief	计算n的所有因式分解
	///@param	n	正整数n
	///@return	返回其所有可能的因式分解，在每种分解中，因子按照升序排列
	///@note	1. dfs
	vector<vector<int>> getFactors(int n) {
		vector<int> factor;
		dfs(factor, 2, n);
		return rslt;
	}

	///@brief	递归辅助函数
	///@param	factor	一个分解
	///@param	bottom	已分解的因子中的最大值
	///@param	n		待分解数
	void dfs(vector<int>& factor, int bottom, int n) {
		for (int i = bottom; i * i <= n; i++) {
			if (n % i == 0) {
				vector<int> new_factor = factor;	//	不直接用factor的原因是后续还需要继续分解
				new_factor.push_back(i);
				dfs(new_factor, i, n / i);
				new_factor.push_back(n / i);
				rslt.push_back(new_factor);
			}
		}
	}

	vector<vector<int>> rslt;
};

class Solution {
public:
	vector<vector<int>> getFactors(int n) {
		vector<int> factors;
		dfs(factors, 2, n);
		return rslt;
	}

	void dfs(vector<int>& factors, int bottom, int n) {
		for (int i = bottom; i * i <= n; i++) {
			if (n % i == 0) {
				vector<int> new_factors = factors;
				new_factors.push_back(i);
				dfs(new_factors, i, n / i);
				new_factors.push_back(n / i);
				rslt.push_back(new_factors);
			}
		}
	}

	vector<vector<int>> rslt;
};

int main() {
	Solution_tle slt_tle;
	vector<vector<int>> r_tle = slt_tle.getFactors(100);
	Solution slt;	
	vector<vector<int>> rslt = slt.getFactors(100);
	return 0;
}