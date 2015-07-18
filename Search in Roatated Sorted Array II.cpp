///@file	Search in Rotated Sorted Array II
/*
Follow up for "Search in Rotated Sorted Array":
Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search. If found in the array return its index, otherwise return -1.

What if duplicates are allowed?

(i.e., 0 0 0 1 1 2 2 2 4 4 5 5 6 6 7 7 7 might become 4 4 5 5 6 6 7 7 7 0 0 0 1 1 2 2 2)

Would this affect the run-time complexity? How and why?

Write a function to determine if a given target is in the array.
*/
///@author	zhaowei
///@date	2015.07.18
///@version	1.1

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	///@brief	查找已排序数组中是否存在某元素（默认为升序）
	///@param	nums	数组
	///@param	target	待查找值
	///@return	如果数组中存在该值，则返回true，否则返回false
	///@author	zhaowei
	///@date	2015.07.15
	///@note	
	bool search(vector<int>& nums, int target)
	{

	}
};

int main()
{
	vector<int> nums;
// 	for (int i = 6; i <= 10; i++)
// 	{
// 		nums.push_back(i);
// 	}
// 	for (int i = 1; i <= 5; i++)
// 	{
// 		nums.push_back(i);
// 	}

//	nums.clear();
	nums.push_back(1);
	nums.push_back(1);
	nums.push_back(3);
	nums.push_back(1);
	Solution slt;
	for (int i = 0; i != nums.size(); i++)
	{
		cout << nums[i] << ' ';
	}
	cout << endl;
	cout << "Target's Index: " << endl;
// 	int k = 0;
// 	while (k <= 12)
// 	{
// 		cout << slt.search(nums, k) << endl;
// 		k++;
// 	}
	cout << slt.search(nums, 1) << endl;
	
	return 0;
}