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

class Solution_v2 {
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

class Solution_wa {
public:
	///@note	1. ��������������¼"()", "[]"��"{}"�Ƿ���˳��ɶԳ��֣�
	//			2. ����������ʱ������1������������ʱ������1��
	//			3. ��������С���㣬����ѭ��ʱ�������ܲ�Ϊ�㣻	
	//			4. ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1).
	//			5. �����"([)]"�ϡ�
	bool isValid(string s) {
		int bcnt[3] = {0};
		string brackets = "()[]{}";
		for (int i = 0; i != s.size(); i++) {
			for (int j = 0; j != 6; j++) {
				if (j % 2 == 0 && s[i] == brackets[j])	bcnt[j/2]++;				
				if (j % 2 == 1 && s[i] == brackets[j]) {
					if (bcnt[j/2] <= 0)	return false;
					bcnt[j/2]--;
					if (!bcnt[j/2]) {
						for (int k = 0; k != 3; k++) {
							if (k == j / 2)	continue;
							if (bcnt[k])	return false;
						}
					}
				}
			}			
		}
		return (!bcnt[0]) && (!bcnt[1]) && (!bcnt[2]);
	}
};

int main()
{
	string s = "([)]";
	Solution slt;
	bool rslt = slt.isValid(s);
	Solution_v1 s1;
	bool r1 = s1.isValid(s);
	Solution_v2 s2;
	bool r2 = s2.isValid(s);
	return 0;
}