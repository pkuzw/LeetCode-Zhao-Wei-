///@file	Spiral Matrix II
/*
Given an integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

For example,
Given n = 3,

You should return the following matrix:
[
[ 1, 2, 3 ],
[ 8, 9, 4 ],
[ 7, 6, 5 ]
]
*/
///@author	zhaowei
///@date	2015.07.07
///@version	1.0

///@date    2015.09.01
///@version 2.0

#include <vector>
#include <iostream>

using namespace std;

class Solution_v1 {
public:
	///@brief	给定常数n，计算出从左上角开始，按照顺时针方向进行盘旋的n*n的二维矩阵，其中元素按照该顺序从1 - n^2
	///@param	n	二维矩阵的大小
	///@return	返回生成的二维矩阵，该矩阵从左上角开始，按照顺时针进行旋转，依次分布有1...n^2
	///@note	利用"Spiral Matrix"中的相关算法，先记录二维矩阵旋转遍历的顺序，然后再根据这个顺序来更新二维矩阵的值。时间复杂度为O(n)，
	//			空间复杂度为O(n)。
	vector<vector<int>> generateMatrix(int n)
	{		
		if (n <= 0)
		{
			return matrix;
		}

		initMatrix(matrix, n);	//	初始化矩阵
		initVisited(visited, n);	//	初始化标志矩阵
		vector<int> line_stack, col_stack;	

		recSpiralOrder(line_stack, col_stack, n);	//	计算旋转轨迹
		
		for (int i = 0; i != line_stack.size(); i++)
		{
			matrix[line_stack[i]][col_stack[i]] = i+1;	//	按照轨迹修改相应值
		}
		return matrix;
	}

private:	
	///@brief	初始化二维矩阵
	///@param	matrix	二维矩阵
	///@param	n	二维矩阵的尺寸
	///@return 无
	void initMatrix(vector<vector<int>> &matrix, const int n)
	{		
		for (int j = 0; j != n; j++)
		{
			vector<int> tmp;
			for (int i = 0; i != n; i++)
			{
				tmp.push_back(0);
			}
			matrix.push_back(tmp);
		}
		return;
	}

	///@brief	初始化标志矩阵，其外面比二维矩阵多一圈，作为哨兵元素
	///@param	visited	布尔型二维标志矩阵
	///@param	n	二维矩阵的尺寸
	///@return	无
	void initVisited(vector<vector<bool>> &visited, const int n)
	{
		vector<bool> line1, line2;
		int width = n;
		int height = n;

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
		return;
	}

	///@brief	计算旋转遍历矩阵的顺序
	///@param	line_stack	记录元素的行号顺序
	///@param	col_stack	记录元素的列号顺序
	///@param	n	矩阵大小
	///@return  无
	void recSpiralOrder(vector<int> &line_stack, vector<int> &col_stack, const int n)
	{
		int width = n;
		int height = n;
		int cnt = width*height;
		int line_indx = 0, col_indx = 0;

		while (cnt != 0)
		{
			cnt--;
			bool up = true, down = true, left = true, right = true;	//	标记应该继续前进的方向
			if (!visited[line_indx+1][col_indx+1])
			{
				line_stack.push_back(line_indx);
				col_stack.push_back(col_indx);
				visited[line_indx+1][col_indx+1] = true;				
			}
			if (!visited[line_indx][col_indx+1])	 up = false;
			if (!visited[line_indx+2][col_indx+1]) down = false;
			if (!visited[line_indx+1][col_indx])	 left = false;
			if (!visited[line_indx+1][col_indx+2]) right = false;

			if (!right)	//	按照顺时针顺序，从左上角开始
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
		return;
	}

	vector<vector<int>> matrix;
	vector<vector<bool>> visited;		//	标识二维数组，用于标定还有哪些位置可以走
};

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix(n, vector<int>(n, 1));
        int val = 1;
        int p = n;
        for (int i = 0; i < n / 2; i++, p -= 2)
        {
            for (int col = i; col < i + p; col++)
                matrix[i][col] = val++;
            for (int row = i + 1; row < i + p; row++)
                matrix[row][i + p - 1] = val++;
            for (int col = i + p - 2; col >= i; col--)
                matrix[i + p - 1][col] = val++;
            for (int row = i + p - 2; row > i; row--)
                matrix[row][i] = val++;
        }
        if (n % 2)  matrix[n / 2][n / 2] = val;
        return matrix;
    }
};

int main()
{
	vector<vector<int>> matrix;
	Solution slt;
	int n = 5;
	matrix = slt.generateMatrix(n);

	for (int i = 0; i != n; i++)
	{
		for (int j = 0; j != n; j++)
		{
			cout << matrix[i][j] << ' ';
		}
		cout << endl;
	}
	return 0;
}