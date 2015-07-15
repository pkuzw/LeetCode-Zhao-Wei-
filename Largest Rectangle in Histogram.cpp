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
#include <stack>

using namespace std;

class Solution {
public:
	///@brief	计算直方图最大的矩形面积
	///@param	height	直方图的高度数组
	///@return	返回最大矩形的面积
	///@note	比较朴素的想法是通过一个二重循环枚举每一种矩形，然后找出其中的最大值。时间复杂度为O(n^2)，空间复杂度为O(1)；
	//			通过思考，可以做如下改进，对于每一个柱子，以它为中心进行延展，即该柱子的高度为它所代表的矩形的最低高度，这样时间复杂度在最坏
	//			情况下也为O(n^2)，但最好情况能到O(n)。空间复杂度为O(1)
	int largestRectangleArea_time_O_n2(vector<int>& height) {
		int max_area = 0;	//	最大矩形面积
		for (int i = 0; i != height.size(); i++)
		{
			int width = sequentialHistograms(height, i);
			int area = height[i]*width;
			max_area = max(max_area, area);
		}
		return max_area;
	}

	///@brief	计算直方图最大的矩形面积
	///@param	height	直方图的高度数组
	///@return	返回最大矩形的面积
	///@note	通过维护一个栈，来保存连续递增的圆柱的下标，当遇到比上一个柱子小的柱子时，弹栈并计算栈中柱子的面积。
	//			如果栈为空，则计算当前柱子高度与当前下标的乘积。每次计算前要在末尾加上一个0，用来最后清栈。要不然就在最后清一次栈。
	//			时间复杂度为O(n)，空间复杂度为O(n)。
	int largestRectangleArea_time_O_n(vector<int>& height) {
		stack<int> stck;	//	保存柱子下标的栈
		height.push_back(0);//	末尾添加0元素，便于最后清栈
		int max_area = 0;	
		int i = 0;
		while (i < height.size())
		{
			if (stck.empty() || height[stck.top()] <= height[i])
			{
				stck.push(i);
				i++;
			}
			else
			{
				int tp = stck.top();
				stck.pop();
				max_area = max(max_area, height[tp] * (stck.empty() ? i : i-stck.top()-1));
			}
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
// 	for (int i = 0; i < 20000; i++)
// 	{
// 		histogram.push_back(i);
// 	}
 	
 	histogram.push_back(4);
 	histogram.push_back(2);
 	histogram.push_back(7);
 	histogram.push_back(3);
 	histogram.push_back(2);
 	histogram.push_back(5);

	Solution slt;
	cout << slt.largestRectangleArea_time_O_n(histogram) << endl;
	cout << slt.largestRectangleArea_time_O_n2(histogram) << endl;
	return 0;
}