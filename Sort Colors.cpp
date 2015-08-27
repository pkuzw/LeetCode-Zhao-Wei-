///@file	Sort Color
/*
Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, 
with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.
*/
///@author	zhaowei
///@date	2015.07.13
///@version 1.1

///@date	2015.08.27
///@version	2.0

#include <iostream>
#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	对数组nums进行排序
	///@param	nums	数组
	///@return  无
	///@note	手写快速排序（《算法导论》版），时间复杂度为O(nlogn)，空间复杂度为O(1)。
	void sortColors_quickSort(vector<int>& nums) {
		if (nums.empty())
		{
			return;
		}
		quickSort(nums, 0, nums.size()-1);
		return;
	}

	///@brief	对数组nums进行排序
	///@param	nums	数组
	///@return	无
	///@note	计数排序：共需要遍历两次。第一遍统计0，1，2的数目，第二遍直接将0，1，2从头到尾赋值给数组。时间复杂度为O(n)，空间复杂度为O(1)。
	void sortColors(vector<int>& nums) {
		int red_cnt = 0, white_cnt = 0, blue_cnt = 0;
		for (int i = 0; i != nums.size(); i++)
		{
			switch (nums[i])
			{
			case 0:	red_cnt++;break;
			case 1: white_cnt++;break;
			case 2: blue_cnt++;break;
			}
		}
		for (int i = 0; i != red_cnt; i++)
		{
			nums[i] = 0;
		}
		for (int i = red_cnt; i != red_cnt+white_cnt; i++)
		{
			nums[i] = 1;
		}
		for (int i = red_cnt+white_cnt; i != red_cnt+white_cnt+blue_cnt; i++)
		{
			nums[i] = 2;
		}
		return;
	}
private:
	///@brief	快速排序
	///@param	nums	待排序数组
	///@param	p		数组起始下标
	///@param	r		数组终止下标
	///@return  无
	///@note	快速排序的思想是分治，在指定范围内的数组内找到一个轴值，根据其将数组划分成两部分，左半部分小于等于轴值，有半部分大于轴值。
	void quickSort(vector<int>& nums, int p, int r)
	{
		if (p >= r)
		{
			return;
		}
		int q = partition(nums, p, r);
		quickSort(nums, p, q-1);
		quickSort(nums, q+1, r);
	}

	///@brief	找到轴值，并根据轴值进行划分
	///@param	nums	待排序数组
	///@param	p		数组起始下标
	///@param	r		数组终止下标
	///@return  返回轴值所在下标
	///@note	nums[0...i]是小于等于轴值x的部分，nums[i+1...j]是大于轴值的部分，nums[j+1...r]是未判定的部分
	int partition(vector<int>& nums, int p, int r)
	{
		int x = nums[r];
		int i = p-1;
		for (int j = p; j < r; j++)
		{
			if (nums[j] <= x)
			{
				i++;
				swap(nums[i], nums[j]);
			}
		}
		swap(nums[i+1], nums[r]);
		return i+1;
	}
};

/*
1. 用两个指针标记出红色气球的起始下标和蓝色气球的终止下标。然后从首尾向中间遍历。只需要遍历一次数组，时间复杂度为O(n)，空间复杂度为O(1)。
*/
class Solution {
public:
	void sortColors(vector<int>& nums) {
		int red = 0;
		int blue = nums.size() - 1;
		for (int i = red; i <= blue; i++)
		{
			if (nums[i] == 0)	swap(nums[red++], nums[i]);
			else if (nums[i] == 2)	swap(nums[blue--], nums[i--]);
		}
	}
};

int main()
{
	vector<int> test;
	for (int i = 0; i <= 3; i++)
	{
		test.push_back(0);
		test.push_back(1);
		test.push_back(2);
	}
// 	Solution_v1 slt_v1;
// 	slt_v1.sortColors(test);
	Solution slt;
	slt.sortColors(test);
	
	return 0;
}