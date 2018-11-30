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

///@date	2015.12.19
///@version	3.0

///@date	2016.05.03
///@version	2.1

///@date    November 30, 2018
///@version 4.0

#include <iostream>
#include <vector>
#include <algorithm>

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

class Solution_v2 {
public:
	///@brief	将两个有序数组归并成一个数组
	///@param	nums1	数组1
	///@param	nums2	数组2
	///@param	m		数组1的长度
	///@param	n		数组2的长度
	///@return	无
	///@note	归并排序中的merge操作，时间复杂度为O(n)，空间复杂度为O(n)。
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

class Solution_v3 {
public:
	///@brief	归并排序
	///@param	nums1, nums2	数组1和数组2
	///@param	m, n			数组1和数组2的长度
	///@return	无
	///@note	1. 将nums1添加到nums2的后端，然后调用快速排序进行排序。
	//			2. 时间复杂度为O(nlogn)，空间复杂度为O(m+n)；
	//			3. oj报wa，过不了{}, {1}这组测试数据。
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		if (nums1.empty()) {
			nums1 = nums2;
			return;
		}
		else {
			nums1.insert(nums1.end(), nums2.begin(), nums2.end());
			sort(nums1.begin(), nums1.end());
		}
	}
};

class Solution {
public:
    ///@brief   将两个有序数组合并成一个。
    ///@param   nums1   数组1
    ///@param   nums2   数组2
    ///@return  无
    ///@note    1. 枚举；两种思路，要么新建一个数组用来存放中间结果，时间复杂度为O(m+n)，其中m和n分别是nums1和nums2的长度；
    //             要么将nums2先拷贝到nums1里面，然后在nums1里面做排序，时间复杂度为O((m+n)lg(m+n))，空间复杂度为O(1)。
    //          2. 将nums2先拷贝到nums1里面
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if (nums1.empty() || nums2.empty()) return;
        for (int i = m; i < m + n; i++) {
            nums1[i] = nums2[i-m];
        }
        sort(nums1.begin(), nums1.end());
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
	n1.clear();
	n2.clear();
	n2.push_back(1);
	Solution slt;
	slt.merge(n1, n1.size(), n2, n2.size());
	return 0;
}
