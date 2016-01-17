///@file	Two Sum II - Input array is sorted
/*
Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.

You may assume that each input would have exactly one solution.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2
*/
///@author	zhaowei
///@date	2015.08.12
///@version	1.0

///@date	2016.01.17
///@version	1.1

#include <algorithm>
#include <vector>
using namespace std;

class Solution_v1 {
public:
	///@brief	在已经排好序的数组中寻找两个数之和为指定值的元素下标
	///@param	numbers	数组
	///@param	target	指定值
	///@return	和为指定值的元素下标
	///@note	二分查找。时间复杂度为O(nlogn)，空间复杂度为O(1)。
	vector<int> twoSum(vector<int>& numbers, int target) {
		vector<int> rslt;
		if (target > numbers[numbers.size()-1] + numbers[numbers.size()-2])		return rslt;
		for (int i = 0; i != numbers.size()-1; i++)
		{
			rslt.push_back(i+1);
			int j = binarySearch(numbers, i+1, numbers.size()-1, target-numbers[i]);
			if ( j != -1)
			{
				rslt.push_back(j+1);
				return rslt;
			}
			else
			{
				rslt.pop_back();
			}
		}
	}
private:
	int binarySearch(const vector<int>& nums, int p, int r, const int& v)
	{
		if (p > r)	return -1;
		int mid = (p + r) / 2;
		if (nums[mid] == v)	return mid;
		else if (nums[mid] > v)	return binarySearch(nums, p, mid-1, v);
		else	return binarySearch(nums, mid+1, r, v);
	}
};

class Solution {
public:
	///@brief	在已经排好序的数组中寻找两个数之和为指定值的元素下标
	///@param	numbers	数组
	///@param	target	指定值
	///@return	和为指定值的元素下标
	///@note	1. 二分查找
	vector<int> twoSum(vector<int>& numbers, int target) {
		vector<int> rslt;
		for (int i = 0; i != numbers.size(); i++) {
			if (numbers[i] > target)	break;
			rslt.push_back(i + 1);
			int j = binarySearch(numbers, target - numbers[i], i + 1);
			if (j == -1)		rslt.pop_back();
			else {
				rslt.push_back(j + 1);
				break;
			}
		}
		return rslt;		
	}

	///@brief	二分查找
	///@param	numbers	数组
	///@param	val		指定值
	///@param	l		开始查找的起始下标
	///@return	返回指定值在数组中的下标
	int binarySearch(const vector<int>& numbers, const int& val, const int& l) {
		int i = l, j = numbers.size() - 1;
		while (i <= j) {
			int k = (i + j) / 2;
			if (numbers[k] == val)	return k;
			else if (numbers[k] < val)	i = k + 1;
			else	j = k - 1;
		}
		return -1;
	}
};

int main()
{
	int n[3] = {2, 3, 4};
	vector<int> nums;
	for (int i = 0; i != 3; i++)
		nums.push_back(n[i]);

	//[3,24,50,79,88,150,345], 200
	Solution slt;
	vector<int> rslt = slt.twoSum(nums, 6);
	return 0;
}