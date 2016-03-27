///@file	Patching Array
///@author	zhaowei
///@date	2016.03.27
///@version	1.0

#include <vector>
using namespace std;

class Solution {
public:
	///@brief	给定一个数组和指定值，如果想要使数组的和覆盖所有{1..n}的值，应该最少添加多少元素
	///@param	nums	数组
	///@param	n		指定值
	///@return	返回最少需要添加的元素数目
	/* @note	First before we truly get started, let's suppose we are in a state where we can reach 'top' by the sub-array 
	
	nums[0...i] of the current 'nums' then what should we consider for the next nums[i+1]? now we need to check that if the 
	
	nums[i+1] is less than or equal to top: if it is then top should be updated, right? We can include nums[i+1] to reach 
	
	top+nums[i+1] then. Confused? Think about it thrice $$ but if nums[i+1] is equal to top+1, then we can just use nums[i+1]
	
	alone and nums[0...i] to reach top+1, right? Similarly in this case we can reach 2*top+1 (nums[i+1]+top) right? So to sum up,
	
	if nums[i+1] <= top+1 we need to update the top to top+nums[i+1] and execute i++ to move index;	but if nums[i+1] is greater 
	
	than top+1, then there is a gap (how much? God knows ^^) between top and nums[i+1]; in this case we need to add or patch a 
	
	number to the array, then what should the added number be? You guess? Bingo, it's top+1 and then the top will also be updated 
	
	to 2*top+1, right? but in this case index should not be moved but one number added. Good, let's move on...

	so what's the start? As we can see that the start value should be 1 then the top should be initialized to 0 and then everything
	
	just moves around! End of the story! As for the time cost, the nums array is limited and n is then determined by the top = 2*top+1 
	
	equation, so O(logn) should be better to describe its time cost.

	Space cost O(1)
	Time cost O(logn)
	*/
	int minPatches(vector<int>& nums, int n) {
		int count = 0, index = 0;
		long long top = 0;
		while(top < n) {
			if(index < nums.size() && nums[index] <= top + 1)	top += nums[index++];
			else {
				count++;
				top = 2 * top + 1;
			}
		}
		return count;
	}
};

int main() {
	return 0;
}