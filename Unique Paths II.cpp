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

#include <iostream>
#include <vector>
using namespace std;

class Solution {
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
	line.push_back(0);
	line.push_back(0);	
	line.push_back(0);
	line.push_back(0);	
	obs.push_back(line);

	line.clear();
	line.push_back(0);
	line.push_back(0);
	line.push_back(0);
	line.push_back(0);
	line.push_back(0);	
	obs.push_back(line);


	line.clear();
	line.push_back(0);	
	line.push_back(0);
	line.push_back(0);
	line.push_back(0);
	line.push_back(0);	
	obs.push_back(line);

	Solution slt;
	cout << slt.uniquePathsWithObstacles_saveSpace(obs);
	cout << endl;
	return 0;
}