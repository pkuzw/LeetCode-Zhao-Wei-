///@file	Permutations
/*
			Given a collection of numbers that might contain duplicates, return all possible unique permutations.

			For example,
			[1,1,2] have the following unique permutations:
			[1,1,2], [1,2,1], and [2,1,1].
*/
///@author	zhaowei
///@date	2015.06.25
///@version	1.0

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	///@brief	给定候选元素数组，计算所有可能的组合。如果候选数组中有重复元素，需要排除掉重复的组合
	///@param	nums	候选元素数组
	///@return	返回没有重复组合的集合
	///@note	在Permutation递归的基础上，增加一个筛选重复数组的函数去重。OJ报TLE。
	///@author	zhaowei
	///@date	2015.06.25
	vector<vector<int>> permuteUnique(vector<int>& nums)
	{
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
			if (isExist(rslt, residue))	//	去重
			{
				rslt.push_back(residue);	//	将一种可能的组合加入结果二维数组				
			}
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
			indx++;							//	下标后移一位
		}	
		return;
	}

	///@brief	排除已经存在的组合
	///@param	rslt	结果集合
	///@param	comb	一种组合
	///@return	如果该组合已经存在，则返回true；否则返回false
	bool isExist(vector<vector<int>> rslt, vector<int> comb)
	{
		for (int i = 0; i != rslt.size(); i++)
		{
			if (isEqual(rslt[i], comb))
			{
				return false;
			}
		}
		return true;
	}

	///@brief	判断两个数组是否相同
	///@param	a	数组a
	///@param	b	数组b
	///@return	如果数组相同，则返回true；否则返回false
	bool isEqual(vector<int> a, vector<int> b)
	{
		for (int i = 0; i != a.size(); i++)
		{
			if (a[i] != b[i])
			{
				return false;
			}
		}
		return true;
	}
private:
	vector<vector<int>> rslt;	//	结果数组
};

int main()
{
	vector<int> test;
	test.push_back(1);
	test.push_back(1);
	test.push_back(2);
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