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
	//			1. 去掉最后一个'/'；
	//			2. 去掉最后一个文件夹名之前的所有路径
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