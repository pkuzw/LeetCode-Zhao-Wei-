///@file	Word Search
/*
Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or
vertically neighboring. The same letter cell may not be used more than once.

For example,
Given board =

[
["ABCE"],
["SFCS"],
["ADEE"]
]
word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.
*/
///@author	zhaowei
///@date	2015.07.14
///@version	1.0

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
	///@brief	判断在二维字符矩阵中是否存在指定单词
	///@param	board	二维字符数组
	///@param	word	单词
	///@return	如果能够通过上下左右相邻的方式找到该单词，则返回true；否则返回false
	///@note	遍历矩阵，通过访问它的上下左右邻居来对目标单词进行匹配。需要两个一位数组来存储已经匹配的字符在矩阵中的行列号，便于后续字符不匹配
	//			时进行回溯。还需要4个m*n的bool型二维数组来存储每一个点能否向相邻元素移动。设矩阵尺寸为m*n，单词长度为k，则算法时间复杂度为O(mnk)，空间复杂度为O(mn)。
	bool exist(vector<vector<char>>& board, string word) {
		if (board.empty())
		{
			if (word.empty())	return true;
			else	return false;
		}
		height = board.size();	//	矩阵行数

		if (board[0].empty())
		{
			if (word.empty())	return true;
			else	return false;
		}
		width = board[0].size();	//	矩阵列数

		if (word.empty() && (height != 0 && width != 0))
		{
			return false;
		}

		vector<int> x_indx, y_indx;	//	保存已经匹配的字符在矩阵中的行列号，以便进行回溯

		for (int i = 0; i != height; i++)
		{
			for (int j = 0; j != width; j++)
			{
				resetUp();	//	每次更换匹配起点都要重置方向标志矩阵
				resetDown();
				resetLeft();
				resetRight();
				x_indx.clear();	//	同时重置行列号栈
				y_indx.clear();
				int k = 0;	//	标记单词的下标
				int u = i, v = j;	
				while (k < word.length() && k >= 0)	//	以board[i][j]为起点进行匹配
				{
					if (word[k] == board[u][v] && !visited(x_indx, y_indx, u, v))
					{	
						//	按照上->右->下->左的顺时针顺序来尝试当前匹配字符的邻居
						if (u > 0 && !visited(x_indx, y_indx, u-1, v) && up[u][v])
						{
							x_indx.push_back(u);
							y_indx.push_back(v);
							k++;

							if (k == word.length())	return true;

							if (word[k] == board[u-1][v])
								u--;								
							else
							{
								up[u][v] = false;
								if (v < width-1)
									v++;
								else if (u < height-1)
									u++;
								else if (v > 0)
									v--;
							}
							continue;
						}
						if (v < width-1 && !visited(x_indx, y_indx, u, v+1) && right[u][v])
						{
							x_indx.push_back(u);
							y_indx.push_back(v);
							k++;

							if (k == word.length())	return true;

							if (word[k] == board[u][v+1])
								v++;								
							else
							{
								right[u][v] = false;
								if (u < height-1)
									u++;
								else if (v > 0)
									v--;
							}
							continue;
						}
						if (u < height-1 && !visited(x_indx, y_indx, u+1, v) && down[u][v])
						{
							x_indx.push_back(u);
							y_indx.push_back(v);
							k++;

							if (k == word.length())	return true;

							if (word[k] == board[u+1][v])
								u++;
							else
							{
								down[u][v] = false;
								if (v > 0)
									v--;
							}
							continue;
						}
						if (v > 0 && !visited(x_indx, y_indx, u, v-1) && left[u][v])
						{
							x_indx.push_back(u);
							y_indx.push_back(v);
							k++;

							if (k == word.length())	return true;

							if (word[k] == board[u][v-1])
								v--;
							else
								left[u][v] = false;
							continue;
						}									

						if (up[u][v] || down[u][v] || left[u][v] || right[u][v])
						{
							if (x_indx.empty() && y_indx.empty())	break;
							u = x_indx.back();
							v = y_indx.back();	
							x_indx.pop_back();
							y_indx.pop_back();
							k--;
						}
						else 
							break;
					}
					else
					{
						if (x_indx.empty() && y_indx.empty())	break;

						u = x_indx.back();
						v = y_indx.back();	
						x_indx.pop_back();
						y_indx.pop_back();
						k--;
						if (!x_indx.empty() && !y_indx.empty())
						{
							if (u - x_indx.back() == -1)	
								up[x_indx[x_indx.size()-1]][y_indx[y_indx.size()-1]] = false;
							else if (u - x_indx.back() == 1)
								down[x_indx[x_indx.size()-1]][y_indx[y_indx.size()-1]] = false;
							else if (v - y_indx.back() == -1)	
								left[x_indx[x_indx.size()-1]][y_indx[y_indx.size()-1]] = false;
							else if (v - y_indx.back() == 1)	
								right[x_indx[x_indx.size()-1]][y_indx[y_indx.size()-1]] = false;
						}						
					}
				}				
			}
		}
		return false;
	}

private:
	///@brief	判定在行列号的栈中是否存在指定的点
	///@param	x_indx	行号栈
	///@param	y_indx	列号栈
	///@return	如果存在，则返回true；否则返回false
	bool visited(vector<int>& x_indx, vector<int>& y_indx, const int x, const int y)
	{
		for (int i = 0; i != x_indx.size(); i++)
		{
			if (x_indx[i] == x && y_indx[i] == y)
			{
				return true;
			}
		}
		return false;
	}

	///@brief	重置向上的标志矩阵
	void resetUp()
	{
		up.clear();
		bool flg = false;
		vector<bool> line;
		for (int i = 0; i != width; i++)
		{
			line.push_back(flg);
		}
		up.push_back(line);	
		line.clear();

		flg = true;
		for (int i = 0; i != width; i++)
		{
			line.push_back(flg);
		}
		for (int i = 0; i != height-1; i++)
		{
			up.push_back(line);
		}
		return;
	}

	///@brief	重置向下的标志矩阵
	void resetDown()
	{
		down.clear();
		bool flg = true;
		vector<bool> line;
		for (int i = 0; i != width; i++)
		{
			line.push_back(flg);
		}
		for (int i = 0; i != height-1; i++)
		{
			down.push_back(line);
		}
		line.clear();

		flg = false;
		for (int i = 0; i != width; i++)
		{
			line.push_back(flg);
		}
		down.push_back(line);	
		return;
	}

	///@brief	重置向左的标志矩阵
	void resetLeft()
	{
		left.clear();
		vector<bool> line;
		bool flg = false;
		line.push_back(flg);
		flg = true;
		for (int i = 0; i != width-1; i++)
		{
			line.push_back(flg);
		}
		for (int i= 0; i != height; i++)
		{
			left.push_back(line);	//	初始化向左的标志矩阵
		}
		return;
	}

	///@brief	重置向右的标志矩阵
	void resetRight()
	{
		right.clear();
		vector<bool> line;
		bool flg = true;
		for (int i = 0; i != width-1; i++)
		{
			line.push_back(flg);
		}
		flg = false;
		line.push_back(flg);
		for (int i= 0; i != height; i++)
		{
			right.push_back(line);	//	初始化向右的标志矩阵
		}
		return;
	}

	//	方位标志矩阵，用来表示在点board[i][j]处能否向各个方向移动
	vector<vector<bool>> up;
	vector<vector<bool>> down;
	vector<vector<bool>> left;
	vector<vector<bool>> right;
	
	int width;	//	矩阵的宽
	int height;	//	矩阵的高
};

int main()
{
	vector<vector<char>> board;
	vector<char> cvec;
	cvec.push_back('A');
	cvec.push_back('B');
	cvec.push_back('C');
	cvec.push_back('E');
	board.push_back(cvec);
	cvec.clear();

	cvec.push_back('S');
	cvec.push_back('F');
	cvec.push_back('C');
	cvec.push_back('S');
	board.push_back(cvec);
	cvec.clear();

	cvec.push_back('A');
	cvec.push_back('D');
	cvec.push_back('E');
	cvec.push_back('E');
	board.push_back(cvec);
	cvec.clear();

	//ESECCEDFBASA
	Solution slt;
	string word;
	while (cin >> word)
		cout << slt.exist(board, word) << endl;
	return 0;
}