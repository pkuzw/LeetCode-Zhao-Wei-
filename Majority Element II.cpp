///@file	Majority Element II
/*
Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.

The algorithm should run in linear time and in O(1) space.
*/
///@author	zhaowei
///@date	2015.07.27
///@version	1.0

#include <vector>

using namespace std;

class Solution {
public:
	///@brief	找出一个数组中出现次数超过n/3的所有元素
	///@param	nums	数组
	///@return	返回一个数组中出现次数超过n/3的所有元素
	/* @note	先用投票法找到有可能的候选元素，然后再验证。时间复杂度为O(n)，空间复杂度为O(1)。*/
	vector<int> majorityElement(vector<int>& nums) {
		//数组中出现次数超过n/3的元素不可能超过2个
		int a = 0;	//	候选元素a的下标
		int b = 0;	//	候选元素b的下标
		int a_cnt = 0;	
		int b_cnt = 0;

		//	投票法找到候选元素
		for (int i = 0; i != nums.size(); i++)
		{
			if (nums[i] == nums[a])
				a_cnt++;
			else if (nums[i] == nums[b])
				b_cnt++;
			else if (!a_cnt)
			{
				a = i;
				a_cnt = 1;
			}
			else if (!b_cnt)
			{
				b = i;
				b_cnt = 1;
			}		
			else
			{
				a_cnt--;
				b_cnt--;
			}
		}

		//	验证候选元素
		a_cnt = 0;
		b_cnt = 0;
		for (int i = 0; i != nums.size(); i++)
		{
			if (nums[i] == nums[a])		a_cnt++;
			else if (nums[i] == nums[b])	b_cnt++;
		}

		vector<int> rslt;
		if (a_cnt > nums.size() / 3)	rslt.push_back(nums[a]);
		if (b_cnt > nums.size() / 3)	rslt.push_back(nums[b]);
		return rslt;
	}
};

int main()
{
	vector<int> nums;
	nums.push_back(1);
	nums.push_back(1);
	nums.push_back(3);

	Solution slt;
	vector<int> rslt = slt.majorityElement(nums);
	return 0;
}