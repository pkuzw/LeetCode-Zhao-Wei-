///@file	Maximal Square
/*
Given a 2D binary matrix filled with 0's and 1's, find the largest square containing all 1's and return its area.

For example, given the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

Return 4. 
*/
///@author	zhaowei
///@date	2015.07.30
///@version	1.0
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	///@brief	计算二维0-1矩阵中最大的'1'正方形
	///@param	matrix	矩阵
	///@return	返回最大1正方形的面积
	/* @note	动态规划：设dp[i][j]表示以matrix[i][j]为右下角的1正方形的最大边长。初始条件dp[0][0] = matrix[0][0]，
				dp[i][0] = (matrix[i][0] == 1) ? 1 : 0；
				dp[0][j] = (matrix[0][j] == 1) ? 1 : 0；
				递推关系式为dp[i][j] == (matrix[i][j] == 0) ? 0 : min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])+1.
				时间复杂度为O(n^2)，空间复杂度为O(n^2)，不过网上有算法可以优化到O(n)。*/
	int maximalSquare(vector<vector<char>>& matrix) {
		int row = matrix.size();
		if (!row)	return 0;
		int col = matrix[0].size();

		int max_len = 0;
		vector<vector<int>> dp(row, vector<int>(col, 0));
		dp[0][0] = int(matrix[0][0] - '0');
		max_len = max(dp[0][0], max_len);
		for (int i = 1; i != row; i++)		
		{
			dp[i][0] = (matrix[i][0] == '1') ? 1 : 0;
			max_len = max(dp[i][0], max_len);
		}
		
		for (int j = 1; j != col; j++)
		{
			dp[0][j] = (matrix[0][j] == '1') ? 1 : 0;
			max_len = max(dp[0][j], max_len);
		}


		
		for (int i = 1; i != row; i++)
		{
			for (int j = 1; j != col; j++)
			{
				if (matrix[i][j] == '1')
				{
					dp[i][j] = min(dp[i-1][j], min(dp[i][j-1], dp[i-1][j-1]))+1;
					max_len = max(dp[i][j], max_len);
				}
			}
		}
		return max_len*max_len;
	}
};

int main()
{
	vector<vector<char>> matrix;
	vector<char> line;
	line.push_back('1');
	line.push_back('1');
	line.push_back('1');
	line.push_back('1');
	line.push_back('1');
	matrix.push_back(line);

	line.clear();
	line.push_back('1');
	line.push_back('1');
	line.push_back('1');
	line.push_back('1');
	line.push_back('1');
	matrix.push_back(line);

	line.clear();
	line.push_back('1');
	line.push_back('1');
	line.push_back('1');
	line.push_back('1');
	line.push_back('1');
	matrix.push_back(line);

	line.clear();
	line.push_back('1');
	line.push_back('0');
	line.push_back('0');
	line.push_back('1');
	line.push_back('0');
	matrix.push_back(line);

	Solution slt;
	int rslt = slt.maximalSquare(matrix);
	return 0;
}