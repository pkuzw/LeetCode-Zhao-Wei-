///@file	Wiggle Sort II
///@author	zhaowei
///@date	2016.03.25
///@version	1.0

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	///@brief	给定一组有重复元素的数组，使其大小相间的排列起来。要求时间复杂度为O(n)，空间复杂度为O(1)
	///@param	nums	数组
	///@return	无
	///@note	1. 通过观察，使用如下方法：
	//			2. 将数组元素分为三种，一种是比其中位数小的元素，另一种是比其中位数大的元素，最后一种是中位数。
	//			3. 按照从右至左的顺序，将比其中位数大的元素放在奇数位上，将比起小的元素放在偶数位上即可。
	//			4. 时间复杂度为O(nlogn)，可以优化至O(n)，空间复杂度为O(n)，可优化至O(1)。
	void wiggleSort(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		int k = nums.size();
		vector<int> smaller, larger;
		if (k % 2) {
			for (int i = 0; i <= k / 2; i++)	smaller.push_back(nums[i]);
			for (int i = k / 2 + 1; i < k; i++)	larger.push_back(nums[i]);
		}
		else {
			for (int i = 0; i < k / 2; i++)	smaller.push_back(nums[i]);
			for (int i = k / 2; i < k; i++)	larger.push_back(nums[i]);
		}
		for (int i = k - 1, u = 0, v = 0; i >= 0; i--) {
			if (!(i % 2))	nums[i] = smaller.empty() ? nums[i] : smaller[u++];
			else		nums[i] = larger.empty() ? nums[i] : larger[v++];
		}
	}
};

int main() {
	int n[] = {1,5,1,1,6,4};
	int n1[] = {1};
	vector<int> nums;
	for (int i = 0; i != 6; i ++)	nums.push_back(n[i]);
	Solution slt;
	slt.wiggleSort(nums);
	return 0;
}