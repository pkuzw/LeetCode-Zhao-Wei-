﻿///@file	Contains Duplicate II 
/*
Given an array of integers and an integer k, find out whether there there are two distinct indices i and j 

in the array such that nums[i] = nums[j] and the difference between i and j is at most k. 
*/
///@author	zhaowei
///@date	2015.07.28
///@version	1.0

///@date	2015.08.10
///@version	1.1

///@date	2016.01.27
///@version	1.2

#include <unordered_map>
#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	给定一个数组和整数k，判断数组中是否存在重复的元素且这两个重复元素的下标距离之差不超过k
	///@param	nums	数组
	///@param	k		距离上限
	///@return	如果存在这样的重复元素，返回true；否则返回false
	/* @note	从头到尾遍历数组，遇到没有出现的元素就放入hash表并记录其下标，如果遇到已经在哈希表中的元素，则比较二者的距离差，如果大于k
				则更新哈希表的值，否则返回true。遍历完数组后返回false。时间复杂度为O(n)，空间复杂度为O(n)。 */
	bool containsNearbyDuplicate(vector<int>& nums, int k) {
		if (nums.empty())	return false;

		unordered_map<int, int> hash_table;
		for (int i = 0; i < nums.size(); i++)
		{
			if (hash_table.find(nums[i]) == hash_table.end())
				hash_table[nums[i]] = i;
			else
			{
				if (i - hash_table[nums[i]] > k)	
					hash_table[nums[i]] = i;
				else
					return true;
			}
		}
		return false;
	}
};

class Solution {
public:
	bool containsNearbyDuplicate(vector<int>& nums, int k) {
		unordered_map<int, int> hash_tbl;
		for (int i = 0; i != nums.size(); i++) {
			if (hash_tbl.find(nums[i]) == hash_tbl.end())	hash_tbl[nums[i]] = i;
			else {
				if (i - hash_tbl[nums[i]] <= k)	return true;
				hash_tbl[nums[i]] = i;
			}
		}
		return false;
	}
};

int main()
{
	int n[10] = {1,2,3,4,5,2,4,5,6,2};
	vector<int> nums;
	for (int i = 0; i < 10; i++)
		nums.push_back(n[i]);

	Solution slt;
	bool rslt = slt.containsNearbyDuplicate(nums, 2);

	Solution_v1 slt_v1;
	rslt = slt_v1.containsNearbyDuplicate(nums, 2);
	return 0;
}