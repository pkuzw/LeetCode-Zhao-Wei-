///@file	Longest Substring with At Most Two Distinct Characters
/*
Given a string, find the length of the longest substring T that contains at most 2 distinct characters.

For example, Given s = “eceba”,

T is "ece" which its length is 3.
*/
///@author	zhaowei
///@date	2015.08.14
///@version	1.0

//	如果是n种字符呢？
#include <string>
using namespace std;

class Solution {
public:
	///@brief	计算最多只有两个不同字符组成的字符串的最大长度
	///@param	s	字符串
	///@return	返回字符串的最大长度
	///@note	1. 用i表示合法子串的第一种字符的首次出现下标，初始化为0；j表示合法子串第二种字符的首次出现下标，初始化为-1；
	//			2. 从字符串的s[1]开始遍历，如果s[k] == s[k - 1]，则进入下一次迭代；
	//			3. 如果j > -1 && s[k] != s[j]，则说明子串中出现了超过2种字符，计算出当前子串的长度，并和之前获得的最长子串长度比较，记下较长者，然后更新i；
	//			4. 在每次循环中都要将j更新为k - 1；
	//			5. 最后返回时，要比较最长值和s.size() - i的值，因为有可能后面出现连续相同字符直到结束，这样是没办法进入循环中的更新最长值代码的，需要在最后判断一下；
	//			6. 时间复杂度为O(n)，空间复杂度为O(1)。
	int lengthOfLongestSubstringTwoDistinct(string s) {
		int i = 0, j = -1, rslt = 0;
		for (int k = 1; k < s.size(); k++) {
			if (s[k] == s[k - 1]	)	continue;
			if (j > -1 && s[k] != s[j]) {
				rslt = max(rslt, k - i);
				i = j + 1;
			}
			j = k - 1;
		}
		return rslt > s.size() - i ? rslt : s.size() - i;
	}
};

int main()
{
	string s = "eceecebaaaaaaaaaa";
	Solution slt;
	int rslt = slt.lengthOfLongestSubstringTwoDistinct(s);
	return 0;
}