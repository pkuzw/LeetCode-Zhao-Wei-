﻿///@file	Minimum Path Sum
/*
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes 
the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.
*/
///@author	zhaowei
///@date	2015.07.09
///@version 1.0

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
	///@brief	给定一个二维矩阵，计算从左上角到右下角和最小的路径
	///@param	grid	二维矩阵
	///@return	返回和最小的路径所经过各点值的和
	///@note	贪心法不可行。
	//			动态规划算法：设到达点(i, j)的和最小的路径为dp[i][j]，点(i, j)的数值为grid[i][j]，
	//			则dp[i][j] = grid[i][j] + min{dp[i-1][j], dp[i][j-1]}。
	//			时间复杂度为O(m*n)，空间复杂度为O(m*n)。
	int minPathSum(vector<vector<int>>& grid) 
	{
		if (grid.empty())	return 0;
		int m = grid.size();	//	计算棋盘的行数
		
		if (grid[0].empty())	return 0;
		int n = grid[0].size();	//	计算棋盘的列数
		
		
		vector<int> line(n+1, INT_MAX);	//	将dp初始化为INT_MAX的m+1*n+1的矩阵。之所以是INT_MAX，是为了后续计算时得到前一个点的最小和路径。
		vector<vector<int>> dp(m+1, line);	//	多出来一行和一列，方便第一个点的初始化	
		dp[1][0] = 0;	//	将dp[0][1]或dp[1][0]任意一个置为0，以便初始化第一个点dp[1][1]。
		for (int i = 1; i < m+1; i++)
		{
			for (int j = 1; j < n+1; j++)
			{
				dp[i][j] = grid[i-1][j-1] + min(dp[i-1][j], dp[i][j-1]);
			}
		}
		return dp[m][n];
	}
};

int main()
{
	vector<vector<int>> grid;
	Solution slt;
	
	vector<int> line;
	line.push_back(1);
 	line.push_back(30);
 	line.push_back(1);
 	line.push_back(1000);
 	line.push_back(1);
	grid.push_back(line);

	line.clear();
	line.push_back(1);
	line.push_back(6);
	line.push_back(54);
	line.push_back(5);
	line.push_back(1);
	grid.push_back(line);

	line.clear();
	line.push_back(1);
	line.push_back(50);
	line.push_back(1);
	line.push_back(3);
	line.push_back(1);
	grid.push_back(line);

	line.clear();
	line.push_back(1);
	line.push_back(1);
	line.push_back(1);
	line.push_back(100);
	line.push_back(1);
	grid.push_back(line);
	
	int minPath = slt.minPathSum(grid);
	cout << minPath << endl;
}