///@file	Set Matrix Zeroes
/*
Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.
*/
///@author	zhaowei
///@date	2015.07.13
///@version	1.0

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	///@brief	给定一个m*n的二维矩阵，将'0'所在行和列置为0
	///@param	matrix	二维矩阵
	///@return	无
	///@note	新建两个1维数组，分别记录0元素的行号和列号位置。这两个1维数组初始均为false，当其某一行或者某一列有0元素时就置为true。
	//			最后根据这两个一维bool数组的标记来更新二维矩阵。时间复杂度为O(m*n)，空间复杂度为O(m+n)
	void setZeroes(vector<vector<int>>& matrix) {
		if (matrix.empty())
		{
			return;
		}
		int m = matrix.size();	//	矩阵行数

		if (matrix[0].empty())
		{
			return;
		}
		int n = matrix[0].size();	//	矩阵列数

		//	初始化
		vector<bool> line_flg;
		bool flg = false;
		for (int i = 0; i != m; i++)
		{
			line_flg.push_back(flg);
		}

		vector<bool> col_flg;
		for (int i = 0; i != n; i++)
		{
			col_flg.push_back(flg);
		}

		for (int i = 0; i != m; i++)
		{
			for (int j = 0; j != n; j++)
			{
				if (matrix[i][j] == 0)
				{
					line_flg[i] = true;
					col_flg[j] = true;
				}
			}
		}

		for (int i = 0; i != line_flg.size(); i++)
		{
			if (line_flg[i])
			{
				for (int j = 0; j != n; j++)
				{
					matrix[i][j] = 0;
				}
			}
		}

		for (int i = 0; i != col_flg.size(); i++)
		{
			if (col_flg[i])
			{
				for (int j = 0; j != m; j++)
				{
					matrix[j][i] = 0;
				}
			}
		}
		return;
	}
};

int main()
{
	vector<int> line;
	line.push_back(1);
	line.push_back(1);
	line.push_back(0);
	line.push_back(1);

	vector<vector<int>> matrix;
	matrix.push_back(line);

	line.clear();
	line.push_back(1);
	line.push_back(0);
	line.push_back(1);
	line.push_back(1);
	matrix.push_back(line);

	line.clear();
	line.push_back(1);
	line.push_back(1);
	line.push_back(1);
	line.push_back(1);
	matrix.push_back(line);

	line.clear();
	line.push_back(1);
	line.push_back(1);
	line.push_back(1);
	line.push_back(1);
	matrix.push_back(line);
	
	matrix.clear();
	line.clear();
	line.push_back(0);
	line.push_back(0);
	line.push_back(1);
	matrix.push_back(line);


	line.clear();
	line.push_back(1);
	line.push_back(1);
	line.push_back(1);
	matrix.push_back(line);

	for (int i = 0; i != matrix.size(); i++)
	{
		for (int j = 0; j != matrix[0].size(); j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	Solution slt;
	slt.setZeroes(matrix);

	for (int i = 0; i != matrix.size(); i++)
	{
		for (int j = 0; j != matrix[0].size(); j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}
