﻿///@file	Triangle
/*
Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle
[
	[2],
   [3,4],
  [6,5,7],
 [4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
*/
///@author	zhaowei
///@date	2015.07.24
///@version	1.0
///@version	1.1

///@date	2015.08.22
///@version	1.2

///@date	2016.01.07
///@version	1.3

#include <vector>
using namespace std;

class Solution_v1 {
public:
	///@brief	给定一个三角形，找到从顶点到底层的最小和路径
	///@param	triangle	三角形
	///@return	返回最小和路径的和
	/* @note	动态规划：设dp[i][j]表示第i层元素的第j个元素的最小和路径值。初始条件为dp[0][0] = triangle[0][0].递推关系式为
				dp[i][j] = triangle[i][j] + min(dp[i-1][j], dp[i-1][j-1]), 0 < j < triangle[i].size()-1；
				dp[i][j] = triangle[i][j] + dp[i-1][j], j = 0；
				dp[i][j] = triangle[i][j] + dp[i-1][j-1] , j = triangle[i].size()-1. 
				时间复杂度为O(n^2)，空间复杂度为O(n^2)。
	*/
	int minimumTotal_Space_O_n2(vector<vector<int>>& triangle) {
		if (triangle.empty())	return 0;

		vector<vector<int>> dp(triangle.size(), vector<int>(triangle.back().size(), 0));

		dp[0][0] = triangle[0][0];

		for (vector<vector<int>>::size_type i = 1; i != triangle.size(); i++)
			for (vector<int>::size_type j = 0; j != triangle[i].size(); j++)
			{
				if (j == 0)	dp[i][j] = triangle[i][j] + dp[i-1][j];
				else if (j == triangle[i].size()-1)	dp[i][j] = triangle[i][j] + dp[i-1][j-1];
				else	dp[i][j] = triangle[i][j] + min(dp[i-1][j], dp[i-1][j-1]);
			}

		int min_total = INT_MAX;
		for (vector<int>::size_type i = 0; i != dp.back().size(); i++)
			if (dp.back()[i] < min_total)
				min_total = dp.back()[i];
		return min_total;
	}

	///@brief	给定一个三角形，找到从顶点到底层的最小和路径
	///@param	triangle	三角形
	///@return	返回最小和路径的和
	/* @note	动态规划：设dp[i]表示某层第i个元素的最小和路径值。初始条件为dp[i] = triangle.back()[i]。从底向上递推，
				递推关系式为dp[i] = triangle[i][j] + min(dp[j], dp[j+1]), 0 <= j <= triangle[i].size()-1；
				时间复杂度为O(n^2)，空间复杂度为O(n)。
	*/
	int minimumTotal(vector<vector<int>>& triangle) {
		if (triangle.empty())	return 0;

		vector<int> dp(triangle.back().size(), 0);

		for (int i = 0; i != triangle.back().size(); i++)
			dp[i] = triangle.back()[i];

		for (int i = triangle.size()-2; i >= 0; i--)
			for (int j = 0; j != triangle[i].size(); j++)
				dp[j] = triangle[i][j] + min(dp[j], dp[j+1]);

		return dp[0];
	}
};

///@note	动态规划。自底向上。
class Solution_v1_2 {
public:
	int minimumTotal(vector<vector<int>>& triangle) {
		if (triangle.empty())	return 0;
		vector<int> dp(triangle.back().begin(), triangle.back().end());	//	dp[i]表示表示某一层第i个元素的最小路径和
		for (int i = triangle.size()-2; i >= 0; i--)
			for (int j = 0; j != triangle[i].size(); j++)
				dp[j] = triangle[i][j] + min(dp[j], dp[j+1]);
		return dp[0];
	}
};

class Solution {
public:
	///@brief	给定一个三角形，找到从顶点到底层的最小和路径
	///@param	triangle	三角形
	///@return	返回最小和路径的和
	///@note	1. 动态规划；2. 设dp[i]表示从节点triangle[j][i]向下的最小和，自底向上，最底层初始值dp[i] = triangle[j][i]；
	//			3. 递推关系式为dp[i] = triangle[j-1][i] + min(dp[i], dp[i+1])；
	//			4. 时间复杂度为O(n^2)，空间复杂度为O(n)，其中n为三角形的底层节点数。
	int minimumTotal(vector<vector<int>>& triangle) {
		if (triangle.empty() || triangle[0].empty())	return 0;
		int depth = triangle.size(), width = triangle[depth - 1].size();
		vector<int> dp(triangle[depth - 1].begin(), triangle[depth - 1].end());
		for (int j = depth - 2; j >= 0; j--)
			for (int i = 0; i < triangle[j].size(); i++)
				dp[i] = triangle[j][i] + min(dp[i], dp[i + 1]);					
		return dp[0];
	}
};

int main()
{
	vector<vector<int>> triangle;
	vector<int> line;
	line.push_back(2);
	triangle.push_back(line);

	line.clear();
	line.push_back(3);
	line.push_back(4);
	triangle.push_back(line);

	line.clear();
	line.push_back(5);
	line.push_back(6);
	line.push_back(7);
	triangle.push_back(line);

	line.clear();
	line.push_back(4);
	line.push_back(1);
	line.push_back(80);
	line.push_back(30);
	triangle.push_back(line);

	line.clear();
	line.push_back(10);
	line.push_back(20);
	line.push_back(30);
	line.push_back(1);
	line.push_back(2);
	triangle.push_back(line);

	Solution_v1 slt_v1;
	int rslt_v1 = slt_v1.minimumTotal(triangle);

	Solution slt;
	int rslt = slt.minimumTotal(triangle);

	return 0;
}