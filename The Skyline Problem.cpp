///@file	The Skyline Problem
/*
A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. Now suppose you are given the locations and height of all the buildings as shown on a cityscape photo (Figure A), write a program to output the skyline formed by these buildings collectively (Figure B).

The geometric information of each building is represented by a triplet of integers [Li, Ri, Hi], where Li and Ri are the x coordinates of the left and right edge of the ith building, respectively, and Hi is its height. It is guaranteed that 0 ≤ Li, Ri ≤ INT_MAX, 0 < Hi ≤ INT_MAX, and Ri - Li > 0. You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.

For instance, the dimensions of all buildings in Figure A are recorded as: [ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ] .

The output is a list of "key points" (red dots in Figure B) in the format of [ [x1,y1], [x2, y2], [x3, y3], ... ] that uniquely defines a skyline. A key point is the left endpoint of a horizontal line segment. Note that the last key point, where the rightmost building ends, is merely used to mark the termination of the skyline, and always has zero height. Also, the ground in between any two adjacent buildings should be considered part of the skyline contour.

For instance, the skyline in Figure B should be represented as:[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ].

Notes:

The number of buildings in any input list is guaranteed to be in the range [0, 10000].
The input list is already sorted in ascending order by the left x position Li.
The output list must be sorted by the x position.
There must be no consecutive horizontal lines of equal height in the output skyline. For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable; the three lines of height 5 should be merged into one in the final output as such: [...[2 3], [4 5], [12 7], ...]
*/
///@author	zhaowei
///@date	2015.07.30
///@version	1.0

#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
	///@brief	计算一组大楼的天际线
	///@param	buildings	一幢楼由一个三元组表示<L, R, H>，左边界，右边界和高度值
	///@return	返回大楼的轮廓线
	/* @note	扫描法。先将大楼的高度和左右端点拆分成不同的两个二元组，然后对这些点按照x值进行排序，如果遇到左端点，就进入保存有每个端点高度值的multiset，否则
				就在multiset中删除该元素。然后再看当前multiset中的最大值是否与原先的最大值相同，如果不同就将一个端点压入结果数组。时间复杂度为O(nlogn)，空间复杂度为O(n)。*/
	vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
		vector<pair<int, int>> rslt;
		vector<pair<int, int>> point;
		multiset<int> height;	//	每个点的高度

		for (int i = 0; i != buildings.size(); i++)	//	将线段拆分成端点
		{
			point.push_back(make_pair(buildings[i][0], -buildings[i][2]));
			point.push_back(make_pair(buildings[i][1], buildings[i][2]));
		}

		sort(point.begin(), point.end());	//	对每个点按照x值进行排序

		height.insert(0);	//	插入初始值
		int cur_max = 0;	//	当前最大高度
		int pre_max = 0;	//	之前的最大高度
		for (int i = 0; i != point.size(); i++)
		{
			if (point[i].second < 0)		height.insert(-point[i].second);	//	压入左端点高度值
			else						height.erase(height.find(point[i].second));	//	删除右端点高度值

			cur_max = *height.rbegin();
			if (cur_max != pre_max)	//	如果最大高度值发生变化，说明出现了拐点，压入结果数组
			{
				rslt.push_back(make_pair(point[i].first, cur_max));
				pre_max = cur_max;
			}
		}
		return rslt;
	}
};

int main()
{
	vector<int> line;
	vector<vector<int>> buildings;
	line.push_back(2);
	line.push_back(9);
	line.push_back(10);
	buildings.push_back(line);
	line.clear();

	line.push_back(3);
	line.push_back(7);
	line.push_back(15);
	buildings.push_back(line);
	line.clear();	// [5 12 12], [15 20 10], [19 24 8]

	line.push_back(5);
	line.push_back(12);
	line.push_back(12);
	buildings.push_back(line);
	line.clear();

	line.push_back(15);
	line.push_back(20);
	line.push_back(20);
	buildings.push_back(line);
	line.clear();

	line.push_back(19);
	line.push_back(24);
	line.push_back(8);
	buildings.push_back(line);
	line.clear();

	Solution slt;
	slt.getSkyline(buildings);
	return 0;
}