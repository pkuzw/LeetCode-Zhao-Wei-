﻿///@file	Range Sum Query 2D - Mutable
///@author	zhaowei
///@date	2016.03.18
///@version	1.0

#include <vector>
using namespace std;

///@note	1. Binary Indexed Tree
//			2. https://www.topcoder.com/community/data-science/data-science-tutorials/binary-indexed-trees/#2d
class NumMatrix {
public:
	NumMatrix(vector<vector<int>> &matrix) {
		_row = matrix.size();
		if (0 == _row) return;
		_col = matrix[0].size();
		num = vector<vector<int>>(matrix);
		tree = vector<vector<int>>(_row + 1, vector<int>(_col + 1, 0));
		for (int i = 0; i < _row; i++) 
			for (int j = 0; j < _col; j++) {
				updateTree(i, j, num[i][j]);
			}
	}

	void update(int row, int col, int val) {
		updateTree(row, col, val - num[row][col]);
		num[row][col] = val;
	}

	int sumRegion(int row1, int col1, int row2, int col2) {
		return read(row2+1, col2+1) - read(row1, col2+1) - read(row2+1, col1) + read(row1, col1);
	}

	void updateTree(int row, int col, int val) {
		for (int i = row + 1; i <= _row; i += i & (-i)) 
			for (int j = col + 1; j <= _col; j += j & (-j)) {
				tree[i][j] += val;
			}
	}

	int read(int row, int col) {
		int sum = 0;
		for (int i = row; i > 0; i -= i & (-i))
			for (int j = col; j > 0; j -= j & (-j)) {
				sum += tree[i][j];
			}
			return sum;
	}

	vector<vector<int>> tree;
	vector<vector<int>> num;
	int _row;
	int _col;
};

int main() {
	return 0;
}