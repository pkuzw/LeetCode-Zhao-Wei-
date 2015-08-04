///@file	Different Ways to Add Parentheses
/*
Given a string of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. The valid operators are +, - and *.

Example 1

Input: "2-1-1".

((2-1)-1) = 0
(2-(1-1)) = 2

Output: [0, 2]

Example 2

Input: "2*3-4*5"

(2*(3-(4*5))) = -34
((2*3)-(4*5)) = -14
((2*(3-4))*5) = -10
(2*((3-4)*5)) = -10
(((2*3)-4)*5) = 10

Output: [-34, -14, -10, -10, 10]
*/
///@author	zhaowei
///@date	2015.08.04
///@version	1.0

#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
	///@brief	给定一个算术表达式，计算各种插入括号后可能的值
	///@param	input	算术表达式
	///@return	返回可能的结果值
	/* @note	递归+动规：对于每一个运算符，都是先计算其左边的表达式，再计算其右边的表达式，然后根据中的运算符，来运算左右两边的子结果。
				因为这期间会多次重复计算，建立一个哈希表，key为表达式，val为该表达式可能的值。*/
	vector<int> diffWaysToCompute(string input) {
		unordered_map<string, vector<int>> hash_table;
		return diffWaysToComputeRecur(input, hash_table);
	}
private:
	///@brief	递归的计算算术表达式添加括号后可能的值
	vector<int> diffWaysToComputeRecur(string input, unordered_map<string, vector<int>>& hash_table)
	{
		vector<int> rslt;
		for (int i = 0; i < input.size(); i++)
		{
			if (input[i] == '+' || input[i] == '-' || input[i] == '*')	//	将表达式分为运算符左边的子式和右边的子式
			{
				vector<int> rslt1, rslt2;
				string s1 = input.substr(0, i);
				string s2 = input.substr(i+1, input.length()-i-1);

				if (hash_table.find(s1) != hash_table.end())	rslt1 = hash_table[s1];	//	查找在哈希表中是否存在
				else	rslt1 = diffWaysToComputeRecur(s1, hash_table);		//	不存在就递归的往下算

				if (hash_table.find(s2) != hash_table.end())	rslt2 = hash_table[s2];
				else	rslt2 = diffWaysToComputeRecur(s2, hash_table);

				for (int j = 0; j != rslt1.size(); j++)
				{
					for (int k = 0; k != rslt2.size(); k++)
					{
						if (input[i] == '+')	rslt.push_back(rslt1[j] + rslt2[k]);	//	根据运算符来计算左右两边
						else if (input[i] == '-')	rslt.push_back(rslt1[j] - rslt2[k]);
						else if (input[i] == '*')	rslt.push_back(rslt1[j] * rslt2[k]);
					}
				}
			}
		}

		if (rslt.empty())	//	如果只有一个数字，没有运算符
			rslt.push_back(stoi(input));
		hash_table[input] = rslt;	//	添加到哈希表中
		return rslt;
	}
};

int main()
{
	string s = "2*3-4*5";
	Solution slt;
	vector<int> rslt = slt.diffWaysToCompute(s);
	return 0;
}