///@file	House Robber II
/*
After robbing those houses on that street, the thief has found himself a new place for his thievery so that he will not get too much attention. This time, all houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, the security system for these houses remain the same as for those in the previous street.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
*/
///@author	zhaowei
///@date	2015.08.02
///@version	1.0

#include <vector>

using namespace std;

class Solution {
public:
	///@brief	����ٷ����ٻ�װ���ݵ������
	///@param	nums	���ݽ��
	///@return	����������ٽ��
	///@note	����"House Robber"�е��㷨������װ���ݸĳ���״���еģ��ֱ�ȥ����һ�����Ӻ����һ����������������Ȼ��ȡ�����ֵ���ɡ�
	//			ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(n)��
	int rob(vector<int>& nums) {
		if (nums.empty())		return 0;
		if (nums.size() == 1)	return nums[0];

		vector<int> rooms1(nums.begin(), --nums.end());
		vector<int> rooms2(++nums.begin(), nums.end());
		int n1 = rob_line(rooms1);
		int n2 = rob_line(rooms2);

		return n1 > n2 ? n1 : n2;
	}

private:
	///@brief	����ٷ��ܹ����ٵ������
	///@param	ÿ�ҵĽ��
	///@return	����������ٽ��
	/* @note	��̬�滮����dp[i]��ʾ��ǰi�ҵ�������ʼ����dp[0] = nums[0]��dp[1] = max(nums[0], nums[1])�����ƹ�ϵʽΪ
				dp[i] = max(dp[i-2]+nums[i], dp[i-1])��ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(n)��*/
	int rob_line(vector<int>& nums) {
		if (nums.empty())		return 0;
		if (nums.size() == 1)	return nums[0];

		vector<int> dp(nums.size(), 0);
		dp[0] = nums[0];
		dp[1] = max(nums[0], nums[1]);

		for (int i = 2; i != nums.size(); i++)
		{
			dp[i] = max(nums[i]+dp[i-2], dp[i-1]);
		}

		return dp.back();
	}
};

int main()
{
	int n[4] = {10,1,2,17};
	vector<int> nums;
	for (int i = 0; i < 4; i++)
		nums.push_back(n[i]);

	Solution slt;
	int rslt = slt.rob(nums);
	return 0;
}