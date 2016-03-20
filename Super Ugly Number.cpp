///@file	Super Ugly Number
///@author	zhaowei
///@date	2016.03.20
///@version	1.0

#include <vector>
using namespace std;

class Solution {
public:
	///@brief	给定一组质数，要求计算出第n小的所有因子都是这些质数的数
	///@param	n	第n个数
	///@param	primes	质数数组
	///@note	1. 动态规划；
	//			2. 与Ugly Number II类似，维护一个与质数数组一样大的下标数组；
	//			3. 先遍历一遍所有的质数，找到能够生成最小数的那一个质数，然后将对应的下标自增1；
	//			4. 时间复杂度为O(kn)，其中k为质数个数，n为第n小的合数
	int nthSuperUglyNumber(int n, vector<int>& primes) {
		vector<int> ugly_nums;
		ugly_nums.push_back(1);
		int k = primes.size();
		if (!k)	return 0;
		vector<int> indexes(k, 0);
		while (ugly_nums.size() < n) {
			int next_ugly_num = ugly_nums[indexes[0]] * primes[0];
			for (int i = 0; i != k; i++)	next_ugly_num = min(next_ugly_num, ugly_nums[indexes[i]] * primes[i]);
			for (int i = 0; i != k; i++)
				if (next_ugly_num == ugly_nums[indexes[i]] * primes[i])
					indexes[i]++;
			ugly_nums.push_back(next_ugly_num);
		}
		return ugly_nums[n-1];
	}
};

int main() {
	vector<int> primes;
	int n = 12;
	primes.push_back(2);
	primes.push_back(7);
	primes.push_back(13);
	primes.push_back(19);
	Solution slt;
	int rslt = slt.nthSuperUglyNumber(n, primes);
	return 0;
}