///@file	Range Sum Query 2D - Immutable
///@author	zhaowei
///@date	2016.03.16
///@version	1.0

#include <vector>
#include <numeric>

using namespace std;

///@note	1. 类似于Range Sum Query - Immutable I的解法，利用<numberic>头文件中的partial_sum接口来解，对于矩阵中的每一行都保存一个单行
//			   各元素和的数组，然后逐行再相加即可。
class NumMatrix {
public:
	NumMatrix(vector<vector<int>> &matrix) {
		int row = matrix.size(), col = !matrix.empty() ? matrix[0].size() : 0;
		for (int i = 0; i != row; i++) {
			vector<long long> psum(col + 1, 0);
			partial_sum(matrix[i].begin(), matrix[i].end(), psum.begin() + 1);
			psum_matrix.push_back(psum);
		}
	}

	int sumRegion(int row1, int col1, int row2, int col2) {
		long long rslt = 0;
		for (int i = row1; i <= row2; i++)	rslt += psum_matrix[i][col2+1] - psum_matrix[i][col1];
		return (int)rslt;
	}

	vector<vector<long long>> psum_matrix;
};


// Your NumMatrix object will be instantiated and called as such:
// NumMatrix numMatrix(matrix);
// numMatrix.sumRegion(0, 1, 2, 3);
// numMatrix.sumRegion(1, 2, 3, 4);

int main() {
	vector<vector<int>> matrix;
	vector<int> line;
	line.push_back(3);
	line.push_back(0);
	line.push_back(1);
	line.push_back(4);
	line.push_back(2);
	matrix.push_back(line);
	line.clear();

	line.push_back(5);
	line.push_back(6);
	line.push_back(3);
	line.push_back(2);
	line.push_back(1);
	matrix.push_back(line);
	line.clear();

	line.push_back(1);
	line.push_back(2);
	line.push_back(0);
	line.push_back(1);
	line.push_back(5);
	matrix.push_back(line);
	line.clear();

	line.push_back(4);
	line.push_back(1);
	line.push_back(0);
	line.push_back(1);
	line.push_back(7);
	matrix.push_back(line);
	line.clear();

	line.push_back(1);
	line.push_back(0);
	line.push_back(3);
	line.push_back(0);
	line.push_back(5);
	matrix.push_back(line);
	line.clear();

	NumMatrix numMatrix(matrix);
	int r = numMatrix.sumRegion(0, 0, 4, 4);
	r = numMatrix.sumRegion(0, 0, 3, 3);
	r = numMatrix.sumRegion(3, 3, 4, 4);
	return 0;
}