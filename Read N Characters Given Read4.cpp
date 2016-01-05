///@file	Read N Characters Given Read4
/*
The API: int read4(char *buf) reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

Note:
The read function will only be called once for each test case.
*/
///@author	zhaowei
///@date	2016.01.05
///@version	1.0


#include <iostream>
using namespace std;

// Forward declaration of the read4 API.
int read4(char *buf) {
	return 4;
}

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
	 * @note	1. ����һ����ʱ��������ÿ�ε���read4()��ķ���ֵ���������ʱ����Ϊ4���ۻ������ַ���С��n����һֱ����read4��ֱ������n��
				2. ����n�����ַ����ˣ�����'\0'�����ַ�����
				3. ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)��
     */
    int read(char *buf, int n) {
		int tmp = 4;	//	ÿ�ε���read4()�ķ���ֵ
		int num = 0;	//	�ۻ��������ַ���
		while (num < n && tmp == 4) {
			tmp = read4(buf);
			buf += tmp;	//	�ƶ��ַ���ָ��
			num += tmp;
			while (num > n) {
				buf--;
				num--;
				*buf = '\0';	//	�����ַ���
			}
		}
		return num;
    }
};

int main() {
	char *buf = "";
	Solution slt;
	int k = slt.read(buf, 1);
	return 0;
}