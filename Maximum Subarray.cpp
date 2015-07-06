///@file	Maximum Subarray
/*
Find the contiguous subarray within an array (containing at least one number) which has the largest sum.

For example, given the array [−2,1,−3,4,−1,2,1,−5,4],
the contiguous subarray [4,−1,2,1] has the largest sum = 6.
*/
///@author	zhaowei
///@date	2015.07.06
///@version	1.0

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	///@brief	计算整型数组的最大子段和
	///@param	nums	整型数组
	///@return	返回整型数组中的最大子段和
	///@note	动态规划算法：假设sum[i]为结尾为nums[i]的最大子段和，则sum[i+1] = max(sum[i]+nums[i+1], nums[i+1])。时间复杂度为O(n)，
	//			空间复杂度为O(1)
	int maxSubArray(vector<int>& nums) 
	{
		int rslt = INT_MIN;
		int sum = 0;	//	因为要找的是最大和，所以对于全都是负数的情形，要尽可能的少选，只选最小的那一个。靠初始值sum = 0来分界
		for (int i = 0; i != nums.size(); i++)
		{
			sum = max(nums[i], sum+nums[i]);	//	最大子段和sum[i+1] = max{sum[i]+nums[i], nums[i+1]}
			rslt = max(rslt, sum);
		}
		return rslt;
	}

	///@brief	计算整型数组的最大子段和的首尾下标
	///@param	nums	整型数组
	///@return	返回整型数组中的最大子段和的首尾下标以及子段和
	///@note	动态规划算法：假设sum[i]为结尾为nums[i]的最大子段和，则sum[i+1] = max(sum[i]+nums[i+1], nums[i+1])。时间复杂度为O(n)，
	//			空间复杂度为O(1)
	vector<int> maxSubArrayRange(vector<int>& nums)
	{
		int rslt = INT_MIN;
		int sum = 0;
		int head = 0, tail = 0;	//	最大子段和的首尾下标
		for (int i = 0; i != nums.size(); i++)
		{
			if (sum > 0)
			{
				sum += nums[i];
			}
			else
			{
				sum = nums[i];
				head = i;
			}
			if (sum > rslt)
			{
				rslt = sum;
				tail = i;
			}
		}
		vector<int> subRange;
		subRange.push_back(head);
		subRange.push_back(tail);
		subRange.push_back(rslt);

		return subRange;
	}
};

int main()
{
	//-2 1 -3 4 -1 2 1 -5 4 99
	Solution slt;
	vector<int> nums;
	int k;
	while (cin >> k)
	{
		if (k == 99)
		{
			break;
		}
		nums.push_back(k);
	}
	cout << slt.maxSubArray(nums) << endl;
	vector<int> subArr = slt.maxSubArrayRange(nums);
	for (int i = 0; i != subArr.size(); i++)
	{
		cout << subArr[i] << ' ';
	}
	cout << endl;
	return 0;
}