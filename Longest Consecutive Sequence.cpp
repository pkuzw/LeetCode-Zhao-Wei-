///@file	Longest Consecutive Sequence
/*
Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity.
*/
///@author	zhaowei
///@date	2015.07.25
///@version	1.0

///@date	2015.08.22
///@version	2.0

#include <vector>
#include <unordered_set>

using namespace std;

class Solution_v1 {
public:
	///@brief	计算最长连续整数
	///@param	nums	整数数组
	///@return	返回数组的最长连续整数
	/* @note	利用桶排序的思想，开一个max(nums[i])大的数组，里面凡是在nums中出现过的数都置为true，然后统计连续的下标即可。时间复杂度为O(n)，
				空间复杂度为O(max(nums[i]))。OJ报RE。*/
	int longestConsecutive_RE(vector<int>& nums) {
		int max = 0;
		int min = 0;
		for (int i = 0; i != nums.size(); i++)
		{
			int t = 0;
			if (nums[i] < 0)
			{
				t = -1*nums[i];
				if (t > min)
					min = t;
			}
			else
			{
				t = nums[i];
				if (t > max)
					max = t;
			}			
		}

		vector<bool> bvec1(max+1, false);	//	记录自然数的数组
		vector<bool> bvec2(min+1, false);	//	记录负整数的数组
		for (int i = 0; i != nums.size(); i++)
		{
			int t = 0;
			if (nums[i] < 0)
			{
				t = -1*nums[i];
				bvec2[t] = true;
			}
			else
			{
				t = nums[i];
				bvec1[t] = true;
			}			
		}

		int cnt1 = 0;
		int cnt2 = 0;
		int cnt_tmp = 0;
		for (int i = 0; i != bvec1.size()-1; i++)
		{
			if (bvec1[i] && bvec1[i+1])
				cnt_tmp++;

			if (cnt_tmp > cnt1)	
				cnt1 = cnt_tmp;

			if (bvec1[i] && !bvec1[i+1])
				cnt_tmp = 1;
		}

		cnt_tmp = 0;
		for (int i = 0; i != bvec2.size()-1; i++)
		{
			if (bvec2[i] && bvec2[i+1])
				cnt_tmp++;

			if (cnt_tmp > cnt2)	
				cnt2 = cnt_tmp;

			if (bvec2[i] && !bvec2[i+1])
				cnt_tmp = 1;
		}

		int cnt = (cnt1 > cnt2) ? cnt1 : cnt2;

		if (bvec2[1] && bvec1[0])	//	如果跨0连续，需要单独处理
		{
			int i = 1;
			while (i < bvec2.size() && bvec2[i])
				i++;

			int j = 0;
			while (j < bvec1.size() && bvec1[j])
				j++;

			if (i + j -1 > cnt)
				cnt = i + j - 1;
		}
		
		return cnt;
	}

	///@brief	计算最长连续整数
	///@param	nums	整数数组
	///@return	返回数组的最长连续整数
	/* @note	利用哈希表。先将所有的整数映射到哈希表上，然后逐个遍历，在哈希表上向前向后查找是否存在相邻元素，如果存在，那么计数器自增1。
				否则	删除在该哈希表上的元素。时间复杂度为O(n)，空间复杂度为O(n)*/
	int longestConsecutive(vector<int>& nums) {
		unordered_set<int> hash_table;	//	初始化哈希表
		for (int i = 0; i != nums.size(); i++)
			hash_table.insert(nums[i]);


		int len_cnt = 0;	//	连续整数长度记录
		int max_len = 0;	//	最长连续整数长度记录
		for (int i = 0; i != nums.size(); i++)
		{
			if (hash_table.find(nums[i]) != hash_table.end())
			{
				hash_table.erase(nums[i]);	//	删除连续元素，避免重复计算
				len_cnt++;

				int j = nums[i]+1;
				while (hash_table.find(j) != hash_table.end())
				{
					hash_table.erase(j);	//	删除连续元素，避免重复计算
					len_cnt++;					
					j++;					
				}

				j = nums[i]-1;
				while (hash_table.find(j) != hash_table.end())
				{
					hash_table.erase(j);	//	删除连续元素，避免重复计算
					len_cnt++;					
					j--;					
				}
				if (max_len < len_cnt)	max_len = len_cnt;
				len_cnt = 0;	//	恢复初始值
			}
		}
		return max_len;
	}
};

///@note	利用哈希表保存现有的元素，每当找到一个元素就在哈希表中删除，这样能够减少重复计算。
class Solution {
public:
	int longestConsecutive(vector<int>& nums) {
		unordered_set<int> ht(nums.begin(), nums.end());
		int max_len = INT_MIN, len = 0;
		for (int i = 0; i != nums.size(); i++)
		{
			if (ht.find(nums[i]) != ht.end())
			{
				ht.erase(nums[i]);
				len++;

				int j = nums[i] + 1;
				while (ht.find(j) != ht.end())
				{
					ht.erase(j);
					len++;
					j++;
				}
				j = nums[i] - 1;
				while (ht.find(j) != ht.end())
				{
					ht.erase(j);
					len++;
					j--;
				}
				max_len = max(max_len, len);
				len = 0;
			}			
		}
		return max_len;
	}
};

int main()
{
	int n[10] = {-2, -10, 0, 100, 2, 3, 400, 5, 60, 7};
	vector<int> nums;
	for (int i = 0; i != 10; i++)
		nums.push_back(n[i]);

//	nums.clear();
	Solution slt;
	int rslt = slt.longestConsecutive(nums);
	return 0;
}