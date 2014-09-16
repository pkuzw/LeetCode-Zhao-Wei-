///@file 在O(lgn)的时间复杂度内找到两个已经排好序的数组的中位数
/*
There are two sorted arrays A and B of size m and n respectively. Find the median of the two sorted arrays. 
The overall run time complexity should be O(log (m+n)).
*/
///@brief 最简单的办法是归并排序，然后输出中间的那个数，时间复杂度是O(m+n)。
///@author zhaowei
///@date 2014.09.09
///@version 1.0

///@brief 添加测试样例
///@author zhaowei
///@date 2014.09.11
///@version 1.1

///@brief 参考链接：http://leetcode.com/2011/03/median-of-two-sorted-arrays.html
//		  注意观察两个已经排好序的数组A和B，假设它们的长度分别是m和n，中位数分别是A[i]和B[j]，其中i = m/2，j = n/2，数组从0开始计算下标
//        当A[i] == B[j]时，两个数组的中位数是(A[i]+B[j])/2；
//        当A[i] < B[j]时， 两个数组的中位数位于[A[i..m-1], B[0..j]]中，包括A[i]和B[j]
//		  当A[i] > B[j]时， 两个数组的中位数位于[B[j..n-1], A[0..i]]中，包括A[i]和B[j]
///@author zhaowei
///@date 2014.09.16
///@version 1.1
#include <iostream>
#include <vector>
using namespace std;

class Solution 
{
public:
	double findMedianSortedArrays(int A[], int m, int B[], int n)
	{
		double rslt = 0;
		return rslt;
	}
};

int main()
{
	//样例测试
	int arr_a[6] = {2, 14, 22, 34, 36, 78};
	int arr_b[9] = {1, 3, 8, 13, 17, 21, 25, 28, 30};
	double median = 0;
	Solution slt;
	median = slt.findMedianSortedArrays(arr_a, 6, arr_b, 9);
	cout << "median of two sorted arrays: " << arr_b[5] << endl;
	cout << "program's result: " << median << endl;

	return 0;
}