///@file	Word Ladder
/*
Given two words (beginWord and endWord), and a dictionary, find the length of shortest transformation sequence 

from beginWord to endWord, such that:

Only one letter can be changed at a time
Each intermediate word must exist in the dictionary
For example,

Given:
start = "hit"
end = "cog"
dict = ["hot","dot","dog","lot","log"]
As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Note:
Return 0 if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
*/
///@author	zhaowei
///@date	2015.07.25
///@version	1.0

///@date	2015.08.22
///@version	1.1

///@date	2016.01.09
///@version	1.2

#include <string>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution_v1 {
public:
	///@brief	计算将一个单词转换成另一个单词所用的步数
	///@param	beginWord	起始单词
	///@param	endWord		目标单词
	///@param	wordDict	词典
	///@return	返回从起始单词转换到目标单词的步数
	/* @note	利用BFS的思想解题。将每个单词看做一个节点，起始单词就是根节点，每次改变单词的一个字母，看能否找到该单词，如果能够找到就
				相当于该单词有了孩子，要入队，然后继续向后找，直到找到目标单词。每一层节点相当于把该单词的所有字符逐个替换后的新单词，层
				与层之间靠""隔开。找到新单词后，要在词典中把它删去，以防出现hot->dot->hot的死循环。时间复杂度为O(n)，空间复杂度为O(n)。*/
	int ladderLength(string beginWord, string endWord, unordered_set<string>& wordDict) {
		int steps_cnt = 1;
		queue<string> que;
		que.push(beginWord);
		que.push("");

		while (!que.empty())
		{
			string str = que.front();
			que.pop();

			if (str != "")
			{
				for (int i = 0; i != str.length(); i++)
				{
					char tmp = str[i];
					for (char c = 'a'; c <= 'z'; c++)	//	逐个尝试改变单词的每个字符
					{
						if (tmp == c)	continue;
						str[i] = c;

						if (str == endWord)	return steps_cnt+1;

						if (wordDict.find(str) != wordDict.end())
						{
							que.push(str);
							wordDict.erase(str);	//	防止出现hot->dot->hot的死循环							
						}
					}
					str[i] = tmp;	//	遍历完之后要将单词改回原样
				}
			}
			else
			{
				if (!que.empty())
				{
					que.push("");
					steps_cnt++;
				}
			}
		}
		return 0;	//	如果没有找到能够转换的路径，返回0
	}
};

///@note	BFS.将每个单词看做k叉树的一个节点，相差一个字母的单词是该节点的孩子节点。层与层之间通过特殊字符串隔开。每找到一个后继单词，要
//			在词典中将它删去，以避免出现死循环。
class Solution {
public:
	///@brief	计算将一个单词转换成另一个单词所用的步数
	///@param	beginWord	起始单词
	///@param	endWord		目标单词
	///@param	wordDict	词典
	///@return	返回从起始单词转换到目标单词的步数
	///@note	1. 宽度优先遍历BFS，与二叉树的迭代版宽度优先遍历算法类似，也要使用queue；
	//			2. 将每个单词看做k叉树的一个节点，相差一个字母的单词是该节点的孩子节点；
	//			3. 层与层之间通过特殊字符串隔开；
	//			4. 每找到一个后继单词，要	在词典中将它删去，以避免出现死循环；
	//			5. 时间复杂度为O(nk)，空间复杂度为O(n)。其中n为单词数目，k为单词长度。
	int ladderLength(string beginWord, string endWord, unordered_set<string>& wordDict) {
		queue<string> que;
		int rslt = 1;
		que.push(beginWord);
		que.push("$");
		while (!que.empty()) {
			string word = que.front();
			que.pop();
			if (word != "$") {
				string word_original = word;	//	因为要寻找与word相差一个字符的其余单词，需要改动word，这里进行备份
				for (int i = 0; i != word.size(); i++) {
					for (char j = 'a'; j <= 'z'; j++) {
						if (word[i] != j)	word[i] = j;
						if (word == endWord)	return rslt + 1;
						if (wordDict.find(word) != wordDict.end()) {
							que.push(word);
							wordDict.erase(word);
						}
					}
					word = word_original;
				}
			}
			else {
				if (!que.empty())	que.push("$");
				rslt++;
			}
		}
		return 0;




























// 		if (beginWord == endWord)	return 1;
// 		int cnt = 1;
// 		queue<string> que;
// 		que.push(beginWord);
// 		que.push("");
// 		while (!que.empty())
// 		{
// 			string frt = que.front();
// 			que.pop();
// 			if (frt != "")
// 			{
// 				string tmp = frt;
// 				for (int i = 0; i != frt.size(); i++)
// 				{
// 					for (char j = 'a'; j <= 'z'; j++)
// 					{
// 						if (frt[i] == j)	continue;
// 						frt[i] = j;
// 
// 						if (frt == endWord)	return cnt + 1;
// 						if (wordDict.find(frt) != wordDict.end())
// 						{
// 							wordDict.erase(frt);
// 							que.push(frt);
// 						}
// 					}
// 					frt = tmp;
// 				}
// 			}
// 			else
// 			{
// 				if (!que.empty())
// 				{
// 					que.push("");
// 					cnt++;
// 				}
// 			}
// 		}
// 		return 0;
	}
};

int main()
{
	unordered_set<string> dict;
	dict.insert("hot");
	dict.insert("lot");
	dict.insert("dot");
	dict.insert("dog");
	dict.insert("log");

	Solution slt;
	int rslt = slt.ladderLength("hot", "dog", dict);
	return 0;
}
