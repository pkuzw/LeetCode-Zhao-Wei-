///@file	Product of Array Except Self
/*
Given an array of n integers where n > 1, nums, return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].

Solve it without division and in O(n).

For example, given [1,2,3,4], return [24,12,8,6].

Follow up:
Could you solve it with constant space complexity? (Note: The output array does not count as extra space for the purpose of space complexity analysis.)
*/
///@author	zhaowei
///@date	2015.07.26
///@version	1.0

#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	计算数组中除了自身元素外，其余元素的乘积。
	///@param	nums为O(1)	数组
	///@return	返回求完乘积后的数组
	/* @note	先顺序生成一个中间数组，其中初始元素为1，tmp[i] = tmp[i-1]*nums[i-1]。然后再逆序生成结果数组，引入一个临时变量t = 1，
				tmp[i] = t*tmp[i]; t = t*nums[i];时间复杂度为O(n)，空间复杂度为O(1)。*/
	vector<int> productExceptSelf(vector<int>& nums) {
		if (nums.empty())	return nums;

		vector<int> ivec;
		if (nums.size() == 1)	return ivec;

		vector<int> tmp(nums.size(), 1);
		for (int i = 1; i != nums.size(); i++)
			tmp[i] = tmp[i-1] * nums[i-1];

		int t = 1;
		for (int i = nums.size()-1; i >= 0; i--)
		{
			tmp[i] *= t;			
			t *= nums[i];
		}
		return tmp;
	}
};

class Solution {
public:
	vector<int> productExceptSelf(vector<int>& nums) {		
		vector<int> rslt(nums.size(), 0);
		if (nums.empty())	return rslt;

		rslt[0] = 1;
		for (int i = 1; i != nums.size(); i++)	//	rslt[i]相当于计算0..i-1的阶乘
		{
			rslt[i] = rslt[i-1] * nums[i-1];
		}

		int t = 1;
		for (int i = nums.size()-1; i >= 0; i--)
		{
			rslt[i] = rslt[i] * t;
			t = t * nums[i];	//	t是i+1...n的阶乘
		}

		return rslt;
	}
};

int main()
{
	int n[4] = {4,3,2,1};
	vector<int> nums;
	for (int i = 0; i != 4; i++)
	{
		nums.push_back(n[i]);
	}
	Solution slt;
	vector<int> rslt = slt.productExceptSelf(nums);
	return 0;
}