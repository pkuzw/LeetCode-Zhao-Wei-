///@file	Bulls and Cows
///@author	zhaowei
///@date	2016.03.14
///@version	1.0

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	///@brief	对比两个字符串，返回位数和数字相同的个数以及数字相同而位数不同的个数
	///@param	secret	参考字符串
	///@param	guess	待对比字符串
	///@return	以"XAYB"的形式表示X个位数和数字相同的字符数，Y个位数不同但是数字相同的字符数
	///@note	1. 先遍历一遍，找出所有A的数目；
	//			2. 然后取出所有A的字符，记录下0-9出现的个数，两个字符串有多少个重复的0-9，就有多少个B；
	//			3. 时间复杂度为O(n)，空间复杂度为O(1)，其中n为字符串长度。
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