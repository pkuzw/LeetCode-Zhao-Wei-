///@file	Merge Sorted Array
/*
Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

Note:
You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold additional elements from nums2.
The number of elements initialized in nums1 and nums2 are m and n respectively.
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
	///@brief	将两个有序的数组合并
	///@param	nums1	数组1
	///@param	m	数组1的长度
	///@param	nums2	数组2
	///@param	n	数组2的长度
	///@return  无
	///@note	归并排序的其中一步。时间复杂度为O(m+n)，空间复杂度为O(m+n)。
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		vector<int> nums3;
		int indx1 = 0, indx2 = 0;
		while (indx1 != m && indx2 != n)
		{
			if (nums1[indx1] <= nums2[indx2])
			{
				nums3.push_back(nums1[indx1++]);
			}
			else
			{
				nums3.push_back(nums2[indx2++]);
			}
		}
		if (indx1 == m)
		{
			for (int i = indx2; i != n; i++)
			{
				nums3.push_back(nums2[i]);
			}
		}
		else if (indx2 == n)
		{
			for (int i = indx1; i != m; i++)
			{
				nums3.push_back(nums1[i]);
			}
		}
		nums1 = nums3;
		return;
	}
};

class Solution {
public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		vector<int> nums3;
		int i = 0, j = 0;
		while (i != m && j != n)
		{
			if (nums1[i] <=  nums2[j])	nums3.push_back(nums1[i++]);
			else	nums3.push_back(nums2[j++]);
		}
		if (i == m)	nums3.insert(nums3.end(), nums2.begin()+j, nums2.end());
		if (j == n) nums3.insert(nums3.end(), nums1.begin()+i, nums1.begin()+m);
		nums1 = nums3;
	}
};

int main()
{
	vector<int> n1, n2;
	for (int i = 0; i != 10; i++)
	{
		if (i%2)
		{
			n1.push_back(i);
		}
		else
		{
			n2.push_back(i);
		}
	}
	for (int i = 0; i != 10; i++)
	{
		n1.push_back(10+i*3);
	}
	Solution slt;
	slt.merge(n1, n1.size(), n2, n2.size());
	return 0;
}