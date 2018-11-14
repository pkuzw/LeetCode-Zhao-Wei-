///@file	Combinations
/*
Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:

[
[2,4],
[3,4],
[2,3],
[1,2],
[1,3],
[1,4],
]
*/
///@author	zhaowei
///@date	2015.07.13
///@version	1.0

///@date	2015.08.26
///@version	2.0

///@date	2015.12.07
///@version	2.1

///@date	2016.04.25
///@version	2.2

///@date    November 14, 2018
///@version 3.0

#include <iostream>
#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	计算C(n, k)
	///@param	n	候选元素数目
	///@param	k	选出的元素数目
	///@return	返回所有可能的组合
	///@note	递归：从n个元素中选取k个元素可以先从n个元素中选取一个元素，然后再从剩余n-1个元素中选取k-1个元素。时间复杂度为O(n!)，空间复杂度为O(n^2)。
	vector<vector<int>> combine(int n, int k) {
		vector<int> nums;
		for (int i = 1; i <= n; i++)
		{
			nums.push_back(i);
		}

		getCombination(nums, n, k);
		return rslt;
	}

private:
	vector<vector<int>> rslt;
	vector<int> combination;

	///@brief	计算组合数
	///@param	nums	保存有候选元素的数组
	///@param	n		候选元素的数目
	///@param	k		选出的元素数目
	///@return	无
	void getCombination(vector<int> nums, int n, int k)
	{
		if (k == 0)
		{
			rslt.push_back(combination);
			return;
		}
		for (vector<int>::iterator indx = nums.begin(); indx != nums.end(); indx++)
		{
			combination.push_back(*indx);
			vector<int> new_nums(indx+1, nums.end());
			getCombination(new_nums, n-1, k-1);
			combination.pop_back();
		}
		return;
	}
};

class Solution_v2 {
public:
	///@brief	计算C(n, k)
	///@param	n	候选元素数目
	///@param	k	选出的元素数目
	///@return	返回所有可能的组合
	///@note	1. 递归：从n个元素中选取k个元素可以先从n个元素中选取一个元素，然后再从剩余n-1个元素中选取k-1个元素。
	//			2. 时间复杂度为O(n!)，空间复杂度为O(n^2)。
	vector<vector<int>> combine(int n, int k) {
		vector<vector<int>> rslt;
		vector<int> nums;
		for (int i = 1; i <= n; i++)	nums.push_back(i);
		vector<int> comb;
		getCombination(nums, rslt, comb, n, k);
		return rslt;
	}

private:
	///@brief	递归计算C(n, k)
	///@param	nums	候选元素数组
	///@param	 rslt	结果数组
	///@param	 combination	一个组合
	///@param	n		候选元素个数
	///@param	k		选出的元素个数
	void getCombination(vector<int> nums, vector<vector<int>>& rslt, vector<int>& combination, int n, int k) {
		if (!k) {
			rslt.push_back(combination);
			return;
		}
		for (int i = 0; i < nums.size(); i++) {
			combination.push_back(nums[i]);
			vector<int> new_nums(nums.begin() + i + 1, nums.end());
			getCombination(new_nums, rslt, combination, n - 1, k - 1);
			combination.pop_back();
		}
	}
};

class Solution_v2_2 {
public:
	vector<vector<int>> combine(int n, int k) {
		vector<vector<int>> rslt;
		vector<int> combination;
		vector<int> nums;
		for (int i = 1; i <= n; i++)	nums.push_back(i);
		dfs(nums, rslt, combination, n, k);
		return rslt;
	}

	void dfs(vector<int> nums, vector<vector<int>>& rslt, vector<int>& combination, int n, int k) {
		if (!k) {
			rslt.push_back(combination);
			return;
		}
		for (int i = 0; i != nums.size(); i++) {
			combination.push_back(nums[i]);
			vector<int> new_nums(nums.begin() + i + 1, nums.end());
			dfs(new_nums, rslt, combination, n-1, k-1);
			combination.pop_back();
		}
	}
};

class Solution {
public:
    ///@brief   计算从1到n选k个数的所有可能组合；
    ///@param   n   候选元素数目；
    ///@param   k   选出的元素数目；
    ///@return  返回所有可能的组合，不重不漏。
    ///@note    1. dfs；
    //          2. 设计一个递归辅助函数来帮助计算组合；
    //          3. 时间复杂度为O(n!)？？，空间复杂度为O(1)。
    vector<vector<int>> combine(int n, int k) {
        if (k > n) return rslt;
        vector<int> cmb;
        dfs(cmb, 1, n, k);
        return rslt;
    }
    
    ///@brief   递归辅助函数
    ///@param   cmb 一个正在计算中的有效组合；
    ///@param   base    进入该递归函数时的起始元素；
    ///@param   n       组合应该选出的元素总数；
    ///@param   k       还剩余多少个元素没选出来；
    void dfs(vector<int>& cmb, int base, int n, int k) {
        if (!k) {
            rslt.push_back(cmb);
            return;
        }
        for (int i = base; i <= n; i++) {
            cmb.push_back(i);
            dfs(cmb, i+1, n, k-1);
            cmb.pop_back();
        }
    }
    
    vector<vector<int>> rslt;
};


int main()
{
	int n = 5, k = 3;

	Solution slt;
	vector<vector<int>> rslt = slt.combine(n, k);

	return 0;
}
