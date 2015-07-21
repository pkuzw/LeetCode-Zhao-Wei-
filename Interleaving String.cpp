///@file	Interleaving String
/*
Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

For example,
Given:
s1 = "aabcc",
s2 = "dbbca",

When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false.
*/
///@author	zhaowei
///@date	2015.07.21
///@version	1.0

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
	///@brief	递归判断某个字符串是否是两个字符串交叉生成的
	///@param	s1	字符串1
	///@param	end1	字符串1的最后一个字符下标
	///@param	s2	字符串2
	///@param	end2	字符串2的最后一个字符下标
	///@param	s3	字符串3
	///@param	end3	字符串3的最后一个字符下标
	///@return	如果两个字符串可以交叉生成该字符串，则返回true；否则返回false
	bool isInterleave(string s1, string s2, string s3) {
		return isInterleave_Recursive(s1, s1.size()-1, s2, s2.size()-1, s3, s3.size()-1);
	}

private:
	///@brief	递归判断某个字符串是否是两个字符串交叉生成的
	///@param	s1	字符串1
	///@param	end1	字符串1的最后一个字符下标
	///@param	s2	字符串2
	///@param	end2	字符串2的最后一个字符下标
	///@param	s3	字符串3
	///@param	end3	字符串3的最后一个字符下标
	///@return	如果两个字符串可以交叉生成该字符串，则返回true；否则返回false
	/* @note	递归：如果字符串3的最后一个字符可以和字符串1或2的最后一个字符匹配，则除去匹配的这两个字符，递归继续判断。递归的退出条件是
				当三个字符串的最后一个字符下标均为-1时。时间复杂度为O(2^n)？，空间复杂度为O(1). OJ报TLE
	*/
	bool isInterleave_Recursive(string s1, int end1, string s2, int end2, string s3, int end3)
	{
		if (end3 == -1)
		{
			if (end1 == -1 && end2 == -1)				
					return true;
			else
				return false;
		}
		if ((s1[end1] == s3[end3] && isInterleave_Recursive(s1.substr(0, end1), end1-1, s2, end2, s3.substr(0, end3), end3-1))
			|| (s2[end2] == s3[end3] && isInterleave_Recursive(s1, end1, s2.substr(0, end2), end2-1, s3.substr(0, end3), end3-1)))
			return true;
		
		return false;
	}
};

int main()
{
	string s1 = "a";
	string s2 = "b";
	string s3 = "a";
	Solution slt;
	cout << slt.isInterleave(s1, s2, s3) << endl;
	return 0;
}