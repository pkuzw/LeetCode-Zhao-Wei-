///@file leetcode题解中的解法。时间复杂度O(log(m+n)), 空间复杂度O(log(m+n))
///@author zhaowei
///@date 2014.10.27
///@version 1.0
/// 注意学习一下题解中的代码风格。空行、空格很完整，代码简洁。
#include <iostream> 
using namespace std;

class Solution
{
public: 
	double findMedianSortedArrays(int A[], int m, int B[], int n){
		int total = m + n; //计算两数组的长度之和
		if(total & 0x1)
			return find_kth(A, m, B, n, total / 2 + 1);
		else
			return (find_kth(A, m, B, n, total / 2) + find_kth(A, m, B, n, total / 2 + 1)) / 2;
	}
private:
	static double find_kth(int A[], int m, int B[], int n, int k){
		//假设m不大于n
		if (m > n) return find_kth(B, n, A, m, k);
		if (m == 0) return B[k - 1];
		if (k == 1) return min(A[0], B[0]);


		//将k分为两部分
		int pa = min(k / 2, m), pb = k - pa;
		if (A[pa - 1] < B[pb - 1])
			return find_kth(A + pa, m - pa, B, n, k - pa);
		else if (A[pa - 1] > B[pb - 1])
			return find_kth(A, m, B + pb, n - pb, k - pb);
		else
			return A[pa - 1];

	}
};
int main()
{
	return 0;
}