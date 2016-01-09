///@file	Surrounded Regions
/*
Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

For example,
X X X X
X O O X
X X O X
X O X X

After running your function, the board should be:
X X X X
X X X X
X X X X
X O X X
*/
///@author	zhaowei
///@date	2015.07.25
///@version	1.0

///@date	2015.08.21
///@version	2.0

///@date	2016.01.09
///@version	2.1

#include <vector>
#include <queue>
using namespace std;

///@note	dfs的迭代版
class Solution_v1 {
public:
	struct Node	//	记录棋盘上的格子节点
	{
		int i_;	//	 行号
		int j_;	//	 列号
		Node(int x, int y) : i_(x), j_(y){};
		Node(){};
	};

	///@brief	将棋盘上的非边缘连续'O'块转换成'X'
	///@param	board	棋盘
	///@return	无
	/* @note	先找到所有和边缘'O'连通的'O'，记录下它们的位置，然后将其他的'O'转化成'X'即可。在找连通路径的时候，用到了DFS的思想，
				使用一个队列来模拟连通的各个'O'，向其中的每个节点四周进行探测，如果是'O'，则入队，并标记下其位置，直到队列为空。
				时间复杂度为O(mn)，空间复杂度为O(mn)。*/
	void solve(vector<vector<char>>& board) {
		if (board.empty())	return;
		int row = board.size();		//	行数
		int col = board[0].size();	//	列数

		queue<Node*> que;	//	DFS队列
		vector<vector<bool>> visited(row, vector<bool>(col, false));	//	标记哪些节点已经被访问过

		for (int i = 0; i != row; i++)
		{	
			for (int j = 0; j != col; j++)
			{
				if (i == 0 || i == row - 1 || j == 0 || j == col - 1)	//	从边缘开始找起
				{
					if (visited[i][j] == false && board[i][j] == 'O')	//	找到起点
					{
						Node *n = new Node(i, j);
						que.push(n);	//	起点入队
						visited[i][j] = true;	//	标记位置

						while (!que.empty())
						{
							Node* tmp = que.front();
							que.pop();
							
							if (tmp->i_ > 0 && board[tmp->i_ - 1][tmp->j_] == 'O' && !visited[tmp->i_ - 1][tmp->j_])	//	向上搜索
							{
								visited[tmp->i_ - 1][tmp->j_] = true;
								Node* up_node = new Node(tmp->i_ - 1, tmp->j_);	
								que.push(up_node);
							}

							if (tmp->i_ < row - 1 && board[tmp->i_ + 1][tmp->j_] == 'O' && !visited[tmp->i_ + 1][tmp->j_])	//	向下搜索
							{
								visited[tmp->i_ + 1][tmp->j_] = true;
								Node* down_node = new Node(tmp->i_ + 1, tmp->j_);	
								que.push(down_node);
							}

							if (tmp->j_ > 0 && board[tmp->i_][tmp->j_ - 1] == 'O' && !visited[tmp->i_][tmp->j_ - 1])	//	向左搜索
							{
								visited[tmp->i_][tmp->j_ - 1] = true;
								Node* left_node = new Node(tmp->i_, tmp->j_ - 1);	
								que.push(left_node);
							}

							if (tmp->j_ < col - 1 && board[tmp->i_][tmp->j_ + 1] == 'O' && !visited[tmp->i_][tmp->j_ + 1])	//	向右搜索
							{
								visited[tmp->i_][tmp->j_ + 1] = true;
								Node* right_node = new Node(tmp->i_, tmp->j_ + 1);	
								que.push(right_node);
							}							
						}
					}
				}
			}
		}

		for (int i = 0; i != row; i++)	//	将剩余的'O'进行转换
		{
			for (int j = 0; j != col; j++)
			{
				if (!visited[i][j] && board[i][j] == 'O')
					board[i][j] = 'X';
			}
		}
		return;
	}
};

///@note	dfs的递归版.从棋盘的四边开始寻找'O'字符，然后dfs递归向上下左右找是否有相邻的'O'，都将它们与改变成'*'，这样能与中间的不与边界
//			相连的'O'区别开。然后再遍历矩阵，找到剩余的'O'，将它们改成'X'，原本的'*'恢复成'O'。
class Solution_v2 {
public:
	void solve(vector<vector<char>>& board) {
		for (int i = 0; i != board.size(); i++)
			for (int j = 0; j != board[i].size(); j++)
			{
				if ((i == 0 || i == board.size()-1 || j == 0 || j == board[i].size()-1) && board[i][j] == 'O')
					dfs(board, i, j);
			}
	
		for (int i = 0; i != board.size(); i++)
			for (int j = 0; j != board[i].size(); j++)
			{
				if (board[i][j] == 'O')	board[i][j] = 'X';
				if (board[i][j] == '*')	board[i][j] = 'O';
			}
	}
private:
	void dfs(vector<vector<char>>& board, int i, int j)
	{
		board[i][j] = '*';
		if (i > 0 && board[i-1][j] == 'O')					dfs(board, i-1, j);
		if (i < board.size()-1 && board[i+1][j] == 'O')		dfs(board, i+1, j);
		if (j > 1 && board[i][j-1] == 'O')					dfs(board, i, j-1);	//	注意：这里是 j > 1 而不是 j > 0，否则会报Runtime error.因为当数据量很大时，栈空间会被消耗光。
		if (j < board[i].size()-1 && board[i][j+1] == 'O')	dfs(board, i, j+1);		
	}
};

class Solution {
public:
	///@brief	将棋盘上的非边缘连续'O'块转换成'X'
	///@param	board	棋盘
	///@return	无
	///@note	1. 深度优先遍历；2. 先从棋盘四个边开始寻找相连的'O'，将其转换为'$'，然后对于中间的不与边相连的'O'，转换为'X'，最后把开始调用dfs
	//			递归计算出来的'$'转换回'O'即可；3. 注意在递归dfs时，列号从j > 1开始判断，否则测试数据会栈溢出。
	void solve(vector<vector<char>>& board) {
		int rows = board.size(), cols = board.empty() ? 0 : board[0].size();
		for (int i = 0; i != rows; i++) {
			for (int j = 0; j != cols; j++) {
				if ((i == 0 || i == rows - 1 ||
					j == 0 || j == cols - 1) && board[i][j] == 'O')
					helper(board, i, j);
			}
		}
		for (int i = 0; i != rows; i++) {
			for (int j = 0; j != cols; j++) {
				if (board[i][j] == 'O')	board[i][j] = 'X';
				if (board[i][j] == '$')	board[i][j] = 'O';
			}
		}
	}

	///@brief	dfs辅助函数
	///@param	board	棋盘
	///@param	i, j	当前元素下标
	void helper(vector<vector<char>>& board, int i, int j) {
		board[i][j] = '$';
		if (i > 0 && board[i - 1][j] == 'O')						helper(board, i - 1, j);
		if (i < board.size() - 1 && board[i + 1][j] == 'O')		helper(board, i + 1, j);
		if (j > 1 && board[i][j - 1] == 'O')						helper(board, i, j - 1);
		if (j < board[i].size() - 1 && board[i][j + 1] == 'O')	helper(board, i, j + 1);
	}
};

int main()
{
	vector<char> line(2, 'O');
	vector<vector<char>> board(2, line);
	
	board.clear();
	line.clear();
 	line.push_back('X');
 	line.push_back('O');
 	line.push_back('X');
 	line.push_back('X');
 	board.push_back(line);
 
 	line.clear();
 	line.push_back('X');
 	line.push_back('X');
 	line.push_back('O');
 	line.push_back('X');
 	board.push_back(line);
 
 	line.clear();
 	line.push_back('X');
 	line.push_back('X');
 	line.push_back('X');
 	line.push_back('X');
 	board.push_back(line);

	board.clear();
	Solution slt;
	slt.solve(board);

	return 0;
}