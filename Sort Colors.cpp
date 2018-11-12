///@file	Sort Color
/*
Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, 
with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.
*/
///@author	zhaowei
///@date	2015.07.13
///@version 1.1

///@date	2015.08.27
///@version	2.0

///@date	2015.12.06
///@version	2.1

///@date	2016.04.21
///@version	2.2

///@date    November 12, 2018
///@version 2.3

#include <iostream>
#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	对数组nums进行排序
	///@param	nums	数组
	///@return  无
	///@note	手写快速排序（《算法导论》版），时间复杂度为O(nlogn)，空间复杂度为O(1)。
	void sortColors_quickSort(vector<int>& nums) {
		if (nums.empty())
		{
			return;
		}
		quickSort(nums, 0, nums.size()-1);
		return;
	}

	///@brief	对数组nums进行排序
	///@param	nums	数组
	///@return	无
	///@note	计数排序：共需要遍历两次。第一遍统计0，1，2的数目，第二遍直接将0，1，2从头到尾赋值给数组。时间复杂度为O(n)，空间复杂度为O(1)。
	void sortColors(vector<int>& nums) {
		int red_cnt = 0, white_cnt = 0, blue_cnt = 0;
		for (int i = 0; i != nums.size(); i++)
		{
			switch (nums[i])
			{
			case 0:	red_cnt++;break;
			case 1: white_cnt++;break;
			case 2: blue_cnt++;break;
			}
		}
		for (int i = 0; i != red_cnt; i++)
		{
			nums[i] = 0;
		}
		for (int i = red_cnt; i != red_cnt+white_cnt; i++)
		{
			nums[i] = 1;
		}
		for (int i = red_cnt+white_cnt; i != red_cnt+white_cnt+blue_cnt; i++)
		{
			nums[i] = 2;
		}
		return;
	}
private:
	///@brief	快速排序
	///@param	nums	待排序数组
	///@param	p		数组起始下标
	///@param	r		数组终止下标
	///@return  无
	///@note	快速排序的思想是分治，在指定范围内的数组内找到一个轴值，根据其将数组划分成两部分，左半部分小于等于轴值，有半部分大于轴值。
	void quickSort(vector<int>& nums, int p, int r)
	{
		if (p >= r)
		{
			return;
		}
		int q = partition(nums, p, r);
		quickSort(nums, p, q-1);
		quickSort(nums, q+1, r);
	}

	///@brief	找到轴值，并根据轴值进行划分
	///@param	nums	待排序数组
	///@param	p		数组起始下标
	///@param	r		数组终止下标
	///@return  返回轴值所在下标
	///@note	nums[0...i]是小于等于轴值x的部分，nums[i+1...j]是大于轴值的部分，nums[j+1...r]是未判定的部分
	int partition(vector<int>& nums, int p, int r)
	{
		int x = nums[r];
		int i = p-1;
		for (int j = p; j < r; j++)
		{
			if (nums[j] <= x)
			{
				i++;
				swap(nums[i], nums[j]);
			}
		}
		swap(nums[i+1], nums[r]);
		return i+1;
	}
};

/*
1. 用两个指针标记出红色气球的起始下标和蓝色气球的终止下标。然后从首尾向中间遍历。只需要遍历一次数组，时间复杂度为O(n)，空间复杂度为O(1)。
*/
class Solution_v2 {
public:
	///@brief	对于只有0，1，2三种元素组成的数组，进行排序。
	///@param	nums	数组
	///@return	无
	///@note	1. 因为数组中只有三种元素，那么用两个指针分别记录0和2的下标，然后从首尾开始遍历，遇到0元素，和0指针所指的元素交换，0指针自增1；遇到2元素，和2指针所指的元素交换，
	//			然后2指针自减1，且i也要自减1；将剩余的1元素留在中间即可；2. 时间复杂度为O(n)，空间复杂度为O(1)。n为数组的长度。
	void sortColors(vector<int>& nums) {
		if (nums.empty())	return;
		int red_indx = 0, blue_indx = nums.size() - 1;
		for (int i = red_indx; i <= blue_indx; i++) {
			if (nums[i] == 0)	swap(nums[i], nums[red_indx++]);
			else if (nums[i] == 2) swap(nums[i--], nums[blue_indx--]);	//	这里要将i--，因为位于i的新元素还需要再次判定是否为0或者2.
		}
	}
};

class Solution {
public:
    ///@brief   给定由红色，白色和蓝色三种颜色组成的气球集合，对其进行排序，要求空间复杂度为O(1)；
    ///@param   nums    0代表红色，1代表白色，2代表蓝色；
    ///@note    1. 枚举法；
    //          2. 用一个临时变量存储排好序后的最后一个红色气球；用一个变量存储排好序后的第一个蓝色气球；
    //          3. 从前向后遍历，遇到红色气球，就与第一个临时变量交换；遇到蓝色气球，就与第二个临时变量交换；
    //          4. 这样只需要遍历一遍数组就可以得到排好序的气球集合；
    //          5. 时间复杂度为O(n)，空间复杂度为O(1)，其中n为气球数目。
	void sortColors(vector<int>& nums) {
        int redTail = 0, blueHead = nums.size() - 1;
        for (int i = redTail; i <= blueHead; i++) {
            if (nums[i] == 0)       swap(nums[i], nums[redTail++]);
            else if (nums[i] == 2)  swap(nums[i--], nums[blueHead--]);  //  这里要同时将blueHead--，是因为有可能也将原本就是蓝色气球（2）给交换出来，如果不自减后退的话，就可能跳过被换出来的2；红色气球0不存在这个问题，因为它是从后面换到前面，本身也是小的数，不存在逆序的情况。
        }
	}
};

int main()
{
	vector<int> test;
	for (int i = 0; i <= 3; i++)
	{
		test.push_back(0);
		test.push_back(1);
		test.push_back(2);
	}
// 	Solution_v1 slt_v1;
// 	slt_v1.sortColors(test);
	Solution slt;
	slt.sortColors(test);
	
	return 0;
}
