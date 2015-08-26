///@file	Subsets II
/*
Given a collection of integers that might contain duplicates, nums, return all possible subsets.

Note:
Elements in a subset must be in non-descending order.
The solution set must not contain duplicate subsets.
For example,
If nums = [1,2,2], a solution is:

[
[2],
[1],
[1,2,2],
[2,2],
[1,2],
[]
]
*/
///@author	zhaowei
///@date	2015.07.20
///@version	1.0

///@date	2015.08.26
///@version	2.0

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution_v1 {
public:
	///@brief	给定一个包含有重复元素的数组，计算其所有可能的子集，要求不能有重复子集
	///@param	nums	含有重复元素的数组
	///@return	返回所有子集
	/* @note	利用"Subsets"中的算法来计算可能的子集。先排序，然后遍历数组，调用getCombination()，如果该元素与上一个元素重复，
				那么就进行下一层循环，否则将当前元素选入组合。时间复杂度为O(2^n)，空间复杂度为O(n^2)
	*/
	vector<vector<int>> subsetsWithDup(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		for (int i = 0; i <= nums.size(); i++)
		{
			getCombination(nums, nums.size(), i);	//	依次遍历C(n, k)
		}
		return rslt;
	}

private:	
	///@brief	计算组合数
	///@param	nums	无重复元素的的数组
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
			if (indx == nums.begin() || *indx != *(indx-1))	//	当前元素为候选数组中的第一个元素或者与前一个元素不重复，则选择当前元素
			{
				combination.push_back(*indx);
			}
			else	//	否则进行下一个循环
			{
				continue;
			}
			
			vector<int> new_nums(indx+1, nums.end());
			getCombination(new_nums, n-1, k-1);
			combination.pop_back();
		}
		return;
	}

	vector<vector<int>> rslt;	//	子集集合
	vector<int> combination;	//	一个子集
};

class Solution {
public:
	vector<vector<int>> subsetsWithDup(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		vector<vector<int>> rslt;
		vector<int> combination;
		for (int i = 0; i <= nums.size(); i++)
			getCombinations(nums, nums.size(), i, combination, rslt);
		return rslt;
	}
private:
	void getCombinations(vector<int> nums, int n, int k, vector<int>& combination, vector<vector<int>>& rslt)
	{
		if (!k)
		{
			rslt.push_back(combination);
			return;
		}
		for (int i = 0; i != nums.size(); i++)
		{
			if (i == 0 || nums[i] != nums[i-1])	combination.push_back(nums[i]);
			else continue;
			vector<int> new_nums(nums.begin()+i+1, nums.end());
			getCombinations(new_nums, n-1, k-1, combination, rslt);
			combination.pop_back();
		}
	}
};

int main()
{
	vector<int> nums;
	nums.push_back(1);
	nums.push_back(1);
	nums.push_back(2);
	nums.push_back(2);
	nums.push_back(2);
	nums.push_back(3);

	Solution slt;
	vector<vector<int>> rslt = slt.subsetsWithDup(nums);
	
	Solution_v1 slt_v1;
	rslt = slt_v1.subsetsWithDup(nums);
	return 0;
}