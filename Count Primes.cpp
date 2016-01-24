///@file	Count Primes
/*
Count the number of prime numbers less than a non-negative number, n.
*/
///@author	zhaowei
///@date	2015.07.28
///@version	1.0

///@date	2015.08.11
///@version	1.1

///@date	2016.01.24
///@version	1.2

#include <vector>
using namespace std;

class Solution_v1 {
public:
	///@brief	计算从1到n-1的素数个数
	///@param	n	范围上限
	///@return	返回素数个数
	/* @note	埃氏筛法：从2开始，遍历所有小于根号n的素数，依次将这些素数乘以若干倍，对于所有的素数的倍数，都不是素数，筛掉。最后剩下的元素就是素数。
				时间复杂度为O(sqrt(n))，空间复杂度为O(n)。*/
	int countPrimes(int n) {
		vector<bool> num(n, true);

		for (int i = 2; i * i < n; i++)
		{			
			if (!num[i])	continue;
			for (int j = 2; i * j < n; j++)
			{
				if (num[i*j])	num[i*j] = false;					
			}
		}

		int cnt = 0;
		for (int i = 2; i < num.size(); i++)
		{
			if (num[i])	cnt++;			
		}

		return cnt;
	}
};

class Solution {
public:
	///@note	埃氏筛法
	int countPrimes(int n) {
		vector<bool> flg(n, true);
		for (int i = 2; i * i < n; i++) {
			if (!flg[i])	continue;
			for (int j = 2; j * i < n; j++)
				flg[j * i] = false;
		}
		int rslt = 0;
		for (int i = 2; i < n; i++)
			if (flg[i])	rslt++;
		return rslt;
	}
};

int main()
{
	int n = 12000;
	Solution_v1 slt_v1;
	int rslt1 = slt_v1.countPrimes(n);

	Solution slt;
	int rslt = slt.countPrimes(n);
	return 0;
}