///@file	Longest Substring with At Most K Distinct Characters
///@author	zhaowei
///@date	2016.04.05
///@version	1.0

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
	///@brief	计算最多含有k个不同字符的子串长度
	///@param	s	字符串
	///@param	k	不同字符数目
	///@return	返回合法的最长子串长度
	///@note	1. 用哈希表保存当前子串的不同字符出现的种类数；
	//			2. 设置左右两个指针指向子串的左右边界，当不同字符种类数超过k时，先移动左边界知道左右边界相等时，再移动右边界；
	int lengthOfLongestSubstringKDistinct(string s, int k) {
		unordered_map<char, int> hash_tbl;
		int left = 0, right = 1;
		int max_sub_len = 0;
		if (!k || s.empty())	return 0;
		else if (s.size() == 1)	return 1;
		hash_tbl[s[left]]++;
		for (right = 1; right != s.size(); right++) {			
			if (hash_tbl.size() == k) {
				max_sub_len = max(max_sub_len, right - left + 1);
			}
			else if (hash_tbl.size() > k) {
				hash_tbl[s[left]]--;
				if (!hash_tbl[s[left]])	hash_tbl.erase(hash_tbl.find(s[left++]));
			}
			hash_tbl[s[right]]++;
		}
		return max_sub_len;
	}
};

int main() {
	string s = "eceba";
	Solution slt;
	int rslt = slt.lengthOfLongestSubstringKDistinct(s, 2);
	return 0;
}