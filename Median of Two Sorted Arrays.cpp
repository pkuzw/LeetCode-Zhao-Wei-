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
//		  先把代码拷贝到源程序里，保证能够编译通过。
///@author zhaowei
///@date 2014.09.23
///@version 1.1

///@brief 逐句给原有代码中的findMedianSortedArrays()方法的前半部分添加注释，理解具体含义
///@author zhaowei
///@date 2014.09.24
///@version 1.2

///@date    2015.09.07
///@version 2.0

#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

class Solution_v1
{
public:
	/*
	double findMedianSortedArrays(int A[], int m, int B[], int n)
	{
		double rslt = 0;
		return rslt;
	}
	*/

	double findMedianBaseCase(int med, int C[], int n) {
		if (n == 1)
			return (med+C[0])/2.0;

		if (n % 2 == 0) {
			int a = C[n/2 - 1], b = C[n/2];
			if (med <= a)
				return a;
			else if (med <= b)
				return med;
			else /* med > b */
				return b;
		} else {
			int a = C[n/2 - 1], b = C[n/2], c = C[n/2 + 1];
			if (med <= a)
				return (a+b) / 2.0;
			else if (med <= c)
				return (med+b) / 2.0;
			else /* med > c */
				return (b+c) / 2.0;
		}
	}

	double findMedianBaseCase2(int med1, int med2, int C[], int n) {
		if (n % 2 == 0) {
			int a = (((n/2-2) >= 0) ? C[n/2 - 2] : INT_MIN);
			int b = C[n/2 - 1], c = C[n/2];
			int d = (((n/2 + 1) <= n-1) ? C[n/2 + 1] : INT_MAX);
			if (med2 <= b)
				return (b+max(med2,a)) / 2.0;
			else if (med1 <= b)
				return (b+min(med2,c)) / 2.0;
			else if (med1 >= c)
				return (c+min(med1,d)) / 2.0;
			else if (med2 >= c)
				return (c+max(med1,b)) / 2.0;
			else  /* a < med1 <= med2 < b */
				return (med1+med2) / 2.0;
		} else {
			int a = C[n/2 - 1], b = C[n/2], c = C[n/2 + 1];
			if (med1 >= b)
				return min(med1, c);
			else if (med2 <= b)
				return max(med2, a);
			else  /* med1 < b < med2 */
				return b;
		}
	}

	double findMedianSingleArray(int A[], int n) {
		assert(n > 0);
		return ((n%2 == 1) ? A[n/2] : (A[n/2-1]+A[n/2])/2.0);
	}

	///@brief 找两个整型数组的中位数
	///@param A 整型数组A
	///@param m 整型数组A的大小
	///@param B 整型数组B
	///@param n 整型数组B的大小
	///@return 如果(m+n)的和为偶数，则返回距离中位数最近的两个相邻元素的算术平均值；如果(m+n)的和为奇数，则直接返回中位数。
	double findMedianSortedArrays(int A[], int m, int B[], int n) 
	{
		//如果A数组为空，则直接返回B数组的中位数
		if (m == 0)
			return findMedianSingleArray(B, n);

		//如果B数组为空且A数组不为空，则直接返回A数组的中位数
		else if (n == 0)
			return findMedianSingleArray(A, m);

		//如果A数组只含有一个元素且B数组不为空，则认为是基本情况I
		else if (m == 1)
			return findMedianBaseCase(A[0], B, n);

		//如果B数组只含有一个元素且A数组不为空，则也认为是基本情况I
		else if (n == 1)
			return findMedianBaseCase(B[0], A, m);

		//如果A数组只含有两个元素且B数组不为空，则认为是基本情况II
		else if (m == 2)
			return findMedianBaseCase2(A[0], A[1], B, n);

		//如果B数组只含有两个元素且A数组不为空，则认为是基本情况II
		else if (n == 2)
			return findMedianBaseCase2(B[0], B[1], A, m);


		int i = m/2;	//数组A的中位数下标
		int	j = n/2;	//数组B的中位数下标
		int k = 0;		//用来保存每次查找后子数组截短的长度

		// 如果数组A的中位数小于数组B的中位数，则两数组的中位数应该位于[A[i..m-1], B[0..n]]之间
		if (A[i] <= B[j])
		{
			if(m % 2 == 0)
			{
				if(i - 1 < n - j - 1)
					k = i - 1;
				else
					k = n - j -1;
			}
			else
			{
				if(i < n - j - 1)
					k = i;
				else
					k = n - j - 1;
			}
			//k = ((m%2 == 0) ? min(i-1, n-j-1) : min(i, n-j-1));
			assert(k > 0);

			return findMedianSortedArrays(A+k, m-k, B, n-k);
		}
		else
		{
			if (n % 2 == 0)
			{
				if (m - i - 1 < j - 1)
				{
					k = m - i - 1;
				} 
				else
				{
					k = j - 1;
				}
			}
			else
			{
				if (m - i - 1 < j)
				{
					k = m - i - 1;
				} 
				else
				{
					k = j;
				}
			}
			//k = ((n%2 == 0) ? min(m-i-1, j-1) : min(m-i-1, j));
			assert(k > 0);
			return findMedianSortedArrays(A, m-k, B+k, n-k);
		}
	}
};

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int total = nums1.size() + nums2.size();
        if (total % 2 == 1) {
            return findKth(nums1, 0, nums2, 0, total / 2 + 1);
        } else {
            return (findKth(nums1, 0, nums2, 0, total / 2) + findKth(nums1, 0, nums2, 0, total / 2 + 1)) / 2;
        }
    }
    double findKth(vector<int> &nums1, int i, vector<int> &nums2, int j, int k) {
        if (nums1.size() - i > nums2.size() - j) return findKth(nums2, j, nums1, i, k);
        if (nums1.size() == i) return nums2[j + k - 1];
        if (k == 1) return min(nums1[i], nums2[j]);
        int pa = min(i + k / 2, int(nums1.size())), pb = j + k - pa + i;
        if (nums1[pa - 1] < nums2[pb - 1])
            return findKth(nums1, pa, nums2, j, k - pa + i);
        else if (nums1[pa - 1] > nums2[pb - 1])
            return findKth(nums1, i, nums2, pb, k - pb + j);
        else
            return nums1[pa - 1];
    }
};

int main()
{
	//样例测试
	int len_a = 0, len_b = 0;
	cout << "input length of A: ";
	cin >> len_a;
	cout << "input length of B: ";
	cin >> len_b;

	int* arr_a = new int[len_a];
	int* arr_b = new int[len_b];
	
	cout << "input elements of A: ";
	for(int i = 0; i < len_a; i++)
		cin >> arr_a[i];

	cout << "input elements of B: ";
	for(int i = 0; i < len_b; i++)
		cin >> arr_b[i];

	double median = 0;
	Solution_v1 slt;
	median = slt.findMedianSortedArrays(arr_a, len_a, arr_b, len_b);
	cout << "program's result: " << median << endl;

	return 0;
	
}
