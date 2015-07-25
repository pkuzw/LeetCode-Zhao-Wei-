///@file	Majority Element
/*
Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.

You may assume that the array is non-empty and the majority element always exist in the array.
*/
///@author	zhaowei
///@date	2015.07.26
///@version	1.0

#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
	///@brief	如果数组中某个元素的出现次数大于等于一半，找到这个元素
	///@param	nums	数组
	///@return	返回这个主要的元素
	/* @note	利用哈希表来记录数组中元素出现的次数，然后遍历哈希表即可。时间复杂度为O(n)，空间复杂度为O(n)。*/
	int majorityElement(vector<int>& nums) {
		unordered_map<int, int> hash_table;
		for (int i = 0; i != nums.size(); i++)
		{
			hash_table[nums[i]]++;
		}

		for (unordered_map<int, int>::iterator i = hash_table.begin(); i != hash_table.end(); i++)
		{
			if (i->second >= nums.size() / 2)
				return i->first;
		}
		return 0;
	}
};

int main()
{
	int n[10] = {1,1,1,1,1,1,2,3,4,5};
	vector<int> nums;
	for (int i = 0; i != 10; i++)
		nums.push_back(n[i]);

	Solution slt;
	int rslt = slt.majorityElement(nums);

	return 0;
}