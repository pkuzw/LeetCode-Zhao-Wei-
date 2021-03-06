﻿///@file	Permutations
/*			Given a collection of numbers, return all possible permutations.

			For example,
			[1,2,3] have the following permutations:
			[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].
*/
///@author	zhaowei
///@date	2015.06.29
///@version	1.1

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
#include <deque>
#include <algorithm>

using namespace std;

class Solution_v1 {
public:
	///@brief	给定候选元素数组，计算所有可能的组合
	///@param	nums	候选元素数组
	///@return	返回所有可能的组合
	///@note	利用递归的思想来解题。含有n和候选元素的数组可以分解成1个元素和n-1个元素。基本情况是只有1个元素的情形，只需要输出其本身；
	//			这时候返回上一级递归，假设有k个元素，如果选出的那1个元素还不是这k个元素中的最后一个，则向后选择下一个，并继续递归。直至
	//			最顶层选到了最后一个元素。时间复杂度为O(n!)，空间复杂度为O(n^2)。
	///@author	zhaowei
	///@date	2015.06.25
	vector<vector<int>> permute(vector<int>& nums)
	{
		vector<int> ivec;
		if (nums.empty())	//	如果原始数组为空，则返回空。其实如果不加这个判断语句，返回的是含有一个空数组的二维数组。
		{
			return rslt;
		}
		getPermutate(nums, ivec);
		return rslt;
	}

	///@brief	计算所有可能的组合
	///@param	nums	原始数组
	///@param	residue	可能的一种组合
	///@return	void
	///@note	我的想法是每次拿掉一个元素，将剩余的元素组成一个新数组，并且记录下当前拿掉的是第几个元素；当新数组为空时需要得到一个可能的组合；
	//			此时返回上一级递归，再拿掉下一个元素。依次类推。
	void getPermutate(vector<int> nums, vector<int>& residue)
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
			getPermutate(tmp, residue);		//	递归
			residue.pop_back();				//	将结果中的元素弹出
			indx++;							//	下标后移一位
		}	
		return;
	}
    
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
            while (indx < nums.size() && nums[indx] == nums[indx-1])    //	如果元素重复，不要选择，直到不重复为止
                indx++;
            
        }	
        return;
    }

private:
	vector<vector<int>> rslt;	//	结果数组
};

class Solution_v2 {
public:
	///@brief	给定候选元素数组，计算所有可能的组合
	///@param	nums	候选元素数组
	///@return	返回所有可能的组合
	vector<vector<int>> permute(vector<int>& nums) {
		vector<vector<int>> rslt;
		if (nums.empty())	return rslt;
		vector<int> pmt;
		dfs(rslt, pmt, nums);
		return rslt;
	}

	///@brief	深度优先遍历所有可能的排列
	///@param	rslt	结果数组
	///@param	pmt		一种排列
	///@param	nums	候选元素数组
	///@return	无
	void dfs(vector<vector<int>>& rslt, vector<int>& pmt, vector<int> nums) {
		if (nums.empty()) {
			rslt.push_back(pmt);
		} 
		else {
			for (int i = 0; i != nums.size(); i++) {
				pmt.push_back(nums[i]);
				vector<int> new_nums;
				for (int j = 0; j != nums.size(); j++) {
					if (j != i) new_nums.push_back(nums[j]);
				}
				dfs(rslt, pmt, new_nums);
				pmt.pop_back();
			}
		}
	}
};

class Solution {
public:
    ///@brief   计算由不重复元素组成的数组所有可能的排列
    ///@param   nums    不重复元素组成的数组
    ///@return  返回所有可能的排列
    ///@note    1. 深度优先遍历。
    //          2. 每次从候选数组中取出一个元素放入排列，然后递归的调用由剩余元素组成的新数组。
    vector<vector<int>> permute(vector<int>& nums) {
        if (nums.empty())   return rslt;
        vector<int> permutation;
        dfs(permutation, nums);
        return rslt;
    }
    
    ///@brief   深度优先遍历函数
    ///@param   pmt     排列
    ///@param   nums    候选元素数组
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
        }
    }
    
private:
    vector<vector<int>> rslt;
};

int main()
{
	Solution slt;
	vector<int> nums;
	vector<vector<int>> rslt;
 	nums.push_back(1);
// 	nums.push_back(1);
 	nums.push_back(2);
    nums.push_back(3);
//  nums.push_back(2);
	rslt = slt.permute(nums);
    
	Solution_v2 s2;
	vector<vector<int>> r2 = s2.permute(nums);
    Solution_v1 slt_v1;
    vector<vector<int>> rslt2;
    rslt2 = slt_v1.permuteUnique(nums);

    cout << "显示不去重的所有组合：" << endl;
	for (int i = 0; i != rslt.size(); i++)
	{
		for (int j = 0; j != rslt[i].size(); j++)
		{
			cout << rslt[i][j] << ' ';
		}
		cout << endl;
	}

	cout << rslt.size() << endl;
    
    cout << "显示去重后的所有组合：" << endl;
    
    for (int i = 0; i != rslt2.size(); i++)
    {
        for (int j = 0; j != rslt2[i].size(); j++)
        {
            cout << rslt2[i][j] << ' ';
        }
        cout << endl;
    }
    
    cout << rslt2.size() << endl;
	return 0;
}
