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
//		  注意观察两个已经排好序的数组A和B，假设它们的长度分别是m和n，中位数分别是A[i]和B[j]，其中i = m/2，j = n/2，
//        数组从0开始计算下标.
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

///@date    2015.09.11
///@version 2.1

///@date	2016.03.31
///@version	2.2

///@date    June 14, 2018
///@version 2.3

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

class Solution_v2 {
public:
	///@brief	找到已排好序的数组nums1和nums2的合并后的中位数
	///@param	nums1, nums2	数组
	///@return	返回数组nums1和nums2的合并后的中位数
	/* @note	1. 如果nums1与nums2之和为奇数，则直接返回合并后的中位数；如果为偶数，则返回两个中位数的算术平均数。
				2. 先实现两个已经排好序的数组的第k个元素，然后调用这个函数求中位数。
                3. http://www.cnblogs.com/grandyang/p/4465932.html
                4. https://blog.csdn.net/yutianzuijin/article/details/11499917
                5. https://blog.csdn.net/zxzxy1988/article/details/8587244
	*/
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int total = nums1.size() + nums2.size();
        if (total % 2 == 1) {
            return findKth(nums1, 0, nums2, 0, total / 2 + 1);
        } else {
            return (findKth(nums1, 0, nums2, 0, total / 2) + findKth(nums1, 0, nums2, 0, total / 2 + 1)) / 2;
        }
    }

	///@brief	找到已排好序的数组nums1和nums2分别从第i个和第j个开始合并后的第k个元素
	///@param	nums1, nums2	数组
	///@param	i, j	数组1和数组2的起始下标
	///@param	k		第k个元素
	///@return	返回第k个元素
	/* @note	1. 令nums1的数组剩余长度(nums1.size() - i)要比nums2的剩余长度(nums2.size() - j)更短。否则，就交换两个数组；
				2. 如果nums1的可用长度为0（即nums1.size() - i == 0），则直接返回数组nums2的第k个元素即可；
				3. 如果是找合并后的第一个元素，只需要比较两个数组的可用首元素即可；
				4. 找到nums1中可用元素的第k/2个元素，其下标为pa，同理可得nums2中的第k/2小的元素，其下标为pb；
				5. 如果nums1[pa - 1] < nums2[pb - 1]，则nums1[0..pa-1]不可能大于等于合并后的第k个元素，故抛弃；
                   这个推论的证明采用反证法：假设nums1[pa - 1]大于等于合并后的第k个元素，假设其值为k，那么比nums1[pa - 1]小的数应该为k - 1个。因为num2[pb-1] > num1[pa-1]，那么num2[pb - 1]为合并后的至少第k+1大的数。因为pa - 1 = k/2 - 1，则在nums1中比nums[pa - 1]小的数至多为k/2 - 1个,同理，在nums2中比nums1[pa - 1]小的数至多也为k/2 - 1个，则比nums1[pa - 1]小的数至多为k - 2个，小于nums1[0..pa - 2]的假设值k - 1,假设不成立，证毕。
				6. 同理，如果nums2[pb - 1] < nums1[pa - 1]，则nums2[0..pb-1]也应该抛弃；
				7. 如果两者相同，则直接返回该值就好。
				8. 时间复杂度为O(log(m+n))，空间复杂度为O(1)。
	*/
    double findKth(vector<int> &nums1, int i, vector<int> &nums2, int j, int k) {
        if (nums1.size() - i > nums2.size() - j) return findKth(nums2, j, nums1, i, k);
        if (nums1.size() == i) return nums2[j + k - 1];
        if (k == 1) return min(nums1[i], nums2[j]);
        
        //pa = i + k/2，表示的意思是以i为开端的k/2下取整个数的当前下标
        //pb = j + (k - (pa - i))，其中pa - i为k/2下取整个数，k - (pa - i)为k中剩余的元素，j + (k - (pa - i))的意思就是以j为起始下标的剩余k个元素的当前下标。
        int pa = min(i + k / 2, int(nums1.size())), pb = j + (k - (pa - i));    // pb用括号括起来，方便看出它的来源。
        if (nums1[pa - 1] < nums2[pb - 1])
            return findKth(nums1, pa, nums2, j, k - pa + i);
        else if (nums1[pa - 1] > nums2[pb - 1])
            return findKth(nums1, i, nums2, pb, k - pb + j);
        else
            return nums1[pa - 1];
    }
};

class Solution_v2_2 {
public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int total = nums1.size() + nums2.size();
		if (total % 2)	return findKthNumberSortedArrays(nums1, 0, nums2, 0, total / 2 + 1);
		else	return (findKthNumberSortedArrays(nums1, 0, nums2, 0, total / 2) + findKthNumberSortedArrays(nums1, 0, nums2, 0, total / 2 + 1)) / 2;
	}

	double findKthNumberSortedArrays(vector<int>& nums1, int i, vector<int>& nums2, int j, int k) {
		if (nums1.size() - i > nums2.size() - j)		return findKthNumberSortedArrays(nums2, j, nums1, i, k);		
		if (i == nums1.size())	return nums2[j+k-1];		//	先处理i在nums1的位置，不能跟下一句颠倒，否则无法处理nums1 = {}, nums2 = {1}的情形
		if (k == 1)	return min(nums1[i], nums2[j]);
		int pa = min(i + k / 2, (int)nums1.size()), pb = j + k - pa + i;
		if (nums1[pa-1] < nums2[pb-1])	return findKthNumberSortedArrays(nums1, pa, nums2, j, i + k - pa);
		else if (nums1[pa-1] > nums2[pb-1])	return findKthNumberSortedArrays(nums1, i, nums2, pb, j + k - pb);
		else return nums1[pa-1];
	}
};

class Solution {
public:
    ///@brief   给定两个排好序的数组，找到合并后仍然有序的数组的中位数。
    ///@param   nums1   数组1
    ///@param   nums2   数组2
    ///@return  如果合并后数组的长度len为偶数，返回(nums[len/2] + nums[len/2 + 1]) / 2；如果len为奇数，返回nums[len/2].
    ///@note    调用findKthNumberSortedArrays，分别处理奇数和偶数两种情况。
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.empty() && nums2.empty()) return 0;
        int len = nums1.size() + nums2.size();
        if  (len % 2 == 0)   return (double)(findKthNumberSortedArrays(nums1, 0, nums2, 0, len/2) + findKthNumberSortedArrays(nums1, 0, nums2, 0, len/2 + 1)) / 2;
        return (double)findKthNumberSortedArrays(nums1, 0, nums2, 0, len/2 + 1);
    }
    
    ///@brief   给定两个有序数组nums1和nums2，找到它们合并后的排在第k位的元素。
    ///@param   nums1   数组1
    ///@param   i       数组1的起始检索下标
    ///@param   nums2   数组2
    ///@param   j       数组2的起始检索下标
    ///@param   k       合并后数组的检索目标，即合并后的第k个元素。
    ///@return  返回合并后排在第k位的元素。
    ///@note    设pa = k/2下取整, pb = k/2上取整。首先比较nums1[pa - 1]和nums2[pb - 1]的大小，结果有三种。
    /*          1.  nums1[pa-1] < nums2[pb-1];
                2.  nums1[pa-1] > nums2[pb-1];
                3.  nums1[pa-1] = nums2[pb-1].
                
                情况1：能够推出nums1[0..pa-1]均不可能大于等于合并后数组的第k个元素，即nums1[0..pa-1]可被舍弃；采用反证法证明，如果nums1[pa-1]大于等于合并后的数组第k个元素大，则nums1[pa-1]的最小值为k，合并后数组中比nums1[pa-1]小的元素数目为k - 1。在nums1中比nums[pa-1]小的数至多为k/2 - 1个；由于nums2[pb-1] > nums1[pa-1]，那么在nums2数组中比nums1[pa-1]小的数也至多有k/2 + 1个，二者相加，在合并后的数组中比nums[pa-1]小的数最多有k - 2个，小于假设的最小值k - 1，故假设不成立，得证。
     
                情况2：与情况1类似，不过舍弃的部分是nums2[0..pb-1];
     
                情况3：相当于找到了合并后的第k个元素。直接返回即可。
     
                其次，对于k元素奇偶性的处理，在于pa = i + k/2和pb = j + (k - (pa - i))，pa取的是k/2的下取整，pb取的是k/2的下取整。
     
                最后，之所以要保证nums1.size() - i <= nums2.size() - j，是为了后续在处理nums1整个先被舍弃完，即i == nums1.size()时，j+k-1仍然在nums2的范围内。对于相反的情况，只要颠倒nums1和nums2就好。
     */
    int findKthNumberSortedArrays(vector<int>& nums1, int i, vector<int>& nums2, int j, int k) {
        if (nums1.size() - i > nums2.size() - j)    return findKthNumberSortedArrays(nums2, j, nums1, i, k);
        if (i == nums1.size()) return nums2[j + k - 1];
        if (k == 1) return min(nums1[i], nums2[j]);
        
        int pa = min(i + k/2, (int)nums1.size()), pb = j + (k - (pa - i));
        
        if (nums1[pa - 1] < nums2[pb - 1])  return findKthNumberSortedArrays(nums1, pa, nums2, j, k - (pa - i));
        else if (nums1[pa - 1] > nums2[pb - 1]) return findKthNumberSortedArrays(nums1, i, nums2, pb, k - (pb - j));
        else    return nums1[pa - 1];
    }
};



int main()
{
	//样例测试
 	int len_a = 5, len_b = 1;
	int arr_a[5] = {1,2,3,4,5};
	int arr_b[1] = {1};
// 	cout << "input length of A: ";
// 	cin >> len_a;
// 	cout << "input length of B: ";
// 	cin >> len_b;
// 
// 	int* arr_a = new int[len_a];
// 	int* arr_b = new int[len_b];
// 	
// 	cout << "input elements of A: ";
// 	for(int i = 0; i < len_a; i++)
// 		cin >> arr_a[i];
// 
// 	cout << "input elements of B: ";
// 	for(int i = 0; i < len_b; i++)
// 		cin >> arr_b[i];

	double median = 0;
	vector<int> iveca, ivecb;
	for (int i = 0; i != len_a; i++)	iveca.push_back(arr_a[i]);
	for (int i = 0; i != 1; i++)	ivecb.push_back(arr_b[i]);
	iveca.clear();
// 	Solution_v1 slt;
// 	median = slt.findMedianSortedArrays(arr_a, len_a, arr_b, len_b);
// 	cout << "program's result: " << median << endl;

	Solution slot;
	median = slot.findMedianSortedArrays(iveca, ivecb);

	return 0;
	
}
