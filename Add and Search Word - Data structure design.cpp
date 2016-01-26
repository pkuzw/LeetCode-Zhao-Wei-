///@file	Add and Search Word - Data structure design
/*
Design a data structure that supports the following two operations:

void addWord(word)
bool search(word)
search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . means it can represent any one letter.

For example:

addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
Note:
You may assume that all words are consist of lowercase letters a-z.
*/
///@author	zhaowei
///@date	2015.08.03
///@version	1.0

///@date	2015.08.10
///@version	1.1

///@date	2016.01.26
///@version	1.2

///@note	What is iterative implementatation?

#include <string>
#include <stack>
using namespace std;

///@brief	前缀树的节点类
///@note	每一个节点，除了根节点，都有26个子节点，对应26个字母，另外还有一个标志是否到达此处时构成了一个单词的标志位。
class TrieNode {
public:
	bool isWord;
	TrieNode* child[26];

	TrieNode () : isWord(false)
	{
		for (int i = 0; i != 26; i++)
			child[i] = nullptr;
	}
};

///@brief	字典类，实际上就是前缀树类。利用前缀树的属性来存储单词。
class WordDictionary_v1 {
public:
	WordDictionary_v1()
	{
		root = new TrieNode;
	}
	// Adds a word into the data structure.
	void addWord(string word) {
		TrieNode* p = root;
		for (int i = 0; i != word.size(); i++)
		{
			int ch = word[i] - 'a';
			if (!p->child[ch])	
				p->child[ch] = new TrieNode();
			p = p->child[ch];
		}
		p->isWord = true;
	}

	// Returns if the word is in the data structure. A word could
	// contain the dot character '.' to represent any one letter.
	bool search(string word) {
		return searchRecur(word, root, 0);
	}

	// 递归的查找通配符所匹配的字符串
	bool searchRecur(string word, TrieNode* p, int i)
	{
		if (i == word.size())	return p->isWord;

		if (word[i] == '.')
		{
			for (int j = 0; j != 26; j++)
			{
				if (p->child[j] && searchRecur(word, p->child[j], i+1))	//	逐个尝试子节点
					return true;
			}			
			return false;
		}
		else
		{
			int ch = word[i] - 'a';
			return (p->child[ch] && searchRecur(word, p->child[ch], i+1));				
		}
	}
private:
	TrieNode* root;
};

// Your WordDictionary object will be instantiated and called as such:
// WordDictionary wordDictionary;
// wordDictionary.addWord("word");
// wordDictionary.search("pattern");

class WordDictionary {
public:
	// Constructor
	WordDictionary () {
		root = new TrieNode();
	}

	// Adds a word into the data structure.
	void addWord(string word) {
		TrieNode* indx = root;
		for (int i = 0; i != word.size(); i++) {
			int cur = word[i] - 'a';
			if (!indx->child[cur])	indx->child[cur] = new TrieNode();
			indx = indx->child[cur];
		}
		indx->isWord = true;
	}

	// Returns if the word is in the data structure. A word could
	// contain the dot character '.' to represent any one letter.
	bool search(string word) {
		return dfs(word, root, 0);
	}

	///@brief	dfs辅助递归函数
	///@param	word	字符串
	///@param	node	当前节点
	///@param	i		当前字符的下标
	///@return	如果能够找到该字符串，返回true；否则返回false
	bool dfs(string word, TrieNode* node, int i) {
		if (i == word.size())	return node->isWord;	
		if (word[i] == '.') {
			for (int j = 0; j != 26; j++)
				if (node->child[j] && dfs(word, node->child[j], i + 1))	return true;
			return false;
		}
		else {
			int cur = word[i] - 'a';
			return node->child[cur] && dfs(word, node->child[cur], i + 1);
		}		
	}

private:
	TrieNode* root;
};

int main()
{
	bool rslt = false;
	WordDictionary* dict = new WordDictionary;
	dict->addWord("a");
 	dict->addWord("a");
	rslt = dict->search(".");
 	rslt = dict->search("a");
	rslt = dict->search("aa");
	rslt = dict->search("a");
	rslt = dict->search(".a");
	rslt = dict->search("a.");
	return 0;
}