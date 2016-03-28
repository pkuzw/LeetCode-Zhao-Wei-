///@file	Increasing Triplet Subsequence
///@author	zhaowei
///@date	2016.03.28
///@version	1.0

#include <vector>
#include <algorithm>
#include <map>
#include <stack>
using namespace std;

class Solution {
public:
	///@brief	判断数组中是否存在三个递增的子数组，要求时间复杂度为O(n)，空间复杂度为O(1)。
	///@param	nums	数组
	///@return	Return true if there exists i, j, k such that arr[i] < arr[j] < arr[k] given 0 ≤ i < j < k ≤ n-1 else return false.
	///@note	1. 利用栈来保存元素，当遇到比栈顶小的元素时就弹出，遇到比栈顶大的就压入。wa.
	//			2. 会挂在{11, 19, 12, 7, 15}上。
	bool increasingTriplet(vector<int>& nums) {
		if (nums.empty())	return false;
		stack<int> stk;
		for (int i = 0; i != nums.size(); i++) {
			if (stk.empty()) {
				stk.push(nums[i]);
				continue;
			}
			while (!stk.empty() && nums[i] < stk.top()) {
				stk.pop();
			}
			if (stk.empty() || nums[i] > stk.top())	stk.push(nums[i]);
			if (stk.size() == 3)	break;
		}
		return stk.size() == 3;
	}
};

int main() {
	int n[] = {11, 19, 12, 7, 15};
	vector<int> nums;
	for (int i = 0; i != 5; i++)	nums.push_back(n[i]);
	Solution slt;
	bool rslt = slt.increasingTriplet(nums);
	return 0;
}