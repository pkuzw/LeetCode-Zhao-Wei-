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
///@version	1.1

///@date	2016.01.26
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
	///@brief	利用快速排序的partition思想找到数组中的第k大的数
	///@param	nums	数组
	///@param	k		第k大的数
	///@return	返回数组中第k大的数
	///@note	1. 利用快速排序中的Partition思想，找出第k大的数。
	int findKthLargest(vector<int>& nums, int k) {
		const int size_nums = nums.size();
		int left = 0, right = size_nums;
		while (left < right) {
			int i = left, j = right - 1, pivot = nums[left];
			while (i <= j) {
				while (i <= j && nums[i] >= pivot) i++;
				while (i <= j && nums[j] < pivot) j--;
				if (i < j)	swap(nums[i++], nums[j--]);
			}
			swap(nums[left], nums[j]);
			if (j == k - 1)	return nums[j];
			else if (j < k - 1) left = j + 1;
			else right = j;
		}
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
	int rslt = slt.findKthLargest(nums, 11);
	return 0;
}