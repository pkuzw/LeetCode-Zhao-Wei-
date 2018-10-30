///@file	Length of Last Word
/*
Given a string s consists of upper/lower-case alphabets and empty space characters ' ', 
return the length of last word in the string.

If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space characters only.

For example, 
Given s = "Hello World",
return 5.
*/
///@author	zhaowei
///@date	2015.07.07
///@version	1.0

///@date    2015.09.01
///@version 2.0

///@date	2015.11.18
///@version 2.1

///@date	2016.04.14
///@version	2.2

///@date    October 30, 2018
///@version 2.3

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	给定一个字符串，包含大小写字母和' '字符，计算最后一个单词的长度
	///@param	s	字符串
	///@return	返回最后一个单词的长度
	///@note	从后向前进行遍历，找到最后一个单词，计算其连续的非空格字符长度。时间复杂度为O(n)，空间复杂度为O(1)。
	int lengthOfLastWord(string s)
	{
		bool flg = false;	//	用于标记是否为第一个单词
		int cnt = 0;	//	统计最后一个单词的长度
		for (int i = s.length()-1; i >= 0; i--)
		{
			if (s[i] == ' ' && !flg) continue;

			else if (s[i] == ' ' && flg) break;
			
			else if (s[i] != ' ')
			{
				cnt++;
				flg = true;
			}
		}
		return cnt;
	}
};

class Solution_v2 {
public:
    int lengthOfLastWord(string s) {
        if (s.empty())  return 0;
        int cnt = 0;
        int i = s.size() - 1;
        while (s[i] == ' ')
            i--;
        while (i >= 0 && s[i] != ' ')
        {
            i--;
            cnt++;
        }
        return cnt;
    }
};

class Solution_v2_1 {
public:
	///@brief	计算字符串中最后一个单词的长度
	///@param	s	字符串
	///@return	返回最后一个单词的长度，如果字符串为空，则返回0
	///@note	从后向前遍历字符串，遇到第一个空白字符停止。时间复杂度为O(n)，空间复杂度为O(1)。
	int lengthOfLastWord(string s) {
		if (s.empty())	return 0;
		int len = s.size();
		int cnt = 0;
		int i = len - 1;
		for (i = len - 1; i >= 0 && (s[i] == ' ' || s[i] == '	'); i--)		;	//	处理末尾的空白字符
		for (; i != -1; i--) {
			if (s[i] == ' ' || s[i] == '	')	break;
			cnt++;
		}
		return cnt;
	}
};

class Solution {
public:
    ///@brief   给定一个由大小写字母和空格符组成的字符串，计算最后一个单词的长度。每个单词之间通过空格符隔开。
    ///@param   s   字符串
    ///@return  返回字符串中最后一个单词的长度。如果最后一个单词不存在，则返回0.
    ///@note    1. 枚举法。
    //          2. 从后往前遍历整个字符串，找到第一个空格符或者到达字符串头部时停下即可，返回此时的循环变量数目。
    //          3. 时间复杂度为O(n)，空间复杂度为O(1)，其中n是字符串的长度。
	int lengthOfLastWord(string s) {
        trim(s);
        if (s.empty())  return 0;
        int rslt = 0;
        for (int i = s.length() - 1; i >= 0; i--) {
            if (s[i] != ' ')
                rslt++;
            else
                break;
        }
        return rslt;
	}
    
    ///@brief   去除掉字符串尾部的多余空白字符。
    ///@param   s   字符串
    void trim(string& s) {
        int l = s.length() - 1;
        while (l >= 0 && s[l] == ' ') {
            l--;
            s.pop_back();
        }
    }
};

int main()
{
	string str = " a ";
	

	Solution slt;
	int rslt = slt.lengthOfLastWord(str);
	
	Solution_v2_1 s2;
	int r2 = s2.lengthOfLastWord(str);
	return 0;
}
