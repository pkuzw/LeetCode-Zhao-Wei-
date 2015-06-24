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
#include <deque>

using namespace std;

class Solution {
public:
	///@brief	给定候选元素数组，计算所有可能的组合
	///@param	nums	候选元素数组
	///@return	返回所有可能的组合
	///@note	把长度为n的原始数组简化为长度为1, 2, 3, 4, ... , n-1的，逐级递归。对于只有1个元素的，只需要返回其本身；只有2个的元素的，
	//			返回两个交换过的情形，相当于选出一个，然后剩下一个元素，与处理一个元素的情形类似；3个元素的，每次选出1个元素，
	//			剩下两个就像2各元素那样处理。向上依次类推。
	///@author	zhaowei
	///@date	2015.06.24
	vector<vector<int>> permute(vector<int>& nums)
	{
		vector<int> ivec;
		getPermutate(nums, nums, ivec);
		return rslt;
	}

	///@brief	计算所有可能的组合
	///@param	nums	原始数组
	///@param	pre_nums	递归的上一级数组
	///@param	residue	可能的一种组合
	///@return	void
	///@note	我的想法是每次拿掉一个元素，将剩余的元素组成一个新数组，并且记录下当前拿掉的是第几个元素；当新数组为空时需要得到一个可能的组合；
	//			此时返回上一级递归，再拿掉下一个元素。依次类推。但是程序还是写的有问题。
	void getPermutate(vector<int> nums, vector<int> pre_nums, vector<int>& residue)
	{
		if (nums.empty())	//	如果
		{
			rslt.push_back(residue);
			return;
		}
		int indx = 0;
		bool flag = false;	//	第一遍写入的标识符
		while (indx != pre_nums.size())
		{
			vector<int> tmp;
			if (!flag)
			{
				residue.push_back(nums[indx]);
				for (int i = 0; i != nums.size(); i++)
				{
					if (i == indx)
					{
						continue;
					}
					tmp.push_back(nums[i]);
				}
				getPermutate(tmp, nums, residue);
			}
			
			
			
			
			int pre_size = pre_nums.size();
			while (pre_size != 0)
			{
				residue.pop_back();
				pre_size--;
			}
			indx++;	//	???这里有问题
			
			flag = true;
			residue.push_back(pre_nums[indx]);
			for (int i = 0; i != pre_nums.size(); i++)
			{
				if (i == indx)
				{
					continue;
				}
				tmp.push_back(pre_nums[i]);
			}
			getPermutate(tmp, pre_nums, residue);
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
	nums.push_back(3);
	slt.permute(nums);
	return 0;
}