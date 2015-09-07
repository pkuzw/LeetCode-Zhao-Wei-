///@brief	3Sum Closest. 
/*			Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. 

			Return the sum of the three integers. You may assume that each input would have exactly one solution.

			For example, given array S = {-1 2 1 -4}, and target = 1.

			The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/
///@author  zhaowei
///@date	2015.06.04
///@version	1.0

///@date    2015.09.07
///@version 2.0

#include <iostream>
#include <vector>
using namespace std;

/*
class Solution_v1
{
public:
	///@brief	计算和距离目标值最近的三元组
	///@param	nums	数组
	///@param	target	目标值
	///@return	返回和距离目标值最近的三元组之和
	///@author	zhaowei
	///@date	2015.06.05
	///@note	先对数组进行快排，然后抽取出来没有重复元素组成的数组，以目标值为中心，通过二分查找依次自增和自减1来寻找符合条件的三元组 
	int threeSumClosest(vector<int>& nums, int target) {

		QuickSort(nums, 0, nums.size()-1);	// 对原数组进行快排

		vector<int> nr;	// 构建新数组，其中每个元素只出现一次
		vector<int> rt;	// 记录原数组中元素出现的次数的数组
		int cnt = 1;	// 统计数组中元素出现的次数
		for (int i = 0; i < nums.size(); i++)
		{
			if (i < nums.size()-1 && nums[i] == nums[i+1])
			{
				cnt++;
				continue;
			}
			nr.push_back(nums[i]);
			rt.push_back(cnt);
			cnt = 1;
		}

		int rslt = target;	// 计算距离目标值最近的值
		int a = 0, b = 0, c = 0;	// 分别保存三元组元素
		int k = 0;	// 每次围绕目标值自增或自减1
		int t = 0;	
		while (1)
		{
			rslt = target + k;
			if (rslt > INT_MAX	// 对于明显超出整型表示范围的情况，跳出循环
			|| rslt < INT_MIN)
			{
				break;
			}
			if (t % 2 == 0)
			{
				k *= -1;
				k++;
			}
			else
			{
				k *= -1;
			}
			t++;

			for (int i = 0; i < nr.size(); i++)	
			{
				a = nr[i];
				for (int j = i; j < nr.size(); j++)
				{
					if (j == i && rt[i] == 1)	// 如果该元素没有重复出现2次以上，则继续下一次迭代
					{
						continue;
					}
					b = nr[j];
					c = rslt - a - b;
					if (BinarySearch(nr, i, nr.size()-1, c) == -1)
					{
						continue;
					}
					else if ((BinarySearch(nr, i, nr.size()-1, c) == i && i != j && rt[i] < 2) // 排除元素出现次数不够的情形
						|| (BinarySearch(nr, i, nr.size()-1, c) == j && i != j && rt[j] < 2)
						|| (BinarySearch(nr, i, nr.size()-1, c) == i && i == j && rt[i] < 3))
					{
						continue;
					}
					else
						return rslt;
				}
			}
		}
		return INT_MAX;
	}

	///@brief	交换数组中的两个元素
	///@param	a	待交换的元素a
	///@param	b	待交换的元素b
	///@return	空
	///@author  zhaowei
	///@date	2015.06.04
	void swap(int& a, int& b)
	{
		int tmp = a;
		a = b;
		b = tmp;
	}

	///@brief	寻找快速排序的轴值
	///@param	ivec	待排序的数组
	///@param	p	待排序的数组起始下标
	///@param	r	待排序的数组末尾下标
	///@return	返回数组的轴值下标
	///@author	zhaowei
	///@date	2015.06.04
	int Partition(vector<int>& ivec, const int p, const int r)
	{
		int x = ivec[r];
		int i = p-1;
		for (int j = p; j < r; j++)
		{
			if (ivec[j] <= x)
			{
				i++;
				swap(ivec[i], ivec[j]);
			}
		}
		swap(ivec[i+1], ivec[r]);

		return i+1;
	}

	///@brief	快速排序
	///@param	ivec	待排序的数组
	///@param	p	数组的起始下标
	///@param	r	数组的末尾下标
	///@return	空
	///@author	zhaowei
	///@date	2015.06.04
	void QuickSort(vector<int>& ivec, const int p, const int r)
	{
		if (p < r)
		{
			int q = Partition(ivec, p, r);
			QuickSort(ivec, p, q-1);
			QuickSort(ivec, q+1, r);
		}
		return;
	}

	///@brief	在给定数组中二分查找指定元素
	///@param	ivec	待查找的数组
	///@param	p	数组的起始下标
	///@param	r	数组的末尾下标
	///@param	v	待查找的元素值
	///@return	如果数组中存在该元素，则返回该元素的下标；否则返回-1
	///@author	zhaowei
	///@date	2015.06.05
	int BinarySearch(vector<int>& ivec, const int p, const int r, const int v)
	{
		if (p > r)
		{
			return -1;
		}
		int q = (p+r)/2;
		if (v == ivec[q])
		{
			return q;
		}
		else if (v < ivec[q])
		{
			BinarySearch(ivec, p, q-1, v);
		}
		else 
		{
			BinarySearch(ivec, q+1, r, v);
		}
	}

}; */

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int closest = nums[0] + nums[1] + nums[2];
        int diff = abs(closest - target);
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 2; ++i) {
            int left = i + 1, right = nums.size() - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                int newDiff = abs(sum - target);
                if (diff > newDiff) {
                    diff = newDiff;
                    closest = sum;
                }
                if (sum < target) ++left;
                else --right;
            }
        }
        return closest;
    }
};

int main()
{
	vector<int> ivec;
	ivec.push_back(-1);
	ivec.push_back(2);
	ivec.push_back(1);
	ivec.push_back(-4);

	Solution slt;
	cout << slt.threeSumClosest(ivec, 5);
	cout << endl;

	return 0;
}