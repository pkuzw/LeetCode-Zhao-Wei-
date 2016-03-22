///@file	Generalized Abbreviation
///@author	zhaowei
///@date	2016.03.22
///@version	1.0

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	///@brief	给出所有单词可能的缩写。缩写的规则是单词中的子串用数字表示。
	///@param	word	单词
	///@return	返回所有的缩写
	///@note	1. 递归	
	vector<string> generateAbbreviations(string word) {
		vector<string> rslt;
		dfs(rslt, word, "", 0, false);
		return rslt;
	}

	///@brief	递归辅助函数
	///@param	rslt	结果数组
	///@param	word	单词本身
	///@param	abbr	缩写
	///@param	indx	遍历到了单词的第几个字符
	///@param	pre_num	要准备替换的子串前一个字符是否为数字，如果不是数字，就可以替换为数字，否则不可以
	void dfs(vector<string>& rslt, string& word, string abbr, int indx, bool pre_num) {
		if (indx == word.size()) {
			rslt.push_back(abbr);
			return;
		}
		dfs(rslt, word, abbr + word[indx], indx + 1, false);
		if (!pre_num) {
			for (int len = 1; indx + len <= word.size(); len++)
				dfs(rslt, word, abbr + to_string(static_cast<long long>(len)), indx + len, true);			
		}
	}
};

int main() {
	string word = "word";
	Solution slt;
	vector<string> rslt = slt.generateAbbreviations(word);
	return 0;
}