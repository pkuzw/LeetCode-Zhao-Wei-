///@file	Single Number III
/*
Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once.

For example:

Given nums = [1, 2, 1, 3, 2, 5], return [3, 5].

Note:
The order of the result is not important. So in the above example, [5, 3] is also correct.
Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?
*/
///@author	zhaowei
///@date	2015.08.17
///@version	1.0

#include <vector>
using namespace std;

class Solution {
public:
	///@brief	一个数组中只有两个元素只出现了一次，其余元素出现了两次。找出这两个元素
	///@param	nums	数组
	///@return	返回这两个元素组成的数组
	///@note	先将整个数组都异或一遍，得到的结果是两个只出现一次的两个元素的异或值，然后找到该异或值的为1的最低位，该位表明这两个元素在
	//			该位不一样，一个为0，一个为1.然后根据此位是否为0将数组分成两部分，然后分别对两个子数组异或即可得到这两个元素。时间复杂度为
	//			O(n)，空间复杂度为O(1)。
	vector<int> singleNumber(vector<int>& nums) {

	}
};

int main()
{
	return 0;
}