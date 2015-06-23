///@file	Jump Game II
/*
			Given an array of non-negative integers, you are initially positioned at the first index of the array.

			Each element in the array represents your maximum jump length at that position.

			Your goal is to reach the last index in the minimum number of jumps.

			For example:
			Given array A = [2,3,1,1,4]

			The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)
*/
///@author	zhaowei
///@date	2015.06.23
///@version	1.0

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	///@brief	计算到达数组最后一个下标的最小跳跃步数
	///@param	nums	数组，其中每一个元素值非负，表示能从该下标跳跃的最远距离
	///@return	返回从数组开头到末尾的最少跳跃步数
	///@note	解题思路：寻找从当前下标到其所能到达最远处这一范围内的最远的非零值，然后将当前下标移动到最远的非零值处继续搜索，直到到达数组末尾。
	//			利用库文件<algorithm>中的max_element(first, last)函数来查找指定范围的最大值。时间复杂度为O(n^2)，空间复杂度为O(1)。
	int jump(vector<int>& nums) 
	{
		vector<int>::iterator first = nums.begin();
		int cnt = 0;
		while (1)
		{
			vector<int>::iterator max_iter = max_element(first, first + *first + 1);	//	寻找指定范围内的最大值
			cnt++;	//	计数器自增1
			if (*max_iter >= nums.end()-first-1)		//	如果到达最后一个元素，则返回计数器
			{
				return cnt;
			}
			first = nextPos(nums, first, *first);				//	将当前下标移动到最远的非0值处
			if (first == nums.end())
			{
				return cnt;
			}
		}		
		return cnt;
	}

	vector<int>::iterator nextPos(vector<int>& nums, vector<int>::iterator first, int range)
	{
		vector<int>::iterator max = first;
		for (int i = 0; i <= range; i++)
		{
			if (first >= nums.end() - i)
			{
				return nums.end();
			}
			else
			{
				if (*(first + i) != 0 && first+i > max)
				{
					max = first + i;			
				}
			}
		}
		return max;
	}
};

int main()
{
	vector<int> ivec;
	ivec.push_back(2);
	ivec.push_back(3);
	ivec.push_back(1);
	ivec.push_back(1);
 	ivec.push_back(4);
// 	ivec.push_back(1);
// 	ivec.push_back(1);
// 	ivec.push_back(1);
// 	ivec.push_back(1);
// 	ivec.push_back(1);
// 	ivec.push_back(1);
// 	ivec.push_back(1);
// 	ivec.push_back(1);
// 	ivec.push_back(1);

	Solution slt;
	cout << slt.jump(ivec) << endl;
	return 0;
}