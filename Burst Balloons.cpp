///@file	Burst Balloons
///@author	zhaowei
///@date	2016.03.19
///@version	1.0

#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

class Solution {
public:
	///@brief	����һ������ÿ��ѡ��һ�������õ���ǰ����䱾��ĳ˻���Ȼ�󽫸�����ȥ�����������ۼӺ�����Ƕ���
	///@param	nums	����
	///@return	�������ֵ
	///@note	1. ��̬�滮��
	//			2. ��dp[i][j]��ʾ�����nums[i]��nums[j]�����ͣ����ƹ�ϵʽΪdp[i][j] = dp[i][k-1] + dp[k-1] * dp[k] * dp[k+1] + dp[k+1][j]��
	//			3. ʱ�临�Ӷ�ΪO(n^3)���ռ临�Ӷ�ΪO(n^2)��
	int maxCoins(vector<int>& nums) {
		if (nums.empty())	return 0;
		int n = nums.size() + 2;

		vector<int> balloons(n, 0);
		balloons[0] = 1;
		balloons[n-1] = 1;
		for (int i = 1; i < n - 1; i++)	balloons[i] = nums[i-1];

		vector<vector<int>> dp(n, vector<int>(n, 0));
		for (int k = 2; k < n; k++) {
			for (int left = 0; left < n - k; left++) {
				int right = left + k;
				for (int i = left + 1; i < right; i++) {
					dp[left][right] = max(dp[left][right], dp[left][i] + balloons[left]*balloons[i]*balloons[right] + dp[i][right]);
				}
			}
		}
		return dp[0][n-1];
	}
};

int main() {
	vector<int> nums;
	int n[4] = {3, 1, 5, 8};
	for (int i = 0; i < 4; i++)	nums.push_back(n[i]);
	Solution slt;
	int rslt = slt.maxCoins(nums);
	return 0;
}