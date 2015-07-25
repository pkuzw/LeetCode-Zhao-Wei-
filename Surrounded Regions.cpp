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

#include <vector>
#include <queue>
using namespace std;

class Solution {
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

int main()
{
	vector<char> line(2, 'O');
	vector<vector<char>> board(2, line);
	

	line.clear();
// 	line.push_back('X');
// 	line.push_back('O');
// 	line.push_back('O');
// 	line.push_back('X');
// 	board.push_back(line);
// 
// 	line.clear();
// 	line.push_back('X');
// 	line.push_back('X');
// 	line.push_back('O');
// 	line.push_back('X');
// 	board.push_back(line);
// 
// 	line.clear();
// 	line.push_back('O');
// 	line.push_back('X');
// 	line.push_back('X');
// 	line.push_back('X');
// 	board.push_back(line);

	Solution slt;
	slt.solve(board);

	return 0;
}