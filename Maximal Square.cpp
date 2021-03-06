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

///@date	2015.08.10
///@version	1.1

///@date	2016.01.28
///@version	1.2

#include <iostream>
#include <vector>

using namespace std;

class Solution_v1 {
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

class Solution_v2 {
public:
	int maximalSquare(vector<vector<char>>& matrix) {
		if (matrix.empty())	return 0;
		int row = matrix.size();
		int col = matrix[0].size();
		int rslt = INT_MIN;	// 最大正方形边长

		vector<vector<int>> dp(row, vector<int>(col, 0));

		dp[0][0] = (matrix[0][0] == '1') ? 1 : 0;
		rslt = max(rslt, dp[0][0]);

		for (int i = 0; i != col; i++)
		{
			dp[0][i] = (matrix[0][i] == '1') ? 1 : 0;
			rslt = max(rslt, dp[0][i]);
		}

		for (int i = 0; i != row; i++)
		{
			dp[i][0] = (matrix[i][0] == '1') ? 1 : 0;
			rslt = max(rslt, dp[i][0]);
		}

		for (int i = 1; i != row; i++)
		{
			for (int j = 1; j != col; j++)
			{
				dp[i][j] = (matrix[i][j] == '1') ? min(min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]) + 1 : 0;
				rslt = max(rslt, dp[i][j]);
			}
		}

		return rslt * rslt;
	}
};

class Solution_v2_1 {
public:
	///@brief	空间复杂度缩小到O(n)，只用两个一维数组维护即可。一个用来保存前一列，一个用来保存当前列的包含该点的最大正方形边长。
	int maximalSquare(vector<vector<char>>& matrix) {
		if (matrix.empty())	return 0;
		int row = matrix.size();
		int col = matrix[0].size();

		vector<int> pre(row, 0);	//	上一列
		vector<int> cur(row, 0);	//	当前列

		int rslt = INT_MIN;

		for (int i = 0; i != row; i++)
		{
			pre[i] = matrix[i][0] == '1' ? 1 : 0;
			rslt = max(rslt, pre[i]);
		}

		for (int j = 1; j != col; j++)
		{
			cur[0] = matrix[0][j] == '1' ? 1 : 0;
			rslt  = max(rslt, cur[0]);
			for (int i = 1; i != row; i++)
			{
				cur[i] = matrix[i][j] == '1' ? min(cur[i-1], min(pre[i], pre[i-1])) + 1 : 0;
				rslt = max(rslt, cur[i]);
			}
			pre = cur;
			fill(cur.begin(), cur.end(), 0);
		}
		return rslt * rslt;
	}
};

class Solution {
public:
	///@note	1. 动态规划；
	//			2. 设dp[i][j]为以matrix[i][j]为右下角的正方形边长，递推关系式为dp[i][j] = matrix[i][j] == 1 ? min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1 : 0
	//			3. 时间复杂度为O(n^2)，空间复杂度为O(n^2)。
	int maximalSquare(vector<vector<char>>& matrix) {
		int row = matrix.size();
		if (!row)	return 0;
		int col = matrix[0].size();
		if (!col)	return 0;
		vector<vector<int>> dp(row, vector<int>(col, 0));	//	以matrix[i][j]为右下角的正方形的边长
		dp[0][0] = matrix[0][0] - '0';
		for (int i = 1; i != row; i++)	dp[i][0] = matrix[i][0] == '0' ? 0 : 1;
		for (int j = 1; j != col; j++)	dp[0][j] = matrix[0][j] == '0' ? 0 : 1;
		int rslt = INT_MIN;
		for (int i = 1; i != row; i++)
			for (int j = 1; j != col; j++)
				if (matrix[i][j] == '1')
					dp[i][j] = min(min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]) + 1;
		for (int i = 0; i != row; i++)
			for (int j = 0; j != col; j++)
				rslt = max(rslt, dp[i][j]);
		return rslt * rslt;
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

	Solution_v1 slt_v1;
	int rslt1 = slt_v1.maximalSquare(matrix);

	Solution_v2 slt_v2;
	int rslt2 = slt_v2.maximalSquare(matrix);
	
	Solution_v2_1 slt_v2_1;
	int rslt21 = slt_v2_1.maximalSquare(matrix);

	Solution slt;
	int rslt = slt.maximalSquare(matrix);
	return 0;
}