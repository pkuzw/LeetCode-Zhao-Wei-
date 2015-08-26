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

class Solution {
public:
	vector<vector<int>> combine(int n, int k) {
		vector<vector<int>> rslt;
		vector<int> combination;
		vector<int> nums;
		for (int i = 0; i != n; i++)
			nums.push_back(i+1);		
		getCombination(nums, rslt, combination, n, k);
		return rslt;
	}
private:
	void getCombination(vector<int> nums, vector<vector<int>>& rslt, vector<int>& combination, int n, int k)
	{
		if (!k)
		{
			rslt.push_back(combination);
			return;
		}
		for (int i = 0; i != nums.size(); i++)
		{
			combination.push_back(nums[i]);
			vector<int> new_nums(nums.begin()+i+1, nums.end());
			getCombination(new_nums, rslt, combination, n-1, k-1);
			combination.pop_back();
		}
	}
};

int main()
{
	int n = 5, k = 2;

	Solution slt;
	vector<vector<int>> rslt = slt.combine(n, k);

	return 0;
}