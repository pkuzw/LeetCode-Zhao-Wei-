///@file	Remove Duplicates from Sorted Array II 
/*
Follow up for "Remove Duplicates":
What if duplicates are allowed at most twice?

For example,
Given sorted array nums = [1,1,1,2,2,3],

Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3. 
It doesn't matter what you leave beyond the new length.
*/
///@author	zhaowei
///@date	2015.07.15
///@version	1.0

///@date	2015.08.26
///@version	2.0
#include <iostream>
#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	在一个已经排好序的数组中，如果只允许同一个元素出现两次，生成新数组并计算新数组的长度
	///@param	nums	已经排好序的数组
	///@return	新数组的长度
	///@note	设置一个统计重复元素出现次数的变量，每当重复元素出现的次数超过2，就将其后面的元素向前移动一位，此时重复元素的下标需要随之改变。
	//			时间复杂度为O(n)，空间复杂度为O(1)。
	int removeDuplicates(vector<int>& nums) {
		int len = nums.size();	//	数组的长度，随着重复元素被删除动态变化
		if (len <= 2)	//	当数组的长度小于等于2时，直接返回数组的长度
		{
			return len;
		}
				
		int dup_cnt = 1;
		for (int i = 0; i < len-1; i++)
		{
			int j = i+1;
			dup_cnt = 1;	//	统计元素重复出现的次数
			int delete_times = 0;	//	重复元素的总次数，即数组向前移动过多少次
			while (j-delete_times < len && nums[i] == nums[j-delete_times])	//	因为发现超过两次的重复元素后，都将后面的元素向前移动一位，故相应的j下标也需要减去移动的次数
			{
				dup_cnt++;
				j++;
				if (dup_cnt > 2)
				{
					deleteElement(nums, j-delete_times-1);
					len--;
					delete_times++;
				}
			}
			i = j-delete_times-1;
		}	
		return len;
	}

private:
	///@brief	将数组中指定下标后的所有元素向前移动一位
	///@param	nums	数组
	///@param	indx	指定下标
	///@return	无
	void deleteElement(vector<int> &nums, const int indx)
	{
		for (int i = indx+1; i != nums.size(); i++)
		{
			nums[i-1] = nums[i];
		}
		return;
	}
};

class Solution {
public:
	int removeDuplicates(vector<int>& nums) {
		if (nums.empty())	return 0;
		int rslt = 0;
		vector<int> tmp;
		int i = 0, j = 0;
		for (i = 0; i < nums.size(); i = j)
		{
			int cnt = 0;
			j = i;
			while (j < nums.size() && nums[j] == nums[i])
			{
				if (cnt < 2)	tmp.push_back(nums[j]);
				cnt++;
				j++;
			}
			rslt += cnt > 2 ? 2 : cnt;
		}	
		nums = tmp;
		return rslt;
	}
};

int main()
{
	Solution slt;
	vector<int> test;
 	test.push_back(1);
 	test.push_back(2);
	test.push_back(2);
	test.push_back(3);
	test.push_back(3);
	test.push_back(4);
	test.push_back(4);
	test.push_back(4);
	int new_len = slt.removeDuplicates(test);

	return 0;
}