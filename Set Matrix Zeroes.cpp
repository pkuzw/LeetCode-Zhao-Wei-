///@file	Set Matrix Zeroes
/*
Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.
*/
///@author	zhaowei
///@date	2015.07.13
///@version	1.1

///@date	2015.08.27
///@version	2.0

///@date	2015.12.05
///@version	2.1

///@date	2016.04.21
///@version	2.2

///@date    November 12, 2018
///@version 3.0

#include <iostream>
#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	给定一个m*n的二维矩阵，将'0'所在行和列置为0
	///@param	matrix	二维矩阵
	///@return	无
	///@note	新建两个1维数组，分别记录0元素的行号和列号位置。这两个1维数组初始均为false，当其某一行或者某一列有0元素时就置为true。
	//			最后根据这两个一维bool数组的标记来更新二维矩阵。时间复杂度为O(m*n)，空间复杂度为O(m+n)
	void setZeroes_space_O_m_plus_n(vector<vector<int>>& matrix) {
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

	///@brief	给定一个m*n的二维矩阵，将'0'所在行和列置为0
	///@param	matrix	二维矩阵
	///@return	无
	///@note	用两个临时变量来记录第一行和第一列是否需要置0，然后利用第一行和第一列的空间来记录剩下m-1*n-1的二维矩阵的哪一行和哪一列
	//			需要置零。时间复杂度为O(m*n)，空间复杂度为O(1)
	void setZeroes_space_O_1(vector<vector<int>>& matrix) {
		if (matrix.empty())
		{
			return;
		}
		int m = matrix.size();

		if (matrix[0].empty())
		{
			return;
		}
		int n = matrix[0].size();

		bool first_line = false;	//	标记第一行是否需要置零
		bool first_col = false;		//	标记第一列是否需要置零

		//	记录第一行和第一列是否需要置零
		for (int i = 0; i != n; i++)
		{
			if (matrix[0][i] == 0)
			{
				first_line = true;
				break;
			}
		}

		for (int i = 0; i != m; i++)
		{
			if (matrix[i][0] == 0)
			{
				first_col = true;
				break;
			}
		}
			

		//	利用第一行和第一列的空间来保存剩余m-1*n-1的二维矩阵需要置零的行和列
		for (int i = 1; i != m; i++)
		{
			for (int j = 1; j != n; j++)
			{
				if (matrix[i][j] == 0)
				{
					matrix[i][0] = 0;
					matrix[0][j] = 0;
				}
			}
		}

		//	根据第一行和第一列的记录结果置零
		for (int i = 1; i != n; i++)
		{
			if (matrix[0][i] == 0)
			{
				for (int j = 0; j != m; j++)
				{
					matrix[j][i] = 0;
				}
			}			
		}
		for (int i = 1; i != m; i++)
		{
			if (matrix[i][0] == 0)
			{
				for (int j = 0; j != n; j++)
				{
					matrix[i][j] = 0;
				}
			}			
		}

		//	根据记录将第一行或第一列置零
		if (first_line)
		{
			for (int i = 0; i != n; i++)
			{
				matrix[0][i] = 0;
			}
		}
		if (first_col)
		{
			for (int i = 0; i != m; i++)
			{
				matrix[i][0] = 0;
			}
		}
		return;
	}
};

/*
1. 用flg1和flg2分别来标记是否需要将第0行和第0列置零；
2. 用第一行的1..n-1表示第1..n-1列是否需要置零；用第一列的1..n-1表示第1..n-1行是否需要置零；
3. 空间复杂度为O(1)，时间复杂度为O(n^2)
*/
class Solution_v2 {
public:
	void setZeroes(vector<vector<int>>& matrix) {
		if (matrix.empty())	return;
		int row = matrix.size();
		int col = matrix[0].size();

		bool flg1 = false;	//	第一行是否需要置零
		bool flg2 = false;	//	第一列是否需要置零
		if (!matrix[0][0])
		{
			flg1 = true;
			flg2 = true;
		}
		else
		{
			for (int i = 1; i != row; i++)
			{
				if (!matrix[i][0])
				{
					flg2 = true;
					break;
				}
			}
			for (int i = 1; i != col; i++)
			{
				if (!matrix[0][i])
				{
					flg1 = true;
					break;
				}
			}
		}
		for (int i = 1; i != row; i++)
		{
			for (int j = 1; j != col; j++)
			{
				if (!matrix[i][j])
				{
					matrix[0][j] = 0;
					matrix[i][0] = 0;
				}
			}
		}
		for (int i = 1; i != row; i++)
			if (!matrix[i][0])			
				for (int j = 1; j != col; j++)	
					matrix[i][j] = 0;			
		
		for (int i = 1; i != col; i++)
			if (!matrix[0][i])
				for (int j = 1; j != row; j++)
					matrix[j][i] = 0;

		if (flg1 && flg2)
		{
			for (int i = 0; i != row; i++)	matrix[i][0] = 0;
			for (int i = 0; i != col; i++)	matrix[0][i] = 0;
		}
		else if (flg1 && !flg2)	for (int i = 0; i != col; i++)	matrix[0][i] = 0;
		else if (!flg1 && flg2)	for (int i = 0; i != row; i++)	matrix[i][0] = 0;
	}
};

class Solution_v2_1 {
public:
	///@brief	给定一个二维矩阵，如果某个元素为0，则将该元素所在行列置为0。要求空间复杂度为O(1)。
	///@param	matrix	二维矩阵
	///@return	无
	///@note	1. 如果要达到空间复杂度为O(1)的要求，要尽可能的利用现有元素所占用的空间；
	//			2. 用两个变量记录第一行和第一列是否存在0元素；3. 用第一行和第一列来标记第2..m行，第2..n列中存在0元素的下标。
	//			   如果某个位于[i, j]的元素为0，则将第1行的第j列和第1列的第i行元素值为0；
	//			4. 先遍历第一行和第一列，再遍历剩余行和列，接着根据第一行和第一列的记录将相应行列置零，最后根据临时变量中的标记决定是否将第一行和第一列置零；
	//			5. 时间复杂度为O(mn)，空间复杂度为O(1)，其中m和n分别为二维矩阵的行数和列数。
	void setZeroes(vector<vector<int>>& matrix) {
		if (matrix.empty() || matrix[0].empty())	return;
		int m = matrix.size();
		int n = matrix[0].size();
		bool flg_row1 = false;
		bool flg_col1 = false;
		for (int i = 0; i != n; i++) {
			if (!matrix[0][i]) {
				flg_row1 = true;break;
			}
		}
		for (int i = 0; i != m; i++) {
			if (!matrix[i][0]) {
				flg_col1 = true;break;
			}
		}
		for (int i = 1; i != m; i++) {
			for (int j = 1; j != n; j++) {
				if (!matrix[i][j]) {
					matrix[0][j] = 0;
					matrix[i][0] = 0;
				}
			}
		}
		for (int i = 1; i != m; i++) {
			if (!matrix[i][0]) {
				for (int j = 1; j != n; j++)	
					matrix[i][j] = 0;
			}
		}
		for (int j = 1; j != n; j++) {
			if (!matrix[0][j]) {
				for (int i = 1; i != m; i++)	
					matrix[i][j] = 0;
			}
		}
		if (flg_row1) {
			for (int i = 0; i != n; i++)
				matrix[0][i] = 0;
		}
		if (flg_col1) {
			for (int i = 0; i != m; i++)
				matrix[i][0] = 0;
		}
		return;
	}
};

class Solution {
public:
    ///@brief   给定一个矩阵，将0元素所在行列都置为0。要求空间复杂度为O(1)。
    ///@param   matrix  矩阵；
    ///@note    1. 要想使空间复杂度为O(1)，应该尽可能地利用现有的内存空间；
    //          2. 考虑用两个临时变量保存第一行和第一列是否需要置0；然后用矩阵本身的第一行和第一列来保存剩下的0元素的坐标；
    //          3. 时间复杂度为O(mn)，空间复杂度为O(1)，其中m和n分别为矩阵的行列数。
	void setZeroes(vector<vector<int>>& matrix) {
        if (matrix.empty()) return;
        int  m = matrix.size(), n = matrix[0].size();
        bool firstRowIsZero = false, firstColIsZero = false;
        for (int j = 0; j < n; j++)
            if (!matrix[0][j])  firstRowIsZero = true;
        for (int i = 0; i < m; i++)
            if (!matrix[i][0])  firstColIsZero = true;
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (!matrix[i][j]) {
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
            }
        }
        for (int j = 1; j < n; j++)
            if (!matrix[0][j])
                for (int i = 1; i < m; i++) matrix[i][j] = 0;
        for (int i = 1; i < m; i++)
            if (!matrix[i][0])
                for (int j = 1; j < n; j++) matrix[i][j] = 0;
        if (firstRowIsZero)
            for (int j = 0; j < n; j++) matrix[0][j] = 0;
        if (firstColIsZero)
            for (int i = 0; i < m; i++) matrix[i][0] = 0;
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
	
//  	matrix.clear();
//  	line.clear();
//  	line.push_back(0);
//  	line.push_back(0);
//  	line.push_back(1);
//  	matrix.push_back(line);
//  
//  
//  	line.clear();
//  	line.push_back(1);
//  	line.push_back(1);
//  	line.push_back(1);
//  	matrix.push_back(line);

//  	Solution_v1 slt_v1;
//  	slt_v1.setZeroes_space_O_1(matrix);

	Solution slt;
	slt.setZeroes(matrix);
	return 0;
}
