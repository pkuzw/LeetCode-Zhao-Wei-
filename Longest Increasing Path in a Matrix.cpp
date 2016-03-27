///@file	Longest Increasing Path in a Matrix
///@author	zhaowei
///@date	2016.03.27
///@version	1.0
///@version	2.0

#include <vector>

using namespace std;

class Solution_v1 {
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

class Solution {
public:
	///@note	1. 利用哈希表存储已经搜索过的合法路径的长度值；这样相当于有所剪枝；
	//			2. 哈希表在作为形参时一定要声明为引用，否则超时；
	//			3. 时间复杂度为O(n^3)。
	int longestIncreasingPath(vector<vector<int>>& matrix) {
		if (matrix.empty() || matrix[0].empty())	return 0;
		int m = matrix.size(), n = matrix[0].size();
		vector<vector<int>> hash_tbl(m, vector<int>(n, 0));
		int rslt = 0;
		for (int i = 0; i != m; i++)
			for (int j = 0; j != n; j++)
				rslt = max(rslt, dfs(matrix, hash_tbl, i, j, INT_MIN));
		return rslt;
	}

	///@brief	递归辅助函数
	///@param	matrix	二维矩阵
	///@param	hash_tbl	保存从点<i, j>出发的所有合法路径的最大长度
	///@param	i, j	当前点的坐标
	///@param	val		前一个点的值
	///@return	返回从<i, j>出发的合法路径的最大长度
	int dfs(vector<vector<int>>& matrix, vector<vector<int>>& hash_tbl, int i, int j, int val) {
		if (i < 0 || i >= matrix.size() || j < 0 || j >= matrix[0].size())	return 0;
		if (matrix[i][j] > val) {	//	从<i, j>出发如果存在路径
			if (hash_tbl[i][j])	return hash_tbl[i][j];
			int a = dfs(matrix, hash_tbl, i + 1, j, matrix[i][j]) + 1;
			int b = dfs(matrix, hash_tbl, i - 1, j, matrix[i][j]) + 1;
			int c = dfs(matrix, hash_tbl, i, j + 1, matrix[i][j]) + 1;
			int d = dfs(matrix, hash_tbl, i, j - 1, matrix[i][j]) + 1;
			hash_tbl[i][j] = max(max(max(a, b), c), d);
			return hash_tbl[i][j];
		}
		return 0;
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