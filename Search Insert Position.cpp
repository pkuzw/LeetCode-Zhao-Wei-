///@file	Search Insert Position 
/*
			Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

			You may assume no duplicates in the array.

			Here are few examples.
			[1,3,5,6], 5 → 2
			[1,3,5,6], 2 → 1
			[1,3,5,6], 7 → 4
			[1,3,5,6], 0 → 0
*/
///@author	zhaowei
///@date	2015.06.16
///@version	1.0

///@date    2015.09.05
///@version 2.0

///@date	2015.09.23
///@version	2.1

#include <iostream>
#include <vector>

using namespace std;
/*
class Solution_v1
{
public:
	///@brief	在已经排好序的数组中查找目标元素。
	///@param	nums	已排好序的数组
	///@param	target	目标值
	///@return	如果该目标值存在，则返回目标值所在下标；否则返回该目标值应该插入的下标
	///@note	修改二分查找算法即可，时间复杂度为O(logn)，空间复杂度为O(1)
	///@author	zhaowei
	///@date	2015.06.16
	int searchInsert(vector<int>& nums, int target) 
	{
		//	处理边界情况
		if (target < nums[0])	
		{
			return 0;
		}
		if (target > nums[nums.size()-1])
		{
			return nums.size();
		}

		vector<int> rslt;
		rslt = binarySearch(nums, 0, nums.size()-1, target);		//二分查找
		if (rslt.size() == 1)
		{
			return rslt[0];
		}
		else
		{
			int p = rslt[0];
			int r = rslt[1];
			if (target > nums[r] && target < nums[p])
			{
				return r+1;
			}
		}
	}

	///@brief	二分查找
	///@param	nums	排好序的数组
	///@param	p		起始下标
	///@param	r		终止下标
	///@param	val		目标值
	///@return	如果目标值存在，则返回目标之所在下标；否则返回递归失效时的p值和r值
	vector<int> binarySearch(vector<int>& nums, int p, int r, int val)
	{
		vector<int> rslt;
		if (p > r)
		{
			rslt.push_back(p);
			rslt.push_back(r);
			return rslt;
		}
		int q = (p+r)/2;
		if (nums[q] == val)
		{
			rslt.push_back(q);
			return rslt;
		}
		else if (nums[q] < val)
		{
			return binarySearch(nums, q+1, r, val);
		}
		else
		{
			return binarySearch(nums, p, q-1, val);
		}
	}
};
*/
class Solution{
public:
	///@brief	查找目标值元素的下标，如果它存在在数组中，则返回所在下标，否则返回应该插入的位置。假设数组中没有重复元素
	///@param	nums	已经排好序的数组
	///@param	target	目标值
	///@return	返回目标值所在下标
	///@note	二分查找即可。迭代版。在跳出循环后，左边界即为应该插入的位置。时间复杂度为O(logn)，空间复杂度为O(1)。
    int searchInsert(vector<int>& nums, int target) {
		int l = 0, r = nums.size() - 1;
		while (l <= r) {
			int mid = (l + r) / 2;
			if (target < nums[mid])	r = mid - 1;
			else if (target > nums[mid])	l = mid + 1;
			else return mid;
		}
		return l;
    }
};

int main()
{
	vector<int> ivec;
	ivec.push_back(1);
	ivec.push_back(3);
	ivec.push_back(5);
	ivec.push_back(6);

	Solution slt;
	int input = 2;

	int rslt = slt.searchInsert(ivec, input);

	cout << rslt << endl;

	return 0;
}