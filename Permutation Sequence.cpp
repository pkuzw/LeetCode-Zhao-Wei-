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
///@date	2015.07.07
///@version	1.1

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
	/*
	///@note	利用一个数组记录下k能够被分解成多少个子序列的排列，然后再根据这个数组来进行相应的排列。还没有想的很清楚。
	string getPermutation(int n, int k)
	{
		string str;
		int cnt[10];	//	记录k能够被分解成多少个子排列。cnt[i]表示第1个数到第i个数所组成的全排列数目的倍数。
		memset(cnt, 0, 10*sizeof(int));
		initFractorial(n);

		if (k > fractorial.back() || k < fractorial.front())
		{
			return str;
		}

		for (int i = fractorial.size()-1; i >= 0; i--)
		{
			if (k >= fractorial[i])
			{
				cnt[i] = k/fractorial[i];
				k %= fractorial[i];
			}
		}

		vector<int> nums;
		for (int i = 1; i <= n; i++)
		{
			nums.push_back(i);
		}

	}

private:
	vector<int> fractorial;
	///@brief	初始化1~9的阶乘数组
	///@param	n	候选元素的数目
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

	///@brief	给定候选元素数组，计算所有可能的组合
	///@param	nums	候选元素数组
	///@param	k		候选元素的全排列的第k个排列
	///@return	返回候选元素的全排列的第k个排列
	///@note	利用递归的思想来解题。含有n和候选元素的数组可以分解成1个元素和n-1个元素。基本情况是只有1个元素的情形，只需要输出其本身；
	//			这时候返回上一级递归，假设有k个元素，如果选出的那1个元素还不是这k个元素中的最后一个，则向后选择下一个，并继续递归。直至
	//			最顶层选到了最后一个元素。时间复杂度为O(n!)，空间复杂度为O(n^2)。
	vector<int> permute(vector<int>& nums, int k)
	{
		vector<int> ivec;
		
		getPermutate(nums, ivec);
		return ivec;
	}

	///@brief	计算所有可能的组合
	///@param	nums	原始数组
	///@param	residue	可能的一种组合
	///@return	void
	///@note	我的想法是每次拿掉一个元素，将剩余的元素组成一个新数组，并且记录下当前拿掉的是第几个元素；当新数组为空时需要得到一个可能的组合；
	//			此时返回上一级递归，再拿掉下一个元素。依次类推。
	void getPermutate(vector<int> nums, vector<int>& residue)
	{
		if (nums.empty())	//	如果数组为空，则递归结束
		{
			rslt.push_back(residue);	//	将一种可能的组合加入结果二维数组
			return;
		}
		int indx = 0;	//	标记当前选到的元素下标
		while (indx != nums.size())	//	如果当前元素不是数组中的最后一个元素，则进入循环
		{
			vector<int> tmp;	//	用来保存除了当前选择的元素，剩余元素组成的数组
			residue.push_back(nums[indx]);	//	将当前元素加入结果
			for (int i = 0; i != nums.size(); i++)	//	生成剩余元素组成的数组
			{
				if (i == indx)
				{
					continue;
				}
				tmp.push_back(nums[i]);
			}
			getPermutate(tmp, residue);		//	递归
			residue.pop_back();				//	将结果中的元素弹出
			indx++;							//	下标后移一位
		}	
		return;
	}
	*/
};

int main()
{
	Solution slt;
	int n, k;
	while (cin >> n >> k)
	{
		cout << slt.getPermutation_stl(n, k) << endl;
	}
	return 0;
}
