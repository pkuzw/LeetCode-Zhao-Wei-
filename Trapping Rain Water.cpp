///@file	Trapping Rain Water
/*
			Given n non-negative integers representing an elevation map where the width of each bar is 1, 
			compute how much water it is able to trap after raining.

			For example, 
			Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.
*/
///@author	zhaowei
///@date	2015.06.20

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	///@brief	给定高程值，计算其所能接收的雨水量。每个元素所表示的高程宽度为1
	///@param	height	高程值数组
	///@return	返回其容积
	///@note	在高程值中从高往低遍历，先找到最高值和次高值，然后将次高值到最高值之间所夹矩形面积减去已有的高程值所占面积。
	//			然后将此区间标记为已处理；寻找剩余区间的最高值和次高值，仿照之前的处理，要求矩形不能包含已处理过的区域。
	//			根据主定理，该算法的时间复杂度为T(n) = 2T(n/2) + f(n)。因为是先出里的最大值和次大值区间将问题分成了左右两个子问题；
	//			然后处理中间的区间是找最大值和次大值的时间复杂度均为O(n)，计算高程值和的时间复杂度也为O(n)，故每个子问题的中间区域处理
	//			时间复杂度为f(n) = O(n)。又因为n^(log2_2) = f(n)，所以整个算法的时间复杂度为Theta(nlogn)，空间复杂度为O(1).
	int trap(vector<int>& height) 
	{
		int vol = calVolume(height, 0, height.size());
		return vol;
	}

private:

	///@brief	计算指定范围[first, last)内的容积
	///@param	height	高程值数组
	///@param	first	区间范围的起始下标
	///@param	last	区间范围的终止下标
	///@return	返回容积值
	int	calVolume(vector<int>& height, int first, int last)
	{
		int max_index = maxHeight(height, first, last);
		int second_index = secondHeight(height, first, last, max_index);

		if (max_index == -1 || second_index == -1)	// 如果区间范围不合法，则直接返回0
		{
			return 0;
		}

		int volume = (abs(max_index - second_index) - 1) * height[second_index];		//	先计算矩形的面积
		int sum_height = 0;	//	再计算高程值所占的面积
		if (max_index > second_index)	//	区分两种情形：max_index在second_index之前或之后
		{
			sum_height = sum(height, second_index+1, max_index);
			volume -= sum_height;
			volume += calVolume(height, first, second_index+1);	//	递归求解
			volume += calVolume(height, max_index, last);
		}
		else
		{
			sum_height = sum(height, max_index+1, second_index);	//	同上
			volume -= sum_height;
			volume += calVolume(height, first, max_index+1);
			volume += calVolume(height, second_index, last);
		}
		return volume;
		
	}

	///@brief	计算指定区间[first, last)内的最大值
	///@param	height	高程数组
	///@param	first	区间范围的起始下标
	///@param	last	区间范围的终止下标
	///@return	如果下标范围合法，则返回最大值的下标；否则返回-1
	int maxHeight(vector<int>& height, int first, int last)
	{
		if (first >= last)
		{
			return -1;
		}
		int max = height[first], max_index = first;
		for (int i = first; i != last; i++)
		{
			if (max < height[i])
			{
				max = height[i];
				max_index = i;
			}
		}
		return max_index;
	}

	///@brief	计算指定区间[first, last)内的次大值
	///@param	height	高程数组
	///@param	first	区间范围的起始下标
	///@param	last	区间范围的终止下标
	///@return	如果下标范围合法，则返回次大值的下标；否则返回-1
	int secondHeight(vector<int>& height, int first, int last, int max_index)
	{
		if (first >= last)
		{
			return -1;
		}
		int second1 = height[first], second2 = height[first];
		int second_index1 = first, second_index2 = first;

		second_index1 = maxHeight(height, first, max_index);	//	刨掉最大值，先计算左半区间的最大值
			
		second_index2 = maxHeight(height, max_index+1, last);	//	后计算右半区间的最大值
		

		if (second_index1 == -1)		//	最大值正好在first下标上
		{
			return second_index2;
		}
		else if (second_index2 == -1)	//	最大值正好在last-1下标上
		{
			return second_index1;
		}
		
		return height[second_index1] >= height[second_index2] ? second_index1 : second_index2;
	}

	///@brief	计算指定区间[first, last)的高程和
	///@param	height	高程数组
	///@param	first	区间的起始下标
	///@param	last	区间的终止下标
	///@return	如果区间下标合法，则返回区间的高程和；否则返回-1
	int sum(vector<int>& height, int first, int last)
	{
		int count = 0;
		
		for (int i = first; i < last; i++)
		{
			count += height[i];
		}
		return count;
	}
};

int main()
{
	vector<int> ivec;	//0,1,0,2,1,0,1,3,2,1,2,1
//	sample 1:
// 	ivec.push_back(0);
// 	ivec.push_back(1);
// 	ivec.push_back(0);
// 	ivec.push_back(2);
// 	ivec.push_back(1);
// 	ivec.push_back(0);
// 	ivec.push_back(1);
// 	ivec.push_back(3);
// 	ivec.push_back(2);
// 	ivec.push_back(1);
// 	ivec.push_back(2);
// 	ivec.push_back(1);

//	sample 2:
// 	ivec.push_back(4);
// 	ivec.push_back(3);
// 	ivec.push_back(2);
// 	ivec.push_back(1);
// 	ivec.push_back(2);
// 	ivec.push_back(3);
// 	ivec.push_back(2);
// 	ivec.push_back(1);
// 	ivec.push_back(0);
// 	ivec.push_back(1);
// 	ivec.push_back(2);
// 	ivec.push_back(3);
// 	ivec.push_back(4);
// 	ivec.push_back(4);

//	sample 3:
	ivec.push_back(0);
	ivec.push_back(4);
	ivec.push_back(4);
	ivec.push_back(4);
	ivec.push_back(0);
	Solution slt;
	
	cout << slt.trap(ivec);
	cout << endl;
	return 0;
}