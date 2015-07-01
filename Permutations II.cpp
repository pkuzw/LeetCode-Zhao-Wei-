﻿///@file	Permutations
/*
			Given a collection of numbers that might contain duplicates, return all possible unique permutations.

			For example,
			[1,1,2] have the following unique permutations:
			[1,1,2], [1,2,1], and [2,1,1].
*/
///@author	zhaowei
///@date	2015.06.25
///@version	1.0	LeetCode OJ报TLE

///@author  zhaowei
///@date    2015.06.27
///@version 2.0

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	///@brief	给定候选元素数组，计算所有可能的组合。如果候选数组中有重复元素，需要排除掉重复的组合
	///@param	nums	候选元素数组
	///@return	返回没有重复组合的集合
	///@note	在Permutation递归的基础上，增加一个排序操作和在数组遍历下标选择时去掉重复元素。这样就能够排除掉重复出现的可能组合。时间复杂度还是O(n!), 空间复杂度是O(n^2)
	///@author	zhaowei
	///@date	2015.06.27
	vector<vector<int>> permuteUnique(vector<int>& nums)
	{
        sort(nums.begin(), nums.end()); //先排序，使重复元素在一起。
		vector<int> ivec;
		if (nums.empty())	
		{
			return rslt;
		}
		getPermutateUnique(nums, ivec);
		return rslt;
	}
	

	///@brief	计算去重的所有组合
	///@param	nums	原始数组
	///@param	residue	可能的一种组合
	///@return	void
	///@note	我的想法是每次拿掉一个元素，将剩余的元素组成一个新数组，并且记录下当前拿掉的是第几个元素；当新数组为空时需要得到一个可能的组合；
	//			此时返回上一级递归，再拿掉下一个元素。依次类推。通过去重函数，再加入新的组合时先判断是否已经存在该组合。
	void getPermutateUnique(vector<int> nums, vector<int>& residue)
	{
		if (nums.empty())	//	如果数组为空，则递归结束
		{
            rslt.push_back(residue);	//	将一种可能的组合加入结果二维数组
			return;
		}
		int indx = 0;	//	标记当前选到的元素下标
		while (indx != nums.size())	//	如果当前元素不是数组中的最后一个元素，则进入循环
		{
			vector<int> tmp;	//	用来保存除了当前选择的元素，剩余元素组成的数组
			residue.push_back(nums[indx]);	//	将当前元素加入结果
			for (int i = 0; i != nums.size(); i++)	//	生成剩余元素组成的数组
			{
				if (i == indx)
				{
					continue;
				}
				tmp.push_back(nums[i]);
			}
			getPermutateUnique(tmp, residue);		//	递归
			residue.pop_back();				//	将结果中的元素弹出
            
            indx++;
            while (nums[indx] == nums[indx-1] && indx < nums.size())    //	如果元素重复，不要选择，直到不重复为止
                indx++;
            
		}	
		return;
	}
private:
	vector<vector<int>> rslt;	//	结果数组
};

int main()
{
	vector<int> test;
	test.push_back(2);
	test.push_back(2);
	test.push_back(1);
    test.push_back(1);
	Solution slt;

	vector<vector<int>> rslt = slt.permuteUnique(test);
	for (int i = 0; i != rslt.size(); i++)
	{
		for (int j = 0; j != rslt[i].size(); j++)
		{
			cout << rslt[i][j] << ' ';
		}
		cout << endl;
	}

	cout << rslt.size() << endl;
	return 0;
}