///@file	Search in Rotated Sorted Array II
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

#include <iostream>
#include <vector>

using namespace std;

class Solution {
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

int main()
{
	vector<int> nums;
// 	for (int i = 6; i <= 10; i++)
// 	{
// 		nums.push_back(i);
// 	}
// 	for (int i = 1; i <= 5; i++)
// 	{
// 		nums.push_back(i);
// 	}

//	nums.clear();
	nums.push_back(5);
	nums.push_back(1);
	nums.push_back(3);
	Solution slt;
	for (int i = 0; i != nums.size(); i++)
	{
		cout << nums[i] << ' ';
	}
	cout << endl;
	cout << "Target's Index: " << endl;
// 	int k = 0;
// 	while (k <= 12)
// 	{
// 		cout << slt.search(nums, k) << endl;
// 		k++;
// 	}
	cout << slt.search(nums, 3) << endl;
	
	return 0;
}