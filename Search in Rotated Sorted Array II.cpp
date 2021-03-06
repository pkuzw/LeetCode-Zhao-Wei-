﻿///@file	Search in Rotated Sorted Array II
/*
Follow up for "Search in Rotated Sorted Array":
Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search. If found in the array return its index, otherwise return -1.

What if duplicates are allowed?

(i.e., 0 0 0 1 1 2 2 2 4 4 5 5 6 6 7 7 7 might become 4 4 5 5 6 6 7 7 7 0 0 0 1 1 2 2 2)

Would this affect the run-time complexity? How and why?

Write a function to determine if a given target is in the array.
*/
///@author	zhaowei
///@date	2015.07.18
///@version	1.2

///@date	2015.08.26
///@version	2.0

///@date	2015.12.09
///@version	2.1

///@date	2016.04.30
///@version	2.2

///@date    November 19, 2018
///@version 2.3

#include <iostream>
#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	查找已排序数组中是否存在某元素（默认为升序）
	///@param	nums	数组
	///@param	target	待查找值
	///@return	如果数组中存在该值，则返回true，否则返回false
	///@author	zhaowei
	///@date	2015.07.18
	///@note	当有序数组被颠倒后，关键是找到哪一部分是有序的。通过比较中间值和数组首元素，来判断左半部分还是右半部分有序。
	//			如果数组首部元素小于中间值，则左半部分有序；
	//			如果数组首部元素大于中间值，则右半部分有序；
	//			如果数组首部元素等于中间值，则修改左边界，自增1，因为mid = (l+r)/2，所以中间值也会改变。
	//			时间复杂度为O(logn)，空间复杂度为O(1)。
	bool search(vector<int>& nums, int target)
	{
		int l = 0;
		int r = nums.size()-1;
		while (l <= r)
		{
			int m = (l+r)/2;
			if (nums[m] == target)	//	找到目标值则返回true
			{
				return true;
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
		return false;
	}
};

class Solution_v2 {
public:
	///@brief	寻找翻转数组中的指定元素
	///@param	nums	数组
	///@param	target	目标值
	///@return	如果数组中有该元素，则返回true；否则返回false
	///@note	1. 二分查找；
	//			2. 如果中间元素等于目标值，则返回true；
	//			3. 如果中间元素不等于目标值，则判断首元素和中间值的大小，如果首元素小于中间值，说明数组左半部分有序；
	//			4. 如果首元素大于中间值，则说明右半部分有序；
	//			5. 如果首元素等于中间值，则将首元素左移一位以更新中间元素，继续下一次迭代；
	//			6. 时间复杂度为O(logn)，空间复杂度为O(1)
	bool search(vector<int>& nums, int target) {
		int l = 0, r = nums.size() - 1;
		while (l <= r) {
			int mid = (l + r) / 2;
			if (nums[mid] == target)	return true;
			if (nums[l] < nums[mid]) {
				if (nums[l] <= target && target < nums[mid])	r = mid - 1;
				else	l = mid + 1;
			}
			else if (nums[l] > nums[mid]) {
				if (nums[mid] < target && target <= nums[r])	l = mid + 1;
				else	r = mid - 1;
			}
			else	l++;
		}
		return false;
	}
};

class Solution {
public:
    ///@brief   给定一个部分旋转的含有重复元素的有序数组，判定其中是否存在指定值；
    ///@param   nums    数组
    ///@param   target  目标值
    ///@return  如果目标值存在，返回true；否则返回false。
    ///@note    1. 二分查找；
    //          2. 如果中间值大于左边界，那么说明左半部分有序。这种情况下如果目标值在左半部分，就将右边界移到中间值左边，如果目标值在右半部分，就将左边界移动到中间值右侧；
    //          3. 如果中间值小于左边界，那么说明右半部分有序。这种情况下如果目标值在右半部分，就将左边界移到中间值右侧，如果目标值在左半部分，就将右边界移到中间值左侧；
    //          4. 如果中间值等于左边界，说明中间值到左边界一直都是重复元素，那么将左边界右移一个元素，重新计算中间值。
    //          5. 该算法属于二分查找的变形，时间复杂度为O(logn)，空间复杂度为O(1)，其中n为数组的长度。
	bool search(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;
        while (l <= r) {
            int m = (l + r) / 2;
            if (nums[m] == target)  return true;
            if (nums[l] < nums[m]) {
                if (nums[l] <= target && target < nums[m])   r = m - 1;
                else l = m + 1;
            }
            else if (nums[l] > nums[m]) {
                if (nums[m] < target && target <= nums[r])   l = m + 1;
                else r = m - 1;
            }
            else l++;
        }
        return false;
	}
};

int main()
{
    int a[] = {1, 3, 5};
	vector<int> nums(a, a+3);
    Solution slt;
    bool rslt = slt.search(nums, 1);
    return 0;
}
