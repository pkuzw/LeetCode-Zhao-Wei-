///@file	Game of Life
///@author	zhaowei
///@date	2016.03.08
///@version	1.0

//	如何将空间复杂度提升到O(1)？

#include <vector>

using namespace std;

class Solution {
public:
	///@brief	生存游戏推演，给定一个m*n的棋盘，其中1表示存活，0表示死亡。当一个活动元素的周围活动邻居小于2个时，其会死亡；
	//			当一个活动元素的周围活动邻居数为2个或3个时，其继续存活；当一个活动元素的周围活动邻居数大于3个时，其亦会死亡；
	//			当一个死亡元素的周围活动邻居数为3个时，其会转为活动；否则继续保持死亡状态。在上述规则下，请给出棋盘的下一步状态。
	///@param	board	棋盘
	///@note	1. 新建一个m*n的新棋盘，在上述规则的约束下进行计算，然后将新棋盘赋给原棋盘；
	//			2. 空间复杂度为O(mn)，可以提升至O(1)。
	void gameOfLife(vector<vector<int>>& board) {
		int row_num = board.size(), col_num = board[0].size();
		if (!row_num || !col_num)	return;
		vector<vector<int>> nxt_board(row_num, vector<int>(col_num, 0));
		for (int i = 0; i != row_num; i++) {
			for (int j = 0; j != col_num; j++) {
				int live_neighbors = 0;
				if (i > 0 && j > 0 && board[i-1][j-1])	live_neighbors++;
				if (i > 0 && board[i-1][j])	live_neighbors++;					
				if (i > 0 && j < col_num - 1 && board[i-1][j+1])		live_neighbors++;
				if (j < col_num - 1 && board[i][j+1])	live_neighbors++;
				if (i < row_num - 1 && j < col_num - 1 && board[i+1][j+1])	live_neighbors++;
				if (i < row_num - 1 && board[i+1][j])	live_neighbors++;
				if (i < row_num - 1 && j > 0 && board[i+1][j-1])		live_neighbors++;
				if (j > 0 && board[i][j-1])	live_neighbors++;

				if (board[i][j]) {
					if (live_neighbors < 2)	nxt_board[i][j] = 0;
					else if (live_neighbors == 2 || live_neighbors == 3)	nxt_board[i][j] = 1;
					else	nxt_board[i][j] = 0;
				}
				else {
					if (live_neighbors == 3)	nxt_board[i][j] = 1;
					else	nxt_board[i][j] = 0;
				}
			}
		}
		for (int i = 0; i != row_num; i++)
			for (int j = 0; j != col_num; j++)
				board[i][j] = nxt_board[i][j];
	}
};

int main() {
	return 0;
}