///@file	Maximum Subarray
/*
Find the contiguous subarray within an array (containing at least one number) which has the largest sum.

For example, given the array [−2,1,−3,4,−1,2,1,−5,4],
the contiguous subarray [4,−1,2,1] has the largest sum = 6.
*/
///@author	zhaowei
///@date	2015.07.06
///@version	1.0

///@date    2015.09.03
///@version 2.0

///@date	2016.04.13
///@version	2.1

///@date    October 26, 2018
///@version 3.0

#include <iostream>
#include <vector>
using namespace std;

class Solution_v1 {
public:
	///@brief	计算整型数组的最大子段和
	///@param	nums	整型数组
	///@return	返回整型数组中的最大子段和
	///@note	动态规划算法：假设sum[i]为结尾为nums[i]的最大子段和，则sum[i+1] = max(sum[i]+nums[i+1], nums[i+1])。时间复杂度为O(n)，
	//			空间复杂度为O(1)
	int maxSubArrayDP(vector<int>& nums) 
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

	///@brief	计算整型数组的最大子段和
	///@param	nums	整型数组
	///@return	返回整型数组中的最大子段和
	///@note	分治法：将原数组一分为二，那么最大子段和的位置有三种情况：1. 位于左半部分；2. 位于有半部分；3. 横跨左右部分。
	//			对于前两种情况，可以直接递归继续求解；对于第三种情况，只需要以middle值为中心，向两侧扩展，找出最大的子段和后，和左右
	//			两部分的最大子段和进行比较就可以了。因为T(n) = 2T(n/2) + O(n)，所以时间复杂度根据主定理可知为O(nlogn)，空间复杂度为O(1)
	int maxSubArrayDC(vector<int> &nums)
	{
		int rslt = 0;
		rslt = maxSubArrayRecursive(nums, 0, nums.size()-1);
		return rslt;
	}

	///@brief	递归计算整型数组的最大子段和
	///@param	nums	整型数组
	///@param	beg		数组起始下标
	///@param	end		数组终止下标
	///@return	返回数组的最大子段和
	int maxSubArrayRecursive(vector<int>& nums, int beg, int end)
	{
		if (beg == end)	//	当数组只有一个元素时，递归终止
		{
			return nums[beg];
		}
		int middle = (beg+end)/2;
		int left_max = maxSubArrayRecursive(nums, beg, middle);		//	递归计算左半部分的最大子段和
		int right_max = maxSubArrayRecursive(nums, middle+1, end);	//	递归计算右半部分的最大子段和

		//	计算横跨中心的最大子段和
		int tmp = nums[middle];	//	左半部分的最靠右边的元素值
		int midLeft = nums[middle];	//	记录左半部分的跨中心的最大子段和
		for (int i = middle-1; i >= beg; i--)
		{
			tmp += nums[i];
			if (midLeft < tmp)
			{
				midLeft = tmp;
			}
		}

		tmp = nums[middle+1];	//	右半部分最靠左边的元素值
		int midRight = nums[middle+1];	//	记录右半部分的跨中心的最大子段和
		for (int i = middle+2; i <= end; i++)
		{
			tmp += nums[i];
			if (midRight < tmp)
			{
				midRight = tmp;
			}
		}
		
		return max(max(left_max, right_max), midLeft+midRight);	//	比较三种最大子段和
	}
};

class Solution_v2 {
public:
	///@brief	计算一个整数数组的最大子数组和
	///@param	nums	数组
	///@return	最大整数组之和
	///@note	1. 动态规划解题。
	//			2. dp[i]表示i之前元素的最大子数组之和，则dp[i+1] = max(nums[i+1], dp[i] + nums[i+1])，为了节省存储空间，可以将dp[n]精简到用一个临时变量保存目前的最大值，另一个变量保存最后结果值
    int maxSubArray(vector<int>& nums) {
		if (nums.empty())	return 0;
		int dp = nums[0];		
		int rslt = nums[0];
		for (int i = 1; i != nums.size(); i++) {
			dp = max(nums[i] + dp, nums[i]);
			rslt = max(dp, rslt);
		}
		return rslt;
    }
};

class Solution_v2_1 {
public:
	int maxSubArray(vector<int>& nums) {
		if (nums.empty())	return 0;
		int dp = nums[0];
		int rslt = nums[0];
		for (int i = 1; i != nums.size(); i++) {
			dp = max(nums[i], dp + nums[i]);
			rslt = max(dp, rslt);
		}
		return rslt;
	}
};

class Solution {
public:
    ///@brief   给定一个整型数组，其元素可能为负，也可能为正，计算最大子段和。
    ///@param   nums    整型数组变量
    ///@return  返回最大子段和
    ///@note    1. 动态规划；
    //          2. 设sum[i]为以nums[i]为尾元素的最大子段和，则sum[i+1] = max(sum[i]+nums[i+1], nums[i+1])，只需要从前向后遍历，最终解就存放在sum[nums.size()-1]里面。
    //          3. 时间按复杂度为O(n)，空间复杂度为O(n)，其中n为nums数组的长度。
    int maxSubArray(vector<int>& nums) {
        if (nums.empty())   return 0;
        if (nums.size() == 1)   return nums[0];
        vector<int> sum(nums.size(), 0);
        int rslt = INT_MIN;
        sum[0] = nums[0];
        rslt = max(rslt, sum[0]);
        for (int i = 0; i < nums.size() - 1; i++) {
            sum[i+1] = max(nums[i+1] + sum[i], nums[i+1]);
            rslt = max(rslt, sum[i+1]);
        }
        return rslt;
    }
};



int main()
{
	//-2 1 -3 4 -1 2 1 -5 4 99
	Solution_v1 slt_v1;
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
	cout << slt_v1.maxSubArrayDP(nums) << endl;
	vector<int> subArr = slt_v1.maxSubArrayRange(nums);
	for (int i = 0; i != subArr.size(); i++)
	{
		cout << subArr[i] << ' ';
	}
	cout << endl;
	cout << slt_v1.maxSubArrayDC(nums) << endl;

	Solution slt;
	cout << slt.maxSubArray(nums) << endl;
	return 0;
}
