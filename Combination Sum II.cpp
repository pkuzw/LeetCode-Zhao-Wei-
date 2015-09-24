///@file	Combination Sum II
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
///@version 2.0

///@date	2015.09.24
///@version	2.1
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

class Solution_v2 {
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
	///@brief	给定一个数组和一个指定值，找出所有可能的组合，使之和为指定值。其中每个元素不能重复出现。
	///@param	candidates	数组
	///@param	target		目标值
	///@note	与"Combination Sum I"类似，也是回溯法解题。只是在递归遍历时，候选元素的下标要向后移一位。另外去重也是要注意的部分，在第一题中候选数组中没有重复元素，此题则有重复元素。
	//			在递归函数里面遍历候选数组时，遇到重复元素则跳过即可。
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		vector<vector<int>> rslt;
		if (candidates.empty())	return rslt;
		vector<int> comb;
		sort(candidates.begin(), candidates.end());
		dfs(rslt, comb, candidates, 0, target);
		return rslt;
	}

	///@brief	回溯递归求解组合
	///@param	rslt	结果集合
	///@param	comb	一个结果
	///@param	candidates	候选数组
	///@param	indx	候选数组的元素下标
	///@param	target	目标值
	void dfs(vector<vector<int>>& rslt, vector<int>& comb, vector<int>& candidates, int indx, int target) {
		if (!target)	rslt.push_back(comb);
		else {
			for (int i = indx; i < candidates.size() && candidates[i] <= target; i++) {
				if (i > indx && candidates[i] == candidates[i-1])	continue;	//	跳过候选数组中的重复元素
				comb.push_back(candidates[i]);
				dfs(rslt, comb, candidates, i + 1, target - candidates[i]);
				comb.pop_back();
			}
		}
	}
};

int main()
{
	vector<int> test;
	test.push_back(10);
	test.push_back(1);
	test.push_back(2);
	test.push_back(7);
	test.push_back(6);
	test.push_back(1);
	test.push_back(5);

	Solution slt;
	vector<vector<int>> rslt = slt.combinationSum2(test, 8);

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