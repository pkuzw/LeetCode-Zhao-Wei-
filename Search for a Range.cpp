///@file	Search for a Range
/*			Given a sorted array of integers, find the starting and ending position of a given target value.

			Your algorithm's runtime complexity must be in the order of O(log n).

			If the target is not found in the array, return [-1, -1].

			For example,
			Given [5, 7, 7, 8, 8, 10] and target value 8,
			return [3, 4].

*/
///@author  zhaowei
///@date	2015.06.16
///@version	1.0

///@date    2015.09.05
///@version 2.0

#include <iostream>
#include <vector>
using namespace std;
/*
class Solution_v1
{
public:
	///@brief	给定一个已经排好序的数组，查找其中元素的范围
	///@param	nums	已排好序的数组
	///@param	target	目标值
	///@return	如果该目标值存在，则返回数组中的元素下标范围；否则返回[-1, -1]
	///@note	先通过二分查找找到目标值任意一个元素所在下标；然后以这个下标为中心向两侧扩展，扩展的过程也是以2^n形式。
	//			时间复杂度为O(logn)，空间复杂度为O(1)
	///@author	zhaowei
	///@date	2015.06.16
	vector<int> searchRange(vector<int>& nums, int target) 
	{
		int numsSize = nums.size();
		int center = binarySearch(nums, 0, numsSize-1, target);
		vector<int> rslt;

		int increment[32];	//	预先设置一个包含2^n幂的数组，这样方便快速从中心点向两侧扩展
		increment[0] = 0;
		for (int i = 1; i < 32; i++)
		{
			increment[i] = 1;
			increment[i] = increment[i] << (i-1);
		}

		rslt.push_back(leftExtend(nums, increment, center));
		rslt.push_back(rightExtend(nums, increment, center));
		return rslt;
	}

	///@brief	二分查找
	///@param	nums	排好序的数组
	///@param	p		起始下标
	///@param	r		终止下标
	///@param	val		目标值
	///@return	如果目标值存在，则返回目标之所在下标；否则返回-1
	int binarySearch(vector<int>& nums, int p , int r, int val)
	{
		if (p > r)
		{
			return -1;
		}
		int q = (p+r)/2;
		if (val == nums[q])
		{
			return q;
		}
		else if (val < nums[q])
		{
			return binarySearch(nums, p, q-1, val);
		}
		else
		{
			return binarySearch(nums, q+1, r, val);
		}
	}

	///@brief	扩展目标值的左边界
	///@param	nums	排好序的数组
	///@param	increment	保存有2^n幂的数组
	///@param	center	目标值之一所在下标
	///@return	返回目标值的左边界
	int leftExtend(vector<int>& nums, int* increment, int center)
	{
		if (center == 0 || center == -1)
		{
			return center;
		}
		int left_bound = center;
		
		int k = 0;
		while (nums[left_bound] == nums[center])
		{
			k = decreNum(nums, increment, left_bound, nums[center]);	//	查找当前边界所能扩张的最大的2的n次幂
			if (k == 0)
			{
				return left_bound;
			}
			left_bound -= increment[k];				
		}
	}
	
	///@brief	扩展目标值的左边界
	///@param	nums	排好序的数组
	///@param	increment	保存有2^n幂的数组
	///@param	center	目标值之一所在下标
	///@return	返回目标值的左边界
	int rightExtend(vector<int>& nums, int* increment, int center)
	{
		if (center == nums.size()-1 || center == -1)
		{
			return center;
		}
		int right_bound = center;
		
		int k = 0;
		while (nums[right_bound] == nums[center])
		{
			k = increNum(nums, increment, right_bound, nums[center]);	//	查找当前边界所能扩张的最大的2的n次幂
			if (k == 0)
			{
				return right_bound;
			}
			right_bound += increment[k];				
		}
	}

	///@brief	查找当前左边界所能扩张的在increment数组中的最大值
	///@param	nums	已排好序的数组
	///@param	increment	保存有2^n幂的数组
	///@param	bound	左边界
	///@param	target	目标值
	///@return	返回左边界所能扩张的在Increment数组中的最大值下标
	int decreNum(vector<int>& nums, int* increment, int bound, int target)
	{		
		for (int i = 0; i < 32; i++)
		{
			if (bound >= increment[i])
			{
				if (nums[bound-increment[i]] != target)
				{
					return i-1;
				}
			}
			else
				return i-1;						
		}
	}

	///@brief	查找当前右边界所能扩张的在increment数组中的最大值
	///@param	nums	已排好序的数组
	///@param	increment	保存有2^n幂的数组
	///@param	bound	右边界
	///@param	target	目标值
	///@return	返回右边界所能扩张的在Increment数组中的最大值下标
	int increNum(vector<int>& nums, int* increment, int bound, int target)
	{		
		for (int i = 0; i < 32; i++)
		{
			if (nums.size()-1-bound >= increment[i])
			{
				if (nums[bound+increment[i]] != target)
				{
					return i-1;
				}
			}
			else
				return i-1;						
		}
	}
};
*/

/*
1. 先找左边界，通过二分查找的改进，将目标值大于中间值的情形转到start = mid + 1，其余情况都是end = mid即可；
2. 找到左边界后，将其固定住再找右边界，将目标值小于中间值的情形转到end = mid，其余情况是start = mid + 1。
3. 时间复杂度为O(logn)
*/
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> rslt(2, -1);
        int start = 0, end = nums.size() - 1;
        while (start < end){    // 找左边界
            int mid = (start + end) / 2;
            if (nums[mid] < target) start = mid + 1;
            else    end = mid;
        }
        if (nums[start] != target)  return rslt;
        rslt[0] = start;
        end = nums.size();
        while (start < end){    //  找右边界
            int mid = (start + end) / 2;
            if (nums[mid] > target) end = mid;
            else    start = mid + 1;
        }
        rslt[1] = start - 1;
        return rslt;
    }
};

int main()
{

	vector<int> test;
	for (int i = 0; i < 1000; i++)
	{		
		test.push_back(5);
// 		for (int j = i; j < 10; j++)
// 		{
// 			
// 		}
	}

	Solution slt;

	vector<int> rslt = slt.searchRange(test, 5);
	for (int i = 0; i != rslt.size(); i++)
	{
		cout << rslt[i] << " ";
	}
	cout << endl;
	return 0;
}