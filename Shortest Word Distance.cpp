///@file	Shortest Word Distance
/*
Given a list of words and two words word1 and word2, return the shortest distance between these two words in the list.

For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].

Given word1 = “coding”, word2 = “practice”, return 3.
Given word1 = "makes", word2 = "coding", return 1.

Note:
You may assume that word1 does not equal to word2, and word1 and word2 are both in the list.
*/
///@author	zhaowei
///@date	2015.10.19
///@version	1.0

///@date	2016.02.08
///@version	1.1

#include <vector>
#include <string>
using namespace std;

class Solution {
public:
	///@brief	计算两个单词在数组内的距离
	///@param	words	数组
	///@param	word1, word2	单词
	///@return	返回两个单词的距离
	///@note	枚举法：遍历数组，在每一个word1的前后计算出第一个word2到它的距离，然后找出最小值。时间复杂度为O(n^2)，空间复杂度为O(n)。
	int shortestDistance(vector<string>& words, string word1, string word2) {
		if (words.empty())	return 0;
		vector<int> dis;
		for (int i = 0; i != words.size(); i++) {
			if (words[i] == word1) {
				int after_w1 = 0, before_w1 = 0;
				for (int j = i; j < words.size(); j++) {
					if (words[j] == word2) {
						after_w1 = j - i;break;
					}
				}
				for (int j = i; j >= 0; j--) {
					if (words[j] == word2) {
						before_w1 = i - j;break;
					}
				}
				if (before_w1 && after_w1)			dis.push_back(min(after_w1, before_w1));
				else if (before_w1 && !after_w1)	dis.push_back(before_w1);
				else if (!before_w1 && after_w1)	dis.push_back(after_w1);
			}
		}
		int rslt = INT_MAX;
		for (int i = 0; i != dis.size(); i++)
			rslt = min(dis[i], rslt);
		return rslt;
	}
};

int main() {
	vector<string> words;	
	words.push_back("practice");
	words.push_back("makes");
	words.push_back("perfect");
	words.push_back("coding");
	words.push_back("practice");
	Solution slt;
	int rslt = slt.shortestDistance(words, "practice", "coding");
	rslt = slt.shortestDistance(words, "makes", "coding");
	return 0;
}