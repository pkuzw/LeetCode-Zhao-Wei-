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
	///@brief	����ֱ��ͼ���ľ������
	///@param	height	ֱ��ͼ�ĸ߶�����
	///@return	���������ε����
	///@note	�Ƚ����ص��뷨��ͨ��һ������ѭ��ö��ÿһ�־��Σ�Ȼ���ҳ����е����ֵ��ʱ�临�Ӷ�ΪO(n^2)���ռ临�Ӷ�ΪO(1)��
	//			ͨ��˼�������������¸Ľ�������ÿһ�����ӣ�����Ϊ���Ľ�����չ���������ӵĸ߶�Ϊ��������ľ��ε���͸߶ȣ�����ʱ�临�Ӷ����
	//			�����ҲΪO(n^2)�����������ܵ�O(n)���ռ临�Ӷ�ΪO(1)
	int largestRectangleArea(vector<int>& height) {
		int max_area = 0;	//	���������
		for (int i = 0; i != height.size(); i++)
		{
			int width = sequentialHistograms(height, i);
			int area = height[i]*width;
			max_area = max(max_area, area);
		}
		return max_area;
	}

private:
	///@brief	����ֱ��ͼ��ĳһ���ӵ��±꣬�ҵ�����Ϊ���ĵģ��߶����Ϊ���ĸ߶ȵ�����������Ŀ
	///@pram	height	ֱ��ͼ����
	///@param	indx	���ӵ��±�
	///@return	���ظ߶����Ϊ���ĸ߶ȵ�����������Ŀ
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