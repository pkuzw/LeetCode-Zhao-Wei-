﻿///@file	Subsets
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

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
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

int main()
{
	vector<int> nums;
	nums.push_back(1);
	nums.push_back(2);
	nums.push_back(3);
	nums.push_back(4);
	nums.clear();
	Solution slt;
	
	vector<vector<int>> rslt = slt.subsets(nums);
	cout << "Subsets' number: " << rslt.size() << endl;
	cout << "Subsets: " << endl;
	for (int i = 0; i != rslt.size(); i++)
	{
		for (int j = 0; j != rslt[i].size(); j++)
		{
			cout << rslt[i][j] << ' ';
		}
		cout << endl;
	}
	return 0;
}