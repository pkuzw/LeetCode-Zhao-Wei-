///@file	Combination Sum
/*
			Given a set of candidate numbers (C) and a target number (T), 
			
			find all unique combinations in C where the candidate numbers sums to T.

			The same repeated number may be chosen from C unlimited number of times.

			Note:
			All numbers (including target) will be positive integers.
			Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
			The solution set must not contain duplicate combinations.
			For example, given candidate set 2,3,6,7 and target 7, 
			A solution set is: 
			[7] 
			[2, 2, 3] 
*/
///@author	zhaowei
///@date	2015.06.18
///@version	1.0

///@date    2015.09.04
///@version 2.0

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution_v1
{
public:
	///@brief	计算和为目标值的所有可能组合
	///@param	candidates	候选数字数组
	///@param	target	目标值
	///@return	返回所有可能的数字组合，其中数字按照升序排序，没有重复的数组
	///@note	用回溯的思路解题。先将候选数组排序，然后按照从低到高的顺序逐一尝试，将目标值减去小于目标值的候选数字，直到目标值为0得到一个可能的组合。
	//			否则就返回上一个元素，选择下一个可能的数字。直到找到所有可能的组合。时间复杂度为O(n^2)，空间复杂度为O(1)
	vector<vector<int>> combinationSum(vector<int>& candidates, int target)
	{
		
		sort(candidates.begin(), candidates.end());	//	排序
		vector<int> combination;

		calCombination(candidates, 0, target, combination);	//	递归求解

		return combinations;
	}

	///@brief	计算可能的和为目标值的组合
	///@param	candidates	候选数字数组
	///@param	index	在候选数字数组中的下标
	///@param	target	目标值
	///@param	combination	可能的一个组合
	void calCombination(vector<int>& candidates, int index, int target, vector<int>& combination)
	{
		if (target == 0)	//	如果目标值减为0就算找到了一个组合
		{
			combinations.push_back(combination);	//	压入当前候选数字
			return;
		}
		for (int i = index; i < candidates.size() && target >= candidates[i]; i++)
		{
			combination.push_back(candidates[i]);	//	压入当前候选数字
			calCombination(candidates, i, target-candidates[i], combination);	//	递归调用自身求解
			combination.pop_back();	//	不满足的情况要回溯，需要弹出当前的数字，并尝试下一个候选数组中的数字
		}
	}
private:
	vector<vector<int>> combinations;	//	所有可能的组合集合
};

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
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
                cmb.push_back(candidates[i]);
                dfs(rslt, cmb, candidates, i, target - candidates[i]);
                cmb.pop_back();
            }
        }
    }
};

int main()
{
	vector<int> test;
	test.push_back(3);
	test.push_back(2);
	test.push_back(4);
	test.push_back(7);
	test.push_back(6);

	Solution slt;
	vector<vector<int>> rslt = slt.combinationSum(test, 12);

	for (int i = 0; i < rslt.size(); i++)
	{
		for (int j = 0; j < rslt[i].size(); j++)
		{
			cout << rslt[i][j] << ' ';
		}
		cout << endl;
	}
	return 0;
}