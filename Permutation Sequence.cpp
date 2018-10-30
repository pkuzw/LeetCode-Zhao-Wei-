///@file	Permutation Sequence
/*
The set [1,2,3,…,n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order,
We get the following sequence (ie, for n = 3):

"123"
"132"
"213"
"231"
"312"
"321"
Given n and k, return the kth permutation sequence.

Note: Given n will be between 1 and 9 inclusive.
*/
///@author	zhaowei
///@date	2015.07.11
///@version	1.2

///@date    2015.08.31
///@version 2.0

///@date	2015.11.29
///@version 2.1

///@date	2016.04.14
///@version	2.2

///@date    October 30, 2018
///@version 2.3

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution_v1 {
public:
	///@brief	计算从1到n的全排列中的第k个排列
	///@param	n	元素的数目
	///@param	k	第几个排列
	///@return	返回1到n的全排列中的第k个
	///@note	利用<algorithm>中的next_permutation()函数来进行计算。其时间复杂度为O(n)。OJ还是报TLE。
	string getPermutation_stl(int n, int k)
	{
		vector<int> nums;
		for (int i = 1; i <= n; i++)
		{
			nums.push_back(i);
		}
		while (k != 1)
		{
			next_permutation(nums.begin(), nums.end());
			k--;
		}
		string rslt;
		for (int i = 0; i != nums.size(); i++)
		{
			rslt += nums[i] + '0';
		}
		return rslt;
	}
	
	///@brief	计算从1到n的全排列中的第k个排列
	///@param	n	元素的数目
	///@param	k	第几个排列
	///@return	返回1到n的全排列中的第k个
	///@note	利用一个数组cnt[n]记录下k能够被分解成多少个子序列的排列，cnt[i]表示第i+1个数到第n个数所组成
	//			的全排列数目的倍数。然后再根据这个数组来进行相应的排列。比如对于后备元素是nums[4] = {1, 2, 3, 4}，它的
	//			第17个数应该先自减1变成16，然后被分解成6*2 + 2*2 + 0*1，所以对于第一个元素应该选择nums[2] = 3, nums更新为{1, 2, 4}，
	//			第二个元素是nums[2] = 4，nums更新为{1, 2}，第三个元素是nums[0] = 1，nums更新为{2}，第四个元素是nums[0] = 2.
	//			时间复杂度为O(n)，空间复杂度为O(1)。
	string getPermutation(int n, int k)
	{
		string str;
		int cnt[10];	//	记录k能够被分解成多少个子排列。cnt[i]表示第i+1个数到第n个数所组成的全排列数目的倍数。
		memset(cnt, 0, 10*sizeof(int));
		fractorial.clear();
		initFractorial(n);

		

		if (k > fractorial.back() || k < fractorial.front())
		{
			return str;
		}

		if (k == 1)
			k = fractorial[n - 1];
		else
			k--;
		
		for (int i = fractorial.size()-1; i >= 0; i--)
		{
			if (k >= fractorial[i])
			{
				cnt[n-i-1] = k/fractorial[i];
				k %= fractorial[i];
			}
		}

		
		vector<int> nums;
		for (int i = 1; i <= n; i++)
		{
			nums.push_back(i);
		}

		vector<int> tmp;
		for (int i = 1; i <= n; i++)
		{			
			int t = nums[cnt[i]];
			vector<int>::iterator it = nums.begin();

			for (it = nums.begin(); it != nums.end(); it++)
			{
				if (*it == t)
				{
					break;
				}
			}
			nums.erase(it);
			tmp.push_back(t);
		}

		string rslt;
		for (int i = 0; i != tmp.size(); i++)
		{
			rslt += tmp[i] + '0';
		}
		return rslt;
	}

private:
	vector<int> fractorial;

	///@brief	初始化1~9的阶乘数组
	///@param	n	候选元素的数目
	///@return	无
	void initFractorial(int n)
	{
		int tmp = 1;
		for (int i = 1; i <= n; i++)
		{
			tmp *= i;
			fractorial.push_back(tmp);
		}
		return;
	}
};

class Solution_v2 {
public:
	///@brief	计算制定序号的排列
	///@param	n	候选数组的长度，从1开始，最多有9个
	///@param	k	排列的序号，从1开始
	///@return	返回n个候选元素的第k个排列
	///@note	1. 因为只是计算第k个排列，前面的k-1个和后面的n! - k个不用计算，所以不能用之前的算法来算。
	//			2. 先计算出i（0 < i <= 9）个候选元素的全排列数目；
	//			3. 根据候选元素的长度，计算出排列中第j（0 < j <= n）位的数字，这个数字通过除法来计算，除数是k，被除数就是n - j个候选元素的全排列数目；
	//			4. 每次计算完，要更新k值，并从候选元素中将该数字删去。
	//			5. 时间复杂度为O(n)，空间复杂度为O(n)，n为候选元素的个数。
    string getPermutation(int n, int k) {
		string s;
		for (int i = 1; i <= n; i++)
			s += '0' + i;
		vector<int> f(n, 1);
		for (int i = 1; i < n; i++)
			f[i] = i * f[i - 1];
		k--;
		string rslt;
		for (int i = n - 1; i >= 0; i--) {
			int j = k / f[i];
			k %= f[i];
			rslt.push_back(s[j]);
			s.erase(j, 1);
		}
		return rslt;
    }
};

class Solution {
public:
    ///@brief   计算由n个数字组成的第k个排列。
    ///@param   n   字符串的长度，其中每个字符都不相同，都是阿拉伯数字。
    ///@param   k   排列的序号。
    ///@return  返回第k个排列。
    ///@note    1. 枚举。不能使用<algorithm>中的next_permutation()方法，会超时。因为只需要计算第k个元素，没有必要计算之前的所有排列；
    //          2. 通过观察发现，对于长度为n的字符串来说，第i位的数字等于排列序号k / (n-1)!后在现有可选阿拉伯数字中的第i个数字。
    //          3. 比如说，要计算“1234”的第7个排列，那么因为3! = 6，7 / 6 = 1，那么排列的第0位的字符应该是{1, 2, 3, 4}中的
    //             2；第1位应该是1 / 2! = 0，即排列k的第1位应该是剩余可选元素按照升序排序后的第0位1；依此类推，第2位和第3位分别是3
    //             和4.
    //          4. 时间复杂度为O(n)，空间复杂度为O(1)，其中n为字符串的长度。
	string getPermutation(int n, int k) {
        string originStr = "123456789";
        string s = originStr.substr(0, n);
        string rslt;
        k--;    //计算第k个排列，因为k >= 1，所以这里要自减1，以便从0开始计算。
        for (int i = n-1; i >= 0; i--) {
            int permuteCnt = factorial(i);
            int j = k / permuteCnt;
            k %= permuteCnt;
            rslt.push_back(s[j]);
            s.erase(j, 1);  //  删除s中第j位开始的1个字符
        }
        return rslt;
	}
    
    ///@brief   计算整数n的阶乘
    ///@param   n   整型变量n
    ///@return  返回n阶乘
    int factorial(int n) {
        int rslt = 1;
        for (int i = n; i >= 1; i--)
            rslt *= i;
        return rslt;
    }
};

int main()
{
	Solution_v2 s2;
    string r2 = s2.getPermutation(4, 12);

	Solution s;
	string r = s.getPermutation(4, 12);
	return 0;
}
