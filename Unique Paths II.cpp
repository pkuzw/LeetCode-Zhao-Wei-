///@file	Unique Paths
/*
Follow up for "Unique Paths":

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and empty space is marked as 1 and 0 respectively in the grid.

For example,
There is one obstacle in the middle of a 3x3 grid as illustrated below.

[
[0,0,0],
[0,1,0],
[0,0,0]
]
The total number of unique paths is 2.
*/
///@author	zhaowei
///@date	2015.07.08
///@version	1.0

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	///@brief	计算有障碍物的路径总数
	///@param	obstacleGrid	用二维数组表示障碍物分布，其中1为障碍物，0为通路
	///@return	返回路径总数
	///@note	根据障碍物将棋盘划分成若干个小的不含有障碍物的矩形。通过这些不含有障碍物的矩形，来计算可能的路径总数。还没有想得很清楚。
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) 
	{

	}
};

int main()
{
	return 0;
}