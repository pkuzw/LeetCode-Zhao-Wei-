///@brief	Roman to Integer
///@author  zhaowei
///@date	2015.06.03
///@version 1.0

///@date    2015.09.07
///@version 2.0

///@date	2016.04.02
///@version	2.1

///@date    July 05, 2018
///@version 2.2

#include <string>
#include <iostream>
#include <map>
using namespace std;

class Solution_v1
{
public:
	///@brief	罗马数字转换成阿拉伯数字
	///@param	s	待转换的罗马数字
	///@return	返回转换后的阿拉伯数字
	///@author	zhaowei
	///@date	2015.06.03
	///@note	罗马数字的组成是从头到尾遍历一遍，根据不同的字符进行累加。注意在V, X, L, C, D, M前面的相应字符是减数，其后面的字符是加数。
	int romanToInt(string s) {

		char roman_elmnt[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
		int rslt = 0;

		for (int i = 0; i < s.length(); i++)	//遍历罗马数字，逐位累加，特殊字符前面的数字是减数，后面的才是加数
		{
			if (s[i] == 'M')
			{
				rslt += 1000;
			}
			else if (s[i] == 'D')
			{
				rslt += 500;
			}
			else if (s[i] == 'C')
			{
				if (i+1 < s.length() && (s[i+1] == 'D' || s[i+1] == 'M'))	// 注意要判断i+1是否越界
				{
					rslt -= 100;
				}
				else
					rslt += 100;
			}
			else if (s[i] == 'L')
			{
				rslt += 50;
			}
			else if (s[i] == 'X')
			{
				if (i+1 < s.length() && (s[i+1] == 'C' || s[i+1] == 'L'))	// 注意要判断i+1是否越界
				{
					rslt -= 10;
				}
				else
					rslt += 10;
			}
			else if (s[i] == 'V')
			{
				rslt += 5;
			}
			else if (s[i] == 'I')
			{
				if (i+1 < s.length() && (s[i+1] == 'X' || s[i+1] == 'V'))	// 注意要判断i+1是否越界
				{
					rslt -= 1;
				}
				else
					rslt += 1;
			}
		}
		return rslt;
	}
};

#include <map>
class Solution_v2 {
public:
	///@brief	将罗马数字转换成10进制的int型变量
	///@param	s	罗马数字字符串
	///@return	返回十进制的阿拉伯数字
	///@note	用一个map来映射不同的罗马数字和阿拉伯数字之间的关系，然后根据它们的前后关系来决定增减当前这么多的数。时间复杂度为O(n)，空间复杂度为O(logn)。
    int romanToInt(string s) {
		int rslt = 0;
		map<char, int> roman;
		roman['I'] = 1;
		roman['V'] = 5;
		roman['X'] = 10;
		roman['L'] = 50;
		roman['C'] = 100;
		roman['D'] = 500;
		roman['M'] = 1000;
		for (int i = 0; i < s.size(); i++) {
			int val = roman[s[i]];
			if (i == s.size() - 1 || roman[s[i]] >= roman[s[i+1]])	rslt += val;
			else rslt -= val;
		}
		return rslt;
    }
};

class Solution_ {
public:
	int romanToInt(string s) {
		map<char, int> hash_tbl;
		hash_tbl['I'] = 1;
		hash_tbl['V'] = 5;
		hash_tbl['X'] = 10;
		hash_tbl['L'] = 50;
		hash_tbl['C'] = 100;
		hash_tbl['D'] = 500;
		hash_tbl['M'] = 1000;
		int rslt = 0;
		for (int i = 0; i != s.size(); i++) {
			int val = hash_tbl[s[i]];
			if (i == s.size() - 1 || hash_tbl[s[i]] >= hash_tbl[s[i+1]])		rslt += val;
			else	rslt -= val;
		}
		return rslt;
	}
};

class Solution {
public:
    ///@brief   将罗马数字转换成阿拉伯数字
    ///@param   s   罗马数字表示的字符串，范围是[1, 4000)。
    ///@return  返回罗马数字对应的阿拉伯数字，用整型int表示。
    ///@note    1. 考虑到罗马数字是从高位写到低位，当遇到4，40，400时，较小的数字反而出现在前面，那么分两种情况考虑。
    //          a. 如果当前数字比后继数字大或者相等，那么将当前数字累加到和上面；
    //          b. 如果当前数字小于后继数字，那么将和扣除当前数字即可。
    //          2. 时间复杂度为O(1)，空间复杂度为(1)。因为罗马数字的范围确定，是一个常量。
    int romanToInt(string s) {
        int rslt = 0;
        map<char, int> hash_table;
        hash_table['I'] = 1;
        hash_table['V'] = 5;
        hash_table['X'] = 10;
        hash_table['L'] = 50;
        hash_table['C'] = 100;
        hash_table['D'] = 500;
        hash_table['M'] = 1000;
        
        for (int i = 0; i < s.size(); i++) {
            int t = hash_table[s[i]];
            if (i == s.size() - 1 || t >= hash_table[s[i+1]])   rslt += t;
            else rslt -= t;
        }
        return rslt;
    }
};


int main()
{
	Solution slt;
	Solution_v2 s2;
	string test = "MMMV";
	int num = slt.romanToInt(test);
	int n2 = s2.romanToInt(test);
	return 0;
}
