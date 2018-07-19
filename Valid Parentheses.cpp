///@brief	Valid Parentheses
/*			
			Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

			The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
*/
///@author	zhaowei
///@date	2015.06.05
///@version 1.0
///@note	Õ®π˝π€≤Ï∫ÕÀºøº∑¢œ÷£¨”––ß¿®∫≈∂‘æﬂ”–◊Óƒ⁄≤„µƒ¿®∫≈∂‘“ª∂® «ΩÙ¡⁄◊≈µƒ°£
//			œ»’“µΩµ⁄“ª∏ˆ∞§‘⁄“ª∆µƒ¿®∫≈∂‘£¨Ω´À¸…·»•£¨»ª∫ÛΩ”◊≈’“ΩÙ∞§◊≈µƒ“ª∂‘¿®∫≈£¨÷±µΩƒ‹πªΩ´◊÷∑˚¥Æ…æø’Œ™÷π£¨¥À ±◊÷∑˚¥ÆŒ™”––ß¿®∫≈∂‘£ª∑Ò‘ÚŒ™Œﬁ–ßµƒ¿®∫≈∂‘°£

///@date    2015.09.07
///@version 2.0

///@date	2015.09.21
///@version	2.1

///@date	2016.04.05
///@version	3.0	wa
///@version	2.2

///@date    July 19, 2018
///@version 2.3

#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Solution_v1
{
public:
	///@brief	≈–∂œ◊÷∑˚¥Æ «∑ÒŒ™”––ß¿®∫≈∂‘◊È≥…
	///@param	s	¥˝≈–∂œµƒ◊÷∑˚¥Æ
	///@return	»Áπ˚◊÷∑˚¥Æ”––ß£¨∑µªÿtrue£ª∑Ò‘Ú∑µªÿfalse
	///@author	zhaowei
	///@date	2015.06.05
	bool isValid(string s) {

		int len = s.length();
		int cnt = len/2;
		while (cnt--)	//÷¡…Ÿ”¶∏√”–cnt’‚√¥∂‡∂‘¿®∫≈ «≤ªΩÙ∞§◊≈µƒ
		{
			for (int i = 0; i < s.length()-1; i++)
			{
				if (s.empty())	// »Áπ˚◊÷∑˚¥Æ“—æ≠Œ™ø’£¨‘Ú∑µªÿtrue
				{
					return true;
				}

				// ’“µΩ◊Óƒ⁄≤„¿®∫≈∂‘£¨∂‘∆‰Ω¯––…æ≥˝≤Ÿ◊˜
				if ((s[i] == '(' && s[i+1] == ')') 
					||(s[i] == '[' && s[i+1] == ']') 
					||(s[i] == '{' && s[i+1] == '}') 
					)
				{
					s.erase(i, 2);	// ¿˚”√string::erase(pos, num)¿¥∂‘¥”µ⁄iŒªø™ ºµƒ¡¨–¯¡Ω∏ˆ◊÷∑˚Ω¯––…æ≥˝≤Ÿ◊˜
				}
			}
		}		
		return false;	// »Áπ˚s√ª”–‘⁄while—≠ª∑ƒ⁄≤ø«Âø’£¨‘Ú∑µªÿfalse

	}
};

class Solution_v2 {
public:
	///@brief	≈–∂œ“ª∏ˆ¿®∫≈◊÷∑˚¥Æ «∑Ò∫œ∑®°£
	///@param	s	¿®∫≈◊÷∑˚¥Æ
	///@return	»Áπ˚◊÷∑˚¥Æ «∫œ∑®µƒ¿®∫≈◊÷∑˚¥Æ£¨‘Ú∑µªÿtrue£ª∑Ò‘Ú∑µªÿfalse
	///@note	¿˚”√’ª¿¥¥Ê∑≈¿®∫≈◊÷∑˚¥Æ£¨»Áπ˚ «◊Û¿®∫≈£¨‘Ú—π’ª£ª»Áπ˚ «”“¿®∫≈£¨ø¥’ª∂•‘™Àÿ «∑Ò∫Õ∏√”“¿®∫≈∆•≈‰£¨»Áπ˚≤ª∆•≈‰‘Ú∑µªÿfalse£ª∑Ò‘ÚµØ≥ˆ’ª∂•‘™Àÿ£¨ºÃ–¯œÚ∫Û∆•≈‰°£÷±µΩ◊÷∑˚¥ÆΩ· ¯°£
	//			 ±º‰∏¥‘”∂»Œ™O(n)£¨ø’º‰∏¥‘”∂»Œ™O(n)°£
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
	///@note	1. ”√»˝∏ˆ±‰¡ø¿¥º«¬º"()", "[]"∫Õ"{}" «∑Ò∞¥’’À≥–Ú≥…∂‘≥ˆœ÷£ª
	//			2. ≥ˆœ÷◊Û¿®∫≈ ±±‰¡øº”1£¨≥ˆœ÷”“¿®∫≈ ±±‰¡øºı1£ª
	//			3. ±‰¡ø≤ªƒ‹–°”⁄¡„£¨Ω· ¯—≠ª∑ ±±‰¡ø≤ªƒ‹≤ªŒ™¡„£ª	
	//			4.  ±º‰∏¥‘”∂»Œ™O(n)£¨ø’º‰∏¥‘”∂»Œ™O(1).
	//			5. ª·π“‘⁄"([)]"…œ°£
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

class Solution_v2_1 {
public:
	bool isValid(string s) {
		stack<char> stk;
		if (s.empty())	return true;
		for (int i = 0; i != s.size(); i++) {
			if (s[i] == '(' || s[i] == '[' || s[i] == '{') stk.push(s[i]);
			else {
				if (stk.empty() 
					|| (s[i] == ')' && stk.top() != '(')
					|| (s[i] == ']' && stk.top() != '[')
					|| (s[i] == '}' && stk.top() != '{'))
					return false;
				else	stk.pop();
			}
		}
		return stk.empty();
	}
};

class Solution {
public:
    ///@brief   判定一组由'(', ')', '[', ']', '{', '}'组成的字符串是否是有效的，即每一个左括号都有同种的右括号与之对应。
    ///@param   s   字符串
    ///@return  如果字符串合法，返回true；否则返回false。
    ///@note    1. 用栈来保存字符串中的左括号，遇到右括号时判定栈顶元素是否是同种的左括号，如果不是返回false，否则弹栈，直到栈为空。
    //          2. 时间复杂度为O(n)，空间复杂度为O(n)，其中n为字符串长度。
    bool isValid(string s) {
        stack<char> stk;
        if (s.empty())  return true;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{')  stk.push(s[i]);
            else if (stk.empty() ||
                     (s[i] == ')' && stk.top() != '(') ||
                     (s[i] == ']' && stk.top() != '[') ||
                     (s[i] == '}' && stk.top() != '{'))
                return false;
            else
                stk.pop();
        }
        return stk.empty();
    }
};

int main()
{
	string s = "])";
	Solution slt;
	bool rslt = slt.isValid(s);
	Solution_v1 s1;
	bool r1 = s1.isValid(s);
	Solution_v2 s2;
	bool r2 = s2.isValid(s);
    cout << "rslt: " << rslt << endl;
    cout << "r1: " << r1 << endl;
    cout << "r2: " << r2 << endl;
	return 0;
}
