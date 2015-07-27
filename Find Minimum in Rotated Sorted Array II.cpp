///@file	Find Minimum in Rotated Sorted Array II
/*
Follow up for "Find Minimum in Rotated Sorted Array":
What if duplicates are allowed?

Would this affect the run-time complexity? How and why?
Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

The array may contain duplicates.
*/
///@author	zhaowei
///@date	2015.07.27
///@version	1.0

#include <vector>

using namespace std;

class Solution {
public:
	///@brief	在一个部分翻转的有序数组中查找最小值
	///@param	nums	数组
	///@return	返回数组中的最小值
	/* @note	如果数组中有重复元素，可能使得左边界指针，右边界指针以及中间元素相等。此时直接采用枚举法遍历即可。
				其余与没有重复元素的解法相同，二分查找。时间复杂度为O(n)，空间复杂度为O(1)。*/
	int findMin(vector<int>& nums) {
		if (nums.size() == 1)	return nums[0];

		int l = 0;
		int r = nums.size()-1;

		if (nums[l] < nums[r])	return nums[l];

		else if (nums[l] == nums[r])
		{
			int min = INT_MAX;
			for (int i = 0; i != nums.size(); i++)
				if (nums[i] < min)	min = nums[i];
			return min;
		}

		else
		{
			while (l != r-1)
			{
				int m = (l + r) / 2;
				if (nums[l] <= nums[m])	l = m;	//	因为有重复元素，所以这里比没有重复元素的情况要多一个=号来判定左边界值和中间值
				else					r = m;
			}
			return nums[l] < nums[r] ? nums[l] : nums[r];
		}
	}
};

int main()
{
	int n[10] = {5,6,6,6,9,9,2,2,3,4};
	vector<int> nums;
	for (int i = 0; i != 10; i++)	
		nums.push_back(n[i]);

	Solution slt;
	int rslt = slt.findMin(nums);
	return 0;
}