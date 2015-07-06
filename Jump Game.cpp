///@file	Jump Game
/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

For example:
A = [2,3,1,1,4], return true.

A = [3,2,1,0,4], return false.
*/
///@author	zhaowei
///@date	2015.07.06
///@version	1.0

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	///@brief	给定一个整数数列，其中每个元素代表从该位置向前移动的最大距离，判断能否从初始元素到达最后一个元素
	///@param	nums	整数数组
	///@return	如果能够到达，则返回true；否则返回false
	///@note	首先，通过观察发现，只有数组中出现零元素，才有可能无法到达终点。其次，零元素之前的若干元素的最远跳跃距离应该
	//			小于等于其到零元素的距离。又因为数组中有可能有多个零，应从前往后依次判断能否越过这些零。
	//			时间复杂度为O(n)，空间复杂度为O(1)。
	bool canJump(vector<int>& nums)
	{
		if (nums.size() == 1)
		{
			return true;
		}
		vector<int> zeroIndx;
		for (int i = 0; i != nums.size(); i++)
		{
			if (nums[i] == 0)
			{
				zeroIndx.push_back(i);
			}
		}
		for (int i = 0; i != zeroIndx.size(); i++)
		{
			if (isForestall(nums, zeroIndx[i]))
			{
				return false;
			}
		}
		return true;
	}

private:
	///@brief	判断零元素之前的所有元素能否越过该零元素
	///@param	nums		数组
	///@param	zeroIndx	零元素的下标
	///@return	如果所有的零元素之前的元素都无法越过该零元素，则返回true；否则返回false
	bool isForestall(vector<int>& nums, int zeroIndx)
	{
		for (int i = 0; i != zeroIndx; i++)
		{
			//	如果当前元素的最大跳跃距离大于到零元素的距离或者零元素就是最后一个元素，跳跃距离正好能够到达，则返回false
			if ((nums[i] > zeroIndx-i) || (nums[i] == zeroIndx-i && zeroIndx == nums.size()-1))
			{
				return false;
			}
		}
		return true;
	}
};

int main()
{
	vector<int> nums;
 	nums.push_back(1);
 	nums.push_back(1);
 	nums.push_back(0);

	Solution slt;
	cout << slt.canJump(nums) << endl;
	return 0;
}
