///@file	Kth Largest Element in an Array
//			Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.
//			For example,
//			Given [3,2,1,5,6,4] and k = 2, return 5.
//			Note:
//			You may assume k is always valid, 1 ≤ k ≤ array's length.

///@author	zhaowei
///@date	2015.08.04
///@version	1.0

///@date	2015.08.10
///@version	2.0

#include <algorithm>
#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	找到第k大的元素
	///@param	nums	数组
	///@param	k		第k大
	///@return	返回第k大的元素
	///@note	排序。时间复杂度为O(nlogn)，空间复杂度为O(1)。还有更优的算法。待我下次查一下曲老师的课本。
	int findKthLargest(vector<int>& nums, int k) {
		sort(nums.begin(), nums.end(), greater<int>());
		return nums[k-1];
	}
};

class Solution {
public:
	int findKthLargest(vector<int>& nums, int k) {
		sort(nums.begin(), nums.end());
		return nums[nums.size() - k];
	}
};

int main()
{
	vector<int> nums;
	nums.push_back(3);
	nums.push_back(2);
	nums.push_back(1);
	nums.push_back(6);
	nums.push_back(6);
	nums.push_back(4);
	Solution slt;
	int rslt = slt.findKthLargest(nums, 2);
	return 0;
}