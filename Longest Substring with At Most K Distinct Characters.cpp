///@file	Longest Substring with At Most K Distinct Characters
///@author	zhaowei
///@date	2016.04.06
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
	//			2. 设置左右两个指针指向子串的左右边界，当不同字符种类数超过k时，移动左边界，并且自减其在哈希表中的键值，如果键值减为零，则清除该项；
	//			3. 如果哈希表中的元素数等于k，则判断子串的长度是否超过了最大长度，如果是则更新之；
	//			4. 否则就继续移动右边界。这里的右边界实际并不是子串的最后一个字符，而是最后一个字符的下一个字符；
	//			5. 最后结束循环后要补上含最后一个字符的可能合法字符子串的长度，并返回之；
	//			6. 时间复杂度为O(n)，空间复杂度为O(n)，这里n是字符串长度。
	int lengthOfLongestSubstringKDistinct(string s, int k) {
		unordered_map<char, int> hash_tbl;
		int left = 0, right = 0;
		int max_sub_len = 0;
		if (!k || s.empty())	return 0;
		else if (s.size() == 1)	return 1;		
		for (right = 0; right < s.size(); right++) {
			while (hash_tbl.size() > k) {
				hash_tbl[s[left]]--;
				if (!hash_tbl[s[left]])	hash_tbl.erase(hash_tbl.find(s[left]));
				left++;
			}	
			if (hash_tbl.size() == k)	max_sub_len = max(max_sub_len, right - left);			
			
			if (hash_tbl.size() <= k)	hash_tbl[s[right]]++;								
		}
		return hash_tbl.size() <= k ? max(max_sub_len, right - left) : max_sub_len;		
	}
};

int main() {
	string s = "edaedaeed";
	Solution slt;
	int rslt = slt.lengthOfLongestSubstringKDistinct(s, 2);
	return 0;
}