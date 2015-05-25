///@file	Given a string S, find the longest palindromic substring in S. 
///			You may assume that the maximum length of S is 1000, and there exists one unique longest palindromic substring.
///@author	zhaowei
///@date	2015.05.25
///@version 1.0
///@note	��򵥵ķ�������O(n^2)�ĸ��Ӷ�ö�����������У��ᳬʱ��
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
	string longestPalindrome(string s) {
		int pstr_head = 0;	//���������е����ַ�����
		int pstr_len = 1;	//���������еĳ���
		string pstr;
		for (int i = 0; i < s.length(); i++)	//ö��
		{
			int l = i;
			int count = 0;						//����������еĳ���
			int k = 1;							//���ڱ�ǵڶ���ѭ�����ַ���ĩβ�ַ�
			for (int j = s.length() - 1; j >= i-1 && j >= 0; j--)
			{				
				if (s[l] == s[j] && l != j && l != j+1)	//i != j�ǻ����ַ���Ϊ�������ȵ����Σ�i == j+!�ǻ�������Ϊż�����ȵ�����
				{
					l++;
					count++;
					continue;
				}
				else
				{
					if (j - l == 0)				//�����ַ���Ϊ�������ȵ�����
					{
						if (pstr_len < count*2 + 1)
						{
							pstr_head = i;
							pstr_len = count * 2 + 1;
							break;
						}
					}
					else if (l == j+1)			//�����ַ���Ϊż�����ȵ�����
					{
						if (pstr_len < count*2)
						{
							pstr_head = i;
							pstr_len = count * 2;
							break;
						}
					}
					else						//���ö�ٵ����ַ������ǻ����ַ���������ĩβ�ַ�����ʼ�ַ�
					{						
						j = s.length() - k;
						k++;
						l = i;
						count = 0;
					}
				}
			}
		}
		char buff[1000] = "";
		s.copy(buff, pstr_len, pstr_head);		//ͨ��string�Դ���copy�����������ַ����������ַ�������
		pstr = buff;
		return pstr;
	}
};

int main()
{
	Solution slt;
	string s = "aabbaacccc";
	string pstr = slt.longestPalindrome(s);
	cout << pstr;
	cout << endl;
	return 0;
};