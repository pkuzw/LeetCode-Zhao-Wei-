///@file	Shortest Word Distance II
///@author	zhaowei
///@date	2016.01.08
///@version	1.0

///@date	2016.02.12
///@version	1.1

#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

class WordDistance_v1 {
private:
	unordered_map<string, vector<int>> hash_tbl;	//	以word为键值，以word出现的下标数组为值
public:
	///@brief	构造函数，填充hash_tbl
	///@param	words	词典
	///@note	1. 将词典中的所有单词按照单词为键，其出现的下标数组为值保存起来。
	WordDistance_v1(vector<string>& words) {
		for (int i = 0; i != words.size(); i++) 
			hash_tbl[words[i]].push_back(i);
	}

	///@brief	计算指定的两个单词的最短距离
	///@param	word1, word2	两个单词
	///@return	返回二者的最短距离
	///@note	1. 遍历二者在哈希表中的数组，逐一比对，并更新最短值即可；
	//			2. 时间复杂度O(k^2)，空间复杂度为O(n)，其中k为单词出现的次数，n为单词的总数。
	int shortest(string word1, string word2) {
		int rslt = INT_MAX;
		for (int i = 0; i != hash_tbl[word1].size(); i++) {
			for (int j = 0; j != hash_tbl[word2].size(); j++) {
				int indx1 = hash_tbl[word1][i], indx2 = hash_tbl[word2][j];
				if (indx1 < indx2)	rslt = min(rslt, indx2 - indx1);
				if (indx1 > indx2)	rslt = min(rslt, indx1 - indx2);
			}
		}
		return rslt;
	}
};

class WordDistance {
public:
	WordDistance(vector<string>& words) {
		for (int i = 0; i != words.size(); i++)	hash_tbl[words[i]].push_back(i);
	}

	///@note	1. 哈希表记录下每个单词在单词数组中的下标，其中单词为键，下标数组为值；
	//			2. 由于两个单词之间的距离不可能大于已知的最小值，所以可以在原来的算法基础上进行改进，将时间复杂度降低到O(k)，其中k为单词出现的次数。
	int shortest(string word1, string word2) {
		int i = 0, j = 0, rslt = INT_MAX;
		while (i < hash_tbl[word1].size() && j < hash_tbl[word2].size()) {
			rslt = min(rslt, abs(hash_tbl[word1][i] - hash_tbl[word2][j]));
			hash_tbl[word1][i] < hash_tbl[word2][j] ? i++ : j++;
		}
		return rslt;
	}

	unordered_map<string, vector<int>> hash_tbl;
};

int main() {
	string w[5] = {"make", "world", "practice", "make", "perfect"};
	vector<string> words;
	for (int i = 0; i != 5; i++)	words.push_back(w[i]);
	WordDistance slt(words);
	int rslt = slt.shortest("make", "perfect");
	return 0;
}