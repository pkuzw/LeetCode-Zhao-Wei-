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

///@date	2015.08.13
///@version	1.1

///@date	2016.01.16
///@version	1.2

#include <vector>
#include <algorithm>

using namespace std;

class Solution_v1 {
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

/*
桶排序。桶的容量 = （最大值 - 最小值） / 元素数 + 1；桶的数目 = (最大值 - 最小值) / 桶容量 + 1。排好序的元素的最大差值为相邻两个桶的
后桶最小值减去前桶最大值的最大差值。
*/
class Solution {
public:
	int maximumGap(vector<int>& nums) {
		if (nums.size() < 2)	return 0;
		int max_num = INT_MIN;
		int min_num = INT_MAX;
		for (int i = 0; i != nums.size(); i++) {
			if (nums[i] > max_num)	max_num = nums[i];
			if (nums[i] < min_num)	min_num = nums[i];
		}

		unsigned bucket_capacity = (max_num - min_num) / nums.size() + 1;
		unsigned bucket_num = (max_num - min_num) / bucket_capacity + 1;
		vector<int>max_bucket(bucket_num, INT_MIN);
		vector<int>min_bucket(bucket_num, INT_MAX);

		for (int i = 0; i != nums.size(); i++) {
			if (nums[i] > max_bucket[(nums[i] - min_num) / bucket_capacity])	
				max_bucket[(nums[i] - min_num) / bucket_capacity] = nums[i];
			if (nums[i] < min_bucket[(nums[i] - min_num) / bucket_capacity])
				min_bucket[(nums[i] - min_num) / bucket_capacity] = nums[i];			
		}

		int max_gap = INT_MIN;
		int j = 0;
		for (int i = 1; i != bucket_num; i++) {
			if (min_bucket[i] == INT_MAX || max_bucket[j] == INT_MIN)	continue;
			if (min_bucket[i] - max_bucket[j] > max_gap) {
				max_gap = min_bucket[i] - max_bucket[j];		
			}
			j = i;
		}
		return max_gap;
	}
};

///@brief	leetcode修改了测试数据，增加了连续相同数据，v1.0和v1.1两个版本的代码WA在了{1, 1, 1, 1}上面

int main()
{
	vector<int> nums;
	int n[] = {3, 6, 9, 1};
	for (int i = 0; i != 4; i++)
		nums.push_back(n[i]);

	Solution slt;
	int rslt = slt.maximumGap(nums);

	return 0;
}