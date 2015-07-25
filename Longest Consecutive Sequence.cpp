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

#include <vector>

using namespace std;

class Solution {
public:
	///@brief	�������������
	///@param	nums	��������
	///@return	������������������
	/* @note	����Ͱ�����˼�룬��һ��max(nums[i])������飬���淲����nums�г��ֹ���������Ϊtrue��Ȼ��ͳ���������±꼴�ɡ�ʱ�临�Ӷ�ΪO(n)��
				�ռ临�Ӷ�ΪO(max(nums[i]))��*/
	int longestConsecutive(vector<int>& nums) {
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

		vector<bool> bvec1(max+1, false);	//	��¼��Ȼ��������
		vector<bool> bvec2(min+1, false);	//	��¼������������
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

		if (bvec2[1] && bvec1[0])	//	�����0��������Ҫ��������
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
};

int main()
{
	int n[10] = {0,1,-1,2,6,7,-2,3,4,5};
	vector<int> nums;
	for (int i = 0; i != 10; i++)
		nums.push_back(n[i]);
	Solution slt;
	int rslt = slt.longestConsecutive(nums);
	return 0;
}