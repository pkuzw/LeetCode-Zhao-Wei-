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

///@date	2015.08.11
///@version	2.0

#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution_v1 {
public:
	///@brief	前缀树节点前缀树的每个节点下面有26个子节点，相当于26个字母
	struct TrieNode {
		TrieNode *child[26];
		string str;
		TrieNode() : str("") 
		{
			for (int a = 0; a != 26; a++) 
				child[a] = NULL;
		}
	};

	///@brief	前缀树
	struct Trie {
		TrieNode *root;

		Trie() : root(new TrieNode()) {}

		///@brief	在前缀树中插入一个节点
		void insert(string s) {
			TrieNode *p = root;
			for (int a = 0; a < s.length(); a++) 
			{
				int i = s[a] - 'a';
				if (!p->child[i]) p->child[i] = new TrieNode();
				p = p->child[i];
			}
			p->str = s;
		}
	};

	///@brief	利用前缀树提高算法的效率。
	vector<string> findWords(vector<vector<char> >& board, vector<string>& words) {
		vector<string> res;
		if (words.empty() || board.empty() || board[0].empty()) return res;
		vector<vector<bool> > visit(board.size(), vector<bool>(board[0].size(), false));
		Trie T;
		for (int a = 0; a != words.size(); a++)
			T.insert(words[a]);

		for (int i = 0; i < board.size(); ++i) {
			for (int j = 0; j < board[i].size(); ++j) {
				if (T.root->child[board[i][j] - 'a']) {
					search(board, T.root->child[board[i][j] - 'a'], i, j, visit, res);
				}
			}
		}
		return res;
	}

private:
	void search(vector<vector<char> > &board, TrieNode *p, int i, int j, vector<vector<bool> > &visit, vector<string> &res) { 
		if (!p->str.empty()) {
			res.push_back(p->str);
			p->str.clear();	//	词典中的单词如果找到了，就不必再找。将前缀树中的单词删除
		}
		int d[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
		visit[i][j] = true;
		for (int a = 0; a < 4; a++) {
			int nx = d[a][0] + i, ny = d[a][1] + j;
			if (nx >= 0 && nx < board.size() && ny >= 0 && ny < board[0].size() && !visit[nx][ny] && p->child[board[nx][ny] - 'a']) {
				search(board, p->child[board[nx][ny] - 'a'], nx, ny, visit, res);
			}
		}
		visit[i][j] = false;
	}
};

class Solution_tle {
public:
	///@brief	在二维矩阵中找到所有可能的词典中的单词
	///@param	board	二维字符矩阵
	///@param	words	词典
	///@return	返回在二维矩阵中存才的单词
	/* @note	因为在之前"Word Search"中有算法判断一个单词是否在矩阵中，那么遍历一遍词典，先去掉其中可能重复的单词，然后
				对于其中每一个可能的单词在矩阵中找一遍就行。OJ报TLE*/
	vector<string> findWords_Tle(vector<vector<char>>& board, vector<string>& words) {
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

/*
1. 用trie来保存词典；用深搜来查找单词；
2. trieNode的isWord标志位改成了word，直接标出来到这个节点有哪个单词，便于压入结果数组；
3. 在深搜时，要注意保证数组的下标都是有效值。
*/
class TrieNode {
public:
	TrieNode* child[26];
	string word;

	///@brief	constructor
	TrieNode ()
	{
		for (int i = 0; i != 26; i++)
			child[i] = nullptr;
	}
};

class Trie {
public:
	///@brief	constructor
	Trie ()
	{
		root = new TrieNode();
	}

	///@brief	insert one word
	void insert(string word)
	{
		TrieNode* p = root;
		for (int i = 0; i != word.size(); i++)
		{
			int ch = word[i] - 'a';
			if (!p->child[ch])
				p->child[ch] = new TrieNode();
			p = p->child[ch];
		}
		p->word = word;
	}	

	TrieNode* root;
};

class Solution {
public:
	vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
		vector<string> rslt;
		if (board.empty() || board[0].empty() || words.empty())	return rslt;
		row = board.size();
		col = board[0].size();

		vector<vector<bool>> visited(row, vector<bool>(col, false));

		Trie* trie = new Trie;
		for (int i = 0; i != words.size(); i++)
			trie->insert(words[i]);
		
		for (int i = 0; i != row; i++)
		{
			for (int j = 0; j != col; j++)
			{
				TrieNode* p = trie->root;
				if (p->child[board[i][j] - 'a'])	
					dfs(board, i, j, p->child[board[i][j] - 'a'], rslt, visited);
			}
		}
		return rslt;
	}
private:
	int row, col;

	void dfs(vector<vector<char>>& board, int i, int j, TrieNode* p, vector<string>& rslt, vector<vector<bool>>& visited)
	{
		if (i < 0 || i >= row)		return;
		if (j < 0 || j >= col)		return;
		if (visited[i][j] || !p)	return;

		if (!p->word.empty())
		{
			rslt.push_back(p->word);
			p->word.clear();
		}
		
		visited[i][j] = true;
		//	凡是对于数组的访问，一定要保证下标是有效的
		if (i + 1 < row)	dfs(board, i + 1, j, p->child[board[i + 1][j] - 'a'], rslt, visited);
		if (i - 1 >= 0)		dfs(board, i - 1, j, p->child[board[i - 1][j] - 'a'], rslt, visited);
		if (j + 1 < col)	dfs(board, i, j + 1, p->child[board[i][j + 1] - 'a'], rslt, visited);
		if (j - 1 >= 0)		dfs(board, i, j - 1, p->child[board[i][j - 1] - 'a'], rslt, visited);
		visited[i][j] = false;	// 因为不同的单词可以利用多次同一个字母，所以在递归后将visited标志位重置
	}
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
// 
// 
// 	words.push_back("pea");
// 	words.push_back("eat");
// 
// 	words.push_back("pea");
// 	words.push_back("eat");
// 
// 	words.push_back("pea");
// 	words.push_back("eat");

	Solution slt;
	vector<string> rslt = slt.findWords(board, words);
	
	return 0;
}