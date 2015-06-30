///@file	Rotate Image
/*
			You are given an n x n 2D matrix representing an image.

			Rotate the image by 90 degrees (clockwise).

			Follow up:
			Could you do this in-place?
*/
///@author	zhaowei
///@date	2015.06.30
///@version	1.0

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	///@brief	将一个n*n的二维矩阵顺时针旋转90°
	///@param	matrix	二维矩阵
	///@return	无
	///@note	比较简单的想法是直接利用一个原矩阵同样的临时矩阵，将其复制过去就可以。时间复杂度为O(n^2)，空间复杂度为O(n^2)
	void rotate(vector<vector<int>>& matrix)
	{
		vector<vector<int>> tmp(matrix);

		int len = matrix.size();
		for (int i = 0; i != len; i++)
		{
			for (int j = 0; j != len; j++)
			{
				matrix[i][j] = tmp[len-1-j][i];
			}
		}
		return;
	}

	///@brief	将一个n*n的二维矩阵顺时针旋转90°
	///@brief	将一个n*n的二维矩阵顺时针旋转90°
	///@param	matrix	二维矩阵
	///@return	无
	///@note	可以利用递归的方式在O(1)的空间复杂度下进行旋转。将矩阵看作是从外到内边长依次递减的方框，每个位置在旋转后移动的新位置
	//			会组成一个闭环。每次旋转方框上的一个元素，就会引起一串连锁反应。边长为n的方框，需要旋转的元素为n-1个。当方框的边长为1
	//			时递归停止。
	void rotateInPlace(vector<vector<int>>& matrix)
	{

	}
};

int main()
{
	int len = 5;
	vector<vector<int>> matrix;
	for (int i = 0; i != len; i++)
	{
		vector<int> line;
		for (int j = 0; j != len; j++)
		{
			line.push_back(len*i+j+1);
		}
		matrix.push_back(line);
	}

	for (int i = 0; i != len; i++)
	{
		for (int j = 0; j != len; j++)
		{
			cout << matrix[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	Solution slt;
	slt.rotate(matrix);

	for (int i = 0; i != len; i++)
	{
		for (int j = 0; j != len; j++)
		{
			cout << matrix[i][j] << ' ';
		}
		cout << endl;
	}

	return 0;
}