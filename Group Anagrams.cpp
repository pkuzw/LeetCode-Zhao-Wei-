///@file	Anagrams
/*
			Given an array of strings, return all groups of strings that are anagrams.

			Note: All inputs will be in lower-case.
*/
///@author	zhaowei
///@date	2015.07.01
///@version	1.1

///@author	zhaowei
///@date	2015.07.02
///@version 1.2

///@author  zhaowei
///@date    2015.09.04
///@version 2.0

///@date	2016.04.12
///@version	2.1

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>


using namespace std;

class Solution_v1 {
public:
	///@brief	获取字符串数组中的所有变位词
	///@param	strs	字符串数组
	///@return	返回包含所有变位词的字符串数组，这里所谓的变位词类是指由相同字母组成的单词数超过1个
	///@note	先将所有的单词转换成字母升序排列的新单词，然后将其放入multimap容器中，用变形后的单词作为索引，来记录变形词在原数组中的下标，最终
	//			输出所有记录大于1的原单词即可。时间复杂度为O(n)，空间复杂度为O(n)。
	vector<string> anagrams(vector<string>& strs)
	{
		if (strs.empty())
		{
			return anagrams_vec;
		}

		multimap<string, int> mymap;	//	建立可以存储重复键值的multimap容器
		for (int i = 0; i != strs.size(); i++)
		{
			string cvnt_str = convertWord(strs[i]);	//	转换单词
			mymap.insert(make_pair(cvnt_str, i));	//	将变形单词插入multimap
		}
		
		//	输出变位词数量超过1的所有原单词
		for (multimap<string, int>::iterator i = mymap.begin(); i != mymap.end(); i++)
		{
			multimap<string, int>::iterator j = i;
			j++;
			if (j == mymap.end())
			{
				if (mymap.count(i->first) > 1)
				{
					anagrams_vec.push_back(strs[i->second]);
				}
				break;
			}
			if (j->first == i->first)
			{
				anagrams_vec.push_back(strs[i->second]);
			}
			else
			{
				if (mymap.count(i->first) > 1)
				{
					anagrams_vec.push_back(strs[i->second]);
				}
			}
		}
		
		return anagrams_vec;
	}
	
private:
	///@brief	将单词按照字母升序进行变形转换
	///@param	word	单词
	///@return	返回按照字母升序进行转换后的单词
	string convertWord(string word)
	{
		int len = word.length();
		vector<char> chvec;
		for (int i = 0; i != len; i++)
		{
			chvec.push_back(word[i]);
		}

		sort(chvec.begin(), chvec.end(), less<char>());

		string cnvt_str;
		for (int i = 0; i != len; i++)
			cnvt_str += chvec[i];

		return	cnvt_str;
	}

	vector<string> anagrams_vec;	//结果数组
};

class Solution_v2 {
public:
	///@brief	将所有的变形词进行归类，对于每一组变形词，按照字母升序排序
	///@param	strs	变形词数组
	///@return	返回归类好的变形词词组
	///@note	哈希表解题。
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
		vector<vector<string>> rslt;
		unordered_map<string, multiset<string>> ht;	// 哈希表键值为multiset，这样便于维护内部同类词的有序性
		for (int i = 0; i != strs.size(); i++) {
			string tmp_str = strs[i];
			sort(tmp_str.begin(), tmp_str.end());
			ht[tmp_str].insert(strs[i]);
		}
		for (unordered_map<string, multiset<string>>::iterator i = ht.begin(); i != ht.end(); i++) {
			vector<string> tmp(i->second.begin(), i->second.end());
			rslt.push_back(tmp);
		}
		return rslt;
    }
};

class Solution {
public:
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		vector<vector<string>> rslt;
		unordered_map<string, multiset<string>> hash_tbl;
		for (int i = 0; i != strs.size(); i++) {
			string tmp = strs[i];
			sort(tmp.begin(), tmp.end());
			hash_tbl[tmp].insert(strs[i]);
		}
		for (unordered_map<string, multiset<string>>::iterator i = hash_tbl.begin(); i != hash_tbl.end(); i++) {
			vector<string> tmp(i->second.begin(), i->second.end());
			rslt.push_back(tmp);
		}
		return rslt;
	}
};

int main()
{
	
	vector<string> test;
	
//	int k = 0;
//	while (str[k] != "extemporizing")
//	{
//		test.push_back(str[k]);
//		k++;
//  }
    test.push_back("cat");
    test.push_back("atc");
    test.push_back("act");
    test.push_back("dog");
    test.push_back("god");
    test.push_back("bul");

// 	string a;
// 	while (cin >> a)
// 	{
// 		if (a == "break")
// 		{
// 			break;
// 		}
// 		test.push_back(a);
// 	}
	Solution slt;
	vector<vector<string>> rslt = slt.groupAnagrams(test);
	for (int i = 0; i != rslt.size(); i++)
	{
        for (int j = 0; j != rslt[i].size(); j++)
            cout << rslt[i][j] << ' ';
        cout << endl;
	}
	cout << endl;
	cout << rslt.size() << endl;
	cout << endl;
	return 0;
}

