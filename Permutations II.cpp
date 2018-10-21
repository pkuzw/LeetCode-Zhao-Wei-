///@file	Permutations
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
///@version 1.1

///@date    2015.09.04
///@version 2.0

///@date	2015.10.14
///@version	2.1

///@date	2016.04.12
///@version	2.2

///@date    October 21, 2018
///@version 2.3

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution_v1 {
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
            while ( indx < nums.size() && nums[indx] == nums[indx-1])    //	如果元素重复，不要选择，直到不重复为止
                indx++;
            
		}	
		return;
	}
private:
	vector<vector<int>> rslt;	//	结果数组
};

class Solution_v2 {
public:
	///@brief	计算所有可能的排列，但是不包括重复的排列
	///@param	nums	候选元素数组
	///@return	所有可能的排列
	///@note	利用深度优先遍历思想，先将候选元素排序，然后按照"Permutation"题目中的算法来进行计算，但是在递归结束时，选择新的元素加入排列时，要避开已经选过的相同元素。
	vector<vector<int>> permuteUnique(vector<int>& nums) {
		vector<vector<int>> rslt;
		if (nums.empty())	return rslt;
		vector<int> pmt;
		sort(nums.begin(), nums.end());
		dfs(rslt, pmt, nums);
		return rslt;
	}

	///@brief	深度优先遍历计算去重的所有排列
	///@param	rslt	结果数组
	///@param	pmt		一个排列
	///@param	nums	候选元素数组
	///@note	在一次递归结束后选择新的元素下标时，要排除上一次压入的相同元素
	void dfs(vector<vector<int>>& rslt, vector<int> pmt, vector<int> nums) {
		if (nums.empty()) rslt.push_back(pmt);
		else {			
			for (int i = 0; i != nums.size(); i++) {
				pmt.push_back(nums[i]);
				vector<int> new_nums;
				for (int j = 0; j != nums.size(); j++) 
					if (i != j) new_nums.push_back(nums[j]);
				dfs(rslt, pmt, new_nums);
				pmt.pop_back();
				while (i != nums.size() - 1 && nums[i] == nums[i + 1]) i++;
			}
		}
	}
};

class Solution {
public:
    ///@brief   计算所有不重复的所有排列，候选数组中可能含有重复元素。
    ///@param   nums    候选元素
    ///@return  返回所有可能的排列
    ///@note    1. 深度优先遍历。
    //          2. 算法类似于"Permuations"，但是在dfs()函数中在pop()完后，向后移动候选数组中的循环变量时注意跳过重复元素即可。
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        if (nums.empty())   return rslt;
        sort(nums.begin(), nums.end());
        vector<int> permutation;
        dfs(permutation, nums);
        return rslt;
    }
    
    ///@brief   深度优先遍历函数
    ///@param   pmt     一个有效排列
    ///@param   nums    候选数组
    ///@return  无
    void dfs(vector<int>& pmt, vector<int> nums) {
        if (nums.empty()) {
            rslt.push_back(pmt);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            pmt.push_back(nums[i]);
            vector<int> new_nums;
            for (int j = 0; j < nums.size(); j++) {
                if (i != j) new_nums.push_back(nums[j]);
            }
            dfs(pmt, new_nums);
            pmt.pop_back();
            while (i < nums.size() - 1 && nums[i] == nums[i+1]) i++;
        }
    }
private:
    vector<vector<int>> rslt;
};

int main()
{
	vector<int> test;
//	test.push_back(2);
	test.push_back(2);
	test.push_back(1);
    test.push_back(1);
	Solution slt;
    Solution_v2 slt_v2;
    vector<vector<int>> rslt_v2 = slt_v2.permuteUnique(test);    
	vector<vector<int>> rslt = slt.permuteUnique(test);
	return 0;
}
