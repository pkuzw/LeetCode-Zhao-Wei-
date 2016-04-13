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

///@date    2015.09.01
///@version 2.0

///@date	2015.10.21
///@version	2.1

///@date	2016.04.13
///@version	2.2


#include <iostream>
#include <vector>
using namespace std;

class Solution_v1 {
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

/*
动态规划：dp[i]表示第i个格子处的最大剩余步数。初始条件为dp[0] = 0，递推关系是为dp[i] = max(dp[i-1], nums[i-1]) - 1.
*/
class Solution_v2 {
public:
    bool canJump(vector<int>& nums) {
        vector<int> dp(nums.size(), 0); //dp表示在第i个格子处的剩余最远步数
        for (int i = 1; i != nums.size(); i++){
            dp[i] = max(dp[i-1], nums[i-1]) - 1;
        }
        for (int i = 0; i != dp.size(); i++){
            if (dp[i] < 0)  return false;
        }
        return true;
    }
};

class Solution_v2_1 {
public:
	///@brief	给定一组正整数，代表当前各自能继续向后走的步数，计算能否到达最后一个格子
	///@param	nums	格子
	///@return	如果可以到达最后一个格子，则返回true；否则返回false
	///@note	动态规划：用dp[i]表示到达i时剩余的最大步数，则状态转移方程为dp[i] = max(dp[i-1] - 1, nums[i])。如果中间有一个格子小于等于0，则直接返回false。
	bool canJump(vector<int>& nums) {
		if (nums.size() == 1 || nums.size() == 0)	return true;		
		vector<int> dp(nums.size()-1, 0);
		dp[0] = nums[0];
		for (int i = 1; i < nums.size() - 1; i++) 
			dp[i] = max(dp[i - 1] - 1, nums[i]);
		
		for (int i = 0; i < nums.size() - 1; i++)
			if (dp[i] <= 0)	return false;
		return true;

	}
};

class Solution {
public:
	bool canJump(vector<int>& nums) {
		if (nums.size() == 1 || nums.empty())	return true;
		vector<int> dp(nums.size() - 1, 0);
		dp[0] = nums[0];
		for (int i = 1; i < nums.size() - 1; i++)	dp[i] = max(dp[i-1] - 1, nums[i]);
		for (int i = 0; i < nums.size() - 1; i++)	if (dp[i] <= 0)	return false;
		return true;
	}
};

int main()
{
	vector<int> nums;
 	nums.push_back(3);
 	nums.push_back(2);
 	nums.push_back(1);
	nums.push_back(0);
	nums.push_back(4);

	Solution_v2 s2;
	cout << s2.canJump(nums) << endl;

	Solution slt;
	cout << slt.canJump(nums) << endl;
	return 0;
}
