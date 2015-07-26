///@file	Single Number II
/*
Given an array of integers, every element appears three times except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory? 
*/
///@author	zhaowei
///@date	2015.07.27
///@version	1.0

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
	///@brief	找到数组中出现次数不是3次的数
	///@param	nums	数组
	///@return	返回这个独特的数
	/* @note	利用哈希表，先将数组中数出现的次数记录下来，然后再遍历哈希表即可。时间复杂度为O(n)，空间复杂度为O(n)。*/
	int singleNumber(vector<int>& nums) {
		unordered_map<int, int> ht;
		for (int i = 0; i != nums.size(); i++)
			ht[nums[i]]++;

		for (unordered_map<int, int>::iterator i = ht.begin(); i != ht.end(); i++)
			if (i->second != 3)
				return i->first;
	}
};

int main()
{
	vector<int> nums;
	nums.push_back(1);
	nums.push_back(1);
	nums.push_back(1);

	nums.push_back(2);
	nums.push_back(2);
	nums.push_back(2);

	nums.push_back(3);
	nums.push_back(3);

	Solution slt;
	int rslt = slt.singleNumber(nums);
	return 0;
}