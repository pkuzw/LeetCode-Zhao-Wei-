///@file	Restore IP Addresses
/*
Given a string containing only digits, restore it by returning all possible valid IP address combinations.

For example:
Given "25525511135",

return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)
*/
///@author	zhaowei
///@date	2015.07.21
///@version	1.0

///@date	2015.08.25
///@version	2.0

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	给定一个由数字组成的字符串，对其按照IP地址的格式对其进行划分，得到所有可能的IP地址
	///@param	s	字符串
	///@return	返回所有可能的IP地址
	/*@note	因为一个IP地址分为四段，每一段的范围是0-255，所以从字符串首部开始逐渐增加长度，如果划分出来1，2或3位就能组成1段，则继续
			向后递归寻找。递归退出的条件是最后一段的数字范围超过了255，或者是剩余的字符串长度小于段数或者大于段数乘以3，或者是找到了
			全部4段。最后一种情况是能够得到合法划分的，将结果入队，否则就结束递归。另外，IP地址的每一段数字不能有前缀0。
			时间复杂度为O(n)，空间复杂度为O(n)。
	*/
	vector<string> restoreIpAddresses(string s) {
		vector<string> rslt;
		int cnt = 4;
		string tmpstr;
		restoreIpAddresses_Recur(s, cnt, 0, tmpstr, rslt);
		return rslt;
	}

private:
	///@brief	递归计算可能的IP地址
	///@param	s	字符串s
	///@param	cnt	剩余的段数
	///@param	start	字符串中开始计算的起点
	///@param	tmpstr	已经计算好的部分字符串
	///@param	rslt	合法IP数组
	///@return	无	
	void restoreIpAddresses_Recur(string &s, int cnt, int start, string &tmpstr, vector<string> &rslt)
	{
		int len = s.length();
		if (cnt == 0)	//	如果已经是最后一个段
		{
			if (start == len)	//	找到了一个合法IP
			{
				tmpstr.erase(--tmpstr.end());	//	删除最后一个'.'
				rslt.push_back(tmpstr);
				tmpstr.push_back('.');	//	因为在前两行删掉了最后一个'.'，这里需要补上
										//	为了使退出递归时删除最后一段时的长度与之前一致
			}
			return;
		}

		if (len-start < cnt || len-start > cnt*3)	//	如果剩余的字符串长度超过了段数*3或者小于段数，则直接返回
		{
			return;
		}

		for (int i = 1; i <= 3 && start+i <= len; i++)	//	寻找合适的段数字
		{
			if (!isValidIP(s.substr(start, i)))
			{
				return;
			}
			string tmp = s.substr(start, i)+".";
			tmpstr += tmp;
			restoreIpAddresses_Recur(s, cnt-1, start+i, tmpstr, rslt);
			tmpstr = tmpstr.substr(0, tmpstr.length()-tmp.length());		//从递归处返回后，将该段清出队列
		}
	}

	///@brief	判断一个IP地址中的段是否合法
	///@param	s	表示IP地址中的一个段的字符串
	///@return	如果合法，返回true；否则返回false
	bool isValidIP(string s)
	{		
		int len = s.length();
		if (len > 3)
		{
			return false;
		}
		if (len > 1 && s[0] == '0')	//	不能有前缀0
		{
			return false;
		}

		int num = 0;
		for (int i = 0; i != len; i++)
		{
			num = num*10 + (s[i]-'0');
		}
		if (num < 0 || num > 255)
		{
			return false;
		}
		return true;
	}
};

class Solution {
public:
	vector<string> restoreIpAddresses(string s) {
		vector<string> rslt;
		restoreRecur(s, "", 4, rslt);
		return rslt;
	}
private:
	///@param	s		剩余的IP字符串
	///@param	ip		已经组成的IP地址
	///@param	k	剩余的段数
	///@param	rslt	结果数组
	void restoreRecur(string s, string ip, int k, vector<string>& rslt)
	{
		if (k == 0)		
		{
			if (s.empty())	rslt.push_back(ip);					
		}
		else
		{
			for (int i = 1; i <= 3; i++)
			{
				if (i <= s.size() && isValid(s.substr(0, i)))
				{
					if (k == 1)	restoreRecur(s.substr(i), ip + s.substr(0, i), k-1, rslt);				
					else		restoreRecur(s.substr(i), ip + s.substr(0, i) + ".", k-1, rslt);
				}
			}
		}
	}

	bool isValid(string s)
	{
		if (s.empty() || s.size() > 3 || (s.size() > 1 && s[0] == '0'))	return false;
		int n = stoi(s);
		return n >= 0 && n <= 255;
	}
};

int main()
{
	string s = "25525511135";
	Solution slt;
	vector<string> rslt = slt.restoreIpAddresses(s);
	
	return 0;
}