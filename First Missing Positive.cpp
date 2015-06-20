///@file	First Missing Positive
/*
			Given an unsorted integer array, find the first missing positive integer.

			For example,
			Given [1,2,0] return 3,
			and [3,4,-1,1] return 2.

			Your algorithm should run in O(n) time and uses constant space.
*/
///@author	zhaowei
///@date	2015.06.20
///@versin	1.0

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
	///@brief	找到数组中第一个打破连续性的缺失正整数
	///@param	nums	数组
	///@return	返回该正整数值
	///@note	首先扫描一遍数组，找出数组中的最大值max，然后申请最大值那么大的动态数组，初始化全部为0，然后再扫描一遍数组，
	//			凡是大于0的正整数都在新的数组中相应的下标标为1，最后遍历一遍新数组，找到第一个为0的元素的下标即可。时间复杂度为O(n)，
	//			空间复杂度为O(k)。本质上就是用新数组模拟一个哈希表。
	///@author	zhaowei
	///@date	2015.06.20
	int firstMissingPositive(vector<int>& nums) 
	{
		int max = 0;
		for (int i = 0; i != nums.size(); i++)	//	找到数组中的最大值
		{
			if (nums[i] > max)
			{
				max = nums[i];
			}
		}

		bool* hash_table = new bool[max+1];		//	申请max这么大的hash表
		memset(hash_table, false, sizeof(bool)*(max+1));
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] > 0)
			{
				hash_table[nums[i]] = true;
			}
		}

		for (int i = 1; i < max+1; i++)
		{
			if (!hash_table[i])
			{
				return i;
			}
		}
		return max+1;	//	如果数组为空或者数组中的正整数都能连续增加，返回max+1
	}
};

int main()
{
	vector<int> ivec;
//	ivec.push_back(0);

	Solution slt;
	int rslt = slt.firstMissingPositive(ivec);
	cout << rslt << endl;
	return 0;
}