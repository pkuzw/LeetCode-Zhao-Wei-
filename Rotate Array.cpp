///@file	Rotate Array
/*Rotate an array of n elements to the right by k steps.

For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated to [5,6,7,1,2,3,4].

Note:
Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem. 
*/
///@author	zhaowie
///@date	2015.07.26
///@version	1.0

///@date	2015.08.12
///@version	1.1
///@version	2.0

///@date	2016.01.19
///@version	2.1

#include <deque>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

class Solution_v1 {
public:
	///@brief	翻转一个数组中的指定长度的元素。
	///@param	nums	数组
	///@param	k		指定长度
	///@return	无
	/* @note	用两个数组临时存放数据，一个保存需要翻转的，另一个保存原有的。时间复杂度为为O(n)，空间复杂度为O(n)。*/
	void rotate(vector<int>& nums, int k) {
		k %= nums.size();
		if (k == 0)	return;

		vector<int> ivec1(nums);
		vector<int> ivec2;
		for (int i = 0; i != k; i++)
		{
			ivec2.push_back(ivec1.back());
			ivec1.pop_back();
		}
		reverse(ivec2.begin(), ivec2.end());
		ivec2.insert(ivec2.end(), ivec1.begin(), ivec1.end());

		nums = ivec2;
	}
};

class Solution_v1_1 {
public:
	void rotate(vector<int>& nums, int k) {
		k %= nums.size();
		if (!k)	return;

		vector<int> stk;
		for (int i = 0; i != k; i++)
		{
			stk.push_back(nums.back());
			nums.pop_back();
		}
		vector<int> ivec(stk.rbegin(), stk.rend());
		ivec.insert(ivec.end(), nums.begin(), nums.end());

		nums = ivec;
	}
};

class Solution {
public:
	///@brief	翻转一个数组中的指定长度的元素。
	///@param	nums	数组
	///@param	k		指定长度
	///@note	1. 先将整个数组翻转；
	//			2. 然后对于前k个元素进行翻转；
	//			3. 最后对后面的剩余元素进行翻转；
	//			4. 时间复杂度为O(n)，空间复杂度为O(1)。其中n为数组元素数目。
	void rotate(vector<int>& nums, int k) {
		k %= nums.size();
		if (!k)	return;
		reverse(nums.begin(), nums.end());
		reverse(nums.begin(), nums.begin() + k);
		reverse(nums.begin() + k, nums.end());
	}
};

int main()
{
	vector<int> nums;
	for (int i = 1; i != 8; i++)
		nums.push_back(i);

	Solution slt;
	slt.rotate(nums, 3);
	return 0;
}