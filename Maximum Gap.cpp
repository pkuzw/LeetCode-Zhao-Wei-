///@file	Maximum Gap
/*
Given an unsorted array, find the maximum difference between the successive elements in its sorted form.

Try to solve it in linear time/space.

Return 0 if the array contains less than 2 elements.

You may assume all elements in the array are non-negative integers and fit in the 32-bit signed integer range.
*/
///@author	zhaowei
///@date	2015.07.30
///@version	1.0
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	///@brief	给定一组乱序的数组，找出排好序后两个相邻元素的最大差值。要求时间复杂度为O(n)，空间复杂度为O(n)
	///@param	nums	数组
	///@return	返回排好序后连续的两个元素的最大差值
	/* @note	桶排序的思想：先找出数组中的最大值和最小值，然后计算出桶的容量 = (Max - Min) / 元素个数 + 1，接着计算桶的个数 = (Max - Min) / 桶的容量 + 1，
				将元素放入桶中并统计每个桶的最大值和最小值，排好序的相邻元素的最大差值就是相邻桶之间的后桶最小值减去前桶的最大值。时间复杂度为O(n)，
				空间复杂度为O(n)。*/
	int maximumGap(vector<int>& nums) {
		if (nums.size() < 2)	return 0;
		int size = nums.size();
		int max_n = INT_MIN;
		int min_n = INT_MAX;
		for (int i = 0; i != size; i++)
		{
			if (nums[i] < min_n)	min_n = nums[i];
			if (nums[i] > max_n)	max_n = nums[i]; 
		}

		int bucket_capacity = (max_n - min_n) / size + 1;	//桶容量
		int bucket_num = (max_n - min_n) / bucket_capacity + 1;	//	桶数目

		vector<int> bucket_max(bucket_num, INT_MIN);
		vector<int> bucket_min(bucket_num, INT_MAX);

		for (int i = 0; i != size; i++)
		{
			int indx = (nums[i] - min_n) / bucket_capacity;

			if (nums[i] < bucket_min[indx])
				bucket_min[indx] = nums[i];

			if (nums[i] > bucket_max[indx])
				bucket_max[indx] = nums[i];
		}

		int max_distance = INT_MIN;	//	最大差值
		int pre = 0;
		for (int i = 1; i < bucket_num; i++)
		{
			if (bucket_min[i] == INT_MAX || bucket_max[i] == INT_MIN)	continue;

			if (bucket_min[i] - bucket_max[pre] > max_distance)
			{
				max_distance = bucket_min[i] - bucket_max[pre];				
			}
			pre = i;
		}
		return max_distance;
	}
};

int main()
{
	vector<int> nums;
	int n[] = {1, 10000000};
	for (int i = 0; i != 2; i++)
		nums.push_back(n[i]);

	Solution slt;
	int rslt = slt.maximumGap(nums);

	return 0;
}