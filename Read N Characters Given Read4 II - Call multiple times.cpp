///@file	Read N Characters Given Read4 II - Call multiple times
///@author	zhaowei
///@date	2016.01.06
///@version	1.0

///@date	2016.01.15
///@version	1.1

// Forward declaration of the read4 API.
#include <queue>
using namespace std;
int read4(char *buf);

class Solution_v1 {
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
	 * @note	1. 用一个额外的队列来保存每次读入4个字符的时造成的多余字符，比如n = 10，那么只能读3次，3 * 4 = 12，超出的2个字符就放入队列中，
				   下次优先从队列中读取；
				2. 当读取完队列后，就从buf中读取，直到读出的字符数目不少于n；
				3. 然后将超过部分放入队列；
				4. 最后取min(实际读出的字符数，指定的字符数)来作为读出字符串的结束字符。因为当buf中字符数目不足时，实际读出的字符数就可能比较小；
				   当指定字符数除去之前在队列中读出的字符后不能被4整除时，实际读出的字符数就比较大。
     */
    int read(char *buf, int n) {
        int len = 0;	//	实际读出的字符数
		while (!que.empty()) {
			buf[len++] = que.front();
			que.pop();
			if (len == n)	return len;	//	当队列中剩余的字符已经足够时，直接返回
		}
		int cnt = 0;	//	单次调用read4()读出的字符数
		while (len < n) {
			cnt = read4(buf + len);	//	从read4中读取的字符串房子buf + len的位置
			len += cnt;
			if (cnt < 4)	break;
		}
		for (int i = n; i < len; i++) {
			que.push(buf[i]);
		}
		int end = min(len, n);
		buf[end] = '\0';
		return end;
    }

	queue<char> que;
};

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
		int len = 0;
        while (!que.empty()) {
			buf[len++] = que.front();
			que.pop();
			if (len == n)	return n;
		}
		int num = 0;
		while (len < n) {
			num = read4(buf + len);
			len += num;
			if (num < 4)	break;
		}
		for (int i = n; i < len; i++)
			que.push(buf[i]);
		int end = min(len, n);
		buf[end] = '\0';
		return end;
    }
private:
	queue<char> que;
};

int main() {
	return 0;
}