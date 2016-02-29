///@file	3Sum Smaller
///@author	zhaowei
///@date	2016.01.29
///@version	1.0

///@date	2016.02.29
///@version	1.1

#include <vector>
#include <algorithm>
using namespace std;

class Solution_v1 {
public:
	///@brief	找出数组中比指定值小的三元组数目
	///@param	nums	数组
	///@param	target	指定值
	///@return	返回符合条件的三元组数目
	///@note	1. 对数组排序后，用双指针首尾向中间遍历，类似3Sum的解法；当和小于指定值时，计算出可能组合数，然后移动左指针；否则移动右值针；
	//			2. 重复三元组也可以存在，这与3Sum完全不同；
	//			3. 时间复杂度为O(n^2)，空间复杂度为O(1)。
	int threeSumSmaller(vector<int>& nums, int target) {
		if (nums.size() < 3)	return 0;
		int rslt = 0;
		sort(nums.begin(), nums.end());
		for (int i = 0; i != nums.size() - 2; i++) {		
			int sum = target - nums[i];
			int left = i + 1, right = nums.size() - 1;
			while (left <= right) {
				if (nums[left] + nums[right] < sum) {
					rslt += right - left;						
					left++;	//	与3Sum不同，这里只移动左边界，因为右边界固定好后通过left的增大来判定和是否小于target
				}
				else {
					right--;
				}
			}		
		}
		return rslt;
	}
};

class Solution {
public:
	///@note	1. 计算比指定值小的三元组个数时，内层循环计算的是固定住第一个，第二个元素变化时的元组数目；
	//			外层循环是改变第一个元素的位置来计算元组数目。
	int threeSumSmaller(vector<int>& nums, int target) {
		if (nums.size() < 3)	return 0;
		sort(nums.begin(), nums.end());
		int left = 0, right = nums.size() - 1, rslt = 0, sum = 0;
		for (int i = 0; i != nums.size() - 2; i++) {
			sum = target - nums[i];
			left = i + 1;
			right = nums.size() - 1;
			while (left <= right) {
				if (nums[left] + nums[right] < sum){
					rslt += right - left;
					left++;
				}
				else right--;
			}
		}
		return rslt;
	}
};

int main() {
	int n[] = {3,2,-2,6,2,-2,6,-2,-4,2,3,0,4,4,1};
	vector<int> nums;
	for (int i = 0; i != 15; i++)	nums.push_back(n[i]);
// 	nums.push_back(-2);
// 	nums.push_back(0);
// 	nums.push_back(0);
// 	nums.push_back(2);
// 	nums.push_back(2);
	Solution slt;
	int rslt = slt.threeSumSmaller(nums, 3);
	return 0;
}