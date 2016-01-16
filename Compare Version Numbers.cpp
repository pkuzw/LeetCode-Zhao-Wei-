///@file	Compare Version Numbers
/*
Compare two version numbers version1 and version2.
If version1 > version2 return 1, if version1 < version2 return -1, otherwise return 0.

You may assume that the version strings are non-empty and contain only digits and the . character.
The . character does not represent a decimal point and is used to separate number sequences.
For instance, 2.5 is not "two and a half" or "half way to version three", it is the fifth second-level revision of the second first-level revision.

Here is an example of version numbers ordering:

0.1 < 1.1 < 1.2 < 13.37
*/
///@author	zhaowei
///@date	2015.07.28
///@version	1.0

///@date	2015.08.13
///@version	1.1

///@date	2016.01.16
///@version	2.0

#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <sstream>

using namespace std;

class Solution_v1 {
public:
	///@brief	比较两个版本号的大小
	///@param	version1, version2	版本号
	///@return	如果v1 < v2, 返回-1；如果v1 > v2，返回1；如果相等，则返回0
	/* @note	将版本号根据'.'切割成子段，逐个比较子段大小即可。对于子段较少的版本号，末尾补足0即可。时间复杂度为O(n)，空间复杂度为O(n)。*/
	int compareVersion(string version1, string version2) {
		vector<int> v1 = convertToNum(version1);	//	转换成int型的子段号
		vector<int> v2 = convertToNum(version2);
		if (v1.size() < v2.size())	//	末尾补足0
		{
			int len = v2.size()-v1.size();
			for (int i = 0; i != len; i++)
				v1.push_back(0);
		}
		if (v1.size() > v2.size())
		{
			int len = v1.size()-v2.size();
			for (int i = 0; i != len; i++)
				v2.push_back(0);
		}	

		for (int i = 0; i != v1.size(); i++)
		{
			if (v1[i] < v2[i])		return -1;
			else if (v1[i] > v2[i])	return 1;			
		}
		return 0;
	}

private:
	///@brief	将子段号转换成整型数组
	vector<int> convertToNum(string s)
	{
		vector<int> nums, dot_indxs;
		for (int i = 0; i != s.length(); i++)
		{
			if (s[i] == '.')	dot_indxs.push_back(i);
		}

		int start = 0;
		int end = s.length()-1;
		for (int i = 0; i != dot_indxs.size(); i++)
		{
			end = dot_indxs[i];
			string seg = s.substr(start, end-start);
			nums.push_back(convertToInt(seg));
			start = dot_indxs[i]+1;
		}
		nums.push_back(convertToInt(s.substr(start, s.length()-start)));
		return nums;
	}

	///@brief	将单个子段转换成int型变量
	int convertToInt(string s)
	{
		vector<int> dec;
		dec.push_back(1);
		for (int i = 1; i != 10; i++)
		{
			int k = dec[i-1] * 10;
			dec.push_back(k);
		}

		int num = 0;
		for (int i = 0; i != s.length(); i++)
		{
			num += int(s[i]-'0')*dec[s.length()-i-1];
		}
		return num;
	}
};

class Solution_v1_1 {
public:
	int compareVersion(string version1, string version2) {
		queue<int> v1 = parse(version1);
		queue<int> v2 = parse(version2);

		if (v1.size() < v2.size())
		{
			while (v1.size() != v2.size())
				v1.push(0);
		}
		else if (v1.size() > v2.size())
		{
			while (v1.size() != v2.size())
				v2.push(0);
		}
		while (!v1.empty())
		{
			int t1 = v1.front();
			int t2 = v2.front();
			v1.pop();
			v2.pop();
			if (t1 < t2)		return -1;
			else if (t1 > t2)	return 1;			
		}
		return 0;
	}

	queue<int> parse(string s)
	{
		queue<int> que;
		vector<int> dot;
		for (int i = 0; i != s.size(); i++)
			if (s[i] == '.')	dot.push_back(i);
		if (dot.empty())
		{
			que.push(stoi(s));
			return que;
		}

		que.push(stoi(s.substr(0, dot.front())));
		for (int i = 0; i != dot.size()-1; i++)
			que.push(stoi(s.substr(dot[i]+1, dot[i+1]-dot[i]-1)));
		que.push(stoi(s.substr(dot.back()+1)));
		return que;
	}
};

class Solution {
public:
	///@brief	比较版本号
	///@param	version1, version2	版本号
	///@return	如果版本号1 -版本号2的值
	///@note	1. 使用stringstream；2. 将ver1中的一段输入到val1中，截止到最近的dot为止，同理ver2，然后逐段比较即可。
	int compareVersion(string version1, string version2) {
		istringstream ver1(version1 + "."), ver2(version2 + ".");
		int val1 = 0, val2 = 0;
		char dot = '.';
		while (ver1.good() || ver2.good()) {
			if (ver1.good()) ver1 >> val1 >> dot;	//	将ver1中的一段输入到val1中，截止到最近的dot为止
			if (ver2.good()) ver2 >> val2 >> dot;
			if (val1 > val2) return 1;
			else if (val1 < val2) return -1;
			val1 = val2 = 0;
		}
		return 0;
	}
};

int main()
{
	string s1 = "1.17.23";
	string s2 = "1.0.6";
	Solution slt;
	int rslt = slt.compareVersion(s1, s2);
	return 0;
}