///@file	Contains Duplicate
/*
Given an array of integers, find if the array contains any duplicates. 

Your function should return true if any value appears at least twice in the array, and it should return false if 

every element is distinct.
*/
///@author	zhaowei
///@date	2015.07.25
///@version	1.0

///@date	2015.08.10
///@version	2.0

#include <unordered_set>
#include <vector>
using namespace std;

class Solution_v1 {
public:
	///@brief	判断一个数组中每个元素是否只出现了一次
	///@param	nums	数组
	///@return	如果数组中有重复元素则返回true，否则返回false
	/* @note	利用Hash Map，将每个元素先存入哈希表，如果哈希表中已经存在该元素，则直接返回false即可。时间复杂度为O(n)，空间复杂度为O(n)。*/
	bool containsDuplicate(vector<int>& nums) {
		unordered_set<int> hash_table;	//	哈希表
		for (int i = 0; i != nums.size(); i++)
		{
			if (hash_table.find(nums[i]) == hash_table.end())			
				hash_table.insert(nums[i]);			
			else
				return true;
		}
		return false;
	}
};

class Solution {
public:
	bool containsDuplicate(vector<int>& nums) {
		unordered_set<int> ht;
		for (int i = 0; i != nums.size(); i++)
		{
			if (ht.find(nums[i]) == ht.end())	ht.insert(nums[i]);
			else	return true;
		}
		return false;
	}
};

int main()
{
	int n[7] = {1,14,11,2,34,32,4};
	vector<int> nums;
	 	for (int i = 0; i != 7; i++)
	 		nums.push_back(n[i]);

	Solution slt;
	nums.clear();
	bool rslt = slt.containsDuplicate(nums);
	return 0;
}