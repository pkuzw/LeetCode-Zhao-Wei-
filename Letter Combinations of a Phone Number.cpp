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
///@note	����ö�٣��ύ��Memory Limit Exceed

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
	///@brief	���绰�����ϵ�����ת������ĸ
	///@param	digits	������������ַ���
	///@return	���������ĸ���
	///@author	zhaowei
	///@date	2015.06.08
	vector<string> letterCombinations(string digits) {

		vector<string> digitToChar;	//	��¼������ĸ���
		string str[10] = {" ", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};	//	��¼�����ּ���Ӧ�ķ���
		int d_len = digits.length();
		int *d_cnt = new int[d_len];	//	�½�����Ϊ�����ַ������Ķ�̬int�����飬���汣��ÿһλ���ֵ�ѭ������
		for (int i = 0; i < d_len; i++)	//	��ʼ��Ϊ0
			d_cnt[i] = 0;

		int lmt[10] = {1, 1, 3, 3, 3, 3, 3, 4, 3, 4};	//	ÿ�����ֶ�Ӧ���ַ�����
		bool flg = false;		//	�ж���������ı��
		while (1)
		{ 			
			if (flg)
			{
				break;
			}

			string s;
			for (int i = 0; i < d_len; i++)
			{
				int indx = int(digits[i] - '0');		//	���ַ���ʾ������ת����int�ͱ���
				s += str[indx][d_cnt[i]];

				if ((i < d_len-1 && d_cnt[i+1] == lmt[indx+1])	//	���±�Ϊ���һλ���ֻ��ߺ�һλ�Ѿ���λ����������1
					|| (i == d_len-1))
				{
					d_cnt[i]++;
					if (d_cnt[i] == lmt[indx])	//	��λ
					{
						d_cnt[i] = 0;
						int j = i-1;
						if (j < 0)
						{
							flg = true;
							break;
						}
						d_cnt[j]++;						
						while (d_cnt[j] == lmt[(int)(digits[j]-'0')])	//	�Ӻ���ǰ��λ��λ
						{
							if (j == 0)	//	�����������еĿ���
							{
								flg = true;	
								break;
							}
							d_cnt[j] = 0;
							j--;
							d_cnt[j]++;
						}						
					}					
				}				
			}
			digitToChar.push_back(s);
		}	
		delete []d_cnt;
		return digitToChar;
	}
};

int main()
{
	string s = "2334";	
	Solution slt;
	vector<string> rslt = slt.letterCombinations(s);
	for (int i = 0; i < rslt.size(); i++)
	{
		cout << rslt[i] << ' ';
	}
	cout << endl;

	return 0;
}