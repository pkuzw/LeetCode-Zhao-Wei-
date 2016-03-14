///@file	Longest Increasing Subsequence
///@author	zhaowei
///@date	2016.03.14
///@version	1.0
///@version	2.0

#include <vector>
#include <algorithm>
using namespace std;

class Solution_v1 {
public:
	///@brief	寻找最长的递增子序列
	///@param	nums	数组
	///@return	返回最长递增子序列的长度
	///@note	1. 动态规划；
	//			2. 设dp[i]表示前i个数中最长的递增子序列长度，初始化dp[i] = 1；
	//			3. 递推方程为dp[i] = (dp[j] + 1) > dp[i] ? dp[j] + 1 : dp[i]；其中0 <= j < i；
	//			4. 时间复杂度为O(n^2)，空间复杂度为O(n)。其中n为数组长度。
	int lengthOfLIS(vector<int>& nums) {
		if (nums.empty())	return 0;
		vector<int> dp(nums.size(), 1);
		for (int i = 1; i < nums.size(); i++)
			for (int j = 0; j < i; j++)
				if (nums[j] < nums[i])
					if (dp[j] + 1 > dp[i])	dp[i] = dp[j] + 1;				

		int rslt = 0;
		for (int i = 0; i < nums.size(); i++)	rslt = max(rslt, dp[i]);
		return rslt;
	}
};

class Solution {
public:
	///@note	1. 二分查找；
	//			2. 在从前向后遍历的过程中，维护一组序列，使得其一直有序；
	//			3. 如果该序列为空，将当前元素插入；
	//			4. 如果该序列不为空，找到第一个比当前元素大的元素，将该元素替换为当前元素；
	//			5. 如果不存在比当前元素大的元素，则将当前元素放入末端；以上的插入操作利用lower_bound()即可完成；
	//			6. 可以利用原来的数组来当该序列，空间复杂度降低为O(1)；
	//			7. 时间复杂度为O(nlogn)。
	int lengthOfLIS(vector<int>& nums) {
		if (nums.empty())	return 0;
		vector<int>::iterator i = nums.begin();
		for (int j = 0; j != nums.size(); j++) {
			vector<int>::iterator k = lower_bound(nums.begin(), i, nums[j]);
			*k = nums[j];
			if (k == i)	i++;
		}
		return i - nums.begin();
	}
};

int main() {
	int n[8] = {10, 9, 2, 5, 3, 7, 101, 18};
	vector<int> nums;
	for (int i = 0; i != 8; i++)	nums.push_back(n[i]);
	Solution slt;
	int rslt = slt.lengthOfLIS(nums);
	return 0;
}