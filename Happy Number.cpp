///@file	Happy Number
/*
Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: Starting with any positive integer, 

replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 

(where it will stay), or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends 

in 1 are happy numbers.

Example: 19 is a happy number

12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1

*/
///@author	zhaowei
///@date	2015.07.28
///@version	1.0

///@date	2015.08.11
///@version	1.1

///@date	2016.01.24
///@version	1.2

#include <vector>
#include <unordered_set>

using namespace std;

class Solution_v1 {
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

class Solution {
public:
	///@brief	判断一个正整数是否为幸福数。幸福数的定义为对于一个正整数的各位依次求平方和，得到一个新的数，只要该数不为1，则迭代继续求其各位平方和。如果为1，则是幸福数，否则不是。
	///@param	n	正整数
	///@return	返回一个数是否为幸福数。
	///@note	1. 利用哈希表来保存迭代过程中出现的各个中间值，如果没有重复值且为1，则是幸福数，否则不是。
	bool isHappy(int n) {
		unordered_set<int> hash_tbl;
		while (n != 1) {
			vector<int> digits;			
			while (n) {
				digits.push_back(n % 10);
				n /= 10;
			}
			for (int i = 0; i != digits.size(); i++)
				n += digits[i] * digits[i];
			if (hash_tbl.find(n) == hash_tbl.end())	hash_tbl.insert(n);
			else	return false;
		}
		return true;
	}
};

int main()
{
	int n = 2;
	Solution_v1 slt_v1;
	bool rslt1 = slt_v1.isHappy(n);

	Solution slt;
	bool rslt = slt.isHappy(n);
	return 0;
}