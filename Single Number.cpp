﻿///@file	Single Number
/*
Given an array of integers, every element appears twice except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
*/
///@author	zhaowei
///@date	2015.07.25
///@version	1.0

///@date	2015.08.21
///@version	2.0

///@date	2016.01.11
///@version	2.1

#include <unordered_map>
#include <vector>
using namespace std;

class Solution_v1 {
public:
	///@brief	如果一个数组中每个元素都出现了两遍，只有一个元素例外。找出这个元素。
	///@param	nums	数组
	///@return	返回只出现了一次的元素
	/* @note	利用Hash Map，将每个元素先存入哈希表，然后再遍历哈希表，就可以找到只出现一次的元素了。时间复杂度为O(n)，空间复杂度为O(n)。*/
	int singleNumber(vector<int>& nums) {
		unordered_map<int, int> num_cnt;	//	哈希表
		for (int i = 0; i != nums.size(); i++)
		{
			if (num_cnt.find(nums[i]) == num_cnt.end())
			{
				num_cnt.insert(make_pair(nums[i], 1));
			}
			else
			{
				num_cnt[nums[i]]++;
			}
		}

		for (unordered_map<int, int>::iterator i = num_cnt.begin(); i != num_cnt.end(); i++)
		{
			if (i->second == 1)
				return i->first;
		}
		return 0;
	}
};

class Solution {
public:
	///@brief	寻找数组中唯一一个没有出现2次的元素
	///@param	nums	数组
	///@return	返回该元素
	///@note	1. 位运算；
	//			2. 利用异或运算的特性，如果一个数和自身异或得到0，同时一个数和0异或得到自身的特点，将数组中的所有元素都异或一遍即可，最后得到的结果就是那个没有出现两次的元素。
	//			3. 时间复杂度为O(n)，空间复杂度为O(1)。
	int singleNumber(vector<int>& nums) {
		int rslt = nums[0];
		for (int i = 1; i != nums.size(); i++)
			rslt ^= nums[i];
		return rslt;
	}
};

int main()
{
	int n[7] = {1,1,2,2,3,3,4};
	vector<int> nums;
 	for (int i = 0; i != 7; i++)
 		nums.push_back(n[i]);

	Solution slt;
	int rslt = slt.singleNumber(nums);
	return 0;
}