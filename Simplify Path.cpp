///@file	Simplify Path
/*
Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"
*/
///@author	zhaowei
///@date	2015.07.11
///@version	1.0

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
	///@brief	将给定的绝对路径进行简化
	///@param	path	绝对路径
	///@return	返回简化后的路径
	///@note	路径的简化规则：
	//			1. 去掉位于字符串末尾的'/'；
	//			2. '/.'相当于保持在当前目录；
	//			3. '/..'是返回上一级目录；
	//			4. 多个'/'连续出现相当于一个'/'；
	//			5. '/xxx'就是一个目录，注意这里xxx可以是连续的三个'.'；
	//			首先，将路径中连续出现的'/'简化成一个'/'；其次，如果最后一个字符是'/'，则也需要删去；再次，将由'/'分隔的子串提取出来压栈，如果遇到'/.'，则不
	//			压栈也不弹栈，维持现状，如果遇到'/..'，则弹栈，如果遇到其他合法目录名，则压栈。最后在栈中保留的子串从后向前组成了简化后的路径名；
	//			时间复杂度为O(n)，空间复杂度为O(1)
	string simplifyPath(string path) {
		string rslt;
		int slash_cnt = 0;
		int last_slash = 0;
		for (int i = path.length()-1; i >= 0; i--)
		{
			if (path[i] == '/')
			{
				slash_cnt++;
				if (slash_cnt == 1)
				{
					path = path.substr(0, i);
				}
				else if (slash_cnt == 2)
				{
					last_slash = i;
					path = path.substr(i, path.length() - i);
					return path;
				}
			}
		}
	}
private:
	///@brief	删除连续出现的冗余'/'
	///@param	s	字符串
	///@return	无
	void eraseRedundantSlash(string &s)
	{
		for (string::iterator i = s.begin(); i != s.end()-1; i++)
		{
			while (*i == '/' && *i+1 == '/')
			{
				s.erase(i+1);
			}
		}
	}
};

int main()
{
	string path;
	while (cin >> path)
	{
		Solution slt;
		cout << slt.simplifyPath(path) << endl;
	}
	return 0;
}