///@file	Longest Increasing Path in a Matrix
///@author	zhaowei
///@date	2016.03.27
///@version	1.0

#include <vector>

using namespace std;

class Solution {
public:
	///@brief	给定一个二维矩阵，找到最长的递增路径
	///@param	matrix	二维矩阵
	///@return	返回最长递增路径的长度
	///@note	1. dfs；
	//			2. 时间复杂度为O(n^k)，k > 3。TLE
	int longestIncreasingPath(vector<vector<int>>& matrix) {
		if (matrix.empty() || matrix[0].empty())	return 0;
		int m = matrix.size(), n = matrix[0].size();
		vector<vector<bool>> visited(m, vector<bool>(n, false));
		int rslt = 1;
		for (int i = 0; i != m; i++) {
			for (int j = 0; j != n; j++) {
				int max_len = 1;
				int path_len = 1;
				dfs(matrix, visited, i, j, max_len, path_len);
				rslt = max(rslt, max_len);
			}
		}
		return rslt;
	}

	///@brief	递归辅助函数
	///@param	matrix	二维矩阵
	///@param	visited	访问过的点
	///@param	i, j	当前点的下标
	///@param	max_len	从当前点出发的最长路径长度
	///@param	path_len	当前点的一条合法路径长度	
	void dfs(vector<vector<int>>& matrix, vector<vector<bool>>visited, int i, int j, int& max_len, int& path_len) {
		if (i < 0 || i >= matrix.size() || j < 0 || j >= matrix[0].size() || visited[i][j])	return;		
		if (i > 0 && !visited[i][j] && matrix[i-1][j] > matrix[i][j]) {			
			visited[i][j] = true;
			path_len++;
			max_len = max(max_len, path_len);
			dfs(matrix, visited, i-1, j, max_len, path_len);
			visited[i][j] = false;
			path_len--;
		}
		if (i < matrix.size() - 1 && !visited[i][j] && matrix[i+1][j] > matrix[i][j]) {
			visited[i][j] = true;
			path_len++;
			max_len = max(max_len, path_len);
			dfs(matrix, visited, i+1, j, max_len, path_len);
			visited[i][j] = false;
			path_len--;
		}
		if (j > 0 && !visited[i][j] && matrix[i][j-1] > matrix[i][j]) {
			visited[i][j] = true;
			path_len++;
			max_len = max(max_len, path_len);
			dfs(matrix, visited, i, j-1, max_len, path_len);			
			visited[i][j] = false;
			path_len--;
		}
		if (j < matrix[0].size() - 1 && !visited[i][j] && matrix[i][j+1] > matrix[i][j]) {
			visited[i][j] = true;
			path_len++;
			max_len = max(max_len, path_len);
			dfs(matrix, visited, i, j+1, max_len, path_len);			
			visited[i][j] = false;
			path_len--;
		}		
	}
};

int main() {
	int nums[3][3] = {{3,4,5}, {3,2,6}, {2,2,1}};
	
	vector<vector<int>> matrix;
	for (int i = 0; i != 3; i++) {
		vector<int> row;
		for (int j = 0; j != 3; j++) {
			row.push_back(nums[i][j]);
		}
		matrix.push_back(row);
	}

	Solution slt;
	int rslt = slt.longestIncreasingPath(matrix);
	return 0;
}