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

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
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

int main()
{
	Solution slt;
	int n, k;
	while (cin >> n >> k)
	{
		cout << "My  solution: " << slt.getPermutation(n, k) << endl;
		cout << "Stl solution: " << slt.getPermutation_stl(n, k) << endl;
	}
	return 0;
}
