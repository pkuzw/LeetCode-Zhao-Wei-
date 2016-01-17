///@file	Majority Element
/*
Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.

You may assume that the array is non-empty and the majority element always exist in the array.
*/
///@author	zhaowei
///@date	2015.07.26
///@version	1.0

///@date	2015.08.13
///@version	2.0

///@date	2016.01.17
///@version	2.1

#include <iostream>
#include <unordered_map>

using namespace std;

class Solution_v1 {
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

/*
majority vote algorithm. 投票法能够找出一个数组中出现次数超过一半的元素。它的做法是将初始元素作为众数，然后开始遍历数组。在遍历数组的过程中，
如果遇到和当前众数相同的元素，则计数器自增1，否则自减1；如果计数器已经到0，则将众数改变为当前元素，并修改计数器值。
*/
class Solution_v2 {
public:
	int majorityElement(vector<int>& nums) {
		int a = 0;
		int cnt = 0;
		for (int i = 0; i != nums.size(); i++)
		{
			if (nums[a] == nums[i])	cnt++;			
			else
			{
				if (!cnt)
				{
					a = i;
					cnt++;
				}
				else	cnt--;							
			}
		}
		return nums[a];
	}
};

class Solution {
public:
	///@brief	寻找众数
	///@param	nums	数组
	///@return	返回众数
	///@note	1. 投票法；2. 遍历数组，当前元素为众数时，则将计数器自增1；
	//			3. 否则看计数器是否为0，如果为0则修改众数，并将计数器自增1；
	//			4. 如果计数器不为0，则将计数器自减1；
	//			5. 时间复杂度为O(n)，空间复杂度为O(1)。
	int majorityElement(vector<int>& nums) {
		int cnt = 0, a = 0;
		for (int i = 0; i != nums.size(); i++) {
			if (nums[i] == nums[a])	cnt++;
			else {
				if (!cnt) {
					a = i;
					cnt++;
				}
				else {
					cnt--;
				}
			}
		}
		return nums[a];
	}
};

int main()
{
	int n[10] = {1,1,1,1,2,2,2,2,2,5};
	vector<int> nums;
	for (int i = 0; i != 10; i++)
		nums.push_back(n[i]);

	Solution slt;
	int rslt = slt.majorityElement(nums);

	return 0;
}