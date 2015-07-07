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

using namespace std;

class Solution {
public:
	///@brief	计算出从1到n的全排列中第k个排列
	///@param	n	元素数目，1 <= n <= 9
	///@param	k	全排列中的第k个排列
	///@return	返回第k个排列
	///@note	利用"Permutations"中的算法：
	//			利用递归的思想来解题。含有n和候选元素的数组可以分解成1个元素和n-1个元素。基本情况是只有1个元素的情形，只需要输出其本身；
	//			这时候返回上一级递归，假设有k个元素，如果选出的那1个元素还不是这k个元素中的最后一个，则向后选择下一个，并继续递归。直至
	//			最顶层选到了最后一个元素。因为只需计算出第k个排列，因此不需要计算所有的排列。在到达第k个时就返回。
	//			计算出所有的排列后再返回其中的第k个。时间复杂度为O(n!)，空间复杂度为O(n^2)。
	string getPermutation(int n, int k) 
	{
		vector<int> nums;
		for (int i = 1; i <= n; i++)
		{
			nums.push_back(i);
		}
		vector<int> ivec;
		vector<int> rslt;
		int cnt = 0;
		getPermutate(nums, ivec, k, cnt, rslt);	//计算出所有可能的排列

		string str;
				
		for (int i = 0; i != rslt.size(); i++)
		{
			str += rslt[i]+'0';
		}
		return str;
	}

private:
	///@brief	计算所有可能的组合
	///@param	nums	原始数组
	///@param	residue	可能的一种组合
	///@param	k		全排列中的第k个排列
	///@param	rslt	保存有第k个排列的数组	
	///@return	void
	///@note	我的想法是每次拿掉一个元素，将剩余的元素组成一个新数组，并且记录下当前拿掉的是第几个元素；当新数组为空时需要得到一个可能的组合；
	//			此时返回上一级递归，再拿掉下一个元素。依次类推。只需计算出第k个排列，不需要计算所有的排列，在到达第k个时就返回。
	void getPermutate(vector<int> nums, vector<int>& residue, const int k, int &cnt, vector<int>& rslt)
	{
		if (!rslt.empty())
		{
			return;
		}
		if (nums.empty())	//	如果数组为空，则递归结束
		{
			cnt++;
			if (cnt == k)
			{
				rslt = residue;
				return;
			}
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
			getPermutate(tmp, residue, k, cnt, rslt);		//	递归
			residue.pop_back();				//	将结果中的元素弹出
			indx++;							//	下标后移一位
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
		cout << slt.getPermutation(n, k) << endl;
	}
	return 0;
}
