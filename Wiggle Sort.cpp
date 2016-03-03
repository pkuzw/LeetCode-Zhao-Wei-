///@file	Wiggle Sort
///@author	zhaowei
///@date	2016.03.03
///@version	1.0

#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

class Solution {
public:
	///@brief	将数组原地排序成波浪形顺序
	///@param	nums	数组
	///@note	1. 从前向后依次找出剩余数组内的最大值和最小值，相间的插入前端即可；
	//			2. 时间复杂度为O(n^2)，空间复杂度为O(1)。应该有更优的办法。
	void wiggleSort(vector<int>& nums) {
		if (nums.empty())	return;
		for (int i = 0; i < nums.size(); i += 2) {
			int max_ = INT_MIN, min_ = INT_MAX;
			int k = 0, l = 0;
			for (int j = i; j < nums.size(); j++) {
				if (max_ < nums[j]) {
					max_ = nums[j];
					k = j;
				}
				if (min_ > nums[j]) {
					min_ = nums[j];
					l = j;
				}
			}
			if (min_ != INT_MIN) {
				swap(nums[i], nums[l]);
				if (i == k)	k = l;	//	对于还剩的最后两个元素，防止换走了原本的最大元素，要及时更新
			}
			if (max_ != INT_MAX && i + 1 < nums.size())	swap(nums[i+1], nums[k]);	//	防止数组越界
		}
	}
};

int main() {
	int n[7] = {2, 3, 1, 6, 4, 5, 7};
	vector<int> nums;
	for (int i = 0; i != 7; i++)	nums.push_back(n[i]);
	Solution slt;
	slt.wiggleSort(nums);
	return 0;
}