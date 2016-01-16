///@file	Find Peak Element
/*
A peak element is an element that is greater than its neighbors.

Given an input array where num[i] ≠ num[i+1], find a peak element and return its index.

The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.

You may imagine that num[-1] = num[n] = -∞.

For example, in array [1, 2, 3, 1], 3 is a peak element and your function should return the index number 2.
*/
///@author	zhaowei
///@date	2015.07.28
///@version	1.0

///@date	2015.08.13
///@version	1.1

///@date	2016.01.16
///@version	1.2
#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	找到数组中的一个局部最大值
	///@param	nums	数组
	///@return	返回任意一个局部最大值
	///@note	二分查找。时间复杂度为O(logn)，空间复杂度为O(1)。
	int findPeakElement(vector<int>& nums) {
		if (nums.size() == 1)	return 0;

		int l = 0;
		int r = nums.size()-1;

		while (l <= r)
		{
			if (l == r)	return l;
			int m = (l + r) / 2;
			if (nums[m] < nums[m+1])	l = m+1;
			else						r = m;
		}
	}
};

class Solution {
public:
	int findPeakElement(vector<int>& nums) {
		if (nums.size() == 1)	return 0;
		int l = 0, r = nums.size() - 1;
		while (l <= r) {
			if (l == r)	return l;
			int m = (l + r) / 2;
			if (nums[m] < nums[m+1])	l = m + 1;
			else	r = m;
		}
	}
};

int main()
{
	int n[7] = {1,2,3,5,6,4,2};
	vector<int> nums;
	for (int i = 0; i != 7; i++)
		nums.push_back(n[i]);
	Solution slt;
	int rslt = slt.findPeakElement(nums);
	return 0;
}