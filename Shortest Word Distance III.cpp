///@file	Shortest Word Distance III
///@author	zhaowei
///@date	2016.01.09
///@version	1.0

///@date    2016.02.26
///@version 1.1

#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution_v1 {
public:
	///@brief	计算一组单词中两个单词的最短距离，单词有可能重复，也可能相同
	///@param	words	词典
	///@param	word1, word2	两个单词
	///@return	返回两个单词的最短距离
	///@note	1. hash table；2. 分成两种情况处理，一种是单词相同，直接在哈希表里的同一项中查找最小间隔，另一种是单词不同，与"Shortest Word Distance II"的解法一样；
	//			3. 时间复杂度为O(k^2)，空间复杂度为O(n)，其中k为相同单词的数目，n为单词数目。
	int shortestWordDistance(vector<string>& words, string word1, string word2) {
		if (words.empty())	return 0;
		unordered_map<string, vector<int>> hash_tbl;
		for (int i = 0; i != words.size(); i++)
			hash_tbl[words[i]].push_back(i);
		int min_distance = INT_MAX;
		if (word1 == word2) {			
			for (int i = 1; i != hash_tbl[word1].size(); i++) {
				int distance = hash_tbl[word1][i] - hash_tbl[word1][i - 1];
				min_distance = min(min_distance, distance);
			}			
		}
		else {
			for (int i = 0; i != hash_tbl[word1].size(); i++) {
				for (int j = 0; j != hash_tbl[word2].size(); j++) {
					int indx1 = hash_tbl[word1][i], indx2 = hash_tbl[word2][j];
					if (indx1 < indx2)	min_distance = min(min_distance, indx2 - indx1);				
					else				min_distance = min(min_distance, indx1 - indx2);
				}
			}
		}
		return min_distance;
	}
};

class Solution {
public:
    ///@note    1. 分成两种情况，第一种是两个单词相同，则在同一个数组中查找最短距离即可；
    //          2. 第二种情况参照Shortest Word Distance II，时间复杂度能够压缩到O(n)，n为该单词出现的次数。
    int shortestWordDistance(vector<string>& words, string word1, string word2) {
        if (words.empty())  return 0;
		unordered_map<string, vector<int>> hash_tbl;
		for (int i = 0; i != words.size(); i++)	hash_tbl[words[i]].push_back(i);
		int rslt = INT_MAX;
		if (word1 == word2) {
			for (int i = 1; i != hash_tbl[word1].size(); i++) 
				rslt = min(rslt, hash_tbl[word1][i] - hash_tbl[word1][i-1]);			
		}
		else {
			int i = 0, j = 0;
			while (i < hash_tbl[word1].size() && j < hash_tbl[word2].size()) {
				rslt = min(rslt, abs(hash_tbl[word1][i] - hash_tbl[word2][j]));
				hash_tbl[word1][i] < hash_tbl[word2][j] ? i++ : j++;
			}
		}
		return rslt;
    }
};

int main() {
	string sarr[5] = {"practice", "makes", "perfect", "coding", "makes"};
	vector<string> words;
	for (int i = 0; i < 5; i++)
		words.push_back(sarr[i]);
	Solution slt;
	int r = slt.shortestWordDistance(words, "coding", "makes");
	return 0;
}