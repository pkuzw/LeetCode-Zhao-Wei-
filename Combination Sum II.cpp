﻿///@file	Combination Sum II
/*
			Given a collection of candidate numbers (C) and a target number (T),
			find all unique combinations in C where the candidate numbers sums to T.

			Each number in C may only be used once in the combination.

			Note:
			All numbers (including target) will be positive integers.
			Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
			The solution set must not contain duplicate combinations.
			For example, given candidate set 10,1,2,7,6,1,5 and target 8, 
			A solution set is: 
			[1, 7] 
			[1, 2, 5] 
			[2, 6] 
			[1, 1, 6] 
*/
///@author	zhaowei
///@date	2015.06.19
///@version 1.0

///@date    2015.09.04
///@version 1.1

///@date	2015.09.24
///@version	1.2

///@date	2016.04.09
///@version	1.3

///@date    October 15, 2018
///@version 1.4
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution_v1
{
public:
	///@brief	计算所有和为指定值的所有可能组合
	///@param	candidates	候选值数组
	///@param	target	目标值
	///@return	返回和为指定值的所有可能组合集合
	///@note	与上一题类似。但此题要求候选数组中的元素只能出现一次，故需要增加额外判断。剩余都是类似的，利用回溯来枚举所有的可能组合。
	//			时间复杂度为O(n^2)，空间复杂度为O(1).
	///@author	zhaowei
	///@date	2015.06.19
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
	{
		sort(candidates.begin(), candidates.end());
		vector<int> combination;
		calCombination2(candidates, combination, 0, target);
		return rslt;
	}

	void calCombination2(vector<int>& candidates, vector<int>& combination, int index, int target)
	{
		if (target == 0)
		{
			rslt.push_back(combination);
			return;
		}

		for (int i = index; i < candidates.size() && target >= candidates[i]; i++)
		{
			if (i > index && candidates[i] == candidates[i-1])	//	对于结果中可能出现的重复组合进行排除。
			{
				continue;
			}
			combination.push_back(candidates[i]);
			calCombination2(candidates, combination, i+1, target-candidates[i]);		//	此处第三个参数是i+1，而非i。因为每个候选值只能出现一次
			combination.pop_back();
		}
	}
private:
	vector<vector<int>> rslt;
};

class Solution_v1_1 {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> rslt;
        vector<int> cmb;
        sort(candidates.begin(), candidates.end());
        dfs(rslt, cmb, candidates, 0, target);
        return rslt;
    }
    
    void dfs(vector<vector<int>>& rslt, vector<int>& cmb, vector<int>& candidates, int indx, int target){
        if (!target)    rslt.push_back(cmb);
        else{
            for (int i = indx; i != candidates.size() && target >= candidates[i]; i++){
                if (i > indx && candidates[i] == candidates[i - 1]) continue;
                cmb.push_back(candidates[i]);
                dfs(rslt, cmb, candidates, i + 1, target - candidates[i]);
                cmb.pop_back();
            }
        }
    }
};

class Solution {
public:
    ///@brief   给定一个整型数组和一个指定值，找到所有和为指定值的组合，其中数组中的元素每个只能使用1次，数组元素可以重复出现。
    ///@param   candidates  整型数组
    ///@param   target      目标值
    ///@return  返回所有可能的组合。
    ///@note    1. 此题与Combination Sum很类似，区别在于前者的候选数组元素可以有重复元素，但是每个元素只能使用一次。
    //          2. 这就要求在递归的时候，下一次调用要从i+1个后补元素处开始遍历；
    //          3. 此外，还需要排除掉元素的重复使用。比如说candidates = {1, 1, 2, 2, 2, 2, 3, 4, 6}, target = 8
    //             那么，如果不排除掉重复元素的话，那么当indx = 2时， i + 1可以是3, 4, 5都可以，那么最后就会有三个重复的组合
    //             {1, 2, 2, 3}出现在返回值中。
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		if (candidates.empty())	return combination;
		sort(candidates.begin(), candidates.end());
		vector<int> comb;
		dfs(candidates, comb, 0, target);
		return combination;
	}

    ///@brief   递归辅助函数
    ///@param   candidates  候选数组
    ///@param   comb    正在进行筛选的合法组合
    ///@param   indx    当前遍历到的候选数组元素的下标
    ///@param   target  目标值
    ///@return  无
	void dfs(vector<int>& candidates, vector<int>& comb, int indx, int target) {
		if (!target)	combination.push_back(comb);
		for (int i = indx; i < candidates.size() && candidates[i] <= target; i++) {
			if (i > indx && candidates[i-1] == candidates[i])	continue; // 去除掉结果数组中的重复子数组
			comb.push_back(candidates[i]);
			dfs(candidates, comb, i + 1, target - candidates[i]);   //  i+1使得每个元素只能使用一次
			comb.pop_back();
		}
	}
	vector<vector<int>> combination;
};

int main()
{
	vector<int> test;
	test.push_back(10);
	test.push_back(1);
	test.push_back(2);
    test.push_back(2);
    test.push_back(2);
    test.push_back(2);
	test.push_back(7);
	test.push_back(6);
	test.push_back(1);
	test.push_back(5);

	Solution slt;
	vector<vector<int>> rslt = slt.combinationSum2(test, 8);

	Solution_v1_1 s11;
	vector<vector<int>> r11 = s11.combinationSum2(test, 8);
	return 0;
}
