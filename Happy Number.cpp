///@file	Happy Number
/*
Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: Starting with any positive integer, replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.

Example: 19 is a happy number

12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1

*/
///@author	zhaowei
///@date	2015.07.28
///@version	1.0

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
	///@brief	判断一个数能否通过将各位平方后求和，迭代的最后结果是1
	///@param	n	整数
	///@return	如果能够迭代到1，则返回true；否则返回false
	/* @brief	用哈希表保存每一个数的各位平方和，如果出现以前有过的数，则返回false。否则就一直计算下去，直到计算到1为止。*/
	bool isHappy(int n) {
		unordered_set<int> hash_table;
		while (n != 1)
		{
			vector<int> digit;
			while (n > 0)
			{
				digit.push_back(n % 10);
				n /= 10;
			}
			for (int i = 0; i < digit.size(); i++)
				n += digit[i]*digit[i];

			if (hash_table.find(n) == hash_table.end())	
				hash_table.insert(n);
			else									
				return false;
		}
		return true;
	}
};

int main()
{
	int n = 1;
	Solution slt;
	bool rslt = slt.isHappy(n);
	return 0;
}