///@file	Repeated DNA Sequences
/*
All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.

Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.

For example,

Given s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",

Return:
["AAAAACCCCC", "CCCCCAAAAA"].
*/
///@author	zhaowei
///@date	2015.08.04
///@version	1.0

///@date	2015.08.12
///@version	1.1

///@date	2016.01.19
///@version	1.2

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution_v1 {
public:
	///@brief	找出一个DNA序列中长度为10的多次出现的子串
	///@param	s	DNA序列
	///@return	返回多次重复出现的长度为10的子串
	/* @note	通过观察，'A'的ASCII的二进制表示是0100 0001，'C'的是0100 0011，'G'是0100 0111，'T'是0101 0100，他们的后四位的二进制表示都不相同，可以利用3bit来表示
				其中一个字符。10个字符长的DNA序列的长度也就是30bit，新建一个10字符长的DNA序列和其出现频率的哈希表。如果这个序列已经出现过，则输出到结果数组，否则继续
				向后遍历。时间复杂度为O(n)，空间复杂度为O(n)。*/
	vector<string> findRepeatedDnaSequences(string s) {
		unordered_map<int, int> hash_table;	//key: 10个碱基对的ASCII表示的后三位组成的二进制的十进制表示；val: 该DNA子序列的出现频率
		vector<string> rslt;
		if (s.size() < 10)	return rslt;

		int cur = 0;	//	前9个碱基对的后三位组成的数
		for (int i = 0; i < 9; i++)
		{
			cur = (cur << 3) | (s[i] & 7);
		}

		for (int i = 9; i < s.size(); i++)
		{
			cur = ((cur & 0x7ffffff) << 3) | (s[i] & 7);	//	取当前序列的后二十七位，所以要与0x7ffffff，然后再左移3位，得到新的序列
			if (hash_table.find(cur) != hash_table.end())
			{
				if (hash_table[cur] == 1)	//	不重复输出已经输出过的元素
					rslt.push_back(s.substr(i-9, 10));
				hash_table[cur]++;
			}
			else
				hash_table[cur]++;
		}
		return rslt;
	}
};

class Solution {
public:
	///@brief	找出一个DNA序列中长度为10的多次出现的子串
	///@param	s	DNA序列
	///@return	返回多次重复出现的长度为10的子串
	///@note	1. 通过观察发现A, C, T, G的ASCII码表示只有后三位不同，10位碱基对也就是30bit，故可以通过一个int型变量来表示一个10位的DNA；
	//			2. 整体思路还是枚举遍历DNA，然后利用哈希表来存储DNA片段出现的次数。
	vector<string> findRepeatedDnaSequences(string s) {
		unordered_map<int, int> hash_tbl;
		vector<string> rslt;
		if (s.size() < 10)	return rslt;
		int seg = 0;
		for (int i = 0; i < 9; i++) {
			seg = (seg << 3) | (s[i] & 7);
		}
		for (int i = 9; i < s.size(); i++) {
			seg = ((seg & 0x7ffffff ) << 3) | (s[i] & 7);
			if (hash_tbl.find(seg) != hash_tbl.end()) {
				if (hash_tbl[seg] == 1)	rslt.push_back(s.substr(i - 9, 10));				
			}
			hash_tbl[seg]++;			
		}
		return rslt;
	}
};

int main()
{
	string s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
	Solution slt;
	vector<string> rslt = slt.findRepeatedDnaSequences(s);

	Solution_v1 slt_v1;
	vector<string> rslt1 = slt_v1.findRepeatedDnaSequences(s);

	return 0;
}
