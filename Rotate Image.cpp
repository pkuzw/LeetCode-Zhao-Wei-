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

///@date    2015.09.04
///@version 2.0

///@date	2015.10.14
///@version	2.1

///@date	2016.04.12
///@version	2.2

///@date    October 21, 2018
///@version 2.3

#include <iostream>
#include <vector>
using namespace std;

class Solution_v1 {
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
	///@param	matrix	二维矩阵
	///@return	无
	///@note	可以利用递归的方式在O(1)的空间复杂度下进行旋转。将矩阵看作是从外到内边长依次递减的方框，每个位置在旋转后移动的新位置
	//			会组成一个闭环。每次旋转方框上的一个元素，就会引起一串连锁反应。边长为n的方框，需要旋转的元素为n-1个。当方框的边长为1或0
	//			时递归停止。空间复杂度为O(1)，时间复杂度为O(n^2)
	void rotate2(vector<vector<int>>& matrix)
	{
		int len = matrix.size();
		rotateInPlace(matrix, 0, 0, len);
		return;
	}

	///@brief	将二维矩阵在原地进行90°顺时针旋转
	///@param	start_line	正方形矩阵的左上角行号
	///@param	start_col		正方形矩阵的左上角列号
	///@param	len		正方形矩阵边长
	///@return	无
	///@note	1. 原地进行旋转时，需要两个临时变量来进行替换，tmp1用来存储下一个改变的元素，tmp2存储当前的元素值。在进行闭环的替换时，先保存下一个
	//			元素值到tmp1，然后将保存有当前元素值的临时变量tmp2放入下一个元素，此时移动下标，将tmp1赋值给tmp2；
	//			2. 每个闭环的长度均为4，因为二维矩阵有4条边；
	//			3. 二维矩阵在90°顺时针旋转后，元素的新位置的行号等于原来的列号，新位置的列号等于当前矩阵的左上角行号与列号之和加上边长减1与原来行号的差
	void rotateInPlace(vector<vector<int>>& matrix, int start_line, int start_col, int len)
	{
		if (len == 1 || len == 0)
		{
			return;
		}
		for (int i = 0; i != len-1; i++)		//i: 当前元素列号
		{
			int line_indx = start_line;	//	当前元素行号
			int col_indx = start_col+i;	//	当前元素列号

			int next_line_indx = col_indx;	//	旋转后的行号
			int next_col_indx = start_col + start_line + len - 1 - line_indx;	//	旋转后的列号

			int init_line_indx = line_indx;	//	初始元素行号
			int init_col_indx = col_indx;	//	初始元素行号
			int tmp1 = matrix[next_line_indx][next_col_indx];	//	临时变量1
			int tmp2 = matrix[line_indx][col_indx];				//	临时变量2


			int cnt = 0;
			while (cnt != 4)	//	进行闭环元素的替换
			{					
				tmp1 = matrix[next_line_indx][next_col_indx];
				matrix[next_line_indx][next_col_indx] = tmp2;

				line_indx = next_line_indx;
				col_indx = next_col_indx;
				next_line_indx = col_indx;
				next_col_indx = start_col + start_line + len - 1 - line_indx;	
				tmp2 = tmp1;
				cnt++;
			}
		}
		rotateInPlace(matrix, start_line+1, start_col+1, len-2);
		return;
	}
};

class Solution_v2 {
public:
	///@brief	将一个n * n的二维矩阵顺时针翻转九十度
	///@param	matrix	二维矩阵
	///@return	无
	///@note	1. 将原矩阵转换成转置矩阵，然后将每行翻转即可。另外，如果在转换成转置矩阵后，翻转每一列，则是逆时针翻转90°
	///@note	2. 空间复杂度为O(1)。
    void rotate(vector<vector<int>>& matrix) {
		for (int i = 0; i != matrix.size(); i++)
			for (int j = i + 1; j != matrix.size(); j++)
				swap(matrix[i][j], matrix[j][i]);
		for (int i = 0; i != matrix.size(); i++)
			reverse(matrix[i].begin(), matrix[i].end());        
    }

	///@brief	将一个n * n的二维矩阵逆时针翻转90°
	///@param	matrix	二维矩阵
	///@return	无
	///@note	先将矩阵转换为转置矩阵，然后翻转每一列即可
	void rotate_anticlockwise(vector<vector<int>>& matrix) {
		for (int i = 0; i != matrix.size(); i++)
			for (int j = i + 1; j != matrix.size(); j++)
				swap(matrix[i][j], matrix[j][i]);
		for (int i = 0; i != matrix.size(); i++) 
			for (int j = 0; j != matrix.size() / 2; j++)
				swap(matrix[j][i], matrix[matrix.size() - 1 - j][i]);		
	}
};

class Solution {
public:
    ///@brief   将一个矩阵顺时针翻转90°。要求翻转过程中的空间复杂度为O(1)。
    ///@param   matrix  矩阵
    ///@note    1. 先将矩阵转换为转置矩阵，然后翻转每一行即可。所谓转置矩阵，即原矩阵的每一行是转置矩阵的每一列。
    //          2. 时间复杂度为O(m^2)，其中m为矩阵的行数，空间复杂度为O(1)。
	void rotate(vector<vector<int>>& matrix) {
        for (int i = 0; i < matrix.size(); i++)
            for (int j = i + 1; j < matrix.size(); j++)
                swap(matrix[i][j], matrix[j][i]);
        for (int i = 0; i < matrix.size(); i++)
            reverse(matrix[i].begin(), matrix[i].end());
    }
};

void printMatrix(vector<vector<int>> matrix) {
	for (int i = 0; i != matrix.size(); i++)
	{
		for (int j = 0; j != matrix.size(); j++)
		{
			cout << matrix[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	int len = 3;
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

	printMatrix(matrix);

	Solution_v1 slt_v1;
	slt_v1.rotate(matrix);

	printMatrix(matrix);

	vector<vector<int>> matrix1;
	for (int i = 0; i != len; i++)
	{
		vector<int> line;
		for (int j = 0; j != len; j++)
		{
			line.push_back(len*i+j+1);
		}
		matrix1.push_back(line);
	}

	slt_v1.rotate2(matrix1);
	printMatrix(matrix1);
    
	return 0;
}
