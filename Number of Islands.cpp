﻿///@file	Number of Islands
/*
Given a 2d grid map of '1's (land) and '0's (water), count the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. 

You may assume all four edges of the grid are all surrounded by water.

Example 1:

11110
11010
11000
00000

Answer: 1

Example 2:

11000
11000
00100
00011

Answer: 3
*/
///@author	zhaowei
///@date	2015.08.04
///@version	1.0

///@date	2015.08.11
///@version	1.1

///@date    2016.01.21
///@version 1.2

#include <vector>
using namespace std;

class Solution_v1 {
public:
	///@brief	计算岛屿个数
	///@param	grid	地图：1为陆地，0为海洋
	///@return	返回岛屿的数目
	/* @note	DFS，配合一个二维的标志矩阵。时间复杂度为O(mn)，空间复杂度为O(mn)。*/
	int numIslands(vector<vector<char>>& grid) {
		if (grid.empty() || grid[0].empty())	return 0;
		int row  = grid.size();
		int col = grid[0].size();
		int rslt = 0;
		vector<vector<bool>> visited(row, vector<bool>(col, false));

		for (int i = 0; i != row; i++)
		{
			for (int j = 0; j != col; j++)
			{
				if (grid[i][j] == '1' && !visited[i][j])
				{
					dfs(grid, i, j, visited);
					rslt++;
				}
			}
		}
		return rslt;
	}
private:
	///@brief	DFS查找陆地
	///@param	grid	地图
	///@param	i, j	某个点
	///@param	visited	标志矩阵
	///@return	无
	void dfs(vector<vector<char>>& grid, int i, int j, vector<vector<bool>>& visited)
	{
		if (i < 0 || i >= grid.size())		return;
		if (j < 0 || j >= grid[0].size())	return;
		if (grid[i][j] == '0' || visited[i][j]) return;

		visited[i][j] = true;
		dfs(grid, i+1, j, visited);
		dfs(grid, i, j+1, visited);
		dfs(grid, i-1, j, visited);
		dfs(grid, i, j-1, visited);
	}
};

class Solution {
public:
    ///@brief   计算棋盘中被0包围的1的块数
    ///@param   grid    棋盘
    ///@return  返回1的块数
    ///@note    1. 深度优先遍历；2. 通过一个辅助的标记二维数组来标记那些元素已被访问过。
	int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty())    return 0;
        row = grid.size();
        col = grid[0].size();
        
        vector<vector<bool>> visit(row, vector<bool>(col, false));
        int rslt = 0;
        for (int i = 0; i != row; i++) {
            for (int j = 0; j != col; j++) {
                if (grid[i][j] == '1' && !visit[i][j]) {
                    dfs(grid, i, j, visit);
                    rslt++;
                }
            }
        }
        return rslt;
	}

private:
    ///@bfief   辅助dfs函数
    ///@param   i, j    当前元素的下标
    ///@param   visited 辅助标志数组
	void dfs(vector<vector<char>>& grid, int i, int j, vector<vector<bool>>& visited) {
        if (i < 0 || i >= row || j < 0 || j >= col || grid[i][j] == '0' || visited[i][j]) return;
        visited[i][j] = true;
        dfs(grid, i + 1, j, visited);
        dfs(grid, i - 1, j, visited);
        dfs(grid, i, j + 1, visited);
        dfs(grid, i, j - 1, visited);
	}

	int row, col;
};

int main()
{
	vector<vector<char>> grid;
	vector<char> line;
	line.push_back('1');
	line.push_back('1');
	line.push_back('0');
	line.push_back('1');
	line.push_back('0');
	grid.push_back(line);
	line.clear();

	line.push_back('0');
	line.push_back('0');
	line.push_back('0');
	line.push_back('1');
	line.push_back('0');
	grid.push_back(line);
	line.clear();

	line.push_back('1');
	line.push_back('1');
	line.push_back('0');
	line.push_back('0');
	line.push_back('0');
	grid.push_back(line);
	line.clear();

	line.push_back('0');
	line.push_back('1');
	line.push_back('1');
	line.push_back('0');
	line.push_back('0');
	grid.push_back(line);
	line.clear();

	Solution slt;
	int rslt = slt.numIslands(grid);

	Solution_v1 slt_v1;
	rslt = slt_v1.numIslands(grid);
	return 0;
}
/*
Example 1:

11110
11010
11000
00000

Answer: 1

Example 2:

11000
11000
00100
00011

Answer: 3*/