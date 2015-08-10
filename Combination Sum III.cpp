///@file	Combination Sum III 
/*
Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.

Ensure that numbers within the set are sorted in ascending order.

Example 1:

Input: k = 3, n = 7

Output:

[[1,2,4]]


Example 2:

Input: k = 3, n = 9

Output:

[[1,2,6], [1,3,5], [2,3,4]]

*/
///@author	zhaowei
///@date	2015.07.30
///@version	1.0

///@date	2015.08.10
///@version	2.0
#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	从1到9个数中选择k个数，使其和为n。求所有的组合。注意：所有组合应该升序排列，每个数只能选择一次。
	///@param	k	组合大小
	///@param	n	和
	///@return	返回所有的组合，按照升序排列
	/* @note	递归计算所有可能的组合。时间复杂度为O(n^2)?，空间复杂度为O(n)。*/
	vector<vector<int>> combinationSum3(int k, int n) {
		vector<int> comb;
		vector<int> candidates;
		for (int i = 0; i < 9; i++)
			candidates.push_back(i+1);
		int start = 0;
		getCombine(k, n, comb, candidates, start);
		return rslt;
	}
private:
	///@brief	递归求解
	///@param	comb	可能的一个组合
	///@param	candidates	候选元素
	///@param	start	从候选元素中可以开始选取的位置
	void getCombine(int k, int n, vector<int> &comb, vector<int> &candidates, int start)
	{
		if (k == 0 && n == 0)
		{
			rslt.push_back(comb);
			return;
		}
	
		while (start < 9 && n >= candidates[start])
		{
			comb.push_back(candidates[start]);
			getCombine(k-1, n-candidates[start], comb, candidates, start+1);
			comb.pop_back();
			start++;
		}

		return;		
	}

	vector<vector<int>> rslt;	//	结果数组
};

class Solution {
public:
	vector<vector<int>> combinationSum3(int k, int n) {
		vector<int> candidates;
		for (int i = 1; i <= 9; i++)
			candidates.push_back(i);

		vector<int> comb;

		combine(k, n, comb, candidates, 0);
		return rslt;
	}

private:
	void combine(int k, int n, vector<int>& comb, const vector<int>& candidates, int start)
	{
		if (k == 0 && n == 0)
		{
			rslt.push_back(comb);
			return;
		}

		while(start < 9 && candidates[start] <= n)
		{
			comb.push_back(candidates[start]);
			combine(k-1, n-candidates[start], comb, candidates, start+1);
			comb.pop_back();
			start++;
		}
	}

	vector<vector<int>> rslt;
};

int main()
{
	int k = 5, n = 30; 
	
	Solution slt;
	vector<vector<int>> rslt = slt.combinationSum3(k, n);

	Solution_v1 slt_v1;
	rslt = slt_v1.combinationSum3(k, n);
	return 0;
}