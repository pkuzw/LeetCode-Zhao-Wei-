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

#include <string>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
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

int main()
{
	unordered_set<string> dict;
	dict.insert("hot");
	dict.insert("lot");
	dict.insert("dot");
	dict.insert("dog");
	dict.insert("log");

	Solution slt;
	int rslt = slt.ladderLength("hit", "cog", dict);
	return 0;
}
