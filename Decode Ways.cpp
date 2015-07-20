///@file	Decode Ways
/*
A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given an encoded message containing digits, determine the total number of ways to decode it.

For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

The number of ways decoding "12" is 2.
*/
///@author	zhaowei
///@date	2015.07.20
///@version	2.0

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	///@brief	给定一个数字串，其中数字是按照1->A, 2->B, ..., 26->Z的顺序来进行对应的，计算该数字串有多少种解码方法
	///@param	s	数字串
	///@return	返回总的解码方法数
	/* @note	递归：递归的结束条件是字符串只有0个，1个或者2个字符。分情况讨论：
				1. 当字符串只有0个字符时，直接返回；
				2. 当字符串有1个字符时，如果是0，直接返回，否则在方法数上自增1；
				3. 当字符串有2个字符时，如果这两个字符能够合并解译且也能够分开解译，则方法数自增2；如果这两个字符只能单独解译或者只能放在
				一起解译，方法数自增1；当首字符为'0'时，直接返回；
				递归时如果字符串首部两个元素能否独立解译且合并解译，则递归求解去掉首部两位的子串，然后再递归求解去掉首部一位的子串即可。
				时间复杂度为O(2^n)，空间复杂度为O(n^2)。OJ报TLE。
	*/
	int numDecodings_Recur(string s) {
		int cnt = 0;
		getDecodeMethods(s, cnt);
		return cnt;
	}

	///@brief	给定一个数字串，其中数字是按照1->A, 2->B, ..., 26->Z的顺序来进行对应的，计算该数字串有多少种解码方法
	///@param	s	数字串
	///@return	返回总的解码方法数
	/* @note	动态归划：用dp[i]表示字符串s[0..i-1]能够解码的方法数。初始条件dp[0] = 1, dp[1] = (s[0] == '0') ? 0 : 1，递推方程为
				dp[i] = (s[i-1] <= '9' && s[i-1] > '0') ? dp[i-1] : 0) + 
				((s[i-2] == '2' && s[i-1] <= '6' && s[i-1] >= '0') || (s[i-1] == '1')) ? dp[i-2] : 0.
				时间复杂度为O(n)，空间复杂度为O(n)。	
	*/
	int numDecodings_DP(string s) {
		if (s.empty())
		{
			return 0;
		}
		vector<int> dp;	//	初始化。dp[i]表示s[0..i-1]的解码方法数
		for (int i = 0; i != s.length()+1; i++)
		{
			dp.push_back(0);
		}	

		dp[0] = 1;	//	用于计算dp[i-2]的值
		dp[1] = (s[0] == '0') ? 0 : 1;	//	初始条件
		
		for (int i = 2; i != s.length()+1; i++)	
		{
			if (s[i-1] != '0')	// 先判前一个元素
			{
				dp[i] = dp[i-1];
			}
			else 
				dp[i] = 0;	//	出现无法匹配的'0'，直接置为0


			if ((s[i-2] == '2' && s[i-1] <= '6') || (s[i-2] == '1'))	//	再判前两个元素
			{
				dp[i] += dp[i-2];
			}			
		}
		return dp.back();
	}

private:
	///@brief	递归计算解码方法数
	///@param	s	字符串
	///@param	cnt	方法数
	///@return 无
	void getDecodeMethods(string s, int &cnt)
	{
		if (s.length() == 0)
		{
			return;
		}
		else if (s.length() == 1)
		{
			if (s[0] == '0')
			{
				return;
			}
			cnt++;
			return;
		}
		else if (s.length() == 2)
		{
			if ((s[0] > '2' && s[0] <= '9') 
				|| (s[0] == '2' && ((s[1] > '6' && s[1] <= '9') || s[1] == '0')) 
				|| (s[0] == '1' && s[1] == '0'))
			{				
				cnt++;
				return;
			}
			else if ((s[0] == '2' && s[1] <= '6' && s[1] > '0') || (s[0] == '1' && s[1] > '0' && s[1] <= '9'))
			{
				cnt += 2;
				return;
			}
			else if (s[0] == '0')
			{
				return;
			}
		}
		else
		{
			if ((s[0] > '2' && s[0] <= '9') || (s[0] == '2' && s[1] > '6'))
			{				
				getDecodeMethods(s.substr(1, s.length()-1), cnt);
			}
			else if ((s[0] == '2' && s[1] <= '6' && s[1] >= '0') || (s[0] == '1'))
			{
				getDecodeMethods(s.substr(2, s.length()-2), cnt);
				getDecodeMethods(s.substr(1, s.length()-1), cnt);
			}			
		}
		return;
	}
};

int main()
{
	string s = "9371597631128776948387197132267188677349946742344217846154932859125134924241649584251978418763151253";//3981312
	Solution slt;
	cout << slt.numDecodings_DP(s);
	cout << ' ' << slt.numDecodings_Recur(s);
	cout << endl;
	return 0;
}