///@file	Find the Duplicate Number
///@author	zhaowei
///@date	2016.03.07
///@version	1.0
///@version	2.0

#include <vector>
using namespace std;

class Solution_v1 {
public:
	///@brief	在数组中寻找重复元素，数组由从1到n的n + 1个元素组成，其中有且只有一个多次出现的元素，且可以出现多次。要求时间复杂度为O(n^2)之下，空间复杂度为O(1)，数组是只读的。
	///@param	nums	数组
	///@return	返回数组中的重复元素
	///@note	1. 在数组中依次寻找1， 2， 3，...，n，碰到相同的元素，直接返回，否则继续。
	//			2. 时间复杂度为O(n^2)；TLE
	int findDuplicate(vector<int>& nums) {
		if (nums.empty())	return -1;
		int k = 1;
		for (int i = 0; i != nums.size(); i++) {
			int cnt = 0;
			for (int j = 0; j != nums.size(); j++) {
				if (nums[j] == k)	cnt++;
				if (cnt > 1)	return nums[i];
			}
			k = i + 2;
		}
	}
};

class Solution {
public:
	///@note	1. 将数组看作是一个有环链表即可，我们将问题转换为了找到环的起始点
	//			2. 利用快慢指针法，先找到环中一点，然后再用另一个变量从头出发，另一个继续从交点出发，相交处就是环的起点，即重复元素所在。
	//			3. 时间复杂度为O(n)，空间复杂度为O(1).
	int findDuplicate(vector<int>& nums) {
		int slow = 0, fast = 0, finder = 0;
		while (1) {
			slow = nums[slow];
			fast = nums[nums[fast]];
			if (slow == fast)	break;
		}
		while (1) {
			finder = nums[finder];
			slow = nums[slow];
			if (slow == finder)	break;
		}
		return finder;
	}
};

int main() {
	vector<int> nums;	
	for (int i = 0; i < 10; i++)	nums.push_back(i+1);
	nums.push_back(7);
	Solution slt;
	int rslt = slt.findDuplicate(nums);
	return 0;
}