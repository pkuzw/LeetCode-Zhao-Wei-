///@file	Largest Rectangle in Histogram
/*
Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.

For example,
Given height = [2,1,5,6,2,3],
return 10.
*/
///@author	zhaowei
///@date	2015.7.15
///@version	1.0

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
	///@brief	计算直方图最大的矩形面积
	///@param	height	直方图的高度数组
	///@return	返回最大矩形的面积
	///@note	比较朴素的想法是通过一个二重循环枚举每一种矩形，然后找出其中的最大值。时间复杂度为O(n^2)，空间复杂度为O(1)；
	//			通过思考，可以做如下改进，对于每一个柱子，以它为中心进行延展，即该柱子的高度为它所代表的矩形的最低高度，这样时间复杂度在最坏
	//			情况下也为O(n^2)，但最好情况能到O(n)。空间复杂度为O(1)
	int largestRectangleArea(vector<int>& height) {
		int max_area = 0;	//	最大矩形面积
		for (int i = 0; i != height.size(); i++)
		{
			int width = sequentialHistograms(height, i);
			int area = height[i]*width;
			max_area = max(max_area, area);
		}
		return max_area;
	}

private:
	///@brief	给定直方图和某一柱子的下标，找到以它为中心的，高度最低为它的高度的连续柱子数目
	///@pram	height	直方图数组
	///@param	indx	柱子的下标
	///@return	返回高度最低为它的高度的连续柱子数目
	int sequentialHistograms(vector<int> &height, const int indx)
	{
		int left_cnt = 0, right_cnt = 0;
		for (int i = indx; i >= 0; i--)
		{
			if (height[i] >= height[indx])
				left_cnt++;			
			else
				break;
		}
		for (int i = indx; i < height.size(); i++)
		{
			if (height[i] >= height[indx])
				right_cnt++;			
			else
				break;
		}
		return left_cnt+right_cnt-1;
	}
};

int main()
{
	vector<int> histogram;
	histogram.push_back(0);
/*	histogram.push_back(2);/*
	histogram.push_back(4);
	histogram.push_back(6);
	histogram.push_back(2);
	histogram.push_back(3);*/

	Solution slt;
	cout << slt.largestRectangleArea(histogram) << endl;
	return 0;
}