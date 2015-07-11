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
	///@brief	�������ľ���·�����м�
	///@param	path	����·��
	///@return	���ؼ򻯺��·��
	///@note	·���ļ򻯹���
	//			1. ȥ�����һ��'/'��
	//			2. ȥ�����һ���ļ�����֮ǰ������·��
	//			ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)
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