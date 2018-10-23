///@file	N-Queens
/*
The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.


Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a 
queen and an empty space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:

[
[".Q..",  // Solution 1
"...Q",
"Q...",
"..Q."],

["..Q.",  // Solution 2
"Q...",
"...Q",
".Q.."]
]
*/
///@author	zhaowei
///@date	2015.07.04
///@version 1.0

///@date    2015.09.04
///@version 2.0

///@date	2015.10.15
///@version	2.1

///@date	2016.04.13
///@version	2.2

///@date    October 23, 2018
///@version 2.3

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution_v1
{
public:
	///@brief	给出n皇后问题的所有答案
	///@param	n	棋盘的大小
	///@return	返回n*n棋盘上所有可能的解，其中'.'代表空位，'Q'代表皇后
	///@note	因为n*n的棋盘上要放n个皇后，且皇后所在是每一列、每一行以及斜线上不能有第二个皇后。故外层循环是n个皇后（按照行来遍历），
	//			内层循环是按照该皇后所在的列来遍历。棋盘用n*n的bool型二维矩阵表示，初始均为true；每次放上一个皇后，该皇后所在的行、列
	//			以及斜线就置为false。如果到达某一行时，没有任何一列可以继续放置皇后，则重置棋盘，返回上一行的下一个可能位置。然后利用
	//			一个栈来记录皇后的位置信息，每次从皇后最后一个栈顶元素继续向后寻找可能的位置。直至第一行的皇后到达最后一列。
	//			时间复杂度为O(n^3)，空间复杂度为O(n^2)
	vector<vector<string>> solveNQueens(int n)
	{
		vector<vector<bool>> chessboard;	//	记录棋盘上的可用位置
		vector<bool> chess_line;	
		bool flg = true;
		for (int i = 0; i != n; i++)	//	初始化棋盘
		{
			chess_line.push_back(flg);
		}
		for (int i = 0; i != n; i++)
		{
			chessboard.push_back(chess_line);
		}

		vector<string> slt;
		string line(n, '.');
		for (int i = 0; i != n; i++)
		{
			slt.push_back(line);
		}
				
		vector<int> qline, qcol;	//	记录皇后位置的栈，依靠它提供的皇后位置信息来进行回溯
		int last_line = 0, last_col = -1;
		bool flag = false;	//	标记是否遍历了所有的可能

		while (1)	//	遍历所有的可能
		{		
			last_line = qline.empty() ? 0 : qline.back();	//	从上一次皇后的位置继续向后遍历
			last_col = qcol.empty() ? -1 : qcol.back();
			for (int i = last_line; i != n; i++)
			{
				int cnt = 0;	//	标记棋盘中该行是否放了皇后
				for (int j = last_col+1; j != n; j++)
				{
					if (addQueen(i, j, n, chessboard))	//	如果该位置可放置皇后
					{
						slt[i][j] = 'Q';
						qline.push_back(i);
						qcol.push_back(j);
						cnt = 1;
						last_col = -1;	//	将最新的皇后位置恢复初始值						
						break;			//	找到答案，跳出内层循环
					}				
				}
				if (cnt == 0)	//	如果该行没有皇后，则回溯到上一行的下一个位置
				{
					if (qline.empty())	//	如果已经是最顶行，则说明该尺寸的棋盘不存在解
					{
						continue;
					}
					//	当记录皇后位置的栈只有一个元素，且该皇后已经是第一行的最后一个时，认为遍历完了所有可能
					if (qcol.front() == n-1 && qcol.size() == 1)		
					{
						flag = true;
						break;															
					}
					last_line = qline.back();	//	找到上一行的下一个位置
					last_col = qcol.back();		
					slt[last_line][last_col] = '.';	//	将原来放皇后的地方置空
					qline.pop_back();	//	弹出原先放皇后的位置
					qcol.pop_back();
					resetChessboard(chessboard, n, qline, qcol);	//	重置棋盘的可用位置
					i = last_line-1;
				}
			}

			if (flag)	
				break;
			
			if (qline.size() == n)
			{
				for (int i = 0; i != qline.size(); i++)
				{
					slt[qline[i]][qcol[i]] = 'Q';
				}
			}
			rslt.push_back(slt);			
		}
		return rslt;
	}

private:
	///@brief	根据当前插入的位置，来更改chessboard上的bool值
	///@param	line_num	行号
	///@param	col_num		列号
	///@param	n	棋盘的大小
	///@param	chessboard	棋盘
	///@return	如果当前位置能够插入，修改chessboard值后返回true；否则返回false
	bool addQueen(int line_num, int col_num, int n,vector<vector<bool>> &chessboard)
	{
		if (chessboard[line_num][col_num])
		{
			chessboard[line_num][col_num] = false;
			for (int i = 0; i != n ; i++)
			{
				chessboard[line_num][i] = false;	//	修改皇后所在行
				chessboard[i][col_num] = false;		//	修改皇后所在列
			}

			int line_i = line_num;
			int col_i = col_num;
			while (line_i != n && col_i != n)		//	修改皇后所在的两条斜线
			{
				chessboard[line_i][col_i] = false;
				line_i++;
				col_i++;
			}

			line_i = line_num;
			col_i = col_num;
			while (line_i != -1 && col_i != n)
			{
				chessboard[line_i][col_i] = false;
				line_i--;
				col_i++;
			}

			line_i = line_num;
			col_i = col_num;
			while (line_i != -1 && col_i != -1)
			{
				chessboard[line_i][col_i] = false;
				line_i--;
				col_i--;
			}

			line_i = line_num;
			col_i = col_num;
			while (line_i != n && col_i != -1)
			{
				chessboard[line_i][col_i] = false;
				line_i++;
				col_i--;
			}
			return true;
		}
		return false;
	}

	///@brief	根据删除的皇后位置，更新chessoboard值
	///@param	chessboard	棋盘
	///@param	n	棋盘的大小
	///@param	qline	棋盘中剩余皇后的位置行号
	///@param	qcol	棋盘中剩余皇后的位置列号
	///@return	无
	void resetChessboard(vector<vector<bool>> &chessboard, int n, vector<int> &qline, vector<int> &qcol)
	{
		for (int i = 0; i != n; i++)	//	先重置chessboard为全部为true的情形
		{
			for (int j = 0; j != n; j++)
			{
				chessboard[i][j] = true;
			}			
		}
		for (int i = 0; i != qline.size(); i++)	//	然后根据栈中的皇后位置，来修改chessboard值
		{
			addQueen(qline[i], qcol[i], n, chessboard);
		}
		return;
	}

	vector<vector<string>> rslt;	//	结果数组
};

class Solution_v2 {
public:
	///@brief	n皇后问题
	///@param	n	皇后的数目
	///@return	返回n*n棋盘上所有可能的结果
	///@note	利用深度优先遍历计算所有可能的组合
	vector<vector<string>> solveNQueens(int n) {
		vector<vector<string>> rslt;
		vector<int> pos(n, -1);
		dfs(pos, rslt, 0);
		return rslt;
	}

	///@brief	判断目前的该皇后布局是否合法
	///@param	pos	存放有n个皇后下标的数组, pos[i] = j表示棋盘上第i行的皇后在第j列
	///@param	row	当前行
	///@param	col	当前列
	///@return	如果是合法布局，则将pos[row]赋值为col，否则保持为-1
	bool isValid(vector<int>& pos, int row, int col) {
		for (int i = 0; i != row; i++) {
			if (pos[i] == col || (abs(i - row) == abs(pos[i] - col)))	return false;
		}
		return true;
	}

	///@brief	利用深度优先遍历递归计算所有合法的皇后布局
	///@param	pos	皇后的一种布局
	///@param	rslt所有可能的结果
	///@param	row	当前行号
	///@return	无
	void dfs(vector<int>& pos, vector<vector<string>>& rslt, int row) {
		if (row == pos.size()) {
			vector<string> r(pos.size(), string(pos.size(), '.'));
			for (int i = 0; i != pos.size(); i++) {
				r[i][pos[i]] = 'Q';
			}
			rslt.push_back(r);
		}
		else {
			for (int i = 0; i != pos.size(); i++) {
				if (isValid(pos, row, i)) {
					pos[row] = i;
					dfs(pos, rslt, row + 1);
					pos[row] = -1;
				}
			}
		}
	}
};

class Solution {
public:
	vector<vector<string>> solveNQueens(int n) {
		vector<vector<string>> rslt;
		vector<int> pos(n, -1);
		dfs(rslt, pos, 0);
		return rslt;
	}

	bool isValid(vector<int> pos, int row, int col) {
		for (int i = 0; i != row; i++)
			if (pos[i] == col || abs(i - row) == abs(pos[i] - col))	return false;
		return true;
	}

	void dfs(vector<vector<string>>& rslt, vector<int>& pos, int row) {
		if (row == pos.size()) {
			vector<string> tmp(pos.size(), string(pos.size(), '.'));
			for (int i = 0; i != pos.size(); i++) tmp[i][pos[i]] = 'Q';			
			rslt.push_back(tmp);
			return;
		}
		for (int i = 0; i != pos.size(); i++) {
			if (isValid(pos, row, i)) {
				pos[row] = i;
				dfs(rslt, pos, row + 1);
				pos[row] = -1;
			}
		}
	}
};

int main()
{
	int n = 4;	
	Solution slt;
	vector<vector<string>> rslt = slt.solveNQueens(n);
	return 0;
}
