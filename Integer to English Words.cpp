///@file	Integer to English Words
///@author	zhaowei
///@date	2016.02.29
///@version	1.0

///@date	2016.03.03
///@version	1.1

#include <string>
#include <vector>
using namespace std;

class Solution_v1 {
public:
	///@brief	将正整数转换成英文单词输出
	///@param	num	正整数
	///@return	返回该正整数所表示的英文单词
	///@note	1. 首先根据英文数字的表示规则，将其三三分开；
	//			2. 然后加上billion, million, thousand, hundred等量词，然后再处理几十和十几的特殊词即可；
	//			3. 注意处理One Million这种情形，设置一个flg来进行标记。
	string numberToWords(int num) {
		string three_bits[4] = {"", "Thousand", "Million", "Billion"};
		string one_bit[10] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
		string teen_bits[10] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
		string ty_bits[10] = {"", "Hundred", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
		vector<int> tmp;
		if (!num)	return "Zero";
		while (num) {
			tmp.push_back(num % 1000);
			num /= 1000;
		}
		string rslt;
		for (int i = tmp.size() - 1; i >= 0; i--) {
			bool flg = false;
			if (tmp[i] >= 100) {
				rslt += one_bit[tmp[i] / 100] + " " + ty_bits[1] + " ";
				tmp[i] %= 100;
				flg = true;
			}
			if (tmp[i] >= 20) {
				rslt += ty_bits[tmp[i] / 10] + " " + one_bit[tmp[i] % 10] + " ";
				if (!(tmp[i] % 10))	rslt.pop_back();
				flg = true;
			}
			else if (tmp[i] >= 10) {
				rslt += teen_bits[tmp[i] % 10] + " ";
				flg = true;
			}
			else if (tmp[i] > 0) {
				rslt += one_bit[tmp[i]] + " ";
				flg = true;
			}
			if (flg) rslt += three_bits[i] + " ";	//	flg用来标记是否全部为0的三位数。
		}
		while (rslt.back() == ' ')	rslt.pop_back();
		return rslt;
	}
};

class Solution {
public:
	string numberToWords(int num) {
		string ones[10] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
		string teens[10] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
		string tys[10] = {"", "Hundred", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
		string quantity[4] = {"", "Thousand", "Million", "Billion"};
		if (!num)	return "Zero";
		vector<int> tmp;
		string rslt;
		while (num) {
			tmp.push_back(num % 1000);
			num /= 1000;
		}
		for (int i = tmp.size() - 1; i >= 0; i--) {
			bool flg = false;
			if (tmp[i] >= 100) {
				rslt += ones[tmp[i]/100] + " " + tys[1] + " ";
				tmp[i] %= 100;
				flg = true;
			}
			if (tmp[i] >= 20) {
				rslt += tys[tmp[i]/10] + " " + ones[tmp[i]%10] + " ";
				if (!(tmp[i] % 10))	rslt.pop_back();	//	避免整几十时出现连续空格符。
				flg = true;
			}
			else if (tmp[i] >= 10) {
				rslt += teens[tmp[i]%10] + " ";
				flg = true;
			}
			else if (tmp[i] > 0) {
				rslt += ones[tmp[i]] + " ";
				flg = true;
			}
			if (flg)	rslt += quantity[i] + " ";
		}
		while (rslt.back() == ' ')	rslt.pop_back();
		return rslt;
	}
};

int main() {
	int num[6] = {100000001, 12, 123, 50860, 12345667, 2147483647};
	Solution slt;
	vector<string> strs;
	for (int i = 0; i != 6; i++) 
		strs.push_back(slt.numberToWords(num[i]));	
	return 0;
}