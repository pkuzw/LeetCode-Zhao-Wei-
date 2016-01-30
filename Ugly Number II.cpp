///@file	Ugly Number II
///@author	zhaowei
///@date	2016.01.30
///@version	1.0

#include <vector>
using namespace std;

class Solution {
public:
	///@brief	���ɵ�n������
	///@param	n	���
	///@return	���ص�n������
	///@note	1. ��̬�滮��
	//			2. ��dp[i]��ʾ��i����������ʼ��dp[0] = 1��
	//			3. ����������f2, f3, f5�ֱ�Ϊdp[i-1]����2��3��5�����С����
	//			4. ����������i2, i3, i5�ֱ��ʾָ��f2��f3��f5���±ꣻ
	//			5. ���ƹ�ϵʽΪdp[i] = min(f2 * 2, f3 * 3, f5 * 5)��
	//			6. ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(n)��
	int nthUglyNumber(int n) {
		vector<int> dp(n, 0);
		dp[0] = 1;
		int i2 = 1, i3 = 1, i5 = 1;
		int min_val = 1, f2 = 2, f3 = 3, f5 = 5;
		for (int i = 1; i != n; i++) {
			min_val = min(min(f2, f3), f5);
			dp[i] = min_val;
			if (min_val == f2)	f2 = 2 * dp[i2++];
			if (min_val == f3)	f3 = 3 * dp[i3++];
			if (min_val == f5)  f5 = 5 * dp[i5++];
		}
		return dp[n-1];
	}
};

int main() {
	Solution slt;
	int rslt = slt.nthUglyNumber(10);
	return 0;
}