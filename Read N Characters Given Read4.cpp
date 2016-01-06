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
	 * @note	1. 建立一个临时变量保存每次调用read4()后的返回值，如果该临时变量为4且累积读出字符数小于n，则一直调用read4，直到超过n；
				2. 超过n后逐字符回退，并用'\0'结束字符串。
				3. 时间复杂度为O(n)，空间复杂度为O(1)。
     */
    int read(char *buf, int n) {
		int tmp = 4;	//	每次调用read4()的返回值
		int num = 0;	//	累积读出的字符数
		while (num < n && tmp == 4) {
			tmp = read4(buf);
			buf += tmp;	//	移动字符串指针
			num += tmp;
			while (num > n) {
				buf--;
				num--;
				*buf = '\0';	//	结束字符串
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