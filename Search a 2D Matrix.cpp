///@file	Search a 2D Matrix
/*
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.
For example,

Consider the following matrix:

[
[1,   3,  5,  7],
[10, 11, 16, 20],
[23, 30, 34, 50]
]
Given target = 3, return true.
*/
///@author	zhaowei
///@date	2015.07.13
///@version	1.0

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	///@brief	给定一个m*n的二维矩阵，每一行按照升序排序，且每一列的首元素都大于上一列的尾元素。在其中查找给定值。
	///@param	matrix	二维矩阵
	///@param	target
	///@return	如果二维矩阵中存在target目标元素，则返回true；否则返回false
	///@note	比较直接的方法是直接将改二维矩阵转化成一维数组，然后应用二分查找即可。时间复杂度为O(log(mn))，空间复杂度为O(mn)。
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		if (matrix.empty())
		{
			return false;
		}
		int m = matrix.size();

		if (matrix[0].empty())
		{
			return false;
		}
		int n = matrix[0].size();

		vector<int> tmp;

		for (int i = 0; i != m; i++)
		{
			for (int j = 0; j != n; j++)
			{
				tmp.push_back(matrix[i][j]);
			}
		}

		return binary_search(tmp.begin(), tmp.end(), target);
	}
};

int main()
{
	vector<int> line;
	vector<vector<int>> matrix;

	line.push_back(1);
	line.push_back(3);
	line.push_back(5);
	line.push_back(7);
	matrix.push_back(line);

	line.clear();
	line.push_back(10);
	line.push_back(11);
	line.push_back(16);
	line.push_back(20);
	matrix.push_back(line);

	line.clear();
	line.push_back(23);
	line.push_back(30);
	line.push_back(34);
	line.push_back(50);
	matrix.push_back(line);

	Solution slt;
	cout << slt.searchMatrix(matrix, 4) << endl;
	return 0;
}