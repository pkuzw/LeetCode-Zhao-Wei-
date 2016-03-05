///@file	Move Zeroes
///@author	zhaowei
///@date	2016.03.04
///@version	1.0

///@date	2016.03.05
///@version	1.1

#include <vector>
using namespace std;

class Solution_v1 {
public:
	///@brief	将数组中的0都移动到尾部，保持数组的其他元素相对顺序不变，要求空间复杂度为O(1)；
	///@param	nums	数组
	///@note	1. 用一个变量统计出0的数目，然后用一个变量标记当前移动的顶头的非零元素下标，在遍历时遇到非零的就想前移动到这个下标位置；
	//			2. 然后在尾部补充满足够的0；
	//			3. 时间复杂度为O(n)，空间复杂度为O(1).
	void moveZeroes(vector<int>& nums) {
		int zero_cnt = 0;
		for (int i = 0; i != nums.size(); i++)
			if (!nums[i])	zero_cnt++;
		int k = 0;
		for (int i = 0; i != nums.size() - zero_cnt; i++) {
			if (!nums[i]) {
				int j = k + 1;
				while (j < nums.size() && !nums[j])	j++;
				k = j;
				swap(nums[i], nums[j]);
			}
			else	k++;
		}
	}
};

class Solution {
public:
	///@note	1. 在v1的基础上改良为one-pass。
	void moveZeroes(vector<int>& nums) {
		int k = 0;
		for (int i = 0; i != nums.size(); i++) {
			if (!nums[i]) {
				int j = k + 1;
				while (j < nums.size() && !nums[j])	j++;
				k = j;
				if (j < nums.size())	swap(nums[i], nums[j]);
			}
			else	k++;

		}
	}
};

int main() {
	int n[10] = {4,2,4,0,0,3,0,5,1,0};
	vector<int> nums;
	for (int i = 0; i != 10; i++)	nums.push_back(n[i]);
	Solution slt;
	slt.moveZeroes(nums);
	return 0;
}