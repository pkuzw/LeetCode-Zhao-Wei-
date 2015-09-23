///@file	Next Permutation
/*
			Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

			If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

			The replacement must be in-place, do not allocate extra memory.

			Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
			1,2,3 → 1,3,2
			3,2,1 → 1,2,3
			1,1,5 → 1,5,1
*/
///@author	zhaowei
///@date	2015.06.12
///@note	从最低位向最高位遍历，在后缀的k（k > 0)位中，如果倒数第k（1 < i <= k）位是这k个数中最大的，则需要将倒数第k+1位带入进来。
//			将这k+1个数中大于倒数第k+1位的最小值放入第k+1位，然后将剩余的k个数按照升序依次排列。
///@version 1.0

///@date    2015.09.05
///@version 2.0

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class Solution_v1
{
public:
	///@brief	切换到数组升序的下一个排列
	///@param	nums	数组
	///@author	zhaowei
	///@date	2015.06.12
	void nextPermutation(vector<int>& nums) {
		
		//	因为是从尾向前，所以要用reverse_iterator。如果用iterator，在最开始的判断begin()时会越界。
		for (vector<int>::reverse_iterator i = nums.rbegin(); i != nums.rend(); i++)
		{			
			if (*i == maxNum(nums, i))	//	如果该位是后i位的最大值，则将前一位加入进来
			{
				continue;
			}
			else
			{
				vector<int>::reverse_iterator i_indx = minNumLrg(nums, i, *i);	//	找到比第i位大的最小值
				swap(*i, *i_indx);	//	交换之

				//	这里因为是reverse_iterator，所以要注意：
				//	1. sort()函数在调用的时候需要满足参数1迭代器小于参数2迭代器；这也就是为何是rbegin()在前的缘故
				//	2. sort()函数默认是升序排序，如果想要改为降序，则在第三个参数处添加自己写的比较函数或者调用STL中的greater<Type>()即可
				//	3. sort()的排序范围是[first, last)，注意，是左闭右开区间。

				//剩余i-1位升序排序
//				sort(nums.rbegin(), i, mycmp);			//		自己写的比较函数
				sort(nums.rbegin(), i, greater<int>());	//		利用STL
				return;
			}
		}
		sort(nums.begin(), nums.end());	//	如果已经是最后一个排列，则重新返回第一种排列
	}

private:
	///@brief	找到指定q起始下标到尾部区间内的最大值
	///@param	nums	数组
	///@param	p	起始下标
	///@return	返回最大值
	///@author	zhaowei
	///@date	2015.06.12
	int	maxNum(vector<int>& nums, vector<int>::reverse_iterator p)
	{
		int max_num = 0;
		for (vector<int>::reverse_iterator i = nums.rbegin(); i <= p; i++)
		{
			if (*i > max_num)
			{
				max_num = *i;
			}
		}
		return max_num;
	}

	///@brief	找到指定区间内比指定值大的最小值
	///@param	nums	数组
	///@param	p	起始下标
	///@val		指定值
	///@return	返回该值的下标
	///@author	zhaowei
	///@date	2015.06.12
	vector<int>::reverse_iterator minNumLrg(vector<int>& nums, vector<int>::reverse_iterator p, int val)
	{
		int min_num = INT_MAX;
		vector<int>::reverse_iterator indx = nums.rbegin();
		for (vector<int>::reverse_iterator i = nums.rbegin(); i <= p; i++)
		{
			if (*i > val)
			{
				if (*i < min_num)
				{
					min_num = *i;
					indx = i;
				}
			}
		}
		return indx;
	}

	///@brief	比较函数，降序
	struct myobj
	{
		bool operator()(int a, int b)
		{
			return a>b;
		}
	}mycmp;
	
};

/*
通过观察发现，逆序找到第一个比前面一个数大的数字，然后在后面找到比前面这个数大的最小数，二者交换，然后将后面进行翻转即可。
*/
class Solution {
public:
	///@brief	计算给定数组的下一个字典序排列
	///@param	nums	数组
	///@return	无
	///@note	通过观察发现，如果指定一个按照字典序给出的排列，那么它的下一个排列应该先倒着逆序从后往前找到第一个比前一个元素大的位置，这个前一个元素的位置我们标记为i，
	//			然后再从i向后找到比i位置元素大的最小元素（因为i之后的所有元素都是降序的，所以逆着找到的第一个比i大的就是最小的），我们标记为j，然后交换i和j元素，
	//			再将从i + 1开始到结束的所有元素翻转。对于已经是最后一种排列的情形，直接全部翻转即可。
	//			时间复杂度为O(n^2)，空间复杂度为O(1)。
    void nextPermutation(vector<int>& nums) {
		int i = 0, j = 0;
		for (int i = nums.size() - 2; i >= 0; i--) {
			if (nums[i] < nums[i + 1]) {	//	此处为'<'，为了避免重复元素的排列无法和上一个排列区分
				for (j = nums.size() - 1; j >= i; j--) {
					if (nums[j] > nums[i])	break;
				}
				swap(nums[i], nums[j]);
				reverse(nums.begin() + i + 1, nums.end());
				return;
			}
		}
		reverse(nums.begin(), nums.end());
    }
};

int main()
{
	vector<int> ivec;
	Solution slt;
	string s_test = "4,0,5,29,14,16,9,2,12,14,7,27,15,4,8,11,2,18,29,3,16,8,10,22,11,10,15,1,1,0,28,5,0,26,4,6,12,5,8,16,12,8,14,27,12,14,0,6,2,29,9,10,8,11,3,";
	int test[] = {4,0,5,29,14,16,9,2,12,14,7,27,15,4,8,11,2,18,29,3,16,8,10,22,11,10,15,1,1,0,28,5,0,26,4,6,12,5,8,16,12,8,14,27,12,14,0,6,2,29,9,10,8,11,3};
	int cnt = 0;
	for (int i = 0; i != s_test.size(); i++)
	{
		if (s_test[i] == ',')
		{
			cnt++;
		}
	}
	for (int i = 0; i < cnt; i++)
	{
		ivec.push_back(test[i]);
 	}
// 	ivec.push_back(3);
// 	ivec.push_back(4);
// 	ivec.push_back(1);
// 	ivec.push_back(5);
// 	ivec.push_back(2);

	slt.nextPermutation(ivec);
	for (int i = 0; i < ivec.size(); i++)
	{
		cout << ivec[i] << " ";
	}
	cout << endl;
	return 0;
}
