///@file	Search in Rotated Sorted Array
/*
			Suppose a sorted array is rotated at some pivot unknown to you beforehand.

			(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

			You are given a target value to search. If found in the array return its index, otherwise return -1.

			You may assume no duplicate exists in the array.
*/
///@author	zhaowei
///@date	2015.06.15
///@version 1.0

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	///@brief	查找数组中是否存在某元素
	///@param	nums	数组
	///@param	target	待查找值
	///@return	如果数组中存在该值，则返回该值在数组中的下标，否则返回-1
	int search(vector<int>& nums, int target) {
		int nums_len = nums.size();
		int pivot = getPivot(nums, 0, nums_len-1);

		if (pivot == nums_len-2 && nums[pivot] < nums[pivot+1])
		{
			pivot++;
		}
		

		int max_num = nums[pivot];

		int min_num = 0;
		if (pivot+1 != nums_len)
		{
			min_num = nums[pivot+1];
		}
		else
			min_num = nums[0];

		if (target > max_num || target < min_num)
		{
			return -1;
		}

		int rslt = 0;
		rslt = binarySearch(nums, 0, pivot, target);

		if (rslt == -1 && pivot+1 != nums_len)
		{
			rslt = binarySearch(nums, pivot+1, nums_len-1, target);
		}
		return rslt;		
	}

	int getPivot(vector<int>& nums, int p, int r)
	{
		if (p == r)
		{
			return p;
		}
		int q = (p+r)/2;
		if (nums[p] < nums[q])
		{			
			return getPivot(nums, q, r);
		}
		else
		{		
			return getPivot(nums, p, q);
		}		
	}

	int binarySearch(vector<int>& a, int p, int r, int val)
	{
		if (p > r)
		{
			return -1;
		}
		int q = (p+r)/2;
		if (a[q] == val)
		{
			return q;
		}
		else if (a[q] < val)
		{
			return binarySearch(a, q+1, r, val);
		}
		else if (a[q] > val)
		{
			return binarySearch(a, p, q-1, val);
		}
		return -1;
	}
	
};

int main()
{
	Solution slt;
	for (int j = 1; j <= 10; j++)
	{
		vector<int> nums;
		for (int i = 0; i < j; i++)
		{
			nums.push_back(i+10-j);
		}

		for (int i = 0; i < 10-j; i++)
		{
			nums.push_back(i);
		}

		for (int i = 0; i < 10; i++)
		{
			cout << nums[i] << ' ';
		}
		cout << endl;
		for (int i = 0; i < 12; i++)
		{
			int target = i;
			cout << target << " " << slt.search(nums, target);
			cout << endl;
		}

	}
	
	return 0;
}