///@file	Spiral Matrix
/*
Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

For example,
Given the following matrix:

[
[ 1, 2, 3 ],
[ 4, 5, 6 ],
[ 7, 8, 9 ]
]
You should return [1,2,3,6,9,8,7,4,5].
*/
///@author	zhaowei
///@date	2015.07.06
///@version	1.0

///@date    2015.09.01
///@version 2.0

///@date	2015.10.19
///@version	2.1

#include <iostream>
#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	给定一个m*n的矩阵，输出它的旋转遍历顺序(从左上角开始，沿顺时针遍历)
	///@param	matrix	矩阵
	///@return	返回旋转遍历的顺序数组
	///@note	从左上角出发，按照顺时针顺序依次遍历。用另外一个m*n的布尔型矩阵记录哪些元素已经访问过。元素的访问顺序应该
	//			是right > down >left > up > right。
	//			时间复杂度为O(n*m)，空间复杂度为O(n*m)。
	vector<int> spiralOrder(vector<vector<int>>& matrix)
	{
		if (matrix.empty())
		{
			return rslt;
		}
		int width = matrix[0].size();
		int height = matrix.size();
		vector<bool> line1, line2;
		vector<vector<bool>> visited;	
		for (int i = 0; i != width+2; i++)	//	bool型矩阵多一圈，相当于哨兵元素，便于后边代码的编写
		{
			bool flg = false;
			if (i == 0 || i == width+1)
			{
				flg = true;
			}
			line1.push_back(flg);
			flg = true;
			line2.push_back(flg);
		}
		visited.push_back(line2);
		for (int i = 0; i != height; i++)
		{
			visited.push_back(line1);
		}
		visited.push_back(line2);
		int cnt = width*height;
		int line_indx = 0, col_indx = 0;
		while (cnt != 0)
		{
			cnt--;
			bool up = true, down = true, left = true, right = true;	//	标记应该继续前进的方向
			if (!visited[line_indx+1][col_indx+1])
			{
				rslt.push_back(matrix[line_indx][col_indx]);
				visited[line_indx+1][col_indx+1] = true;				
			}
			if (!visited[line_indx][col_indx+1])	 up = false;
			if (!visited[line_indx+2][col_indx+1]) down = false;
			if (!visited[line_indx+1][col_indx])	 left = false;
			if (!visited[line_indx+1][col_indx+2]) right = false;

			if (!right)
			{
				if (!up)
				{	
					line_indx--;continue;	
				}			
				col_indx++;continue;
			}
			if (!down)
			{
				line_indx++;continue;
			}
			if (!left)
			{
				col_indx--;continue;
			}
			if (!up)
			{	
				line_indx--;continue;	
			}			
			
		}
		return rslt;
	}
private:
	vector<int> rslt;
};

class Solution {
public:
	///@brief	按照顺时针螺旋输出m * n的矩阵元素
	///@note	枚举法：旋转输出。选定min(m, n)的一半上取整作为循环变量的上限，每次旋转输出。时间复杂度为O(n^2)，空间复杂度为O(1).
	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		vector<int> rslt;
		if (matrix.empty() || matrix[0].empty())	return rslt;
		int m = matrix.size(), n = matrix[0].size();
		int bound = (min(m, n) + 1) / 2;
		int p = m, q = n;
		for (int i = 0; i < bound; i++, p -= 2, q -= 2) {
			for (int col = i; col < i + q; col++)		rslt.push_back(matrix[i][col]);
			for (int row = i + 1; row < i + p; row++)	rslt.push_back(matrix[row][i + q - 1]);
			if (p == 1 || q == 1)	break;	// 防止p, q在下一次循环变量减2后变为负数
			for (int col = i + q - 2; col >= i; col--)	rslt.push_back(matrix[i + p - 1][col]);
			for (int row = i + p - 2; row > i; row--)	rslt.push_back(matrix[row][i]);
		}
		return rslt;
	}
};

int main()
{
	Solution slt;
	vector<vector<int>> matrix;
	int k = 0;
	cout << "Input the matrix's line size: ";
	cin >> k;
	cout << "Input the matrix's column size: ";
	int l = 0;
	cin >> l;

	
	for (int i = 0; i != k; i++)
	{
		vector<int> line;
		for (int j = 0; j != l; j++)
		{
			line.push_back(i*l+j+1);
		}
		matrix.push_back(line);		
	}

	for (int i = 0; i != k; i++)
	{
		for (int j = 0; j != l; j++)
			cout << matrix[i][j] << ' ';
		cout << endl;
	}
	
	vector<int> rslt = slt.spiralOrder(matrix);

	for (int i = 0; i != rslt.size(); i++)
	{
		cout << rslt[i] << ' ';		
	}
	cout << endl;
	return 0;
}