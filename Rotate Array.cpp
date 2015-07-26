///@file	Rotate Array
/*Rotate an array of n elements to the right by k steps.

For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated to [5,6,7,1,2,3,4].

Note:
Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem. 
*/
#include <deque>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
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

int main()
{
	vector<int> nums;
	for (int i = 1; i != 8; i++)
		nums.push_back(i);

	Solution slt;
	slt.rotate(nums, 13);
	return 0;
}