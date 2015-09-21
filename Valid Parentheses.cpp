///@brief	Valid Parentheses
/*			
			Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

			The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
*/
///@author	zhaowei
///@date	2015.06.05
///@version 1.0
///@note	ͨ���۲��˼�����֣���Ч���ŶԾ������ڲ�����Ŷ�һ���ǽ����ŵġ�
//			���ҵ���һ������һ������Ŷԣ�������ȥ��Ȼ������ҽ����ŵ�һ�����ţ�ֱ���ܹ����ַ���ɾ��Ϊֹ����ʱ�ַ���Ϊ��Ч���Ŷԣ�����Ϊ��Ч�����Ŷԡ�

///@date    2015.09.07
///@version 2.0

///@date	2015.09.21
///@version	2.1
#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Solution_v1
{
public:
	///@brief	�ж��ַ����Ƿ�Ϊ��Ч���Ŷ����
	///@param	s	���жϵ��ַ���
	///@return	����ַ�����Ч������true�����򷵻�false
	///@author	zhaowei
	///@date	2015.06.05
	bool isValid(string s) {

		int len = s.length();
		int cnt = len/2;
		while (cnt--)	//����Ӧ����cnt��ô��������ǲ������ŵ�
		{
			for (int i = 0; i < s.length()-1; i++)
			{
				if (s.empty())	// ����ַ����Ѿ�Ϊ�գ��򷵻�true
				{
					return true;
				}

				// �ҵ����ڲ����Ŷԣ��������ɾ������
				if ((s[i] == '(' && s[i+1] == ')') 
					||(s[i] == '[' && s[i+1] == ']') 
					||(s[i] == '{' && s[i+1] == '}') 
					)
				{
					s.erase(i, 2);	// ����string::erase(pos, num)���Դӵ�iλ��ʼ�����������ַ�����ɾ������
				}
			}
		}		
		return false;	// ���sû����whileѭ���ڲ���գ��򷵻�false

	}
};

class Solution {
public:
	///@brief	�ж�һ�������ַ����Ƿ�Ϸ���
	///@param	s	�����ַ���
	///@return	����ַ����ǺϷ��������ַ������򷵻�true�����򷵻�false
	///@note	����ջ����������ַ���������������ţ���ѹջ������������ţ���ջ��Ԫ���Ƿ�͸�������ƥ�䣬�����ƥ���򷵻�false�����򵯳�ջ��Ԫ�أ��������ƥ�䡣ֱ���ַ���������
	//			ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(n)��
    bool isValid(string s) {
		stack<char> stk;
		if (s.empty())	return true;
		for (int i = 0; i != s.size(); i++) {
			if (s[i] == '(' || s[i] == '{' || s[i] == '[')	stk.push(s[i]);
			else {
				if (stk.empty())	return false;
				if ((s[i] == ')' && stk.top() != '(') ||
					(s[i] == ']' && stk.top() != '[') ||
					(s[i] == '}' && stk.top() != '{'))
					return false;
				stk.pop();
			}
		}
		return stk.empty();
    }
};

int main()
{
	string s = "([]{}{}{})";
	Solution slt;
	cout << slt.isValid(s) << endl;
	return 0;
}