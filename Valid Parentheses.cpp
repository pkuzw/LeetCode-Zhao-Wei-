///@brief	Valid Parentheses
/*			
			Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

			The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
*/
///@author	zhaowei
///@date	2015.06.05
///@version 1.0
///@note	通过观察和思考发现，有效括号对具有最内层的括号对一定是紧邻着的。
//			先找到第一个挨在一起的括号对，将它舍去，然后接着找紧挨着的一对括号，直到能够将字符串删空为止，此时字符串为有效括号对；否则为无效的括号对。

///@date    2015.09.07
///@version 2.0
#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Solution_v1
{
public:
	///@brief	判断字符串是否为有效括号对组成
	///@param	s	待判断的字符串
	///@return	如果字符串有效，返回true；否则返回false
	///@author	zhaowei
	///@date	2015.06.05
	bool isValid(string s) {

		int len = s.length();
		int cnt = len/2;
		while (cnt--)	//至少应该有cnt这么多对括号是不紧挨着的
		{
			for (int i = 0; i < s.length()-1; i++)
			{
				if (s.empty())	// 如果字符串已经为空，则返回true
				{
					return true;
				}

				// 找到最内层括号对，对其进行删除操作
				if ((s[i] == '(' && s[i+1] == ')') 
					||(s[i] == '[' && s[i+1] == ']') 
					||(s[i] == '{' && s[i+1] == '}') 
					)
				{
					s.erase(i, 2);	// 利用string::erase(pos, num)来对从第i位开始的连续两个字符进行删除操作
				}
			}
		}		
		return false;	// 如果s没有在while循环内部清空，则返回false

	}
};

class Solution {
public:
    bool isValid(string s) {
        stack<char> parentheses;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{') parentheses.push(s[i]);
            else {
                if (parentheses.empty()) return false;
                if (s[i] == ')' && parentheses.top() != '(') return false;
                if (s[i] == ']' && parentheses.top() != '[') return false;
                if (s[i] == '}' && parentheses.top() != '{') return false;
                parentheses.pop();
            }
        }
        return parentheses.empty();
    }
};

int main()
{
	string s = "([]{}{}{})";
	Solution slt;
	cout << slt.isValid(s) << endl;
	return 0;
}