﻿///@file	Valid Sudoku
/*
			Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.

			The Sudoku board could be partially filled, where empty cells are filled with the character '.'.

			Note:
			A valid Sudoku board (partially filled) is not necessarily solvable. Only the filled cells need to be validated.
*/
///@author	zhaowei
///@date	2015.06.17
///@version	1.1

///@date    2015.09.04
///@version 2.0

#include <iostream>
#include <vector>

using namespace std;

class Solution_v1
{
public:
	///@brief	判断一个数独是否有效
	///@param	board	数独
	///@return	如果一个数独有效，则返回true；否则返回false
	///@author	zhaowei
	///@date	2015.06.17
	///@note	设置三个9*9的bool型二维数组来保存每一行、每一列以及每一个3*3的方块中是否有重复数字。时间复杂度为O(n^2)，空间复杂度为O(n^2)。
	bool isValidSudoku(vector<vector<char>>& board) {

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
					if (!row[i][a-1])	//	如果是第一次出现该数字，则将其设为true
					{
						row[i][a-1] = true;
					}
					else				//	如果曾经出现过，则直接返回false
					{
						return false;
					}
				}

				if (board[j][i] != '.')
				{
					int a = board[j][i] - '0';
					if (!column[i][a-1])
					{
						column[i][a-1] = true;
					}
					else
					{
						return false;
					}
				}	

				if (board[i][j] != '.')
				{
					int a = board[i][j] - '0';
					if (!square[(i/3)*3+(j/3)][a-1])
					{
						square[(i/3)*3+(j/3)][a-1] = true;
					}
					else
					{
						return false;
					}
				}			
			}
		}
		return true;
	}
};

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty())    return false;
        int n = board.size();
        vector<vector<bool>> row_flg(n, vector<bool>(n, false));
        vector<vector<bool>> col_flg(n, vector<bool>(n, false));
        vector<vector<bool>> cell_flg(n, vector<bool>(n, false));
        for (int i = 0; i != n; i++){
            for (int j = 0; j != n; j++){
                if (board[i][j] >= '1' && board[i][j] <= '9'){
                    int k = board[i][j] - '1';
                    if (row_flg[i][k] || col_flg[k][j] || cell_flg[3 * (i / 3) + j / 3][k]) return false;
                    row_flg[i][k] = true;
                    col_flg[k][j] = true;
                    cell_flg[3 * (i / 3) + j / 3][k] = true;
                }
            }
        }
        return true;
    }
};

int main()
{
	vector<char> chvec[10];
	vector< vector<char> > chchvec;

	//	[".87654321","2........","3........","4........","5........","6........","7........","8........","9........"]
	chvec[0].push_back('.');
	chvec[0].push_back('8');
	chvec[0].push_back('7');
	chvec[0].push_back('6');
	chvec[0].push_back('5');
	chvec[0].push_back('4');
	chvec[0].push_back('3');
	chvec[0].push_back('2');
	chvec[0].push_back('1');

	chvec[1].push_back('2');
	chvec[1].push_back('.');
	chvec[1].push_back('.');
	chvec[1].push_back('.');
	chvec[1].push_back('.');
	chvec[1].push_back('.');
	chvec[1].push_back('.');
	chvec[1].push_back('.');
	chvec[1].push_back('.');

	chvec[2].push_back('3');
	chvec[2].push_back('.');
	chvec[2].push_back('.');
	chvec[2].push_back('.');
	chvec[2].push_back('.');
	chvec[2].push_back('.');
	chvec[2].push_back('.');
	chvec[2].push_back('.');
	chvec[2].push_back('.');

	chvec[3].push_back('4');
	chvec[3].push_back('.');
	chvec[3].push_back('.');
	chvec[3].push_back('.');
	chvec[3].push_back('.');
	chvec[3].push_back('.');
	chvec[3].push_back('.');
	chvec[3].push_back('.');
	chvec[3].push_back('.');

	chvec[4].push_back('5');
	chvec[4].push_back('.');
	chvec[4].push_back('.');
	chvec[4].push_back('.');
	chvec[4].push_back('.');
	chvec[4].push_back('.');
	chvec[4].push_back('.');
	chvec[4].push_back('.');
	chvec[4].push_back('.');

	chvec[5].push_back('6');
	chvec[5].push_back('.');
	chvec[5].push_back('.');
	chvec[5].push_back('.');
	chvec[5].push_back('.');
	chvec[5].push_back('.');
	chvec[5].push_back('.');
	chvec[5].push_back('.');
	chvec[5].push_back('.');

	chvec[6].push_back('7');
	chvec[6].push_back('.');
	chvec[6].push_back('.');
	chvec[6].push_back('.');
	chvec[6].push_back('.');
	chvec[6].push_back('.');
	chvec[6].push_back('.');
	chvec[6].push_back('.');
	chvec[6].push_back('.');

	chvec[7].push_back('8');
	chvec[7].push_back('.');
	chvec[7].push_back('.');
	chvec[7].push_back('.');
	chvec[7].push_back('.');
	chvec[7].push_back('.');
	chvec[7].push_back('.');
	chvec[7].push_back('.');
	chvec[7].push_back('.');

	chvec[8].push_back('9');
	chvec[8].push_back('.');
	chvec[8].push_back('.');
	chvec[8].push_back('.');
	chvec[8].push_back('.');
	chvec[8].push_back('.');
	chvec[8].push_back('.');
	chvec[8].push_back('.');
	chvec[8].push_back('.');

	for (int i = 0; i < 9; i++)
	{
		chchvec.push_back(chvec[i]);
	}

	Solution slt;

	bool rslt = slt.isValidSudoku(chchvec);

	cout << rslt << endl;

	return 0;
}