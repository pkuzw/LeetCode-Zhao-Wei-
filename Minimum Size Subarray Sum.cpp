///@file	Minimum Size Subarray Sum
/*
Given an array of n positive integers and a positive integer s, find the minimal length of a subarray of which the sum ≥ s. If there isn't one, return 0 instead.

For example, given the array [2,3,1,2,4,3] and s = 7,
the subarray [4,3] has the minimal length under the problem constraint. 
*/
///@author	zhaowei
///@date	2015.08.04
///@version	1.0

///@date	2015.08.11
///@version	1.1

///@date	2016.01.25
///@version	1.2

#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	计算最短子串和不小于指定值的长度
	///@param	s	指定值
	///@param	nums	数组
	///@return	返回最短长度。如果没有符合条件的子串，则返回0.
	///@note	用左右两个指针标记处符合条件的子串，先固定住右边界，然后再缩短左边界。时间复杂度为O(n)，空间复杂度为O(1)。
	int minSubArrayLen(int s, vector<int>& nums) {
		if (nums.empty())	return 0;

		int len = nums.size();
		int r = 0;
		int l = 0;
		int rslt = INT_MAX;
		int sum = 0;
		while (r < len)
		{
			sum += nums[r++];

			while (sum >= s)
			{
				sum -= nums[l++]	;
				rslt = min(rslt, r-l+1);		//	因为l和r都是已经自增过1的，所以计算长度时相减就抵消了
			}
		}
		
		return rslt == INT_MAX ? 0 : rslt;	//	如果rslt == INT_MAX，说明即使将所有的元素累加，都不够s那么大
	}
};

/*
设置左右两个指针，先将右值针选定到能够使得和大于等于s的位置，然后将左指针尽可能的向右移动，然后记录下满足条件的最短距离；
然后继续移动右值针，直到到达右边界，期间只要能够使得范围内的数之和大于等于指定值就停止移动，并开始移动左指针。
最后输出这个过程中记录的最小范围。
*/
class Solution {
public:
	///@note	1. 设置左右边界指针，先将右边界移动至累积和大于指定值的位置，然后再将左指针尽可能的右移，保证累积和不能小于指定值，记录下当前
	//			   子数组的长度；
	//			2. 直到右值针到达右边界为止，找到最短子数组。
	int minSubArrayLen(int s, vector<int>& nums) {
		int l = 0, r = 0, rslt = INT_MAX, sum = 0;
		while (r < nums.size()) {
			sum += nums[r++];
			while (sum >= s) {
				sum -= nums[l++];
				rslt = min(rslt, r - l + 1);
			}
		}
		return rslt == INT_MAX ? 0 : rslt;
	}
};

int main()
{
	vector<int> nums;	//2,3,1,2,4,3
	nums.push_back(2);
	nums.push_back(3);
	nums.push_back(1);
	nums.push_back(2);
	nums.push_back(4);
	nums.push_back(3);
	Solution slt;
	int rslt = slt.minSubArrayLen(10, nums);

	Solution_v1 slt_v1;
	int rslt1 = slt_v1.minSubArrayLen(10, nums);
	return 0;
}