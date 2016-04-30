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
///@date	2015.07.18
///@version	1.2

///@date	2015.08.26
///@version	2.0

///@date	2015.12.07
///@version	2.1

///@date	2016.04.30
///@version	2.2

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution_v1
{
public:
	///@brief	判断在二维字符矩阵中是否存在指定单词
	///@param	board	二维字符数组
	///@param	word	单词
	///@return	如果能够通过上下左右相邻的方式找到该单词，则返回true；否则返回false
	///@note	遍历矩阵，通过访问它的上下左右邻居来对目标单词进行匹配。需要两个一维数组来存储已经匹配的字符在矩阵中的行列号，
	//			便于后续字符不匹配时进行回溯。还需要4个m*n的bool型二维数组来存储每一个点能否向相邻元素移动。设矩阵尺寸为m*n，
	//			单词长度为k，则算法时间复杂度为O(mnk)，空间复杂度为O(mn)。OJ报TLE。
	bool exist_tle(vector<vector<char>>& board, string word) {
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
					if (word[k] == board[u][v])	//如果匹配则进行四周的探索
					{
						x_indx.push_back(u);	//	将匹配字符的行列号入栈
						y_indx.push_back(v);
						k++;	
						if (up[u][v])
						{						
							u--;
							down[u][v] = false;	//	其上一个元素则不可再次到达
						}
						else if (right[u][v])
						{						
							v++;
							left[u][v] = false;	//	同上
						}
						else if (down[u][v])
						{						
							u++;
							up[u][v] = false;	//	同上
						}
						else if (left[u][v])
						{
							v--;
							right[u][v] = false;//	同上
						}						
						else
						{
							if (!x_indx.empty() && !y_indx.empty())	//	回溯并将这条路堵死，置为false
							{
								if (u - x_indx.back() == 1 && v - y_indx.back() == 0)
									down[u-1][v] = false;
								else if (u - x_indx.back() == -1 && v - y_indx.back() == 0)
									up[u+1][v] = false;
								else if (u - x_indx.back() == 0 && v - y_indx.back() == 1)
									right[u][v-1] = false;
								else if (u - x_indx.back() == 0 && v - y_indx.back() == -1)
									left[u][v+1] = false;
								else if (u == x_indx.back() && v == y_indx.back())
								{
									x_indx.pop_back();
									y_indx.pop_back();
									k--;
									if (x_indx.empty() && y_indx.empty())
										break;							

									if (u - x_indx.back() == 1 && v - y_indx.back() == 0)	//	将这条路堵死，置为false
										down[u-1][v] = false;
									else if (u - x_indx.back() == -1 && v - y_indx.back() == 0)
										up[u+1][v] = false;
									else if (u - x_indx.back() == 0 && v - y_indx.back() == 1)
										right[u][v-1] = false;
									else if (u - x_indx.back() == 0 && v - y_indx.back() == -1)
										left[u][v+1] = false;									
								}
								u = x_indx.back();
								v = y_indx.back();
								x_indx.pop_back();
								y_indx.pop_back();
								k--;
							}	
							else
								break;
						}
					}
					else
					{
						if (!x_indx.empty() && !y_indx.empty())
						{
							if (u - x_indx.back() == 1 && v - y_indx.back() == 0)
								down[u-1][v] = false;
							else if (u - x_indx.back() == -1 && v - y_indx.back() == 0)
								up[u+1][v] = false;
							else if (u - x_indx.back() == 0 && v - y_indx.back() == 1)
								right[u][v-1] = false;
							else if (u - x_indx.back() == 0 && v - y_indx.back() == -1)
								left[u][v+1] = false;
							u = x_indx.back();
							v = y_indx.back();
							x_indx.pop_back();
							y_indx.pop_back();
							k--;
						}	
						else
							break;
					}									
				}
				if (k == word.length())
				{
					return true;
				}
			}
		}
		return false;
	}

	///@brief	判断在二维字符矩阵中是否存在指定单词
	///@param	board	二维字符数组
	///@param	word	单词
	///@return	如果能够通过上下左右相邻的方式找到该单词，则返回true；否则返回false
	///@note	遍历二维矩阵，找到能够跟首字母匹配的元素作为起始下标，然后通过深度搜索来遍历上下左右四个方向。对于能够匹配的字符可以通过
	//			临时改变为其他字符来避免再次访问，在返回前要改回去。
	//			时间复杂度为O(mnk)，空间复杂度为O(1)。
	bool exist(vector<vector<char>> &board, string word)
	{
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

		for (int i = 0; i != height; i++)
		{
			for (int j = 0; j != width; j++)
			{
				if (board[i][j] == word[0] && dfs(board, i, j, word, 0))
				{
					return true;
				}
			}
		}
		return false;
	}

private:
	///@brief	深度搜索可能的方向
	///@param	board	二维字符矩阵
	///@param	i	行号
	///@param	j	列号
	///@param	word	待匹配的字符串
	///@param	indx	待匹配的字符下标
	///@return	如果能够找到匹配的字符串，则返回true；否则返回false
	///@note	深度搜索的递归实现。依次向上下左右四个方向进行搜索尝试，直到到达矩阵边界或者无法匹配为止。每次把已经尝试过的位置设置为
	//			其他非字母符号，比如"@"
	bool dfs(vector<vector<char>> &board, const int i, const int j, string word, int indx)
	{
		if (indx == word.length()-1)
		{
			return true;
		}
		const char tmp = board[i][j];
		board[i][j] = '@';

		//	向上搜索
		if (i-1 >= 0 && board[i-1][j] == word[indx+1])	//	上面的相邻元素能够与下一个字符匹配
		{
			if(dfs(board, i-1, j, word, indx+1))
				return true;
		}
		//	向右搜索
		if (j+1 < width && board[i][j+1] == word[indx+1])	//	这里不能使用else if，否则就没办法依次判定上下左右能否匹配了
		{
			if (dfs(board, i, j+1, word, indx+1))
				return true;
		}
		//	向下搜索
		if (i+1 < height && board[i+1][j] == word[indx+1])//	下面的相邻元素能够与下一个字符匹配
		{
			if (dfs(board, i+1, j, word, indx+1))
				return true;
		}
		//	向左搜索
		if (j-1 >= 0 && board[i][j-1] == word[indx+1])//	左面的相邻元素能够与下一个字符匹配
		{
			if (dfs(board, i, j-1, word, indx+1))
				return true;
		}
		
		board[i][j] = tmp;
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

///@note	dfs
class Solution_v2 {
public:
	///@brief	在矩阵中匹配字符串
	///@param	board	矩阵
	///@param	word	字符串
	///@return	如果能够找到相应字符串，返回true；否则返回false
	///@note	1. 深度优先遍历：设置一个标记矩阵用来标记矩阵中某个元素是否已经被访问过，然后从左上角开始逐一进行深度优先遍历；
	//			2. 时间复杂度为O(mnk)，空间复杂度为O(mn)，其中m和n为矩阵的边长，k为字符串长度。
	bool exist(vector<vector<char>>& board, string word) {
		if (board.empty() && !word.empty())	return false;
		if (word.empty())	return true;
		int m = board.size();
		int n = board[0].size();
		vector<vector<bool>> visit(m, vector<bool>(n, false));
		for (int i = 0; i != m; i++) {
			for (int j = 0; j != n; j++) {
				if (dfs(board, word, visit, i, j, 0))	return true;
			}
		}
		return false;
	}

private:
	///@brief	深度优先遍历矩阵
	///@param	board	二维矩阵
	///@param	word	字符串
	///@param	visited	标识矩阵
	///@param	i,j		元素坐标
	///@param	k		字符在字符串中下标
	///@param	如果能够找到该字符串则返回true；否则返回false。
	bool dfs(vector<vector<char>>& board, string& word, vector<vector<bool>>& visited, int i, int j, int k) {
		if (k == word.size())	return true;
		if (!visited[i][j] && board[i][j] == word[k]) {
			visited[i][j] = true;
			k++;
			if (i > 0 && dfs(board, word, visited, i - 1, j, k))		return true;
			if (i < board.size() - 1 && dfs(board, word, visited, i + 1, j, k))	return true;
			if (j > 0 && dfs(board, word, visited, i, j - 1, k))		return true;
			if (j < board[0].size() - 1 && dfs(board, word, visited, i, j + 1, k))	return true;
			visited[i][j] = false;
		}
		return k == word.size() ? true : false;	//	对于只有一个元素的字符串，在经过上一个条件语句的判断后，到这里就可以通过这个三元符号得出结果。
	}
};

class Solution {
public:
	bool exist(vector<vector<char>>& board, string word) {
		if (board.empty() || board[0].empty())	return false;
		if (word.empty())	return true;
		int row = board.size(), col = board[0].size();
		vector<vector<bool>> visited(row, vector<bool>(col, false));
		for (int i = 0; i != row; i++)
			for (int j = 0; j != col; j++)
				if (dfs(board, word, visited, i, j, 0))	return true;
		return false;
	}

	bool dfs(vector<vector<char>>& board, string& word, vector<vector<bool>>& visited, int i, int j, int k) {
		if (k == word.size())	return true;
		if (!visited[i][j] && word[k] == board[i][j]) {
			visited[i][j] = true;
			k++;
			if (i > 0 && dfs(board, word, visited, i - 1, j, k))		return true;
			if (i < board.size() - 1 && dfs(board, word, visited, i + 1, j, k))	return true;
			if (j > 0 && dfs(board, word, visited, i, j - 1, k))		return true;
			if (j < board[0].size() - 1 && dfs(board, word, visited, i, j + 1, k))	return true;			
			visited[i][j] = false;
		}
		return k == word.size() ? true : false;
	}
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

	//ESECCEDFBASA	true
	//ASFBCCED	true

	Solution slt;
	string word("SEE");
	bool rslt = slt.exist(board, word);
	return 0;
}