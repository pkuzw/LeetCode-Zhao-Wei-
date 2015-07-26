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
	/* @note	��ʮ������n���Լ�1��Ȼ�󲻶ϵ�ģ26������+'A'����ĳһλ��Ȼ����n�Գ�26��ֱ����Ϊ0Ϊֹ��ʱ�临�Ӷ�ΪO(logn)���ռ临�Ӷ�ΪO(1)*/
	string convertToTitle(int n) {
		string s;
		while (n > 0)
		{
			n--;
			int k = n % 26;
			s = char('A'+k) + s;
			n /= 26;
		}
		return s;
	}


};

int main()
{
	int n = 702;
	Solution slt;

	string s = slt.convertToTitle(n);
	return 0;
}
