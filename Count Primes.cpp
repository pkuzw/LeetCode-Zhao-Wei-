///@file	Count Primes
/*
Count the number of prime numbers less than a non-negative number, n.
*/
///@author	zhaowei
///@date	2015.07.28
///@version	1.0

///@date	2015.08.11
///@version	2.0

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
	int countPrimes(int n) {
		vector<bool> candidates(n+1, true);
		float tmp = n;
		int x = sqrt(tmp);
		for (int i = 2; i <= x; i++)
		{
			for (int j = 2; i * j < n; j++)
			{
				candidates[i * j] = false;
			}
		}

		int cnt = 0;
		for (int i = 2; i < n; i++)
			if (candidates[i])	cnt++;

		return cnt;
	}
};

int main()
{
	int n = 12000;
	Solution_v1 slt_v1;
	int rslt = slt_v1.countPrimes(n);

	Solution slt;
	rslt = slt.countPrimes(n);
	return 0;
}