/* @brief	Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:
Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
	The solution set must not contain duplicate triplets.
	For example, given array S = {-1 0 1 2 -1 -4},

	A solution set is:
	(-1, 0, 1)
	(-1, -1, 2)
*/
///@author	zhaowei
///@date	2015.06.03
///@version 1.0

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

class Solution
{
public:
	///@brief	求三个数之和为0的所有组合
	///@param	nums	待处理的数组
	///@return	返回所有可能的组合，在每一个3元组答案中按照非降序排列元素
	///@author	zhaowei
	///@date	2015.06.03
	/* @note	
	*/
	vector<vector<int>> threeSum(vector<int>& nums) {

		QuickSort(nums, 0, nums.size()-1);	// 快排

		int l = 0, r = nums.size()-1;	

		int a, b = 0, c;
		vector<vector<int>> ivvec;
		vector<int> avec, bvec, cvec;

		for (int i = 0; i < r-2; i++)
		{				
			a = nums[i];
			if (a >= 0)	//	不可能三个都是自然数
			{
				break;
			}


			for (int j = r-1; j > i; j--)	//从另一边向中间靠拢，能够减少不必要的遍历次数
			{				
				vector<int> triplet;
				b = nums[j];
				c = BinarySearch(nums, l, r, 0-a-b);
				if (c != -1 && nums[c] >= b)
				{
					triplet.push_back(a);
					triplet.push_back(b);
					triplet.push_back(nums[c]);

					avec.push_back(a);
					bvec.push_back(b);
					cvec.push_back(nums[c]);

					if (avec.size() == 1 && bvec.size() == 1 && cvec.size() == 1)
					{
						ivvec.push_back(triplet);
					}

					if ((avec.size() > 1 && bvec.size() > 1 && cvec.size() > 1) &&
						(BinarySearch(avec, 0, avec.size()-2, a) == -1 || 
						BinarySearch(bvec, 0, bvec.size()-2, b) == -1 ||
						BinarySearch(cvec, 0, cvec.size()-2, nums[c]) == -1 ||
						(BinarySearch(avec, 0, avec.size()-2, a) != BinarySearch(bvec, 0, bvec.size()-2, b)) ||
						(BinarySearch(avec, 0, avec.size()-2, a) != BinarySearch(cvec, 0, cvec.size()-2, nums[c]) ||
						BinarySearch(cvec, 0, cvec.size()-2, nums[c]) != BinarySearch(bvec, 0, bvec.size()-2, b))
						)
						)
					{
						ivvec.push_back(triplet);
					}						
 				}
			}				
		}
		return ivvec;
	}

	///@brief	检查三元组向量中是否已经存在该三元组
	///@param	tri		待检查的三元组
	///@param	ivvec	三元组向量
	///@return	如果不存在，返回true；否则返回false
	///@author	zhaowei
	///@date	2015.06.03
	bool checkTriplet(vector<vector<int>>& ivvec, vector<int> tri)
	{
		for (int i = 0; i < ivvec.size(); i++)
		{
			if (ivvec[i][0] == tri[0] && ivvec[i][1] == tri[1] &&ivvec[i][2] == tri[2])
			{
				return false;
			}
		}
		return true;
	}

	///@brief 交换两个整型变量
	///@param a, b 待交换的两个元素
	///@author zhaowei
	///@date 2014.07.15
	void swap(int& a, int& b)
	{
		int t = a;
		a = b;
		b = t;
		return;
	}

	///@brief 将数组分割，使其左半部分的元素都比返回值小，右半部分的元素都比返回值大。
	///@param arr 数组指针
	///@param p	起始下标
	///@param r 终止下标
	///@return 返回分割后数组的中轴值
	///@author zhaowei
	///@date 2014.07.15	
	int Partition(vector<int>& arr, const int p, const int r)
	{		
		int x = arr[r];
		int i = p-1;
		for(int j = p; j < r; j++)
		{
			if(arr[j] <= x)
			{
				i++;
				swap(arr[j], arr[i]);
			}		
		}
		swap(arr[i+1], arr[r]);
		return i+1;
	}

	///@brief 用递归实现快速排序
	///@param arr 数组指针。这里应该是引用，否则无法进行递归
	///@param p	数组起始下标
	///@param r 数组终止下标
	///@author zhaowei
	///@date 2014.07.15
	void QuickSort(vector<int>& arr, const int p, const int r)
	{
		if(p < r)
		{
			int q = Partition(arr, p, r);
			QuickSort(arr, p, q-1);
			QuickSort(arr, q+1, r);
		}
		return;
	}

	///@brief	二分查找函数
	///@param	&array_int	 排好序的数组，这里应该是引用，否则无法进行递归
	///@param	p			 数组的起始下标
	///@param	r	 数组的终止下标
	///@param	v	 待查找的值
	///@return	如果在数组中找到v值，则返回该值所在下标；否则返回-1
	int BinarySearch(vector<int>& array_int, int p, int r, int v)
	{
		if(p > r)/* || v < array_int[p] || v > array_int[r])*/
			return -1;
		int q = (p + r) / 2;
		if(v == array_int[q])
			return q;
		else if(v < array_int[q])
			BinarySearch(array_int, p, q-1, v);
		else 
			BinarySearch(array_int, q+1, r, v);
	}
};

int main()
{
	vector<int> ivec;	
	int n[109] = {7,-1,14,-12,-8,7,2,-15,8,8,-8,-14,-4,-5,7,9,11,-4,-15,-6,1,-14,4,3,10,-5,2,1,6,11,2,-2,-5,-7,-6,2,-15,11,-6,8,-4,2,1,-1,4,-6,-15,1,5,-15,10,14,9,-8,-6,4,-6,11,12,-15,7,-1,-9,9,-1,0,-4,-1,-12,-2,14,-9,7,0,-3,-4,1,-2,12,14,-10,0,5,14,-1,14,3,8,10,-8,8,-5,-2,6,-11,12,13,-7,-12,8,6,-13,14,-2,-5,-11,1,3,-6};
	string s = "7,-1,14,-12,-8,7,2,-15,8,8,-8,-14,-4,-5,7,9,11,-4,-15,-6,1,-14,4,3,10,-5,2,1,6,11,2,-2,-5,-7,-6,2,-15,11,-6,8,-4,2,1,-1,4,-6,-15,1,5,-15,10,14,9,-8,-6,4,-6,11,12,-15,7,-1,-9,9,-1,0,-4,-1,-12,-2,14,-9,7,0,-3,-4,1,-2,12,14,-10,0,5,14,-1,14,3,8,10,-8,8,-5,-2,6,-11,12,13,-7,-12,8,6,-13,14,-2,-5,-11,1,3,-6";
 	
 	int cnt = 0;
 	for (int i = 0; i < s.length(); i++)
 	{
 		if (s[i] == ',')
 		{
 			cnt ++;
 		}
 	}
 	cout << cnt << endl;
 	for (int i = 0; i < 109; i++)
 	{
 		ivec.push_back(n[i]);
 	}
 	

	Solution slt;
	vector<vector<int>> ivvec;
	ivvec = slt.threeSum(ivec);
	for (int i = 0; i < ivvec.size(); i++)
	{
		for (int j = 0; j < ivvec[i].size(); j++)
		{
			cout << ivvec[i][j] << ' ';
		}
		cout << endl;
	}
	return 0;
}