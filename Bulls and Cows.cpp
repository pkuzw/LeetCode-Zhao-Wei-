///@file	Bulls and Cows
///@author	zhaowei
///@date	2016.03.14
///@version	1.0

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	///@brief	�Ա������ַ���������λ����������ͬ�ĸ����Լ�������ͬ��λ����ͬ�ĸ���
	///@param	secret	�ο��ַ���
	///@param	guess	���Ա��ַ���
	///@return	��"XAYB"����ʽ��ʾX��λ����������ͬ���ַ�����Y��λ����ͬ����������ͬ���ַ���
	///@note	1. �ȱ���һ�飬�ҳ�����A����Ŀ��
	//			2. Ȼ��ȡ������A���ַ�����¼��0-9���ֵĸ����������ַ����ж��ٸ��ظ���0-9�����ж��ٸ�B��
	//			3. ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)������nΪ�ַ������ȡ�
	string getHint(string secret, string guess) {
		int len = secret.length();
		if (!len)	return "";
		int a = 0, b = 0;
		int scrt_hash_tbl[10] = {0}, gss_hash_tbl[10] = {0};
		for (int i = 0; i != len; i++) {
			if (secret[i] == guess[i])	a++;
			else {
				scrt_hash_tbl[secret[i] - '0']++;
				gss_hash_tbl[guess[i] - '0']++;
			}
		}
		for (int i = 0; i != 10; i++)
			if (scrt_hash_tbl[i] && gss_hash_tbl[i])	b += min(scrt_hash_tbl[i], gss_hash_tbl[i]);			
		
		return to_string(static_cast<long long>(a)) + "A" + to_string(static_cast<long long>(b)) + "B";
	}
};

int main() {
	string secret = "1807", guess = "7810";
	Solution slt;
	string rslt = slt.getHint(secret, guess);
	return 0;
}