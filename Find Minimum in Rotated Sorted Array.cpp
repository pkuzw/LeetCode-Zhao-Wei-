///@file	Find Minimum in Rotated Sorted Array
/*
Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

You may assume no duplicate exists in the array.
*/
///@author	zhaowei
///@date	2015.07.27
///@version	1.0

///@date	2015.08.18
///@version	1.1

///@date	2016.01.14
///@version	1.2

#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	在一个已经排好序但部分翻转的数组中查找最小值
	///@param	nums	数组
	///@return	返回最小值
	/* @note	二分查找。建立首尾指针和中间指针，只要左右指针还未相邻，如果首指针比中间指针小，说明前半部分有序，进入后半部分查找；
				否则进入前半部分查找。时间复杂度为O(logn)，空间复杂度为O(1)。	*/
	int findMin(vector<int>& nums) {
		if (nums.size() == 1)	return nums[0];

		int l = 0;
		int r = nums.size()-1;
		if (nums[l] < nums[r])	return nums[l];

		while (l != r-1)
		{
			int m = (l + r) / 2;
			if (nums[l] < nums[m])	l = m;
			else					r = m;
		}

		return (nums[l] < nums[r]) ? nums[l] : nums[r];
	}
};

class Solution {
public:
	///@brief	在一个已经排好序但部分翻转的数组中查找最小值
	///@param	nums	数组
	///@return	返回最小值
	///@note	1. 二分查找
	int findMin(vector<int>& nums) {
		int l = 0, r = nums.size() - 1;
		if (l == r)	return nums[0];
		if (nums[l] < nums[r])	return nums[l];
		while (l < r - 1) {
			int m = (l + r) / 2;
			if (nums[l] < nums[m])	l = m;
			else	r = m;
		}
		return (nums[l] < nums[r]) ? nums[l] : nums[r];
	}
};

int main()
{
	int n[10] = {5,6,7,8,9,10,1,2,3,4};
	vector<int> nums;
	for (int i = 0; i != 10; i++)	
		nums.push_back(n[i]);

	Solution slt;
	int rslt = slt.findMin(nums);
	return 0;
}
