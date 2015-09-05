﻿///@file	Search in Rotated Sorted Array
/*
			Suppose a sorted array is rotated at some pivot unknown to you beforehand.

			(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

			You are given a target value to search. If found in the array return its index, otherwise return -1.

			You may assume no duplicate exists in the array.
*/
///@author	zhaowei
///@date	2015.06.15
///@version 1.0

///@date    2015.09.05
///@version 2.0

#include <iostream>
#include <vector>
using namespace std;

class Solution_v1 {
public:
	///@brief	查找已排序数组中是否存在某元素（默认为升序）
	///@param	nums	数组
	///@param	target	待查找值
	///@return	如果数组中存在该值，则返回该值下标，否则返回-1
	///@author	zhaowei
	///@date	2015.07.18
	///@note	当有序数组被颠倒后，关键是找到哪一部分是有序的。通过比较中间值和数组首元素，来判断左半部分还是右半部分有序。
	//			如果数组首部元素小于中间值，则左半部分有序；
	//			如果数组首部元素大于中间值，则右半部分有序；
	//			如果数组首部元素等于中间值，则修改左边界，自增1，因为mid = (l+r)/2，所以中间值也会改变。
	//			时间复杂度为O(logn)，空间复杂度为O(1)。
	int search_2(vector<int>& nums, int target)
	{
		int l = 0;
		int r = nums.size()-1;
		while (l <= r)
		{
			int m = (l+r)/2;
			if (nums[m] == target)	//	找到目标值则返回true
			{
				return m;
			}
			if (nums[l] < nums[m])	//	左半部分有序
			{
				//	target的范围应该是左闭右开
				if (nums[l] <= target && target < nums[m])	//	如果目标值在左半部分，则修改右边界
				{
					r = m-1;
				}
				else	//	否则修改左边界
				{
					l = m+1;
				}
			}
			else if (nums[m] < nums[l])	//	右半部分有序
			{
				//	target的范围应该是左开右闭
				if (nums[m] < target && target <= nums[r])	//	如果目标值在右半部分，则修改左边界
				{
					l = m+1;
				}
				else
				{
					r = m-1;		//	否则修改右边界
				}
			}
			else
				l++;	//	如果中间值恰好等于首部元素，则更新左边界，以使中间值下标变化
		}
		return -1;
	}

	///@brief	查找已排序数组中是否存在某元素（默认为升序）
	///@param	nums	数组
	///@param	target	待查找值
	///@return	如果数组中存在该值，则返回该值在数组中的下标，否则返回-1
	///@author	zhaowei
	///@date	2015.06.15
	///@note	采用二分查找法先找到pivot值，然后再分成两部分[0...pivot]和[pivot+1...n-1]二分查找该值。时间复杂度为O(logn)，空间复杂度为O(1)
	int search(vector<int>& nums, int target) {
		
		int nums_len = nums.size();	
		int pivot = getPivot(nums, 0, nums_len-1);

		if (pivot == nums_len-2 && nums[pivot] < nums[pivot+1])	//	特殊情况处理：对于没有翻转过的情形，getPivot的返回值是倒数第二个元素下标，需要后移一位
		{
			pivot++;
		}
		

		int max_num = nums[pivot];

		int min_num = 0;

		if (pivot+1 != nums_len)
		{
			min_num = nums[pivot+1];	//	pivot的后一位就是最小值
		}
		else
			min_num = nums[0];	//	循环移位

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

private:
	///@brief	二分查找Pivot值，即最大值
	///@param	nums	已排好序的数组
	///@param	p	数组起始下标
	///@param	r	数组终止下标
	///@return	返回pivot值所在下标
	///@author	zhaowei
	///@date	2015.06.15
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

	///@brief	二分查找目标值
	///@param	a	已排好序的数组
	///@param	p	数组起始下标
	///@param	r	数组终止下标
	///@param	val	目标值
	///@return	如果目标值val所在下标存在，则返回其下标；否则返回-1
	///@author	zhaowei
	///@date	2015.06.15
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

class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (nums.empty())   return -1;
        int start = 0, end = nums.size() - 1;
        while (start <= end){
            int mid = (start + end) / 2;
            if (nums[mid] == target)    return mid;
            else if (nums[mid] < nums[end]){
                if (nums[mid] < target && target <= nums[end])  start = mid + 1;
                else end = mid - 1;
            }
            else{
                if (nums[mid] > target && target >= nums[start])    end = mid - 1;
                else    start = mid + 1;
            }
        }
        return -1;
    }
};

int main()
{
	Solution_v1 slt_v1;
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
			cout << target << " " << slt_v1.search(nums, target) << ' ' << slt_v1.search_2(nums, target);
			cout << endl;
            Solution slt;
            cout << "v2: " << slt.search(nums, target) << endl;
		}

	}
	
	return 0;
}