///@file	Jump Game II
/*
			Given an array of non-negative integers, you are initially positioned at the first index of the array.

			Each element in the array represents your maximum jump length at that position.

			Your goal is to reach the last index in the minimum number of jumps.

			For example:
			Given array A = [2,3,1,1,4]

			The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)
*/
///@author	zhaowei
///@date	2015.06.23
///@version	1.0

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	///@brief	计算到达数组最后一个下标的最小跳跃步数
	///@param	nums	数组，其中每一个元素值非负，表示能从该下标跳跃的最远距离
	///@return	如果能够最后到达终点，则返回从数组开头到末尾的最少跳跃步数；否则返回-1
	///@note	解题思路：寻找从当前下标到其所能到达最远处这一范围内的下一跳最远的元素，然后将当前下标移动到该处继续搜索，直到到达数组末尾。
	//			需要开辟两个长度为n的新数组，其中一个为原始数组的副本，用来划定寻找最远下一跳的范围；另外一个用来标记该元素是否被修改过。
	//			时间复杂度为O(n^2)，空间复杂度为O(n)。
	int jump(vector<int>& nums) 
	{
		int first = 0;
		int cnt = 0;
		vector<int> init_nums(nums);	//	复制一个初始数组
		//	用于标记该数组元素是否修改过。因为修改之前的元素表示以其为中心所能到达的范围（一个相对值），修改之后的则表示该元素所能到达的
		//	最远下标（一个绝对值），二者不能混淆
		bool *modified = new bool[nums.size()];	
		memset(modified, false, nums.size());
		while (nums[first] < nums.size()-1)
		{
			cnt++;
			for (int i = first; i != first + init_nums[first] + 1; i++)	//	i的范围应该用初始数组来标定
			{
				if (!modified[i])
				{
					nums[i] += i;
					modified[i] = true;
				}				
			}

			first = getMax(nums, first, first+init_nums[first]+1);	//	为了防止寻找最大值范围超过数组本身，需要使用原始数组来计算

			if (cnt > nums.size())
			{
				return -1;	//	表示陷入了死循环，无法到达终点。比如[1, 0, 1]
			}
		}		
		delete []modified;
		if (init_nums.size() == 1)	//	处理边界情况：只有一个元素的情形，返回0
		{
			return cnt;
		}
		else
			return cnt+1;
	}

	///@brief	找到指定区间的最大值
	///@param	nums	数组
	///@param	p		起始下标
	///@param	r		终止下标的后一个元素
	///@return	返回该范围内的第一个最大值下标
	int getMax(vector<int>& nums, int p, int r)
	{
		int max_val = nums[p];
		int max_indx = p;
		for (int i = p; i != r; i++)
		{
			if (nums[i] > max_val)
			{
				max_val = nums[i];
				max_indx = i;
			}
		}
		return max_indx;
	}

};

int main()
{
	vector<int> ivec;
	ivec.push_back(5);
// 	ivec.push_back(1);
// 	ivec.push_back(0);
// 	ivec.push_back(0);
//  ivec.push_back(4);
// 	ivec.push_back(1);
// 	ivec.push_back(1);
// 	ivec.push_back(1);
// 	ivec.push_back(1);
// 	ivec.push_back(1);
// 	ivec.push_back(1);
// 	ivec.push_back(1);
// 	ivec.push_back(1);
// 	ivec.push_back(1);

	Solution slt;
	cout << slt.jump(ivec) << endl;
	return 0;
}