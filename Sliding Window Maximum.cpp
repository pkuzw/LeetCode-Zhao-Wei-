///@file	Sliding Window Maximum 
/*
Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
1 [3  -1  -3] 5  3  6  7       3
1  3 [-1  -3  5] 3  6  7       5
1  3  -1 [-3  5  3] 6  7       5
1  3  -1  -3 [5  3  6] 7       6
1  3  -1  -3  5 [3  6  7]      7
Therefore, return the max sliding window as [3,3,5,5,6,7].

Note: 
You may assume k is always valid, ie: 1 ≤ k ≤ input array's size for non-empty array.

Follow up:
Could you solve it in linear time?
*/
///@author	zhaowei
///@date	2015.08.02
///@version	1.0

#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

class Solution_v1 {
public:
	///@brief	计算最大窗口值
	///@param	nums	数组
	///@param	k		窗口大小
	///@return	返回窗口最大值的累加值
	/* @note	用一个双端队列保存当前窗口中的最大元素，队首元素是当前窗口的最大值下标，队列中的元素会按照它所代表的数组元素的大小降序排列。至少保证有一个元素。
				时间复杂度为O(nlogn)，空间复杂度为O(n)。*/
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		vector<int> rslt;
		deque<int> deq;
		for (int i = 0; i != nums.size(); i++)
		{
			if (!deq.empty() && deq.front() == i-k)	//	当队首元素是应该出窗口时，弹出队首
				deq.pop_front();
			while (!deq.empty() && nums[deq.back()] < nums[i])	//	当要添加的元素比队尾元素大时，弹出队尾直到队尾元素不比当前元素小
				deq.pop_back();

			deq.push_back(i);	//	压入当前元素的下标

			if (i >= k-1)	//	统计每一次窗口的最大值，即队首元素
				rslt.push_back(nums[deq.front()]);
		}
		return rslt;
	}
};

class Solution {
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		vector<int> rslt;
		deque<int> deq;
		for (int i = 0; i != nums.size(); i++)
		{
			if (!deq.empty() && i - deq.front() >= k)
				deq.pop_front();
			while (!deq.empty() && nums[i] > nums[deq.back()])
				deq.pop_back();

			deq.push_back(i);

			if (i >= k-1)
				rslt.push_back(nums[deq.front()]);
		}
		return rslt;
	}
};

int main()
{
	vector<int> nums;
	int n[8] = {1,3,-1,-3,5,3,6,7};
	for (int i = 0; i != 8; i++)	nums.push_back(n[i]);

	Solution slt;
	vector<int> rslt = slt.maxSlidingWindow(nums, 3);

	return 0;
}