///@file	Permutations
/*			Given a collection of numbers, return all possible permutations.

			For example,
			[1,2,3] have the following permutations:
			[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].
*/
///@author	zhaowei
///@date	2015.06.24
///@version	1.0

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
	///@note	把长度为n的原始数组简化为长度为1, 2, 3, 4, ... , n-1的，逐级递归。对于只有1个元素的，只需要返回其本身；只有2个的元素的，
	//			返回两个交换过的情形，相当于选出一个，然后剩下一个元素，与处理一个元素的情形类似；3个元素的，每次选出1个元素，
	//			剩下两个就像2各元素那样处理。向上依次类推。
	vector<vector<int>> permute(vector<int>& nums)
	{
		vector<int> vec;
		calPermute(nums, vec, 0, nums.size());
		return rslt;
	}
	///@param	r	计算组合的终止下标的后一个元素
	void calPermute(vector<int> nums, vector<int>& stk, int p, int r)
	{
		if (p == r)
		{
			rslt.push_back(stk);
			return;
		}
		while (p != r)
		{
			stk.push_back(nums[p]);
			calPermute(nums, stk, p+1, r);	
			stk.pop_back();
			p++;
		}
		return;
	}

private:
	vector<vector<int>> rslt;
};

int main()
{
	Solution slt;
	vector<int> nums;
	nums.push_back(1);
	nums.push_back(2);
	slt.permute(nums);
	return 0;
}