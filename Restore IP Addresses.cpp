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

///@date	2015.12.28
///@version	2.1

///@date	2016.05.10
///@version	2.2

///@date    December 7, 2018
///@version 2.3

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

class Solution_v2 {
public:
	///@brief	将一组数字字符串转换成所有可能的合法IP地址
	///@param	s	数字字符串
	///@return	返回所有可能的IP地址集合
	///@note	1. 递归；
	//			2. 递归函数有4个参数，分别是剩余数字字符串，当前IP段的字符子串，剩余IP段数目和结果集合；
	//			3. 当剩余段数目为0时，递归终止，在终止时应该注意，如果此时剩余数字字符串为空时，应该将当前IP段的字符子串压入结果数组，否则直接结束；
	//			4. 因为IP地址分为4段，每段的长度为1到3位，大小是0~255，没有前缀0，所以在判断每一段的时候应该有一个判断当前段是否合法的函数。
	vector<string> restoreIpAddresses(string s) {
		vector<string> rslt;
		helper(s, 4, "", rslt);
		return rslt;
	}

	///@brief	递归划分IP地址
	///@param	s		字符串
	///@param	k		剩余段数目
	///@param	ip		当前段
	///@param	rslt	结果数组
	void helper(string s, int k, string ip, vector<string>& rslt) {
		if (!k) {
			if (s.empty())	rslt.push_back(ip);
			return;
		}
		for (int i = 1; i < 4; i++) {
			if (i <= s.size() && isValid(s.substr(0, i))) {
				if (k == 1)	helper(s.substr(i), k - 1, ip + s.substr(0, i), rslt);
				else		helper(s.substr(i), k - 1, ip + s.substr(0, i) + ".", rslt);
			}
		}
	}

	///@brief	判断IP地址的段是否合法
	///@param	s	字符串
	///@return	如果段合法，则返回true；否则返回false
	bool isValid(const string& s) {
		if (s.size() > 3 || s.size() < 1 || (s.size() > 1 && s[0] == '0'))	return false;
		int n = stoi(s);
		return n <= 255 && n >= 0;
	}
};

class Solution {
public:
    ///@brief   给定一个只由数字组成的字符串，计算所有转化成合法IPv4地址的可能。
    ///@param   s   字符串
    ///@return  返回所有的可能。
	vector<string> restoreIpAddresses(string s) {
		vector<string> rslt;
		dfs(s, rslt, 4, "");
		return rslt;
	}

private:
    ///@brief   判断一个子段是否合法。
    ///@param   s   子段字符串。
    ///@return  返回是否合法。
	bool isValid(string s) {
		if (s.size() > 3 || s.size() < 1 || (s.size() > 1 && s[0] == '0'))	return false;
		int n = stoi(s);
		return n <= 255 && n >= 0;
	}

    ///@brief   递归辅助函数。
    ///@param   s   字符串剩余的子串
    ///@param   rslt    结果数组
    ///@param   k   一个合法IP地址的剩余段数
    ///@param   ip  一个正在拼接的IP地址
	void dfs(string s, vector<string>& rslt, int k, string ip) {
		if (!k) {
			if (s.empty())	rslt.push_back(ip);
			return;
		}
		for (int i = 1; i < 4; i++) {
			if (i <= s.size() && isValid(s.substr(0, i))) {
				if (k == 1)	dfs(s.substr(i), rslt, k - 1, ip + s.substr(0, i));
				else dfs(s.substr(i), rslt, k - 1, ip + s.substr(0, i) + ".");
			}
		}
	}
};

int main()
{
	string s = "111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
	Solution slt;
	vector<string> rslt = slt.restoreIpAddresses(s);
	
	return 0;
}
