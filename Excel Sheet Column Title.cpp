///@file	Excel Sheet Column Title
/*
Given a positive integer, return its corresponding column title as appear in an Excel sheet.

For example:

1 -> A
2 -> B
3 -> C
...
26 -> Z
27 -> AA
28 -> AB 
*/
///@author	zhaowei
///@date	2015.07.26
///@version	1.0

#include <string>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
	///@brief	��int��������ת���ɶ�ʮ����������:A, B, C, ..., Z, AA, AB, ...
	///@param	n	ʮ��������
	///@return	���ض�ʮ���������ַ���
	/* @note	����һ������洢26^k�ݣ�Ȼ����ʮ������n�Ӹߵ��ͳ���������飬�õ����̾��Ƕ�ʮ�����Ƶĸ���λ*/
	string convertToTitle(int n) {
		int ts[7] = {0};
		ts[0] = 1;
		for (int i = 1; i < 7; i++)
		{
			int k = 1;
			for (int j = 0; j < i; j++)
				k *= 26;
			ts[i] = k;
		}

		string s;
		for (int i = 6; i >= 0; i--)
		{
			int div = 0;
			if (n > ts[i])
			{
				div = n / ts[i];

				s += char('A' + div - 1);
				
				n %= ts[i];
			}
		}
		//s += char('A' + n - 1);

		return s;
	}
};

int main()
{
	int n = 1;
	Solution slt;

	string s = slt.convertToTitle(n);
	return 0;
}
