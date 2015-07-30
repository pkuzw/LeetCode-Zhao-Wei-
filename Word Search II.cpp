///@file	Word Search II
/*
Given a 2D board and a list of words from the dictionary, find all words in the board.

Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

For example,
Given words = ["oath","pea","eat","rain"] and board =

[
['o','a','a','n'],
['e','t','a','e'],
['i','h','k','r'],
['i','f','l','v']
]
Return ["eat","oath"].
*/
///@author	zhaowei
///@date	2015.07.30
///@version	1.0

#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
	///@brief	在二维矩阵中找到所有可能的词典中的单词
	///@param	board	二维字符矩阵
	///@param	words	词典
	///@return	返回在二维矩阵中存才的单词
	/* @note	因为在之前"Word Search"中有算法判断一个单词是否在矩阵中，那么遍历一遍词典，先去掉其中可能重复的单词，然后
				对于其中每一个可能的单词在矩阵中找一遍就行。OJ报TLE*/
	vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
		vector<string> rslt;
		unordered_set<string> hash_table;
		for (int i = 0; i != words.size(); i++)	//	去除词典中的重复单词
		{
			if (hash_table.find(words[i]) == hash_table.end())
				hash_table.insert(words[i]);			
		}
		words.clear();
		for (unordered_set<string>::iterator i = hash_table.begin(); i != hash_table.end(); i++)
			words.push_back(*i);

		for (int i = 0; i != words.size(); i++)
		{
			if (exist(board, words[i]))	rslt.push_back(words[i]);
		}
		return rslt;
	}

private:
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

	int width;	//	矩阵的宽
	int height;	//	矩阵的高

};

int main()
{
	/*
	For example,
	Given words = ["oath","pea","eat","rain"] and board =

	[
	['o','a','a','n'],
	['e','t','a','e'],
	['i','h','k','r'],
	['i','f','l','v']
	]
	*/
	vector<vector<char>> board;
	vector<char> cvec;
	cvec.push_back('o');
	cvec.push_back('a');
	cvec.push_back('a');
	cvec.push_back('n');
	board.push_back(cvec);
	cvec.clear();

	cvec.push_back('e');
	cvec.push_back('t');
	cvec.push_back('a');
	cvec.push_back('e');
	board.push_back(cvec);
	cvec.clear();

	cvec.push_back('i');
	cvec.push_back('h');
	cvec.push_back('k');
	cvec.push_back('r');
	board.push_back(cvec);
	cvec.clear();

	cvec.push_back('i');
	cvec.push_back('f');
	cvec.push_back('l');
	cvec.push_back('v');
	board.push_back(cvec);
	cvec.clear();

	vector<string> words;
	words.push_back("oath");
	words.push_back("pea");
	words.push_back("eat");
	words.push_back("rain");


	words.push_back("pea");
	words.push_back("eat");

	words.push_back("pea");
	words.push_back("eat");

	words.push_back("pea");
	words.push_back("eat");

	Solution slt;
	vector<string> rslt = slt.findWords(board, words);
	
	return 0;
}