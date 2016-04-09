///@file	Sudoku Solver
/*
			Write a program to solve a Sudoku puzzle by filling the empty cells.

			Empty cells are indicated by the character '.'.

			You may assume that there will be only one unique solution.
*/
///@author	zhaowei
///@date	2015.06.17
///@version	1.0

///@date    2015.09.04
///@version 2.0

///@date	2015.09.23
///@version	2.1

///@date	2016.04.09
///@version	2.2

#include <iostream>
#include <vector>

using namespace std;

class Solution_v1
{
public:
	///@brief	求解数独
	///@param	board	二维char型vector表示的9*9数独
	///@return	无
	///@note	先将数独中已有的数字进行标记，然后利用遍历和回溯法逐一尝试。其中回溯利用到了vector，它作为栈来使用，
	//			可以模拟元素的尝试回溯过程。时间复杂度为O(n^2)，空间复杂度为O(n)。
	///@author	zhaowei
	///@date	2015.06.17
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

		for (int i = 0; i < 9; i++)	//	记录数独中已有的数字
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

				if (board[i][j] != '.')
				{
					int a = board[i][j] - '0';
					square[(i/3)*3+(j/3)][a-1] = true;					
				}			
			}
		}

		vector<int> rowIndex, colIndex, numIndex;	//分别用于记录已经填充的行下标，列下标和数字
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				int tmp = -1;
				bool next = false;
				while (board[i][j] == '.')	//	一直尝试，直到找到合适的数字位置
				{
					rowIndex.push_back(i);
					colIndex.push_back(j);
					for (int k = tmp+1; k < 9; k++)
					{
						if (!row[i][k] && !column[j][k] && !square[(i/3)*3+(j/3)][k])
						{
							board[i][j] = char(int('0')+k+1);
							row[i][k] = true;
							column[j][k] = true;
							square[(i/3)*3+(j/3)][k] = true;
							numIndex.push_back(k);
							next = true;	//	用于标记是否需要回溯
							break;
						}
					}
					if (!next)	//	回溯
					{
						rowIndex.pop_back();
						i = rowIndex.back();
						rowIndex.pop_back();
						
						colIndex.pop_back();
						j = colIndex.back();
						colIndex.pop_back();

						tmp = numIndex.back();
						numIndex.pop_back();

						row[i][tmp] = false;
						column[j][tmp] = false;
						square[(i/3)*3+(j/3)][tmp] = false;		
						next = false;
						board[i][j] = '.';
					}					
				}				
			}
		}
	}
};

class Solution_v2 {
public:
	///@brief	计算数独的一个解。假设给定的数独有且只有一个解
	///@param	board	数独
	///@return	无
	///@note	递归回溯法求解。从左上角开始，以先逐列再逐行尝试添加数字，对于'.'字符，每添加一个数字，就用验证函数检验一下数独是否合法。如果合法，则继续下一列的添加。如果不合法，则将该位置重置为'.'，
	//			并尝试下一个数字。对于已经标记了数字的格子，则转向下一列。时间复杂度为O(2^n)，空间复杂度为O(1)。
	void solveSudoku(vector<vector<char>>& board) {
		if (board.empty() || board[0].empty())	return;
		dfs(board, 0, 0);
	}

	///@brief	回溯递归求解数独
	///@param	board	数独表
	///@param	row		行号
	///@param	col		列号
	///@return	如果能够找到最后一行，则返回true，否则返回false。之所以是最后一行而不是最后一列，是因为深搜的顺序是按照先逐列再逐行的顺序。
	bool dfs(vector<vector<char>>& board, int row, int col) {
		if (row == 9)	return true;
		if (col == 9)	return dfs(board, row + 1, 0);
		if (board[row][col] == '.') {
			for (int i = 1; i <= 9; i++) {
				board[row][col] = '0' + i;
				if (isValid(board, row, col)) {
					if (dfs(board, row, col + 1))	return true;
				}
				board[row][col] = '.';
			}
		}
		else	return dfs(board, row, col + 1);
		return false;
	}

	///@brief	检验某个位置是否已经有同样的数字被填充
	///@param	board	数独表
	///@param	row		行号
	///@param	col		列号
	///@return	如果合法则返回true，否则返回false
	bool isValid(vector<vector<char>>& board, int row, int col) {
		for (int i = 0; i != 9; i++) 
			if (i != row && board[i][col] == board[row][col])	return false;
		for (int j = 0; j != 9; j++)
			if (j != col && board[row][j] == board[row][col])	return false;
		for (int i = 3 * (row / 3); i != 3 * (row / 3) + 3; i++)
			for (int j = 3 * (col / 3); j != 3 * (col / 3) + 3; j++)
				if (i != row && j != col && board[i][j] == board[row][col])	return false;
		return true;
	}
};

class Solution {
public:
	void solveSudoku(vector<vector<char>>& board) {
		if (board.empty() || board[0].empty())	return;
		dfs(board, 0, 0);
	}

	bool dfs(vector<vector<char>>& board, int row, int col) {
		if (row == 9)	return true;
		if (col == 9)	return dfs(board, row + 1, 0);
		if (board[row][col] == '.') {
			for (int i = 0; i < 9; i++) {
				board[row][col] = '1' + i;
				if (isValid(board, row, col))
					if (dfs(board, row, col + 1))	return true;
				board[row][col] = '.';				
			}
		}
		else	return dfs(board, row, col + 1);
		return false;
	}

	bool isValid(vector<vector<char>>& board, int row, int col) {
		for (int i = 0; i < 9; i++)
			if (i != row && board[i][col] == board[row][col])	return false;
		for (int j = 0; j < 9; j++)
			if (j != col && board[row][j] == board[row][col])	return false;
		for (int i = 3 * (row / 3); i < 3 * (row / 3) + 3; i++)
			for (int j = 3 * (col / 3); j < 3 * (col / 3) + 3; j++)
				if (i != row && j != col && board[i][j] == board[row][col])	return false;
		return true;
	}
};

int main()
{
	vector<char> chvec[10];
	vector< vector<char> > chchvec;

	//	[".87654321","2........","3........","4........","5........","6........","7........","8........","9........"]
	chvec[0].push_back('5');
	chvec[0].push_back('3');
	chvec[0].push_back('.');
	chvec[0].push_back('.');
	chvec[0].push_back('7');
	chvec[0].push_back('.');
	chvec[0].push_back('.');
	chvec[0].push_back('.');
	chvec[0].push_back('.');

	chvec[1].push_back('6');
	chvec[1].push_back('.');
	chvec[1].push_back('.');
	chvec[1].push_back('1');
	chvec[1].push_back('9');
	chvec[1].push_back('5');
	chvec[1].push_back('.');
	chvec[1].push_back('.');
	chvec[1].push_back('.');

	chvec[2].push_back('.');
	chvec[2].push_back('9');
	chvec[2].push_back('8');
	chvec[2].push_back('.');
	chvec[2].push_back('.');
	chvec[2].push_back('.');
	chvec[2].push_back('.');
	chvec[2].push_back('6');
	chvec[2].push_back('.');

	chvec[3].push_back('8');
	chvec[3].push_back('.');
	chvec[3].push_back('.');
	chvec[3].push_back('.');
	chvec[3].push_back('6');
	chvec[3].push_back('.');
	chvec[3].push_back('.');
	chvec[3].push_back('.');
	chvec[3].push_back('3');

	chvec[4].push_back('4');
	chvec[4].push_back('.');
	chvec[4].push_back('.');
	chvec[4].push_back('8');
	chvec[4].push_back('.');
	chvec[4].push_back('3');
	chvec[4].push_back('.');
	chvec[4].push_back('.');
	chvec[4].push_back('1');

	chvec[5].push_back('7');
	chvec[5].push_back('.');
	chvec[5].push_back('.');
	chvec[5].push_back('.');
	chvec[5].push_back('2');
	chvec[5].push_back('.');
	chvec[5].push_back('.');
	chvec[5].push_back('.');
	chvec[5].push_back('6');

	chvec[6].push_back('.');
	chvec[6].push_back('6');
	chvec[6].push_back('.');
	chvec[6].push_back('.');
	chvec[6].push_back('.');
	chvec[6].push_back('.');
	chvec[6].push_back('2');
	chvec[6].push_back('8');
	chvec[6].push_back('.');

	chvec[7].push_back('.');
	chvec[7].push_back('.');
	chvec[7].push_back('.');
	chvec[7].push_back('4');
	chvec[7].push_back('1');
	chvec[7].push_back('9');
	chvec[7].push_back('.');
	chvec[7].push_back('.');
	chvec[7].push_back('5');

	chvec[8].push_back('.');
	chvec[8].push_back('.');
	chvec[8].push_back('.');
	chvec[8].push_back('.');
	chvec[8].push_back('8');
	chvec[8].push_back('.');
	chvec[8].push_back('.');
	chvec[8].push_back('7');
	chvec[8].push_back('9');

	for (int i = 0; i < 9; i++)
	{
		chchvec.push_back(chvec[i]);
	}

	Solution slt;

	slt.solveSudoku(chchvec);

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << chchvec[i][j] << ' ';
		}
		cout << endl;
	}

	return 0;
}