///@file	Design Tic-Tac-Toe
///@author	zhaowei
///@date	2016.05.07
///@version	1.0

#include <vector>
using namespace std;

class TicTacToe {
public:
    /** Initialize your data structure here. */
    TicTacToe(int n) {
        vector<int> row(n, 0);
		for (int i = 0; i != n; i++)	board.push_back(row);
    }
    
    /** Player {player} makes a move at ({row}, {col}).
        @param row The row of the board.
        @param col The column of the board.
        @param player The player, can be either 1 or 2.
        @return The current winning condition, can be either:
                0: No one wins.
                1: Player 1 wins.
                2: Player 2 wins. 

		@note	Player 1: 1
				Player 2: 2
				初始为0

				1. 每走一步，就检查是否该选手获胜。检查的条件有3种，一种是该行为指定的连续元素，另一种是该列是指定的连续元素，最后一种是对角线为
				指定的元素。
				2. 时间复杂度为O(nk)，其中n为棋盘的行数或列数，k为走的步数。
				*/

    int move(int row, int col, int player) {
		int win_row = 0, win_col = 0, win_diag = 0;
        if (player == 1) {
			board[row][col] = 1;
			win_row = checkRow(row);
			win_col = checkCol(col);
			win_diag = checkDiag();
			if (win_row == 1 || win_col == 1 || win_diag == 1)	return 1;
		}
		else {
			board[row][col] = 2;
			win_row = checkRow(row);
			win_col = checkCol(col);
			win_diag = checkDiag();
			if (win_row == 2 || win_col == 2 || win_diag == 2)	return 2;
		}
		return 0;
    }

	///@brief	检查某行是否全部为1或0
	///@return	如果全是1，则返回1；如果全是2，则返回2；否则返回0.
	int checkRow(int row) {
		bool flg1 = true, flg2 = true;
		for (int i = 0; i != board.size(); i++) {
			if (board[row][i] == 1)	flg2 = false;							
			else if (board[row][i] == 2)	flg1 = false;			
			else	flg1 = flg2 = false;			
		}
		if (flg1 && !flg2)	return 1;
		if (!flg1 && flg2)	return 2;
		return 0;
	}

	///@brief	检查某列是否全部为1或0
	///@return	如果全是1，则返回1；如果全是2，则返回2；否则返回0.
	int checkCol(int col) {
		bool flg1 = true, flg2 = true;
		for (int i = 0; i != board.size(); i++) {
			if (board[i][col] == 1)	flg2 = false;							
			else if (board[i][col] == 2)	flg1 = false;			
			else	flg1 = flg2 = false;			
		}
		if (flg1 && !flg2)	return 1;
		if (!flg1 && flg2)	return 2;
		return 0;
	}

	///@brief	检查对角线是否全部为1或0
	///@return	如果全是1，则返回1；如果全是2，则返回2；否则返回0.
	int checkDiag() {
		bool flg1 = true, flg2 = true;
		for (int i = 0; i != board.size(); i++) {
			if (board[i][i] == 1)	flg2 = false;							
			else if (board[i][i] == 2)	flg1 = false;			
			else	flg1 = flg2 = false;			
		}

		bool flg1_ = true, flg2_ = true;
		for (int i = 0; i != board.size(); i++) {
			if (board[i][board.size()-1-i] == 1)		flg2_ = false;
			else if (board[i][board.size()-1-i] == 2)		flg1_ = false;
			else flg1_ = flg2_ = false;
		}

		if ((flg1 && !flg2) || (flg1_ && !flg2_))	return 1;
		if ((!flg1 && flg2)	|| (!flg1_ && flg2_))	return 2;
		return 0;
	}

	vector<vector<int>> board;

};

/**
 * Your TicTacToe object will be instantiated and called as such:
 * TicTacToe obj = new TicTacToe(n);
 * int param_1 = obj.move(row,col,player);
 */

int main() {
	TicTacToe t(2);
	int r = 0;
	r = t.move(0, 0, 2);
	r = t.move(1, 1, 1);
	r = t.move(0, 1, 2);	
	return 0;
}