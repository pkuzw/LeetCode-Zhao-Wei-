///@file	Count and Say
/*
			The count-and-say sequence is the sequence of integers beginning as follows:
			1, 11, 21, 1211, 111221, ...

			1 is read off as "one 1" or 11.
			11 is read off as "two 1s" or 21.
			21 is read off as "one 2, then one 1" or 1211.
			Given an integer n, generate the nth sequence.

			Note: The sequence of integers will be represented as a string.
*/
///@author	zhaowei
///@date	2015.06.18
///@version	1.0

///@date    2015.09.04
///@version 1.1

///@date	2015.09.24
///@version	1.2

///@date	2016.04.09
///@version	2.0

///@date    October 11, 2018
///@version 2.1

#include <iostream>
#include <string>
using namespace std;

class Solution_v1
{
public:
	///@brief	计算第n个count&say序列元素
	///@param	n	下标
	///@return	返回第n个count&say序列元素
	///@author	zhaowei
	///@date	2015.06.18
	///@note	若元素相邻，则计算连续元素的个数，后续再接上该元素；如果元素不相邻，则直接输出'1'+'该元素'。
	//			时间复杂度为O(n^2)，空间复杂度为O(n).
	string countAndSay(int n)
	{
		string a = "1";
		if (n == 1)
		{
			return a;
		}
		int j = 1;
		while (j != n)
		{
			string b;		//	下一个元素
			int cnt = 1;	//	统计连续数字个数
			for (int i = 0; i != a.length(); i++)
			{
				if (i == a.length()-1)	//	如果是最后一位，则计算出它的连续出现次数和它本身
				{
					b += char(cnt+'0');
					b += a[i];
					cnt = 1;
				}
				else
				{
					if (a[i] == a[i+1])	//	统计连续数字个数
					{
						cnt++;
					}
					else
					{
						b += char(cnt+'0');
						b += a[i];
						cnt = 1;
					}
				}
			}
			a = b;
			j++;
		}
		return a;
	}
};

class Solution_v2 {
public:
	///@note	1. 递归；
	//			2. 每次递归时看后续字符和首字符是否连续相同，如果是则记录连续相同的子串长度，然后将其转换为结果字符串；
	//			3. 如果不连续，则直接将计数器和当前字符压入结果字符串尾部即可。
    string countAndSay(int n) {
		if (n == 1)	return "1";
		string rslt;
		string tmp = countAndSay(n - 1);
		char c = tmp[0];
		int count = 1;
		for (int i = 1; i < tmp.size(); i++) {
			if (tmp[i] == c)	count++;
			else {
				rslt += to_string(static_cast<long long>(count));
				rslt += c;
				count = 1;
				c = tmp[i];
			}
		}
		rslt += to_string(static_cast<long long>(count));
		rslt += c;
		return rslt;
    }
};

class Solution {
public:
    ///@brief   计算第n（n <= 30）次迭代后的字符串，具体释义参见题目。
    ///@param   n   迭代次数
    ///@return  返回迭代后的字符串。
    ///@note    1. 递归法；
    //          2. 如果次数n为1，直接返回"1"；如果次数n > 1，则返回countAndSay(n-1)；
    //          3. 在遍历字符串的时候统计连续出现的相同字符，然后将其转换成次数+数字的形式拼接在结果字符串中；
    //          4. 时间复杂度为O(n^2)，空间复杂度为O(1).
    string countAndSay(int n) {
        if (n == 1) return "1";
        string rslt;
        string tmp = countAndSay(n - 1);
        int cnt = 1;
        char ch = tmp[0];
        for (int i = 1; i < tmp.size(); i++) {
            if (tmp[i] == ch)   cnt++;
            else {
                rslt += to_string(static_cast<long long>(cnt));
                rslt += ch;
                cnt = 1;    // 连续字符中断，需要更新cnt和ch值，为下一次计算连续字符做准备。
                ch = tmp[i];
            }
        }
        rslt += to_string(static_cast<long long>(cnt));
        rslt += ch;
        return rslt;
    }
};

int main()
{
	int n = 0;
	Solution slt;
	string rslt;
	while (cin >> n)
	{
		rslt = slt.countAndSay(n);
		cout << rslt << endl;
	}
	return 0;
}
