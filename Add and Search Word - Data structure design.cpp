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

#include <string>
using namespace std;

///@brief	前缀树的节点类
///@note	每一个节点，除了根节点，都有26个子节点，对应26个字母，另外还有一个标志是否到达此处时构成了一个单词的标志位。
class TrieNode {
public:
	TrieNode* child[26];
	bool isWord;
	// Initialize your data structure here.	
	TrieNode() : isWord(false)
	{
		for (int i = 0; i != 26; i++)
			child[i] = nullptr;
	}
};

///@brief	字典类，实际上就是前缀树类。利用前缀树的属性来存储单词。
class WordDictionary {
public:
	WordDictionary()
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

int main()
{
	WordDictionary* dict = new WordDictionary;
	dict->addWord("mad");
 	dict->addWord("bad");
 	dict->addWord("dad");
	dict->addWord("a");

	bool rslt = dict->search(".");
 	rslt = dict->search("bad");
 	rslt = dict->search(".ad");
 	rslt = dict->search("b..");

	return 0;
}