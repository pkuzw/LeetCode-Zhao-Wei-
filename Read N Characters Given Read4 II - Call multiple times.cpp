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
	 * @note	1. ��һ������Ķ���������ÿ�ζ���4���ַ���ʱ��ɵĶ����ַ�������n = 10����ôֻ�ܶ�3�Σ�3 * 4 = 12��������2���ַ��ͷ�������У�
				   �´����ȴӶ����ж�ȡ��
				2. ����ȡ����к󣬾ʹ�buf�ж�ȡ��ֱ���������ַ���Ŀ������n��
				3. Ȼ�󽫳������ַ�����У�
				4. ���ȡmin(ʵ�ʶ������ַ�����ָ�����ַ���)����Ϊ�����ַ����Ľ����ַ�����Ϊ��buf���ַ���Ŀ����ʱ��ʵ�ʶ������ַ����Ϳ��ܱȽ�С��
				   ��ָ���ַ�����ȥ֮ǰ�ڶ����ж������ַ����ܱ�4����ʱ��ʵ�ʶ������ַ����ͱȽϴ�
     */
    int read(char *buf, int n) {
        int len = 0;	//	ʵ�ʶ������ַ���
		while (!que.empty()) {
			buf[len++] = que.front();
			que.pop();
			if (len == n)	return len;	//	��������ʣ����ַ��Ѿ��㹻ʱ��ֱ�ӷ���
		}
		int cnt = 0;	//	���ε���read4()�������ַ���
		while (len < n) {
			cnt = read4(buf + len);	//	��read4�ж�ȡ���ַ�������buf + len��λ��
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