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
///@date	2015.08.18
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
		int xor_all = 0;
		xor_all = nums.front();	//	先将所有数都异或起来
		for (int i = 1; i != nums.size(); i++)
			xor_all ^= nums[i];

		int cnt = 0;
		int tmp = 1;	//	找到异或结果的最低为1的位
		while ((xor_all & tmp) == 0)	//	异或操作符优先级比较低，需要括号括起来
		{
			xor_all >>= 1;
			cnt++;
		}
		tmp <<= cnt;

		vector<int> a, b;	//	按照从右向左数第cnt位为1来对原数组进行划分
		for (int i = 0; i != nums.size(); i++)
		{
			if ((nums[i] & tmp) == 0)	a.push_back(nums[i]);
			else b.push_back(nums[i]);
		}

		//	分别对子数组进行异或操作
		int xor_a = a.front(), xor_b = b.front();
		for (int i = 1; i != a.size(); i++)
			xor_a ^= a[i];
		for (int i = 1; i != b.size(); i++)
			xor_b ^= b[i];
		vector<int> rslt;
		rslt.push_back(xor_a);
		rslt.push_back(xor_b);
		return rslt;
	}
};

int main()
{
	vector<int> nums;
	nums.push_back(101);
	nums.push_back(2055);
	nums.push_back(3);
	nums.push_back(3);
	nums.push_back(4);
	nums.push_back(4);
	nums.push_back(5);
	nums.push_back(5);
	Solution slt;
	vector<int> rslt = slt.singleNumber(nums);
	return 0;
}