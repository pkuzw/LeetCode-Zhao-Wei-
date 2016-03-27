///@file	Longest Increasing Path in a Matrix
///@author	zhaowei
///@date	2016.03.27
///@version	1.0

#include <vector>

using namespace std;

class Solution {
public:
	///@brief	����һ����ά�����ҵ���ĵ���·��
	///@param	matrix	��ά����
	///@return	���������·���ĳ���
	///@note	1. dfs��
	//			2. ʱ�临�Ӷ�ΪO(n^k)��k > 3��TLE
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

	///@brief	�ݹ鸨������
	///@param	matrix	��ά����
	///@param	visited	���ʹ��ĵ�
	///@param	i, j	��ǰ����±�
	///@param	max_len	�ӵ�ǰ��������·������
	///@param	path_len	��ǰ���һ���Ϸ�·������	
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