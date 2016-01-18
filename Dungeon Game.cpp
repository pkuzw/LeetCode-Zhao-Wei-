///@file	Dugeon Game
/*
The demons had captured the princess (P) and imprisoned her in the bottom-right corner of a dungeon. The dungeon consists of M x N rooms laid out in a 2D grid. Our valiant knight (K) was initially positioned in the top-left room and must fight his way through the dungeon to rescue the princess.

The knight has an initial health point represented by a positive integer. If at any point his health point drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons, so the knight loses health (negative integers) upon entering these rooms; other rooms are either empty (0's) or contain magic orbs that increase the knight's health (positive integers).

In order to reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.


Write a function to determine the knight's minimum initial health so that he is able to rescue the princess.
Notes:

The knight's health has no upper bound.
Any room can contain threats or power-ups, even the first room the knight enters and the bottom-right room where the princess is imprisoned.
*/
///@author	zhaowei
///@date	2015.08.01
///@version	1.0

///@date	2015.08.12
///@version	1.1

///@date	2016.01.18
///@version	1.2

#include <vector>
using namespace std;

class Solution_v1 {
public:
	///@brief	计算到达右下角的最小HP
	///@param	dungeon	二维矩阵地图
	///@return	返回所需的最小HP
	/* @note	动态规划。设dp[i][j]表示到达dungeon[i][j]仍能存活的最小HP。初始条件为dp[row-1][col-1] = max(1, 1-dungeon[row-1][col-1])，
				dp[i][col-1] = max(1, dp[i+1][col-1] - dungeon[i][col-1])；dp[row-1][j] = max(1, dp[row-1][j+1] - dungeon[row-1][j])；
				递推关系式为dp[i][j] = max(min(dp[i][j+1], dp[i+1][j])-dungeon[i][j], 1)。时间复杂度为O(n^2)，空间复杂度为O(n^2)。*/
	int calculateMinimumHP(vector<vector<int>>& dungeon) {
		int row = dungeon.size();
		if (row == 0)	return 0;
		int col = dungeon[0].size();

		vector<vector<int>> dp(row, vector<int>(col, 1));
		dp[row-1][col-1] = max(1, 1-dungeon[row-1][col-1]);
		for (int i = row-2; i >= 0; i--)
			dp[i][col-1] = max(1, dp[i+1][col-1] - dungeon[i][col-1]);
		for (int j = col-2; j >= 0; j--)
			dp[row-1][j] = max(1, dp[row-1][j+1] - dungeon[row-1][j]);

		for (int i = row-2; i >= 0; i--)
		{
			for (int j = col-2; j >= 0; j--)
			{
				dp[i][j] = max(1, min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j]);
			}
		}
		return dp[0][0];
	}
};

class Solution {
public:
	///@brief	计算到达右下角的最小HP
	///@param	dungeon	二维矩阵地图
	///@return	返回所需的最小HP
	///@note	1. 动态规划；2. 设dp[i][j]表示到达点[i][j]时的最小hp；3. 初始化dp[row-1][col-1] = max(1, 1 - dungeon[row-1][col-1]), 
	//			dp[i][col-1] = max(1, dp[i+1][col-1] - dungeon[i][col-1]), dp[row-1][j] = max(1, dp[row-1][j+1] - dungeon[row-1][j])；
	//			4. 递推关系式为dp[i][j] = max(1, min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j]).
	int calculateMinimumHP(vector<vector<int>>& dungeon) {
		int row = dungeon.size(), col = dungeon[0].size();
		vector<vector<int>> dp(row, vector<int>(col, 0));
		dp[row-1][col-1] = max(1, 1 - dungeon[row-1][col-1]);
		for (int i = row - 2; i >= 0; i--)	dp[i][col-1] = max(1, dp[i+1][col-1] - dungeon[i][col-1]);
		for (int j = col - 2; j >= 0; j--)	dp[row-1][j] = max(1, dp[row-1][j+1] - dungeon[row-1][j]);
		for (int i = row - 2; i >= 0; i--)
			for (int j = col - 2; j >= 0; j--)
				dp[i][j] = max(1, min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j]);
		return dp[0][0];
	}
};

int main()
{
	vector<vector<int>> dungeon;
	vector<int> line;
	line.push_back(-2);
	line.push_back(-3);
	line.push_back(3);
	dungeon.push_back(line);
	line.clear();

	line.push_back(-5);
	line.push_back(-10);
	line.push_back(1);
	dungeon.push_back(line);
	line.clear();

	line.push_back(10);
	line.push_back(30);
	line.push_back(-5);
	dungeon.push_back(line);
	line.clear();

	Solution slt;
	Solution_v1 slt_v1;
	int hp = slt.calculateMinimumHP(dungeon);
	hp = slt_v1.calculateMinimumHP(dungeon);
	return 0;
}