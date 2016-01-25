///@file	Implement Trie (Prefix Tree) 
/*
Implement a trie with insert, search, and startsWith methods.
*/
///@author	zhaowei
///@date	2015.08.03
///@version	1.0

///@date	2015.08.11
///@version	2.0

///@date	2016.01.25
///@version	1.1

#include <string>

using namespace std;

///@brief	前缀树的节点类
///@note	每一个节点，除了根节点，都有26个子节点，对应26个字母；和一个标志是否到达此处时构成了一个单词的标志位。
class TrieNode {
public:
	TrieNode* child[26];
	bool isWord;

	TrieNode() : isWord(false) {
		for (int i = 0; i != 26; i++)
			child[i] = nullptr;
	}
};

///@brief	前缀树类
 class Trie_v1 {
 public:
 	Trie_v1() {
 		root = new TrieNode();
 	}
 
 	// Inserts a word into the trie.
 	void insert(string word) {
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
 
 	// Returns if the word is in the trie.
 	bool search(string word) {
 		TrieNode* p = root;
 		for (int i = 0; i != word.size(); i++)
 		{
 			int ch = word[i] - 'a';
 			if (!p->child[ch])	return false;
 			p = p->child[ch];
 		}
 		return p->isWord;
 	}
 
 	// Returns if there is any word in the trie
 	// that starts with the given prefix.
 	bool startsWith(string prefix) {
 		TrieNode* p = root;
 		for (int i = 0; i != prefix.size(); i++)
 		{
 			int ch = prefix[i] - 'a';
 			if (!p->child[ch])	return false;
 			p = p->child[ch];
 		}
 		return true;
 	}
 
 private:
 	TrieNode* root;
 };

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");

///@note	递归版实现
class Trie_v2 {
public:
	Trie_v2() {
		root = new TrieNode();
	}

	// Inserts a word into the trie.
	void insert(string word) {
		TrieNode* p = root;
		for (int i = 0; i != word.size(); i++)
		{
			int ch = word[i] - 'a';
			if (p->child[ch] == nullptr)
				p->child[ch] = new TrieNode();
			p = p->child[ch];
		}
		p->isWord = true;
	}

	// Returns if the word is in the trie.
	bool search(string word) {
		TrieNode* p = root;
		return searchRecur(word, 0, p);
	}

	bool searchRecur(const string& word, int i, TrieNode* p)
	{
		if (i == word.size())	return p->isWord;

		int ch = word[i] - 'a';
		return (p->child[ch] && searchRecur(word, i+1, p->child[ch]));
	}

	// Returns if there is any word in the trie
	// that starts with the given prefix.
	bool startsWith(string prefix) {
		TrieNode* p = root;
		return prefixRecur(prefix, 0, p);
	}

	bool prefixRecur(const string& prefix, int i, TrieNode* p)
	{
		if (i == prefix.size())
		{
			if (p->isWord)	return true;
			for (int i = 0; i != 26; i++)
			{
				if (p->child[i])		return true;
			}
			return false;
		}

		int ch = prefix[i] - 'a';
		return (p->child[ch] && prefixRecur(prefix, i+1, p->child[ch]));
	}

private:
	TrieNode* root;
};

class Trie {
public:
	Trie() {
		root = new TrieNode();
	}

	// Inserts a word into the trie.
	void insert(string word) {
		TrieNode* indx = root;
		for (int i = 0; i != word.size(); i++) {
			int cur = word[i] - 'a';
			if (!indx->child[cur])		indx->child[cur] = new TrieNode();
			indx = indx->child[cur];
		}
		indx->isWord = true;
	}

	// Returns if the word is in the trie.
	bool search(string word) {
		TrieNode* indx = root;
		for (int i = 0; i != word.size(); i++) {
			int cur = word[i] - 'a';
			if (!indx->child[cur])	return false;
			indx = indx->child[cur];
		}
		return indx->isWord;
	}

	// Returns if there is any word in the trie
	// that starts with the given prefix.
	bool startsWith(string prefix) {
		TrieNode* indx = root;
		for (int i = 0; i != prefix.size(); i++) {
			int cur = prefix[i] - 'a';
			if (!indx->child[cur])	return false;
			indx = indx->child[cur];
		}
		return true;
	}

private:
	TrieNode* root;
};

int main() {
	return 0;
}