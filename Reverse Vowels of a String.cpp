///@file	Reverse Vowels of a String
///@author	zhaowei
///@date	2016.04.23
///@version	1.0

#include <string>
#include <vector>
using namespace std;

class Solution {
public:
	///@brief	将字符串中的元音字符颠倒
	///@param	s	字符串
	///@return	返回颠倒元音字符后的字符串	
	///@note	1. 枚举；
	//			2. 用一个数组记录下元音字符的下标，用swap函数交换前后端的元音字符；
	//			3. 时间复杂度为O(n)，空间复杂度为O(n)。
	string reverseVowels(string s) {
		if (s.empty())	return s;
		vector<int> vowel;
		for (int i = 0; i != s.size(); i++)
			if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' ||
				s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U')	vowel.push_back(i);
		for (int i = 0; i != vowel.size() / 2; i++)	swap(s[vowel[i]], s[vowel[vowel.size() - 1 - i]]);
		return s;
	}
};

int main() {
	string s = "eeaoo";
	Solution slt;
	string r = slt.reverseVowels(s);
	return 0;
}