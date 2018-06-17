///@file	Given a string S, find the longest palindromic substring in S. 
///			You may assume that the maximum length of S is 1000, and there exists one unique longest palindromic substring.
///@author	zhaowei
///@date	2015.05.25
///@version 1.0
///@note	最简单的方法就是O(n^2)的复杂度枚举所有子串，然后再验证每一个子串是否是回文字符串（O(n)），总计O(n^3)，会超时。

///@date    2015.09.07
///@version 2.0
///@note    Manacher's Algorithm

///@date	2016.03.31
///@version	2.1

///@date    June 17, 2018
///@version 2.2

#include <iostream>
#include <string>
using namespace std;

class Solution_v1 {
public:
	///@brief	枚举法
	///@param	s	待处理的字符串
	///@return  返回最长回文字符串
	///@author	zhaowei
	///@date	2015.05.25
	///@note	时间复杂度O(n^3)，空间复杂度O(n)
	string longestPalindrome_BruteForce(string s) {
		int pstr_head = 0;	//最大回文序列的首字符坐标
		int pstr_len = 1;	//最大回文序列的长度
		string pstr;
		for (int i = 0; i < s.length(); i++)	//枚举
		{
			int l = i;
			int count = 0;						//计算回文序列的长度
			int k = 1;							//用于标记第二层循环的字符串末尾字符
			for (int j = s.length() - 1; j >= i-1 && j >= 0; j--)
			{				
				if (s[l] == s[j] && l != j && l != j+1)	//i != j是回文字符串为奇数长度的情形；i == j+!是回文序列为偶数长度的情形
				{
					l++;
					count++;
					continue;
				}
				else
				{
					if (j - l == 0)				//回文字符串为奇数长度的情形
					{
						if (pstr_len < count*2 + 1)
						{
							pstr_head = i;
							pstr_len = count * 2 + 1;
							break;
						}
					}
					else if (l == j+1)			//回文字符串为偶数长度的情形
					{
						if (pstr_len < count*2)
						{
							pstr_head = i;
							pstr_len = count * 2;
							break;
						}
					}
					else						//如果枚举的子字符串不是回文字符串，重置末尾字符和起始字符
					{						
						j = s.length() - k;
						k++;
						l = i;
						count = 0;
					}
				}
			}
		}
		/*
		char buff[1000] = "";
		s.copy(buff, pstr_len, pstr_head);		//通过string自带的copy函数将回文字符串拷贝到字符串数组
		pstr = buff;
		return pstr;
		*/
		return s.substr(pstr_head, pstr_len);	//或者使用substring函数也可以，这样更简洁
	}

	///@brief	动态规划法
	///@param	s	待处理字符串
	///@return	返回最长回文子串
	///@author	zhaowei
	///@date	2015.05.25
	///@note	时间复杂度O(n^2)，空间复杂度O(n^2)
	///			考虑到"a"和"aa"就是最简单的回文子串，如果存在子串P[i, j]是回文子串且S[i-1] = S[j+1]，则P[i-1, j+1]也是回文子串
	string longestPalindrome_DP(string s)
	{
		int pstr_head = 0;	//回文子串的起始下标
		int pstr_len = 1;	//回文子串的长度
		bool table[1000][1000] = {false};	//用于记录回文子串的首末位置


		for (int i = 0; i < s.length(); i++)	//处理基本情况1：只有1个字符的子串一定是回文子串
		{
			table[i][i] = true;
		}

		for (int i = 0; i < s.length()-1; i++)	//处理基本情况2：2个重复字符的子串一定是回文子串
		{			
			if (s[i] == s[i+1])
			{
				table[i][i+1] = true;
				pstr_head = i;
				pstr_len = 2;
			}
		}

		for (int len = 3; len <= s.length(); len++)	//开始处理3个字符以上的情形
		{
			for (int i = 0; i < s.length()-len+1; i++)	//i是子串的首字符
			{
				int j = i + len - 1;		//j是子串的末尾字符
				if (table[i+1][j-1] && s[i] == s[j])		//如果P[i+1, j-1]是回文子串且S[i] = S[j]，则P[i, j]也是回文子串
				{
					table[i][j] = true;
					pstr_head = i;
					pstr_len = len;
				}
			}
		}
		return s.substr(pstr_head, pstr_len);	//返回计算结果
	}

	///@brief	中心扩展法
	///@param	s	字符串
	///@param	i	扩展中心的左边界
	///@param	j	扩展中心的右边界
	///@return	返回扩展出的回文子串
	///@author	zhaowei
	///@date	2015.05.25
	string ExtendAroundCenter(string s, int l, int r)
	{
		int left_bound = l;
		int right_bound = r;
		while (left_bound >= 0 && right_bound <= s.length()-1 && s[left_bound] == s[right_bound])
		{
			left_bound--;
			right_bound++;
		}
		return s.substr(left_bound+1, right_bound-left_bound-1);		//这里要注意，left_bound和right_bound在跳出循环时已经各自又向两侧延伸过，所以要减去这部分。
	}

	///@brief	中心扩展法找最长回文子串
	///@param	s	待处理的字符串
	///@return	返回最长回文子串
	///@author  zhaowei
	///@date	2015.05.25
	string longestPalindrome_extendAroundCenter(string s)
	{
		int pstr_head = 0;
		int pstr_len = 1;
		string pstr = s.substr(0, 1);

		for (int i = 0; i < s.length()-1; i++)
		{
			string p1 = ExtendAroundCenter(s, i, i);	//基本情形1：从一个字符的中心点开始向两侧扩展
			if (p1.length() > pstr.length())
			{
				pstr = p1;
			}

			string p2 = ExtendAroundCenter(s, i, i+1);	//基本情形2：从有两个相同字符的中心点向两侧扩展
			if (p2.length() > pstr.length())
			{
				pstr = p2;
			}
		}
		return pstr;
	}

	///@brief	Manacher's Algorithm
	///@author	zhaowei
	///@date	2015.05.26
	///@note	1. 首先进行预处理，将原来的字符串的字符之间都添加上"#"，在首部添加"$"，尾部添加"^"。
	//			   这样可以将中心为1个字符或2个字符的回文子串转换为1个字符；
	//			2. 然后利用一个数组p[i]来保存以字符s[i]为中心时的回文子串长度. 根据回文字符串的对称性特点，
	//			   在中心右侧的字符s[i]对应的回文子串长度等于其左侧相应的p[2*c - i]和右边界减i的最小值，
	//             这是因为i' = c - (i - c)，如果i没有超过p[c]的右边界。否则就要算作p[c]的右边界减去i，超出部分重新计算。
	//			   因为这个差根据回文子串对称性能够保证是回文的。如果p[i]的子串右边界超过了p[c]的右边界，那么就将c移动到i，重新确立p[c]右边界。
	
	///@brief	对字符串进行预处理，插入"$"，"^"和"#"
	///@param	s	待处理的字符串
	///@return	返回插入字符"$"和"#"的字符串
	///@author	zhaowei
	///@date	2015.05.26
	string preprocessString(string s)
	{
		string ret = "$";
		int n = s.length();
		if (n == 0)
		{
			return ret;
		}

		for (int i = 0; i < n; i++)
		{
			ret += "#" + s.substr(i, 1);
		}
		ret += "#^";
		return ret;
	}

	///@brief	Manacher's Algorithm寻找最长回文子串
	///@param	s	待处理子串
	///@return	最长回文子串
	///@author  zhaowei
	///@date	2015.05.26
	string longestPalindrome_Manacher(string s)
	{
		string str_p = preprocessString(s);
		int n = str_p.length();
		int *p = new int[n];
		int c = 0;
		int r = 0;

		for (int i = 1; i < n-1; i++)	
		{
			int i_mirror = 2*c - i;

			p[i] = (i < r) ? min(p[i_mirror], r-i) : 0;

			while (str_p[i + p[i] + 1] == str_p[i - p[i] - 1])
			{
				p[i]++;
			}

			if (p[i] + i > r)
			{
				c = i;
				r = i + p[i];
			}
		}

		int pstr_head = 0;
		int pstr_len = 0;
		for (int i = 0; i < n-1; i++)
		{
			if (p[i] > pstr_len)
			{
				pstr_head = i;
				pstr_len = p[i];
			}
		}

		string pstr = s.substr((pstr_head - 1 - pstr_len)/2, pstr_len);

		delete []p;
		
		return pstr;
	}
};

#include <vector>

class Solution_v2 {
public:
	///@note	Manacher Algorithm. time: O(n)
	//			http://www.geeksforgeeks.org/manachers-algorithm-linear-time-longest-palindromic-substring-part-1/
	//			http://www.geeksforgeeks.org/manachers-algorithm-linear-time-longest-palindromic-substring-part-2/
    string longestPalindrome(string s) {
        string t ="$#";
        for (int i = 0; i < s.size(); ++i) {
            t += s[i];
            t += '#';
        }
        vector<int> p(t.size(), 0);
        int id = 0, mx = 0, resId = 0, resMx = 0;
        for (int i = 0; i < t.size(); ++i) {
            p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
            while (t[i + p[i]] == t[i - p[i]]) ++p[i];
            if (mx < i + p[i]) {
                mx = i + p[i];
                id = i;
            }
            if (resMx < p[i]) {
                resMx = p[i];
                resId = i;
            }
        }
        return s.substr((resId - resMx) / 2, resMx - 1);
    }
};

class Solution_v2_1 {
public:
	///@note	Manacher Algorithm. time: O(n)
	//			http://www.geeksforgeeks.org/manachers-algorithm-linear-time-longest-palindromic-substring-part-1/
	//			http://www.geeksforgeeks.org/manachers-algorithm-linear-time-longest-palindromic-substring-part-2/
	string longestPalindrome(string s) {
		int N = s.length();
		if (N == 0)	return "";
		if (N == 1)	return s;
		N = 2*N + 1; //Position count
		int* L = new int[N]; //LPS Length Array
		L[0] = 0;
		L[1] = 1;
		int C = 1; //centerPosition 
		int R = 2; //centerRightPosition
		int i = 0; //currentRightPosition
		int iMirror; //currentLeftPosition
		int expand = -1;
		int diff = -1;
		int maxLPSLength = 0;
		int maxLPSCenterPosition = 0;
		int start = -1;
		int end = -1;

		for (i = 2; i < N; i++) 
		{
			//get currentLeftPosition iMirror for currentRightPosition i
			iMirror  = 2*C-i;
			//Reset expand - means no expansion required
			expand = 0;
			diff = R - i;
			//If currentRightPosition i is within centerRightPosition R
			if(diff > 0) 
			{
				if(L[iMirror] < diff) // Case 1
					L[i] = L[iMirror];
				else if(L[iMirror] == diff && i == N-1) // Case 2
					L[i] = L[iMirror];
				else if(L[iMirror] == diff && i < N-1)  // Case 3
				{
					L[i] = L[iMirror];
					expand = 1;  // expansion required
				}
				else if(L[iMirror] > diff)  // Case 4
				{
					L[i] = diff;
					expand = 1;  // expansion required
				}
			}
			else
			{
				L[i] = 0;
				expand = 1;  // expansion required
			}

			if (expand == 1)
			{
				//Attempt to expand palindrome centered at currentRightPosition i
				//Here for odd positions, we compare characters and 
				//if match then increment LPS Length by ONE
				//If even position, we just increment LPS by ONE without 
				//any character comparison
				while (((i + L[i]) < N && (i - L[i]) > 0) && 
					( ((i + L[i] + 1) % 2 == 0) || 
					( s[(i + L[i] + 1)/2] == s[(i-L[i]-1)/2] )))
				{
					L[i]++;
				}
			}

			if(L[i] > maxLPSLength)  // Track maxLPSLength
			{
				maxLPSLength = L[i];
				maxLPSCenterPosition = i;
			}

			// If palindrome centered at currentRightPosition i 
			// expand beyond centerRightPosition R,
			// adjust centerPosition C based on expanded palindrome.
			if (i + L[i] > R) 
			{
				C = i;
				R = i + L[i];
			}
		}
		start = (maxLPSCenterPosition - maxLPSLength)/2;
		end = start + maxLPSLength - 1;
		delete []L;
		return s.substr(start, end - start + 1);
	}
};

class Solution {
public:
    string longestPalindrome(string s) {
        
    }
};

int main()
{
	Solution_v1 slt;
	string s = "a";
	string pstr_bf = slt.longestPalindrome_BruteForce(s);
	string pstr_dp = slt.longestPalindrome_DP(s);
	string pstr_extend = slt.longestPalindrome_extendAroundCenter(s);
	string pstr_manacher = slt.longestPalindrome_Manacher(s);

	Solution slt_;
	string rslt = slt_.longestPalindrome(s);
	cout << pstr_bf << endl;
	cout << pstr_dp;
	cout << endl;
	cout << pstr_extend << endl;
	cout << pstr_manacher << endl;
	return 0;
};
