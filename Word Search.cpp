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
		int m = board.size();	//	矩阵行数

		if (board[0].empty())
		{
			if (word.empty())	return true;
			else	return false;
		}
		int n = board[0].size();	//	矩阵列数

		if (word.empty() && (m != 0 && n != 0))
		{
			return false;
		}

		vector<int> x_indx, y_indx;	//	保存已经匹配的字符在矩阵中的行列号，以便进行回溯

		bool flg = false;
		vector<bool> line;
		for (int i = 0; i != n; i++)
		{
			line.push_back(flg);
		}
		up.push_back(line);	//	初始化向上的标志矩阵
		line.clear();

		flg = true;
		for (int i = 0; i != n; i++)
		{
			line.push_back(flg);
		}
		for (int i = 0; i != m-1; i++)
		{
			up.push_back(line);
			down.push_back(line);
		}		
		line.clear();
		flg = false;
		for (int i = 0; i != n; i++)
		{
			line.push_back(flg);
		}
		down.push_back(line);		//	初始化向下的标志矩阵	
		line.clear();

		line.push_back(flg);
		flg = true;
		for (int i = 0; i != n-1; i++)
		{
			line.push_back(flg);
		}
		for (int i= 0; i != m; i++)
		{
			left.push_back(line);	//	初始化向左的标志矩阵
		}

		line.clear();
		flg = true;
		for (int i = 0; i != n-1; i++)
		{
			line.push_back(flg);
		}
		flg = false;
		line.push_back(flg);
		for (int i= 0; i != m; i++)
		{
			right.push_back(line);	//	初始化向右的标志矩阵
		}
		line.clear();

		int k = 0;	
		while (k != word.length())
		{
			int i = 0;
			int j = 0;
			while (i != m && j != n)
			{
				if (word[k] == board[i][j] && !visited(x_indx, y_indx, i, j))
				{
					x_indx.push_back(i);
					y_indx.push_back(j);
					k++;
					
				}

				//	按照上->右->下->左的顺时针顺序来尝试当前匹配字符的邻居
				if (i > 0 && !visited(x_indx, y_indx, i-1, j))
				{
					if (word[k] == board[i-1][j])
					{
						x_indx.push_back(i-1);
						y_indx.push_back(j);
						i--;
						k++;
					}					
				}
				else if (j < n-1 && !visited(x_indx, y_indx, i, j+1))
				{
					if (word[k] == board[i][j+1])
					{
						x_indx.push_back(i);
						y_indx.push_back(j+1);
						j++;
						k++;
					}	
				}
				else if (i < m-1 && !visited(x_indx, y_indx, i+1, j))
				{
					if (word[k] == board[i+1][j])
					{
						x_indx.push_back(i+1);
						y_indx.push_back(j);
						i++;
						k++;
					}	
				}
				else if (j > 0 && !visited(x_indx, y_indx, i, j-1))
				{
					if (word[k] == board[i][j-1])
					{
						x_indx.push_back(i);
						y_indx.push_back(j-1);
						j--;
						k++;
					}	
				}
				else
				{
 					x_indx.pop_back();
 					y_indx.pop_back();
 					i = x_indx.back();
 					j = y_indx.back();
// 					i = x_indx[x_indx.size()-2];
// 					j = y_indx[y_indx.size()-2];
				}

			}
		}
		
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

	vector<vector<bool>> up;
	vector<vector<bool>> down;
	vector<vector<bool>> left;
	vector<vector<bool>> right;
	
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

	Solution slt;
	string word;
	while (cin >> word)
		cout << slt.exist(board, word) << endl;
	return 0;
}