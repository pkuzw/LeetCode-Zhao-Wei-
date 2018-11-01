///@file	Minimum Path Sum
/*
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes 
the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.
*/
///@author	zhaowei
///@date	2015.07.09
///@version 1.1

///@date	2015.08.27
///@version	2.0

///@date	2015.12.01
///@version 2.1

///@date	2015.12.01
///@version 2.2

///@date	2016.04.18
///@version	2.3

///@date    November 1, 2018
///@version 3.0

#include <vector>
#include <iostream>

using namespace std;

class Solution_v1 {
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

	///@brief	给定一个二维矩阵，计算从左上角到右下角和最小的路径
	///@param	grid	二维矩阵
	///@return	返回和最小的路径所经过各点值的和
	///@note	动态规划算法：设到达点(i, j)的和最小的路径为dp[i][j]，点(i, j)的数值为grid[i][j]，
	//			则dp[i][j] = grid[i][j] + min{dp[i-1][j], dp[i][j-1]}。
	//			时间复杂度为O(m*n)，空间复杂度为O(n)。
	int minPathSum_saveSpace(vector<vector<int>>& grid) 
	{
		if (grid.empty())	return 0;
		int m = grid.size();	//	计算棋盘的行数

		if (grid[0].empty())	return 0;
		int n = grid[0].size();	//	计算棋盘的列数


		//	将dp初始化为INT_MAX的n+1长度的一维数组。之所以是INT_MAX，是为了后续计算时得到前一个点的最小和路径。
		vector<int> dp(n+1, INT_MAX);	//	多出来一列，方便第一个点的初始化	
		dp[0] = INT_MAX;	//	将dp[0][1]或dp[1][0]任意一个置为0，以便初始化第一个点dp[1][1]。
		dp[1] = grid[0][0];
		for (int i = 1; i < m+1; i++)
		{
			for (int j = 1; j < n+1; j++)
			{
				if (i*j == 1) continue;
				dp[j] = grid[i-1][j-1] + min(dp[j], dp[j-1]);
			}
		}
		return dp[n];
	}
};

class Solution_v2 {
public:
	///@brief	给定一个m*n的棋盘，计算从左上角到右下角的和最小的路径
	///@param	grid	棋盘
	///@return	返回最小路径和
	///@note	1. 动态规划算法：设dp[i][j]表示到达点grid[i][j]的最小路径和，则递推关系式为dp[i][j] = grid[i][j] + min{dp[i-1][j], dp[i][j-1]}；
	//			2. 先初始化左上角dp[0][0] = grid[0][0]；再初始化第0行和第0列，dp[i][0] = grid[i][0] + dp[i-1][0], i > 0；dp[0][j] = grid[0][j] + dp[0][j-1], j > 0；
	//			3. 时间复杂度为O(mn)，空间复杂度为O(mn)，其中m和n分别是棋盘的行数和列数。
	int minPathSum(vector<vector<int>>& grid) {
		if (grid.empty() || grid[0].empty())	return 0;
		int row = grid.size();
		int col = grid[0].size();
		vector<vector<int>> dp(row, vector<int>(col, 0));
		dp[0][0] = grid[0][0];
		for (int i = 1; i != row; i++)	dp[i][0] = grid[i][0] + dp[i-1][0];
		for (int j = 1; j != col; j++)	dp[0][j] = grid[0][j] + dp[0][j-1];
		for (int i = 1; i != row; i++)
			for (int j = 1; j != col; j++)
				dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1]);
		return dp[row-1][col-1];
	}

	///@brief	给定一个m*n的棋盘，计算从左上角到右下角的和最小的路径
	///@param	grid	棋盘
	///@return	返回最小路径和
	///@note	1. 动态规划算法：设dp[j]表示当前行第j列的最小路径和，则dp[j] = grid[i][j] + min{dp[j-1], dp[j]}；
	//			2. 初始化时，dp[0]并没有实际意义，初始化为INT_MAX，dp[1]才表示为第0列的最小路径和。之所以将dp整个初始化为INT_MAX，是因为递推关系式在计算第0行的各列最小路径和时，
	//			便于直接将grid[i][j]算作dp[j-1]；另外也需要在进入循环前将dp[1]初始化为grid[0][0]，否则无法在循环内通过递推关系式计算出dp[1]；
	//			3. 时间复杂度为O(mn)，空间复杂度为O(n)，其中m和n分别是棋盘的行数和列数。
	int minPathSum_space_O_1(vector<vector<int>>& grid) {
		if (grid.empty() || grid[0].empty())	return 0;
		int row = grid.size();
		int col = grid[0].size();
		vector<int> dp(col + 1, INT_MAX);
		dp[1] = grid[0][0];
		for (int i = 1; i != row + 1; i++) {
			for (int j = 1; j != col + 1; j++) {
				if (i == 1 && j == 1)	continue;
				dp[j] = grid[i-1][j-1] + min(dp[j-1], dp[j]);
			}
		}
		return dp[col];
	}
};

class Solution {
public:
    ///@brief   在一个二维棋盘上，每个格子标注了权值grid[i][j]，计算从左上角出发，每一步只能向下或者向右移动，达到右下角的最小代价是多少。
    ///@param   grid    棋盘
    ///@return  返回有效路径的最小代价。
    ///@note    1. 动态规划；
    ///         2. 根据《算法导论》关于动态规划算法的应用场景和步骤描述，动态规划主要用来解决最优解问题。
    //          3. 首先，我们应该刻画问题的最优子结构的特征，设dp[i][j]用来保存到达grid[i][j]时的最小权值路径，则dp[row-1][col-1]就是问题的解。其依赖于左边的格子和上边的格子的值；
    //          4. 其次，递归地表达最优子结构，那么dp[i][j] = min{dp[i-1][j], dp[i][j-1]} + grid[i][j]；
    //          5. 再次，自底向上进行求解即可；
    //          6. 最后，如果有必要，再通过上述计算过程得到的值计算一条最小权值路径。不过此题不需要。
    //          7. 时间复杂度为O(mn)，空间复杂度为O(mn)，其中m和n分别是棋盘的行列数。
	int minPathSum(vector<vector<int>>& grid) {
        if (grid.empty())   return 0;
        int row = grid.size(), col = grid[0].size();
        vector<vector<int>> dp(row, vector<int>(col, 0));
        dp[0][0] = grid[0][0];
        for (int i = 1; i < col; i++)   dp[0][i] = dp[0][i-1] + grid[0][i];
        for (int i = 1; i < row; i++)   dp[i][0] = dp[i-1][0] + grid[i][0];
        for (int i = 1; i < row; i++) {
            for (int j = 1; j < col; j++) {
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
            }
        }
        return dp[row-1][col-1];
    }
};

int main()
{
	vector<vector<int>> grid;
	Solution_v1 slt_v1;
	
	vector<int> line;
	line.push_back(1);
 	line.push_back(1);
 	line.push_back(1);

	grid.push_back(line);

	line.clear();
	line.push_back(1);
	line.push_back(5);
	line.push_back(10);
	grid.push_back(line);

	line.clear();
	line.push_back(4);
	line.push_back(2);
	line.push_back(1);
	grid.push_back(line);

	
//	int minPath = slt_v1.minPathSum_saveSpace(grid);
//	Solution_v2 slt2;
//	int rslt = slt2.minPathSum(grid);
//	int r_save = slt2.minPathSum_space_O_1(grid);
	Solution slt;
	int r = slt.minPathSum(grid);
	return 0;
}
