﻿///@file	Implement Trie (Prefix Tree) 
/*
Implement a trie with insert, search, and startsWith methods.
*/
///@author	zhaowei
///@date	2015.08.03
///@version	1.0

#include <string>

using namespace std;

///@brief	前缀树的节点类
///@note	每一个节点，除了根节点，都有26个子节点，对应26个字母；和一个标志是否到达此处时构成了一个单词的标志位。
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

///@brief	前缀树类
class Trie {
public:
	Trie() {
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

int main()
{
	return 0;
}