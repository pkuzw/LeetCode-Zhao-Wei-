///@file	Simplify Path
/*
Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"
*/
///@author	zhaowei
///@date	2015.07.12
///@version	1.1

///@date	2015.08.27
///@version	2.0

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution_v1 {
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
	//			6. 在根目录时无法再向上，则无论出现多少返回上级目录的命令，都应该保持在根目录。
	//			首先，将路径中连续出现的'/'简化成一个'/'；其次，如果最后一个字符是'/'，则也需要删去；再次，将由'/'分隔的子串提取出来压栈，
	//			如果遇到'/.'，则不压栈也不弹栈，维持现状，如果遇到'/..'，则弹栈，如果此时栈为空，则先压入'/'（根目录），再弹栈；
	//			如果遇到其他合法目录名，则压栈。最后在栈中保留的子串从后向前组成了简化后的路径名；
	//			时间复杂度为O(n)，空间复杂度为O(1)。
	string simplifyPath(string path) 
	{		
		string rslt;

		eraseRedundantSlash(path);	//	删除冗余的'/'
		eraseLastSlash(path);	//	删除位于字符串末尾的'/'

		vector<string> stck;
		vector<int> slash_indx;

		for (int i = 0; i != path.length(); i++)	//	记录下'/'的下标
		{		
			if (path[i] == '/')
			{
				slash_indx.push_back(i);
			}
		}

		for (int i = 0; i != slash_indx.size(); i++)
		{
			string dname;
			if (i < slash_indx.size()-1)		
				dname = path.substr(slash_indx[i], slash_indx[i+1]-slash_indx[i]);			
			else
				dname = path.substr(slash_indx[i], path.length()-slash_indx[i]+1);

			if (dname == "/..")
			{
				if (stck.empty())	//	当容器为空时，不允许弹出操作。又因为到达根目录后无法再向上，故先添加一个根目录，再弹出。
				{
					stck.push_back("/");
				}
				stck.pop_back();
			}
			else if (dname == "/.")
			{
				continue;
			}
			else
			{
				stck.push_back(dname);
			}						 
		}

		for (int i = stck.size()-1; i >= 0; i--)
		{
			rslt = stck[i] + rslt;
		}
		if (rslt.empty())
		{
			rslt = "/";
		}
		return rslt;
	}

private:
	///@brief	删除连续出现的冗余'/'
	///@param	s	字符串
	///@return	无
	void eraseRedundantSlash(string &s)
	{
		for (int i = 0; i <= s.length()-1; i++)
		{
			while (i+1 < s.length() && s[i] == '/' && s[i+1] == '/')
			{
				s.erase(i+1, 1);	//	删除从下标i+1处开始的1个字符。
			}
		}
		return;
	}

	///@brief	删除位于字符串最末尾的'/'
	///@param	s	字符串
	///@return	无
	void eraseLastSlash(string &s)
	{
		if (s.back() == '/')
		{
			s = s.substr(0, s.length()-1);
		}
		return;
	}
};

class Solution {
public:
	string simplifyPath(string path) {
		vector<string> svec;
		int i = 0;
		while (i < path.size())
		{
			while (i < path.size() && path[i] == '/')	i++;
			if (i == path.size())	break;
			int start = i;
			while (i < path.size() && path[i] != '/')	i++;
			string dir = path.substr(start, i - start);
			if (dir == "..")
			{
				if (!svec.empty())	svec.pop_back();				
			}
			else if (dir != ".")	svec.push_back(dir);
		}
		string rslt;
		for (int i = 0; i != svec.size(); i++)
			rslt += "/" + svec[i];
		if (rslt.empty())	rslt = "/";
		return rslt;
	}
};

int main()
{
	string path = "/a/./b/../../c/";
	Solution slt;
	string rslt = slt.simplifyPath(path);
	return 0;
}