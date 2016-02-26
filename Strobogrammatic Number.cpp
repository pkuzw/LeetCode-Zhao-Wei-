///@file	Strobogrammatic Number
///@author	zhaowei
///@date	2016.01.10
///@version	1.0

///@date	2016.02.26
///@version	2.0

#include <string>
#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	判断一个数字组成的字符串旋转180°后（从上往下看）是否和原来一样
	///@param	num	数字字符串
	///@return	如果一样则返回true；否则返回false
	///@note	1. 旋转180°后一样的数字对有[0, 0]，[1, 1]，[6, 9]，[8, 8]，[9, 6]；2. 与判断回文字符串类似，只有对应的数字对对称出现才可以；3. 时间复杂度为O(n)，空间复杂度为O(1)。
	bool isStrobogrammatic(string num) {
		if (num.empty())	return true;
		char sbg_num[5][2] = {{'0', '0'}, {'1', '1'}, {'6', '9'}, {'8', '8'}, {'9', '6'}};
		int i = 0, j = num.size() - 1;
		
		while (i <= j) {
			int k = 0;
			for (k = 0; k < 5; k++) {
				if (num[i] == sbg_num[k][0] && num[j] == sbg_num[k][1]) {
					i++;
					j--;
					break;
				}
			}
			if (k == 5)	return false;
		}
		return true;		
	}
};

class Solution {
public:
	///@note	1. 满足旋转回文字符串的字符有0-0, 1-1, 6-9, 8-8, 9-6，其中0-0不能出现在第一个字符。
	bool isStrobogrammatic(string num) {
		if (num.empty())	return true;
		const char stro_nums[5] = {'0', '1', '6', '8', '9'};
		int len = num.size();
		if (len % 2) {
			char mid = num[len / 2];
			if (mid != '0' && mid != '1' && mid != '8')	return false;
		}		
		for (int i = 0; i != len / 2; i++) {
			if ((num[i] == '6' && num[len-1-i] == '9') || (num[i] == '9' && num[len-1-i] == '6'))	continue;
			else if ((num[i] == '0' || num[i] == '1' || num[i] == '8') && num[i] == num[len-1-i])	continue;
			else return false;
		}
		return true;
	}
};

int main() {
	string num = "81890106818";
	Solution slt;
	bool rslt = slt.isStrobogrammatic(num);
	return 0;
}