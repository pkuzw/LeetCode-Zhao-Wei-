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
///@date	2015.07.09
///@version	1.1

///@date	2015.08.28
///@version	2.0

///@date	2015.12.01
///@version 2.1

///@date	2016.04.18
///@version	2.2

#include <iostream>
#include <vector>
using namespace std;

class Solution_v1 {
public:
	///@brief	计算有障碍物的路径总数
	///@param	obstacleGrid	用二维数组表示障碍物分布，其中1为障碍物，0为通路
	///@return	返回路径总数
	///@note	动态规划算法：设到点(i, j)共有dp[i][j]种不同的路径，则dp[i][j] = dp[i][j-1] + dp[i-1][j]。在遇到障碍物grid[i][j] == 1
	//			时，将dp[i][j] = 0。在初始化时生成一个所有元素为0的m+1*n+1的二维矩阵。对于左上角第一个元素要单独初始化，在双重循环中跳过
	//			左上角的dp[1][1]，否则其会由于多出来的一列和一行，被再次置为0.时间复杂度为O(m*n)，空间复杂度为O(m*n)。
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) 
	{
		if (obstacleGrid.empty())	return 0;	//	除去无效棋盘
		int m = obstacleGrid.size();

		if (obstacleGrid[0].empty())	return 0;
		int n = obstacleGrid[0].size();
		
		vector<vector<int>> dp(m+1, vector<int>(n+1, 0));	//	初始化dp二维数组
		dp[1][1] = obstacleGrid[0][0] == 1 ? 0 : 1;			//	对于左上角的第一个dp值要根据棋盘上在该处是否有障碍物来单独初始化

		for (int i = 1; i != m+1; i++)
		{
			for (int j = 1; j != n+1; j++)
			{				
				if (i == 1 && j == 1)	continue;	//	跳过处理dp[1][1]
				
				if (obstacleGrid[i-1][j-1] == 1)
					dp[i][j] = 0;
				else
					dp[i][j] = dp[i][j-1] + dp[i-1][j];				
			}
		}
		return dp[m][n];
	}

	///@brief	计算有障碍物的路径总数
	///@param	obstacleGrid	用二维数组表示障碍物分布，其中1为障碍物，0为通路
	///@return	返回路径总数
	///@note	动态规划算法：设到点(i, j)共有dp[i][j]种不同的路径，则dp[i][j] = dp[i][j-1] + dp[i-1][j]。在遇到障碍物grid[i][j] == 1
	//			时，将dp[i][j] = 0。在初始化时生成一个所有元素为0的n+1的一维矩阵。对于左上角第一个元素要单独初始化，在双重循环中跳过
	//			左上角的dp[1]，否则其会由于多出来的一列，被再次置为0。通过观察可以发现，dp[i][j]只与它上面和左面的元素值有关，因
	//			此可以将空间复杂度降为O(n)。只记录与当前行的每一列dp[j]。这样因为外面包了一层dp[0]，每次求dp[j]时，dp[j]+dp[j-1]分别代表
	//			了dp(i-1, j)和dp(i, j-1)。时间复杂度为O(m*n)，空间复杂度为O(n)。
	int uniquePathsWithObstacles_saveSpace(vector<vector<int>>& obstacleGrid) 
	{
		if (obstacleGrid.empty())	return 0;	//	除去无效棋盘
		int m = obstacleGrid.size();

		if (obstacleGrid[0].empty())	return 0;
		int n = obstacleGrid[0].size();

			
		vector<int> dp(n+1,0);	//	初始化dp一维数组
		dp[1] = obstacleGrid[0][0] == 1 ? 0 : 1;			//	对于左上角的第一个dp值要根据棋盘上在该处是否有障碍物来单独初始化


		for (int i = 1; i != m+1; i++)
		{
			for (int j = 1; j != n+1; j++)
			{				
				if (i == 1 && j == 1)	continue;	//	跳过处理dp[1][1]

				if (obstacleGrid[i-1][j-1] == 1)		//	对于是障碍物的点，直接置为0
				{
					dp[j] = 0;
				}
				
				else
				{
					//根据dp[j]与dp[j-1]来获取dp[k]的值
					dp[j] += dp[j-1];					
				}
			}
		}		
		return dp[n];		
	}
};

class Solution_v2 {
public:
	///@brief	计算带有障碍物的棋盘从左上角出发到达右下角的方法数
	///@param	obstableGrid	棋盘
	///@return	返回方法数
	///@note	1. 动态规划算法：设dp[i][j]表示从左上角出发，到达第i行，第j列的方法数。递推关系式dp[i][j] = grid[i][j] == 1 ? 0 : dp[i-1][j] + dp[i][j-1]；
	//			2. 初始化时，左上角根据grid[0][0]是否为1，来设置；第0行和第0列也是从左至右，从上到下来设置，如果中间某一个点为障碍物，则其后的所有格子达到的方法数均为0；
	//			3. 时间复杂度为O(mn)，空间复杂度为O(mn)，其中m和n分别为行数和列数。
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
		if (obstacleGrid.empty() || obstacleGrid[0].empty())	return 0;
		int row = obstacleGrid.size();
		int col = obstacleGrid[0].size();
		vector<vector<int>> dp(row, vector<int>(col, 0));
		dp[0][0] = obstacleGrid[0][0] ? 0 : 1;
		if (!dp[0][0])	return 0;

		for (int i = 1; i != row; i++)	dp[i][0] = obstacleGrid[i][0] ? 0 : dp[i-1][0];
		for (int j = 1; j != col; j++)	dp[0][j] = obstacleGrid[0][j] ? 0 : dp[0][j-1];
		for (int i = 1; i != row; i++)
			for (int j = 1; j != col; j++)
				dp[i][j] = obstacleGrid[i][j] ? 0 : dp[i-1][j] + dp[i][j-1];
		return dp[row-1][col-1];
	}
};

class Solution {
public:
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
		if (obstacleGrid.empty() || obstacleGrid[0].empty())	return 0;
		int row = obstacleGrid.size(), col = obstacleGrid[0].size();
		vector<vector<int>> dp(row, vector<int>(col, 0));
		dp[0][0] = obstacleGrid[0][0] ? 0 : 1;
		for (int i = 1; i != col; i++)	dp[0][i] = obstacleGrid[0][i] ? 0 : dp[0][i-1];
		for (int i = 1; i != row; i++)	dp[i][0] = obstacleGrid[i][0] ? 0 : dp[i-1][0];
		for (int i = 1; i != row; i++)
			for (int j = 1; j != col; j++)
				dp[i][j] = obstacleGrid[i][j] ? 0 : dp[i-1][j] + dp[i][j-1];
		return dp[row-1][col-1];
	}
};


int main()
{
	vector<vector<int>> obs;
	vector<int> line;
	line.push_back(0);
	line.push_back(0);
	line.push_back(0);	
	line.push_back(0);
	line.push_back(0);
	obs.push_back(line);

	line.clear();
	line.push_back(0);
	line.push_back(1);
	line.push_back(0);	
	line.push_back(0);
	line.push_back(0);	
	obs.push_back(line);

	line.clear();
	line.push_back(0);
	line.push_back(0);
	line.push_back(0);
	line.push_back(1);
	line.push_back(0);	
	obs.push_back(line);


	line.clear();
	line.push_back(0);	
	line.push_back(0);
	line.push_back(0);
	line.push_back(0);
	line.push_back(0);	
	obs.push_back(line);

	Solution_v1 slt_v1;
	int rslt_v1 = slt_v1.uniquePathsWithObstacles_saveSpace(obs);
	Solution slt;
	int rslt = slt.uniquePathsWithObstacles(obs);
	return 0;
}