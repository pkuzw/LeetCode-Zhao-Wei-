///@file	Subsets
/*
Given a set of distinct integers, nums, return all possible subsets.

Note:
Elements in a subset must be in non-descending order.
The solution set must not contain duplicate subsets.
For example,
If nums = [1,2,3], a solution is:

[
[3],
[1],
[2],
[1,2,3],
[1,3],
[2,3],
[1,2],
[]
]
*/
///@author	zhaowei
///@date	2015.07.14
///@version	1.0

///@date	2015.08.26
///@version	2.0

///@date	2015.12.07
///@version	2.1

///@date	2016.04.29
///@version	2.2

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution_v1 {
public:
	///@brief	给定数组，计算其所有可能的子集
	///@param	nums	数组
	///@return	返回其所有的子集，子集中元素应该按照非降序排列
	///@note	先对数组进行升序排序，然后利用上一题"Combinations"中计算组合数C(n, k)的函数getCombination()，令k = 0...n即可。时间复杂度为O(2^n)，空间复杂度为O(n^2)。
	vector<vector<int>> subsets(vector<int>& nums) {
		sort(nums.begin(), nums.end());	//	根据题意，对nums先进行升序排序
		for (int i = 0; i <= nums.size(); i++)
		{
			getCombination(nums, nums.size(), i);	//	依次遍历C(n, k)
		}
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
	///@brief	给定数组，计算其所有可能的子集
	///@param	nums	数组
	///@return	返回其所有的子集，子集中元素应该按照非降序排列
	///@note	1. 类似"Combination"中的思路，先对数组进行排序，然后所有可能的C(n, k)即可。2. 时间复杂度为O(2^n)。
	vector<vector<int>> subsets(vector<int>& nums) {
		vector<vector<int>> rslt;
		vector<int> comb;
		sort(nums.begin(), nums.end());
		for (int i = 0; i <= nums.size(); i++)	getCombinations(nums, rslt, comb, nums.size(), i);
		return rslt;
	}
private:
	///@brief	计算组合数
	///@param	nums	保存有候选元素的数组
	///@param	n		候选元素的数目
	///@param	k		选出的元素数目
	void getCombinations(vector<int>& nums, vector<vector<int>>& rslt, vector<int>& combination, int n, int k) {
		if (!k) {
			rslt.push_back(combination);
			return;
		}
		for (int i = 0; i != nums.size(); i++) {
			combination.push_back(nums[i]);
			vector<int> new_nums(nums.begin() + i + 1, nums.end());
			getCombinations(new_nums, rslt, combination, n - 1, k - 1);
			combination.pop_back();
		}
	}
};

class Solution {
public:
	vector<vector<int>> subsets(vector<int>& nums) {
		vector<vector<int>> rslt;
		vector<int> combination;
		sort(nums.begin(), nums.end());
		for (int k = 0; k <= nums.size(); k++) dfs(nums, rslt, combination, nums.size(), k);
		return rslt;
	}

	void dfs(vector<int> nums, vector<vector<int>>& rslt, vector<int> combination, int n, int k) {
		if (!k) {
			rslt.push_back(combination);
			return;
		}
		for (int i = 0; i != nums.size(); i++) {
			combination.push_back(nums[i]);
			vector<int> new_nums(nums.begin() + i + 1, nums.end());
			dfs(new_nums, rslt, combination, n - 1, k - 1);
			combination.pop_back();
		}		
	}
};

int main()
{
	vector<int> nums;
	nums.push_back(1);
	nums.push_back(2);
	nums.push_back(3);
	nums.push_back(4);
	Solution_v1 slt_v1;
	vector<vector<int>> rslt = slt_v1.subsets(nums);

	Solution slt;	
	rslt = slt.subsets(nums);
	return 0;
}