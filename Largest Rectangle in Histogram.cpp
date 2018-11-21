///@file	Largest Rectangle in Histogram
/*
Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, 
find the area of largest rectangle in the histogram.

For example,
Given height = [2,1,5,6,2,3],
return 10.
*/
///@author	zhaowei
///@date	2015.7.15
///@version	1.0

///@date	2015.08.26
///@version	2.0

///@date	2015.12.09
///@version	2.1

///@date	2016.05.02
///@version	2.2

///@date    November 20, 2018
///@version 2.3

#include <vector>
#include <iostream>
#include <stack>

using namespace std;

class Solution_v1 {
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
	//			如果栈为空，则计算当前柱子高度与当前下标的乘积。计算前要在输入数据末尾加上一个0，用来最后清栈。要不然就在最后清一次栈。
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

class Solution_v2 {
public:
	///@brief	计算直方图最大的矩形面积
	///@param	height	直方图的高度数组
	///@return	返回最大矩形的面积
	///@note	1. 通过维护一个栈，来保存连续递增的圆柱的下标，当遇到比上一个柱子矮的柱子时，弹栈并计算栈中柱子的面积。
	//			2. 如果栈为空，则计算当前柱子高度与当前下标的乘积。
	//			3. 计算前要在输入数据末尾加上一个0，用来最后清栈。
	//			4. 时间复杂度为O(n)，空间复杂度为O(n)。
	//			5. 理解的不够透彻，还需要继续再想想。
	int largestRectangleArea(vector<int>& height) {
		height.push_back(0);
		int rslt = 0;
		stack<int> stk;
		int i = 0;
		while (i < height.size()) {
			if (stk.empty() || height[i] >= height[stk.top()])	stk.push(i++);
			else {
				int tp = stk.top();
				stk.pop();
				rslt = max(rslt, height[tp] * (stk.empty() ? i : i - stk.top() - 1));
			}
		}
		return rslt;
	}
};

class Solution {
public:
    ///@brief   给定一组直方图，每个长方形柱体的宽度为1，高度通过数组给定。计算直方图所包含矩形的最大面积。
    ///@param   heights 直方图的高度数组
    ///@return  返回直方图包含的矩形的最大面积。
    ///@note    1. 栈；
    //          2. 通过栈来记录连续非降直方图序列；
    //          3. 从前向后遍历整个直方图序列，如果当前遍历的直方图柱体不比栈顶直方图高度低，就压栈；
    //             否则就弹栈，并计算弹栈后该柱体的高度乘以当前柱体的下标减去当前栈顶柱体的下标（注意：不是弹栈后柱体的下标！）再减1（作
    //             为宽度）。
    //          4. 这样计算能够保证计算出所有连续柱体中不同高度的最大矩形面积。注意，因为栈中始终是保存着非降柱体的序列，所以无论何时，
    //             heights[tp]作为已经弹出的柱体的高度，视为矩形的高度；i - stk.top() - 1是这么个意思，i是矩形的右边界的右邻居柱
    //             体下标，stk.top()是矩形左边界的左邻居下标，那么这两个求差再减1就是矩形的宽度，因为栈内保存的柱体高度是非降的，那么
    //             无论stk.top()和已经弹出的tp = stk.pop()是否连续，一定能够保证(stk.top(), tp)之间的柱体最低高度是
    //             heights[tp]；
    //          5. 最后，为了收尾，需要实现在heights数组中的末尾添加0，以确保所有的栈内元素都会被弹出。
    //          5. 时间复杂度为O(n)，空间复杂度为O(n)，其中n是直方图柱体的个数。这个算法确实巧妙，第4步的理解也比较违反直觉，需要仔细
    //             构造例子来理解。
    //          6. 几个例子：a. {1, 100, 99, 100}；
    //                     b. {1, 99, 100, 1, 100}.
    //             把这两个例子想明白，你也就理解了。
	int largestRectangleArea(vector<int>& heights) {
        if (heights.empty())    return 0;
        stack<int> stk;
        int rslt = 0;
        int i = 0;
        heights.push_back(0);
        while (i < heights.size()) {
            if (stk.empty() || heights[i] >= heights[stk.top()]) {
                stk.push(i++);
            }
            else {
                int tp = stk.top();
                stk.pop();
                rslt = max(rslt, heights[tp] * (stk.empty() ? i : i - stk.top() - 1));
            }
        }
        return rslt;
    }
};

int main()
{
    int a[6] = {1,99,100,1,100};
	vector<int> histogram(a, a+4);

//	Solution_v1 slt_v1;
//	int rslt = slt_v1.largestRectangleArea_time_O_n(histogram);
//	rslt = slt_v1.largestRectangleArea_time_O_n2(histogram);
	Solution slt;
	int rslt = slt.largestRectangleArea(histogram);
	return 0;
}
