﻿///@file	Text Justification
/*
Given an array of words and a length L, format the text such that each line has exactly L characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly L characters.

Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left justified and no extra space is inserted between words.

For example,
words: ["This", "is", "an", "example", "of", "text", "justification."]
L: 16.

Return the formatted lines as:
[
"This    is    an",
"example  of text",
"justification.  "
]
Note: Each word is guaranteed not to exceed L in length.
*/
///@author	zhaowei
///@date	2015.07.10
///@version	1.0

///@date	2015.08.27
///@version	1.1

///@date	2015.12.04
///@version	1.2

///@date	2016.04.19
///@version	2.0

///@date    November 6, 2018
///@version 2.1

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution_v1 {
public:
	///@brief	给定一个字符串数组和单行最大列数。计算出每一行文本的单词分布。
	//			要求：1. 每个单词之间的空格数是一样的，如果需要添加的空格数不能够被单词数整除，则使左边的空格数多于右边的空格数；
	//				  2. 每一行的单词在左右两端是顶格的； 
	//				  3. 最后一行文本应该左对齐且不插入额外的空格。
	///@param	words		单词数组
	///@param	maxWidth	单行最大列数
	///@return	返回新生成的文本字符串数组，其中每一个元素是一行。
	///@note	不考虑maxWidth < words[i]的情形。首先尝试尽可能多的在一行中放入单词，除了最后一个单词，每一个单词后面至少有一个空格，
	//			直到遇到无法完整放下的单词，然后将额外需要补充的空格数均匀的放入每个单词后面，然后转入下一行。
	//			时间复杂度为O(k*n)，k为一行的单词数，空间复杂度为O(n)。
	vector<string> fullJustify(vector<string>& words, int maxWidth) {
		int line_ch_nums = 0;
		int line_words_cnt = 0;
		vector<string> svec;
		for (int i = 0; i != words.size(); i++)
		{
			if (line_ch_nums + line_words_cnt + words[i].length() > maxWidth)
			{
				int extra_space_num = maxWidth - line_ch_nums - line_words_cnt + 1;	//	因为最后一个单词后面没有空格，所以要多加1

				int j = 0;
				while (extra_space_num > 0)
				{
					svec[j] += " ";			
					
					if (svec.size() > 1)	//	如果一行能放多于1个单词，则循环添加格外的空白符，否则continue，要不然会出现j模0的情况
					{
						j++;
						j %= svec.size()-1;	//	最后一个单词不添加额外的空格字符
					}
					
					extra_space_num--;					
				}

				string str;
				for (j = 0; j != svec.size(); j++)	//	给每个单词后添加本应该属于它们的空格
				{
					if (j != svec.size()-1)
					{
						svec[j] += " ";
					}
					str += svec[j];
				}
				rslt.push_back(str);

				svec.clear();
				line_ch_nums = 0;
				line_words_cnt = 0;
				i--;
				continue;
			}

			svec.push_back(words[i]);
			line_ch_nums += words[i].length();
			line_words_cnt++;
		}
		rslt.push_back(lastLine(svec, maxWidth));	//处理最后一行
		return rslt;
	}

private:
	///@brief	处理文本的最后一行
	///@param	svec	文本最后一行的单词数组
	///@param	maxWidth	一行的最大列数
	///@return	返回没有均匀添加过额外字符的最后一行字符串
	string lastLine(vector<string> svec, int maxWidth)
	{
		string s;
		for (int i = 0; i != svec.size(); i++)
		{
			if (i != svec.size()-1)
			{
				svec[i] += " ";
			}
			s += svec[i];
		}
		int extra_space_num = maxWidth - s.length();

		string extra_space;
		for (int i = 0; i != extra_space_num; i++)
		{
			extra_space += " ";
		}
		s += extra_space;
		return s;
	}

	vector<string> rslt;
};

class Solution_v1_1 {
public:
	///@brief	将单词组均匀的分布在各行当中
	///@param	words	原来的单词组
	///@param	maxWidth	单行的宽度
	///@return	返回新的段落
	///@note	不考虑maxWidth < words[i]的情形。首先尝试尽可能多的在一行中放入单词，除了最后一个单词，每一个单词后面至少有一个空格，
	//			直到遇到无法完整放下的单词，然后将额外需要补充的空格数均匀的放入每个单词后面，然后转入下一行。
	//			时间复杂度为O(k*n)，k为一行的单词数，空间复杂度为O(n)。
	vector<string> fullJustify(vector<string>& words, int maxWidth) {
		int ch_cnt = 0; //	当前行的字符个数
		int word_cnt = 0;	//	当前行单词的数目
		vector<string> svec;
		for (int i = 0; i != words.size(); i++)
		{
			if (ch_cnt + words[i].size() + word_cnt > maxWidth)
			{
				int extra_spc_cnt = maxWidth - ch_cnt - word_cnt + 1;
				int j = 0;
				while (extra_spc_cnt)
				{
					svec[j] += " ";
					if (svec.size() > 1)
					{
						j++;
						j %= svec.size()-1;
					}
					extra_spc_cnt--;
				}
				string s;
				for (j = 0; j != svec.size(); j++)
				{
					if (j != svec.size() - 1)	svec[j] += " ";
					s += svec[j];
				}
				rslt.push_back(s);
				svec.clear();
				word_cnt = 0;
				ch_cnt = 0;
				i--;
			}
			else
			{
				svec.push_back(words[i]);
				ch_cnt += words[i].size();
				word_cnt++;
			}
		}
		string last_line = processLastLine(svec, maxWidth);
		rslt.push_back(last_line);
		return rslt;
	}
private:
	vector<string> rslt;

	///@brief	处理最后一行
	///@param	svec	最后一行的单词数组
	///@param	maxWidth	单行宽度，单词之间不留多余空格
	///@return	返回最后一行字符串
	string processLastLine(vector<string> svec, int maxWidth)
	{
		string s;
		for (int i = 0; i != svec.size(); i++)
		{
			if (i != svec.size()-1)	svec[i] += " ";
			s += svec[i];
		}
		s.append(maxWidth - s.size(), ' ');
		return s;
	}
};

class Solution {
public:
    ///@brief   给定一组单词和每一行的最大长度，向一行内插入若干空格符，使得一行可以包含尽可能多的单词，同时又没有单词被截断。
    ///@param   words   单词数组
    ///@param   maxWidth    一行的长度
    ///@return  返回重新加入若干空白符的单词词组。如果一行内的单词间空白不能均匀分布，那么尽可能使左边的空白符长。最后一行的
    //          单词空白符应该是右边的空白符长。
	vector<string> fullJustify(vector<string> &words, int maxWidth) {
		vector<string> rslt;
		int begin = 0;
		while (begin < words.size()) {
			int last = begin;
			int linesize = words[begin++].size();
			while (begin < words.size() && linesize + 1 + words[begin].size() <= maxWidth) {
				linesize += 1 + words[begin].size();
				begin++;
			}

			int spaces = 1, extra = 0;
			if (begin < words.size() && begin != last + 1) {
				spaces = (maxWidth - linesize) / (begin - last - 1) + 1;
				extra = (maxWidth - linesize) % (begin - last - 1);
			}

			rslt.push_back(words[last++]);
			while (extra--) {
				rslt.back().append(spaces+1, ' ');
				rslt.back().append(words[last++]);
			}
			while (last < begin) {
				rslt.back().append(spaces, ' ');
				rslt.back().append(words[last++]);
			}
			rslt.back().append(maxWidth-rslt.back().size(), ' ');
		}

		return rslt;
	}
};

int main()
{
	vector<string> text, words;
	int len = 0;
	words.push_back("this");
	words.push_back("is");
	words.push_back("an");
	words.push_back("example");
	words.push_back("of");
	words.push_back("text");
	words.push_back("justification.");	

	len = 16;
	Solution slt;
	text = slt.fullJustify(words, len);
	for (int i = 0; i != text.size(); i++)
	{
		cout << text[i] << endl;
	}
	return 0;
}
