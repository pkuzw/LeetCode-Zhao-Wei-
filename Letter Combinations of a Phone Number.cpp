///@brief	Letter Combinations of a Phone Number 
/*			Given a digit string, return all possible letter combinations that the number could represent.

			A mapping of digit to letters (just like on the telephone buttons) is given below.

			Input:Digit string "23"

			Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

			Although the above answer is in lexicographical order, your answer could be in any order you want.
*/
///@author  zhaowei
///@date	2015.06.05
///@version	1.0

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
	vector<string> letterCombinations(string digits) {

		vector<string> digitToChar;
		string str[10] = {" ", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
		vector<string> rslt;
		string s;
		int cnt[10] = {0};
		for (int i = 0; i < 10; i++)
		{
			cnt[i] = 0;
		}

		int k = 0;
		for (int j = 0; j < str[k].length(); j++)
		{
			for (int i = 0; i < digits.length(); i++)
			{
				s += str[i][cnt[i]++];
			}
			k++;
		}

		
	}
};

int main()
{
	string s = "23";
	Solution slt;
	vector<string> rslt = slt.letterCombinations(s);
	for (int i = 0; i < rslt.size(); i++)
	{
		cout << rslt[i] << ' ';
	}
	cout << endl;

	return 0;
}