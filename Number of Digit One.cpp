///@file	Number of Digit One
/*
Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.

For example:
Given n = 13,
Return 6, because digit 1 occurred in the following numbers: 1, 10, 11, 12, 13. 
*/
///@author	zhaowei
///@date	2015.07.27
///@version	1.0

///@date	2015.08.06
///@version	1.1

///@date	2016.01.30
///@version	1.2
using namespace std;

class Solution_v1 {
public:
	///@brief	计算比n小的所有正整数中出现的'1'的个数。
	///@param	n	正整数n
	///@return	返回比n小的所有正整数中出现的'1'的个数
	/* @note	
	Go through the digit positions by using position multiplier m with values 1, 10, 100, 1000, etc.

	For each position, split the decimal representation into two parts, for example split n=3141592 into 
	
	a=31415 and b=92 when we're at m=100 for analyzing the hundreds-digit. And then we know that the hundreds-digit 
	
	of n is 1 for prefixes "" to "3141", i.e., 3142 times. Each of those times is a streak, though. Because it's the 
	
	hundreds-digit, each streak is 100 long. So (a / 10 + 1) * 100 times, the hundreds-digit is 1.

	Consider the thousands-digit, i.e., when m=1000. Then a=3141 and b=592. The thousands-digit is 1 for prefixes "" to "314", 
	
	so 315 times. And each time is a streak of 1000 numbers. However, since the thousands-digit is a 1, the very last streak 
	
	isn't 1000 numbers but only 593 numbers, for the suffixes "000" to "592". So (a / 10 * 1000) + (b + 1) times, the 
	
	thousands-digit is 1.

	The case distincton between the current digit/position being 0, 1 and >=2 can easily be done in one expression. 
	
	With (a + 8) / 10 you get the number of full streaks, and a % 10 == 1 tells you whether to add a partial streak.
	*/
	int countDigitOne(int n) {
		int ones = 0;
		for (long long m = 1; m <= n; m *= 10)
		{
			int a = n / m;
			int b = n % m;
			ones += ((a + 8) / 10 * m) + (a % 10 == 1) * (b + 1);
		}
		return ones;
	}
};

class Solution {
public:
	///@note	1. 用c = {1, 10, 100, 1000, ...}来将正数逐位分成两部分，第一部分是a / c，第二部分是a % c。
	//			2. 举个例子，对于3141592这个数来说，当c = 1时，a = 3141592，b = 0，此时对a部分来说，末尾的1出现了314160 * 1次，因为除了末位，其前缀是从0到314159；
	//			3. 当c = 10时，a = 314159, b = 2，此时a中的末位1出现了31416 * 10次；
	//			4. 当c = 100时，a = 31415，b = 92，a的末位1出现了3142 * 100次；
	//			5. 当c = 1000时，a = 3141，b = 592，a的末位1在前缀从0到313的314次中都是出现了314 * 1000次，而在前缀为314时，因为末位是1，所以只出现了b + 1次，即593次，共计314 * 1000 + 593次；
	//			6. 当c = 10000时，a = 314, b = 1592，a的末位1出现了32 * 10000次；
	//			7. 当c = 100000时，a = 31，b = 41592，a的末位1出现了3 * 100000 + 41593；
	//			8. 当c = 1000000时，a = 3，b = 141592，a的末位1出现了1 * 1000000次。计算完毕。
	//			9. 当a的末位是0时，其末位1出现的次数是其前缀的数目 * c。
	int countDigitOne(int n) {
		int rslt = 0;
		for (long long c = 1; n / c > 0; c *= 10) {
			int a = n / c, b = n % c;
			rslt += ((a + 8) / 10) * c + (a % 10 == 1) * (b + 1);
		}
		return rslt;
	}
};

int main()
{
	Solution slt;
	int rslt = slt.countDigitOne(13);
	return 0;
}