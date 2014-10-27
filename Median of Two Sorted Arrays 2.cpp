///@file leetcode����еĽⷨ��ʱ�临�Ӷ�O(log(m+n)), �ռ临�Ӷ�O(log(m+n))
///@author zhaowei
///@date 2014.10.27
///@version 1.0
/// ע��ѧϰһ������еĴ����񡣿��С��ո�������������ࡣ
#include <iostream>
using namespace std;

class Solution
{
public:
	double findMedianSortedArrays(int A[], int m, int B[], int n){
		int total = m + n; //����������ĳ���֮��
		if(total & 0x1)
			return find_kth(A, m, B, n, total / 2 + 1);
		else
			return (find_kth(A, m, B, n, total / 2) + find_kth(A, m, B, n, total / 2 + 1)) / 2;
	}
private:
	static double find_kth(int A[], int m, int B[], int n, int k){
		//����m������n
		if (m > n) return find_kth(B, n, A, m, k);
		if (m == 0) return B[k - 1];
		if (k == 1) return min(A[0], B[0]);


		//��k��Ϊ������
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