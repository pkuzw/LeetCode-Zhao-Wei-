///@file	Single Number II
/*
Given an array of integers, every element appears three times except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory? 
*/
///@author	zhaowei
///@date	2015.07.27
///@version	1.0

///@date	2015.08.21
///@version	2.0

///@date	2016.01.11
///@version	2.1

#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution_v1 {
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

///@note	因为数组中每个元素都出现三次，只有一个例外，所以对元素的每一位进行1的计数，在遍历所有元素后，如果该位的1累加之和模3不为0，
//			则说明该位是出现不是3次的元素的位，然后再逐一对各位进行累加即可。时间复杂度为O(n)，空间复杂度为O(1)。
class Solution_v2 {
public:
	int singleNumber(vector<int>& nums) {
		vector<int> cnt(32, 0);
		int rslt = 0;
		for (int i = 0; i != nums.size(); i++)
		{
			for (int j = 0; j != 32; j++)
			{
				if ((nums[i] >> j) & 1)
					cnt[j] = (cnt[j] + 1) % 3;
			}
		}
		for (int i = 0; i != 32; i++)
		{
			if (cnt[i])
				rslt += (1 << i);
		}
		return rslt;
	}
};

class Solution {
public:
	///@brief	找出数组中出现次数不为3的元素
	///@param	nums	数组
	///@return	返回出现次数不为3的元素
	///@note	1. 位运算；2. 因为数组中除了一个特殊元素，其余所有元素都只出现三次。所以对所有元素的1位进行累加，如果模3后不为0，则说明该位是特殊元素的1位，否则就是0位；
	//			3. 时间复杂度为O(n)，空间复杂度为O(1)。
	int singleNumber(vector<int>& nums) {
		int cnt[32] = {0};
		int rslt = 0;
		for (int i = 0; i != nums.size(); i++) {
			for (int j = 0; j != 32; j++) {
				if ((nums[i] >> j) & 1)
					cnt[j]++;
			}
		}
		for (int i = 31; i >= 0; i--) {
			if (cnt[i] % 3) {
				int j = 1;
				j <<= i;
				rslt |= j;				
			}
		}
		return rslt;
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

	Solution_v1 slt_v1;
	int rslt = slt_v1.singleNumber(nums);
	Solution slt;
	rslt = slt.singleNumber(nums);
	return 0;
}