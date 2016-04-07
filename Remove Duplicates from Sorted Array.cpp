/* @file	Remove Duplicates from Sorted Array
			Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.

			Do not allocate extra space for another array, you must do this in place with constant memory.

			For example,
			Given input array nums = [1,1,2],

			Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively. 
			
			It doesn't matter what you leave beyond the new length.
	
	@author		zhaowei
	@date		2015.06.10
	@version	1.0
*/

///@date    2015.09.07
///@version 2.0

///@date	2015.09.22
///@version	2.1

///@date    2016.04.07
///@version 2.2

#include <iostream>
#include <vector>
using namespace std;

class Solution_v1
{
public:
	///@brief	移除已经排好序的数组中的重复元素
	///@param	nums	已经排好序的数组
	///@return	返回移除重复元素后的数组的长度
	///@author	zhaowei
	///@date	2015.06.10
	int removeDuplicates(vector<int>& nums) {
		if (nums.empty())	//	注意排除空数组的情形
		{
			return 0;
		}
		int j = 0;	//	用于标记下一个不重复元素应该交换的位置
		for (int i = 0; i != nums.size(); i++)	//	遍历数组
		{
			if (nums[i] == nums[j])
			{
				continue;
			}
			else
			{
				swapNum(nums[j+1], nums[i]);
				j++;
			}
		}
		return j+1;
	}
private:
	///@brief	交换两元素
	///@author	zhaowei
	///@date	2015.06.10
	void swapNum(int& a, int& b)
	{
		int t = a;
		a = b;
		b = t;
	}
};

class Solution_v2 {
public:
	///@brief	删除已经排好序的数组中的重复元素
	///@param	nums	排好序的数组
	///@return	返回删除元素后的数组大小，并把新数组以引用形参传出
	///@note	1. 用一个下标标记应该交换的元素的位置，然后遍历数组。
    //          2. 对于相同的元素，继续向后遍历，遇到不相同的元素，将其和之前的下标标记的元素互换，并让标记下标自增1.
	//			3. 时间复杂度为O(n)，空间复杂度为O(1)。
    int removeDuplicates(vector<int>& nums) {
		if (nums.empty())	return 0;
		int j = 0;
		for (int i = 0; i != nums.size(); i++) {
			if (nums[i] != nums[j]) {
				swap(nums[j + 1], nums[i]);
				j++;
			}
		}
		return j + 1;
    }
};

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty())   return 0;
        int j = 0;
        for (int i = 0; i != nums.size(); i++)
            if (nums[i] != nums[j]) swap(nums[++j], nums[i]);
        return j + 1;
    }
};

int main()
{
	int k = 10;
	vector<int> ivec;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			ivec.push_back(i);
		}		
	}
	
	Solution slt;
	int rslt = slt.removeDuplicates(ivec);
	for (int i = 0; i != ivec.size(); i++)
	{
		cout << ivec[i] << ' ';
	}
	cout << endl;
	cout << rslt << endl;
	return 0;
}