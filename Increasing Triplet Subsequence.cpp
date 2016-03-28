///@file	Increasing Triplet Subsequence
///@author	zhaowei
///@date	2016.03.28
///@version	1.0
///@version	1.1

#include <vector>
#include <algorithm>
#include <map>
#include <stack>
using namespace std;

class Solution_v1 {
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

class Solution {
public:
	///@note	1. 在v1的基础上，进行修改。	
	//			2. 如果stack中为空，则压入当前元素；
	//			3. 如果stack中有一个元素，则找到一个比它大的元素入栈。如果当前元素比它小，则出栈，将当前元素压入，如果比它大，则入栈；
	//			4. 如果stack中已经有两个元素了，就在剩余数组中寻找比栈顶元素大的元素；
	//			5. 时间复杂度为O(n^2)，空间复杂度为O(1)。
	bool increasingTriplet(vector<int>& nums) {
		if (nums.empty())	return false;
		stack<int> stk;
		for (int i = 0; i != nums.size(); i++) {
			if (stk.empty())	stk.push(nums[i]);
			else if (stk.size() == 1) {
				if (nums[i] < stk.top()) {
					stk.pop();
					stk.push(nums[i]);
				}
				else if (nums[i] > stk.top())	stk.push(nums[i]);
			}
			else if (stk.size() == 2) {
				for (int j = i; j < nums.size(); j++) {
					if (nums[j] > stk.top())	return true;
				}
				stk.pop();
				i--;
			}
		}
		return false;
	}
};

int main() {
	int n[] = {17, 29, 12, 7, 15, 23};
	vector<int> nums;
	for (int i = 0; i != 6; i++)	nums.push_back(n[i]);
	Solution slt;
	bool rslt = slt.increasingTriplet(nums);
	return 0;
}