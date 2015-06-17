///@file	Sudoku Solver
/*
			Write a program to solve a Sudoku puzzle by filling the empty cells.

			Empty cells are indicated by the character '.'.

			You may assume that there will be only one unique solution.
*/
///@author	zhaowei
///@date	2015.06.17
///@version	1.0

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
	void solveSudoku(vector<vector<char>>& board) {

		bool column[9][9];	//	保存每一列中数字是否有重复出现，如果还未出现是false，出现过的设为true
		bool row[9][9];		//	保存每一行中数字是否有重复出现
		bool square[9][9];	//	保存每一3*3方块中数字是否有重复出现
		for (int i = 0; i < 9; i++)	//	初始化
		{
			for (int j = 0; j < 9; j++)
			{
				row[i][j] = false;
				column[i][j] = false;
				square[i][j] = false;
			}
		}

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (board[i][j] != '.')
				{
					int a = board[i][j] - '0';
					row[i][a-1] = true;					
				}

				if (board[j][i] != '.')
				{
					int a = board[j][i] - '0';
					column[i][a-1] = true;
				}			
			}
		}

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					for (int l = 0; l < 3; l++)
					{
						if (board[i*3+k][j*3+l] != '.')	
						{
							int a = board[i*3+k][j*3+l] - '0';
							square[i*3+j][a-1] = true;							
						}			
					}
				}
			}
		}

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (board[i][j] == '.')
				{
					for (int k = 0; k < 9; k++)
					{
						if (!row[i][k] && !column[j][k] && !square[(i/3)*3+(j/3)][k])
						{
							board[i][j] = char(int('0')+k+1);
							row[i][k] = true;
							column[j][k] = true;
							square[(i/3)*3+(j/3)][k] = true;
							break;
						}
					}
				}
			}
		}
	}
};

int main()
{
	return 0;
}