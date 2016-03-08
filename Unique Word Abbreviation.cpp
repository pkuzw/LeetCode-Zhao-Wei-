///@file	Unique Word Abbreviation
///@author	zhaowei
///@date	2016.03.08
///@version	1.0

#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include <utility>

using namespace std;

class ValidWordAbbr {
public:
	///@brief	判断给定的词典里面是否存在缩写相同的单词
	///@param	dictionary	单词表
	///@note	1. 维护2个哈希表，一个是键为单词的缩写，值是缩写的出现次数；另一个是键为单词的缩写，值为原单词；
	//			2. 只有当单词表中的单词是不一样的时候，才会在缩写的哈希表中增加其次数；
	//			3. 时间复杂度为O(n)，空间复杂度为O(n)。
	ValidWordAbbr(vector<string> &dictionary) {		
		for (int i = 0; i != dictionary.size(); i++) {
			string abbr_word = getAbbrWord(dictionary[i]);
			pair<set<string>::iterator, bool> ret = hash_tbl_[abbr_word].insert(dictionary[i]);
			if (ret.second)	hash_tbl[abbr_word]++;			
		}
	}

	///@brief	判断某单词是否有重复的缩写
	///@param	word	单词
	///@return	如果存在重复的缩写，返回false；否则返回true
	///@note	1. 注意，题目要求当调用isUnique()时，参数中的单词不在原dictionary中时，如果其缩写已经存在，则返回false；
	//				如果调用的是其本身且其只出现过一次，则返回true。
	bool isUnique(string word) {		
		string abbr_word = getAbbrWord(word);
		return (!hash_tbl[abbr_word]) || (hash_tbl[abbr_word] == 1 && hash_tbl_[abbr_word].find(word) != hash_tbl_[abbr_word].end());
	}
private:
	///@brief	计算单词的缩写形式
	///@param	word	单词
	///@return	返回单词的缩写，形式为首尾字符加上其中间部分的长度
	string getAbbrWord(string word) {		
		string abbr_word = word.front() + to_string(static_cast<long long>(word.size() - 2)) + word.back();
		return abbr_word;
	}

	unordered_map<string, int> hash_tbl;			//key: abbreviation, value: appearance count
	unordered_map<string, set<string>>hash_tbl_;	//key: abbreviation, value: words
};


// Your ValidWordAbbr object will be instantiated and called as such:
// ValidWordAbbr vwa(dictionary);
// vwa.isUnique("hello");
// vwa.isUnique("anotherWord");

int main() {
	string strs[1] = {"dog"};
	vector<string> dictionary;	
	for (int i = 0; i != 1; i++)	dictionary.push_back(strs[i]);
	ValidWordAbbr vwa(dictionary);
	bool rslt = vwa.isUnique("dig");
	rslt = vwa.isUnique("dug");
	rslt = vwa.isUnique("dag");
	rslt = vwa.isUnique("dog");
	rslt = vwa.isUnique("doge");
	return 0;
}