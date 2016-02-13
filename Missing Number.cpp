///@file	Missing Number
///@author	zhaowei
///@date	2016.02.13
///@version	1.0
///@version	1.1

#include <vector>
using namespace std;

class Solution_v1 {
public:
	///@brief	给定从0至n的无序数组，从中抽掉一个数，找到缺失的那个数。要求时间复杂度为O(n)，空间复杂度为最好为O(1)
	///@param	nums	数组
	///@return	返回缺失的那个数
	///@note	1. 遍历；
	//			2. 设置一个标记数组flg，初始化为false。当nums出现元素i时，flg[i]置为true，最后flg中为false的元素下标就是缺失元素；
	//			3. 时间复杂度为O(n)，空间复杂度为O(n)。
	int missingNumber(vector<int>& nums) {
		vector<bool> flg(nums.size() + 1, false);
		for (int i = 0; i != nums.size(); i++)	flg[nums[i]] = true;
		for (int i = 0; i != flg.size(); i++)
			if (!flg[i])	return i;
	}
};

class Solution {
public:
	///@brief	给定从0至n的无序数组，从中抽掉一个数，找到缺失的那个数。要求时间复杂度为O(n)，空间复杂度为最好为O(1)
	///@param	nums	数组
	///@return	返回缺失的那个数
	///@note	1. 遍历；
	//			2. 先计算出0 ~ n的数列和，然后减去nums中的每个元素，剩下的元素就是缺失元素；
	//			3. 时间复杂度为O(n)，空间复杂度为O(1)。
	int missingNumber(vector<int>& nums) {
		int len = nums.size();
		int sum = len * (1 + len) / 2;
		for (int i = 0; i != nums.size(); i++)	sum -= nums[i];
		return sum;
	}
};

int main() {
	vector<int> nums;
	for (int i = 0; i != 10; i++) {
		if (i == 6)	continue;
		nums.push_back(i);
	}
	Solution slt;
	int rslt = slt.missingNumber(nums);
	return 0;
}